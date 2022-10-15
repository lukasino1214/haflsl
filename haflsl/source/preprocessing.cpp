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

        for(auto& define : defines) {
            INFO("found define name: {:s}", define.first);
            INFO("found define expr: {:s}", define.second);
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

        std::string code_after_defines = "";
        for(u32 i = 0; i < removed_defines_lines.size(); i++) {
           if(i != removed_defines_lines.size() - 1) {
                code_after_defines += removed_defines_lines[i] + "\n";
            } else {
                code_after_defines += removed_defines_lines[i];
            }
        }

        return code_after_defines;
    }
}