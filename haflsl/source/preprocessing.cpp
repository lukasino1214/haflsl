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
                    if(i != lines[i].size() - 1) {
                        removed_includes += lines[i] + "\n";
                    } else {
                        removed_includes += lines[i];
                    }
                }
            }

            std::string code = included_code + "\n" + removed_includes;

            return code;
        };

        std::string str = includer(file_path, "");

        std::unordered_map<std::string, std::string> defines;

        return str;
    }
}