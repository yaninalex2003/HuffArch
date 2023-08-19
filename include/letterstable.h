#pragma once

#include <cinttypes>
#include <map>

namespace huffman
{
    class LettersTable : public std::map<uint8_t, uint32_t>
    {
    public:
        uint32_t getCharsCount();
        uint32_t getCompressSize();
    };

} // namespace huffman
