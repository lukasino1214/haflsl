#include <haflsl/types.hpp>
#include <haflsl/preprocessing.hpp>
#include <haflsl/utils.hpp>
#include <haflsl/logger.hpp>

#include <unordered_map>

namespace HAFLSL {
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
        for(auto& line : src_lines) {
            usize index = line.find("#define");
            if(index != std::string::npos) {                
                u32 begin_name = 0;
                u32 end_name = 0;
                u32 begin_expr = 0;
                u32 end_expr = 0;
                for(u32 i = index + 6 + 1; i < line.size(); i++) {
                    if(begin_name == 0 && line[i] != ' ') {
                        begin_name = i;
                    }

                    if(begin_name != 0 && line[i] == ' ') {
                        end_name = i;
                    }

                    if(end_name != 0 && begin_expr == 0 && line[i] != ' ') {
                        begin_expr = i;
                    }
                }

                for(u32 i = line.size(); i >= begin_expr; i--) {
                    if(begin_expr != 0 && line[i] != ' ') {
                        end_expr = i;
                        break;
                    }
                }

                std::string name = line.substr(begin_name, end_name - begin_name);
                std::string expr = line.substr(begin_expr, end_expr - begin_expr);

                if(defines.find(name) == defines.end()) {
                    defines.insert({name, expr});
                } else {
                    throw std::runtime_error("define named: " + name + " was already defined");
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

        //std::vector<std::string> lines_a = string_to_lines(code_after_defines);

        return code_after_removing_comments;
    }
}