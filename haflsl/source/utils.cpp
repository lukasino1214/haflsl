#include <haflsl/types.hpp>
#include <haflsl/utils.hpp>

#include <fstream>
#include <sstream>
#include <algorithm>

namespace HAFLSL {
    auto read_file_to_string(const std::string &file_path) -> std::string {
        std::string content;
        std::ifstream in(file_path, std::ios::in | std::ios::binary);
        if (in) {
            in.seekg(0, std::ios::end);
            u32 size = static_cast<u32>(in.tellg());
            if (size != 0) {
                content.resize(size);
                in.seekg(0, std::ios::beg);
                in.read(&content[0], size);
            } else {
                throw std::runtime_error("file is empty");
            }
        } else {
            throw std::runtime_error("couldnt read a file");
        }
        return content;
    }

    auto string_to_words(const std::string &content) -> std::vector<std::string> {
        std::vector<std::string> words{};
        std::string_view view = content;
        u32 counter = 0;
        u32 len = 0;

        for(u32 i = 0; i < content.size(); i++) {
            if(view[i] != ' ' && view[i] != '\n'&& view[i] != '\t' && view[i] != '\v' && view[i] != '\r' && view[i] != '\f') {
                len += 1;
            } else {
                if(len != 0) {
                    words.push_back(content.substr(counter, len));
                }

                counter = i+1;
                len = 0;
            }
        }
        words.push_back(content.substr(counter, len));
        return words;
    }

    auto string_to_lines(const std::string &content) -> std::vector<std::string> {
        std::vector<std::string> lines{};
        std::stringstream ss{content};

        for (std::string line; std::getline(ss, line, '\n');) {
            //line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            lines.push_back(line);
        }

        return lines;
    }

    auto lines_to_string(const std::vector<std::string> &lines) -> std::string {
        std::string content = "";
        for(u32 i = 0; i < lines.size(); i++) {
           if(i != lines.size() - 1) {
                content += lines[i] + "\n";
            } else {
                content += lines[i];
            }
        }

        return content;
    }
}