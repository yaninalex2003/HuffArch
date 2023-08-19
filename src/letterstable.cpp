#include <letterstable.h>

namespace huffman
{
    uint32_t LettersTable::getCharsCount()
    {
        uint32_t res = 0;
        for (auto item : *this)
            res += item.second;
        return res;
    }

    uint32_t LettersTable::getCompressSize()
    {
        return this->size() * (sizeof(uint32_t) + sizeof(uint8_t)) + sizeof(uint32_t);
    }

} // namespace huffman
