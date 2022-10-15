#include <haflsl/types.hpp>
#include <haflsl/preprocessing.hpp>
#include <haflsl/utils.hpp>
#include <haflsl/logger.hpp>

#include <unordered_map>

namespace HAFLSL {
    struct Macro {
        std::vector<std::string> parameters;
        std::vector<std::string> text;
    };

    auto preprocessing(const std::string& file_path) -> std::string {
        std::function<std::string(std::string, std::string)> includer;
        includer = [&includer](const std::string& header_name, const std::string& includer_name) -> std::string {
            std::string src = read_file_to_string(header_name);


            std::vector<std::string> include_paths = {};
            std::vector<std::string> lines = string_to_lines(src);
            for(auto& line : lines) {
                usize index = line.find("#include");
                if(index != std::string::npos) {
                    bool b_found = false;
                    u32 found = 0;
                    for(u32 i = index + 7 + 1; i < line.size(); i++) {
                        if(b_found) {
                            if(line[i] == '"') {
                                include_paths.push_back(std::move(line.substr(found, i - found)));
                            }
                        }

                        if(line[i] == '"') {
                            b_found = true;
                            found = i + 1;
                        }
                    }
                }
            }

            std::string included_code = {};
            for(auto& path : include_paths) {
                if(path == includer_name) { throw std::runtime_error("Recursive including"); }
                included_code += includer(path, header_name) + "\n";
            }

            std::string removed_includes = {};
            for(u32 i = 0; i < lines.size(); i++) {
                usize len = lines[i].find("#include");
                if(len == std::string::npos) {
                    if(i != lines.size() - 1) {
                        removed_includes += lines[i] + "\n";
                    } else {
                        removed_includes += lines[i];
                    }
                }
            }

            std::string code = included_code + removed_includes;

            return code;
        };

        std::string src = includer(file_path, "");
        std::vector<std::string> src_lines = string_to_lines(src);

        std::unordered_map<std::string, std::string> defines;
        std::unordered_map<std::string, Macro> macros;
        for(auto& line : src_lines) {
            bool found_macro = false;
            usize index = line.find("#define");
            if(index != std::string::npos) {                
                u32 begin_name = 0;
                u32 end_name = 0;
                u32 begin_expr = 0;
                u32 end_expr = 0;
                for(u32 i = index + 6 + 1; i < line.size(); i++) {
                    if(begin_name == 0 && line[i] != ' ') {
                        begin_name = i;
                        bool test = false;
                        for(u32 j = i + 1; j < line.size(); j++) {
                            if(line[j] == '(') { test = true; }
                            if(line[j] == ' ' && !test) {
                                end_name = j;
                                break;
                            }

                            if(line[j] == ')' && test) {
                                end_name = j + 1;
                                found_macro = true;
                                break;
                            }
                        }
                    }
                }

                for(u32 i = end_name; i < line.size(); i++) {
                    if(line[i] != ' ') {
                        begin_expr = i;
                        break;
                    }
                }

                for(u32 i = line.size(); i >= begin_expr; i--) {
                    if(line[i] != ' ') {
                        end_expr = i;
                        break;
                    }
                }

                if(!found_macro) {
                    std::string name = line.substr(begin_name, end_name - begin_name);
                    std::string expr = line.substr(begin_expr, end_expr - begin_expr);

                    if(defines.find(name) == defines.end()) {
                        defines.insert({name, expr});
                    } else {
                        throw std::runtime_error("define named: " + name + " was already defined");
                    }
                } else {
                    std::string name = line.substr(begin_name, end_name - begin_name);
                    std::string expr = line.substr(begin_expr, end_expr - begin_expr);

                    std::vector<std::string> parameters;

                    bool found_bracket = false;
                    bool has_parameter = false;
                    u32 found_start_parameter = 0;
                    for(u32 i = 0; i < name.size(); i++) {
                        if(found_bracket && name[i] != ' ' && name[i] != ',' && !has_parameter) {
                            has_parameter = true;
                            found_start_parameter = i;
                        }

                        if(found_bracket && has_parameter && (name[i] == ',' || name[i] == ')')) {
                            parameters.push_back(name.substr(found_start_parameter, i - found_start_parameter));
                            has_parameter = false;
                        }

                        if(name[i] == '(' && !found_bracket) {
                            found_bracket = true;
                        }
                    }

                    std::vector<std::string> splitted_expr;

                    u32 offset = 0;
                    for(u32 i = 0; i < parameters.size(); i++) {
                        usize index = expr.find(parameters[i]);
                        if(index != std::string::npos) {
                            for(u32 j = index; j < expr.size(); j++) {
                                if(i == 0 && j == index) {
                                    splitted_expr.push_back(expr.substr(0, index));
                                }

                                if(expr[j] == ',' || expr[j] == ')') {
                                    splitted_expr.push_back(expr.substr(index + parameters[i].size(), j - index + parameters[i].size()));
                                    break;
                                }
                            }
                        }
                    }

                    Macro macro {
                        .parameters = std::move(parameters),
                        .text = std::move(splitted_expr)
                    };

                    std::string macro_name = "";
                    for(u32 i = 0; i < name.size(); i++) {
                        if(name[i] == '(') {
                            macro_name = name.substr(0, i);
                            //INFO("bruh {}", name.substr(0, i));
                        }
                    }

                    if(macros.find(macro_name) == macros.end()) {
                        macros.insert({macro_name, macro});
                    } else {
                        throw std::runtime_error("macro named: " + macro_name + " was already defined");
                    }
                }
            }
        }

        std::string removed_defines = {};
        for(u32 i = 0; i < src_lines.size(); i++) {
            usize len = src_lines[i].find("#define");
            if(len == std::string::npos) {
                if(i != src_lines.size() - 1) {
                    removed_defines += src_lines[i] + "\n";
                } else {
                    removed_defines += src_lines[i];
                }
            }
        }

        INFO("Found defines:");
        for(auto& d : defines) {
            INFO("name: {}", d.first);
            INFO("expr: {}", d.second);
        }

        INFO("Found macros:");
        for(auto& m : macros) {
            INFO("name: {}", m.first);
            std::string expr;

            expr += m.second.text[0];
            for(u32 i = 1; i < m.second.text.size(); i++) {
                expr += m.second.parameters[i - 1];
                expr += m.second.text[i];
            }
            INFO("expr: {}", expr);
        }

        std::vector<std::string> removed_defines_lines = string_to_lines(removed_defines);
        for(u32 i = 0; i < removed_defines_lines.size(); i++) {
            for(auto& define : defines) {
                usize len = removed_defines_lines[i].find(define.first);
                if(len != std::string::npos) {
                    std::string str = removed_defines_lines[i].substr(0, len);
                    std::string end = removed_defines_lines[i].substr(len + define.first.size(), removed_defines_lines[i].size() - len - define.first.size());
                    removed_defines_lines[i] = str + define.second + end;
                }
            }
            for(auto& macro : macros) {
                usize len = removed_defines_lines[i].find(macro.first);
                if(len != std::string::npos) {
                    std::string str = removed_defines_lines[i].substr(0, len);
                    std::string code = macro.second.text[0];

                    std::string end = "";
                    bool bracket = false;
                    u32 start_n = 0;
                    u32 end_n = 0;
                    u32 parameter_count = 0;
                    for(u32 j = len + macro.first.size(); j < removed_defines_lines[i].size(); j++) {
                        INFO("char: {}", removed_defines_lines[i][j]);
                        if(removed_defines_lines[i][j] == '(') {
                            bracket = true;
                            start_n = j + 1;
                        }
                        if(bracket && removed_defines_lines[i][j] == ',') {
                            parameter_count += 1;
                            end_n = j - 1;
                            code += removed_defines_lines[i].substr(start_n + (parameter_count == 1 ? 0 : 1), end_n - start_n + (parameter_count == 1 ? 1 : 0));
                            code += macro.second.text[parameter_count];
                            //INFO("paramter {}", removed_defines_lines[i].substr(start_n, end_n - start_n + 1));
                            start_n = j + 1;
                        }

                        if(macro.second.parameters.size() - 1 == parameter_count && removed_defines_lines[i][j] == ')') {
                            parameter_count += 1;
                            end_n = j - 1;
                            code += removed_defines_lines[i].substr(start_n + 1, end_n - start_n);
                            code += macro.second.text[parameter_count];
                        }

                        if(macro.second.parameters.size() == parameter_count) {
                            end = removed_defines_lines[i].substr(j + 1, removed_defines_lines[i].size() - j);
                            break;
                        }
                    }

                    removed_defines_lines[i] = str + code + end;
                }
            }
        }

        std::string code_after_defines = lines_to_string(removed_defines_lines);

        std::vector<std::string> lines_a = string_to_lines(code_after_defines);
        std::vector<std::string> lines_b;
        bool found_multi_line_comment = false;
        u32 found_multi_line_comment_line = 0;
        u32 found_multi_line_comment_pos = 0;
        for(u32 i = 0; i < lines_a.size(); i++) {
            if(found_multi_line_comment) {
                usize index = lines_a[i].find("*/");
                if(index != std::string::npos) {
                    lines_b.push_back(lines_a[found_multi_line_comment_line].substr(0, found_multi_line_comment_pos));
                    lines_b.push_back(lines_a[i].substr(index + 2, lines_a[i].size() - index));
                    found_multi_line_comment_line = 0;
                    found_multi_line_comment_pos = 0;
                    found_multi_line_comment = false;
                }
            } else {
                usize index_1 = lines_a[i].find("//");
                usize index_2 = lines_a[i].find("/*");
                if(index_1 != std::string::npos) {
                    lines_b.push_back(lines_a[i].substr(0, index_1));
                } else if(index_2 != std::string::npos) {
                    usize index = lines_a[i].find("*/");
                    if(index != std::string::npos) {                                               // if the mutli line comment is found one same line with end
                        std::string start = lines_a[i].substr(0, index_2);                         // |- start  -|             |-  end  -|
                        std::string end = lines_a[i].substr(index + 2, lines_a[i].size() - index); // vec3 bruh = /* comment */ vec3(2.0);

                        lines_b.push_back(start + end);
                    } else {
                        found_multi_line_comment = true;
                        found_multi_line_comment_line = i;
                        found_multi_line_comment_pos = index_2;
                    }
                } else {
                    lines_b.push_back(lines_a[i]);
                }
            }
        }

        std::string code_after_removing_comments = lines_to_string(lines_b);
        return code_after_removing_comments;
    }
}