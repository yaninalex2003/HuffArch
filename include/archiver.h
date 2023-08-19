#pragma once

#include <fstream>

namespace huffman
{

    class HuffmanArchiver
    {
    public:
        HuffmanArchiver(const std::string &input_name, const std::string &output_name);

        void archive();
        void unarchive();

    private:
        std::ifstream _input;
        std::ofstream _output;
    };

} // namespace huffman
