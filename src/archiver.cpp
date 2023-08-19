#include "archiver.h"
#include "reader.h"
#include "tree.h"
#include "writer.h"
#include "letterstable.h"
#include <iostream>
#include <sstream>
#include <numeric>

using io::Reader;
using io::Writer;

namespace huffman
{
    HuffmanArchiver::HuffmanArchiver(const std::string &input_name, const std::string &output_name)
    {
        _input = std::ifstream(input_name, std::ifstream::in);
        _input.exceptions(std::ofstream::failbit | std::ofstream::badbit);

        _output = std::ofstream(output_name, std::ofstream::out);
        _output.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    }

    void HuffmanArchiver::archive()
    {
        std::stringstream buffer;
        buffer << _input.rdbuf();
        std::string text = buffer.str();
        std::stringstream().swap(buffer);
        LettersTable freqs;
        for (auto i : text)
            ++freqs[i];
        Tree tree(freqs);
        auto codes = tree.getCodes();
        Writer writer(_output);
        writer << static_cast<uint32_t>(freqs.size());
        if (freqs.empty())
        {
            std::cout << 0 << std::endl
                      << 0 << std::endl
                      << sizeof(uint32_t) << std::endl;
            return;
        }

        for (auto [ch, number] : freqs)
            writer << ch << number;

        for (auto ch : text)
            for (const auto &bit : codes[ch])
                writer << bit;
        writer.flush();

        std::size_t added_size = freqs.getCompressSize();
        std::cout << text.size() << std::endl
                  << writer.getBytesCount() - added_size << std::endl
                  << added_size << std::endl;
    }

    void HuffmanArchiver::unarchive()
    {
        Reader reader(_input);
        LettersTable freqs;
        std::uint32_t size;
        reader >> size;
        if (size == 0)
        {
            std::cout << 0 << std::endl
                      << 0 << std::endl
                      << reader.getBytesCount() << std::endl;
            return;
        }
        for (uint32_t i = 0; i < size; ++i)
        {
            uint8_t ch;
            uint32_t number;
            reader >> ch >> number;
            freqs[ch] = number;
        }
        uint32_t chars_count = freqs.getCharsCount();
        if (size == 1)
        {
            for (std::uint32_t i = 0; i < chars_count; i++)
                _output << static_cast<char>(freqs.begin()->first);
            std::cout << 0 << std::endl
                      << chars_count << std::endl
                      << reader.getBytesCount() << std::endl;
            return;
        }
        Tree tree(freqs);
        for (uint32_t i = 0; i < chars_count; ++i)
        {
            bool bit;
            do
            {
                reader >> bit;
            } while (tree.moveToChild(bit));
            _output << tree.getChar();
            tree.moveToRoot();
        }

        std::size_t added_size = freqs.getCompressSize();
        std::cout << reader.getBytesCount() - added_size << std::endl
                  << chars_count << std::endl
                  << added_size << std::endl;
    }

} // namespace huffman
