#include <haflsl/types.hpp>
#include <haflsl/utils.hpp>

#include <fstream>

namespace HAFLSL {
    std::string read_file_to_string(const std::string &filepath) {
        std::string content;
        std::ifstream in(filepath, std::ios::in | std::ios::binary);
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

    std::vector<std::string> string_to_words(const std::string &content) {
        std::vector<std::string> words{};
        std::string_view view = content;
        u32 counter = 0;
        u32 len = 0;

        for(u32 i = 0; i < content.size(); i++) {
            if(view[i] != ' ' && view[i] != '\n') {
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
        return std::move(words);
    }
}