#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdexcept>

std::string load_file(const std::string& file_path) {
    std::stringstream buffer_stream;
    std::ifstream input_stream(file_path, std::ios_base::in | std::ios_base::binary);
    if (!input_stream) throw std::runtime_error("can't open file " + file_path);

    std::copy(std::istreambuf_iterator<char>(input_stream), 
            std::istreambuf_iterator<char>(),
            std::ostreambuf_iterator<char>(buffer_stream));

    return buffer_stream.str();
}

int main(int argc, char *argv[]) {
    std::cout << load_file("smakefile") << std::endl;
    std::cout << "ending" << std::endl;
    return 0;
}
