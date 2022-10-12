#include <iostream>
#include <haflsl/types.hpp>
#include <haflsl/utils.hpp>
#include <vector>

int main() {
    std::string file_name = "test.txt";

    std::cout << "reading this file: " << file_name << std::endl;
    std::string content = HAFLSL::read_file_to_string(file_name);

    std::cout << "content of the file" << std::endl;
    std::cout << content << std::endl;

    std::cout << "separating into words" << std::endl;
    std::vector<std::string> words = HAFLSL::string_to_words(content);

    for(auto& word : words) {
        std::cout << word << std::endl;
    }

    std::cout << "done!" << std::endl;
    return 0;
}