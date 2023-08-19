#include "reader.h"

namespace io
{
    Reader::Reader(std::istream &is) : is(is)
    {
        is.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    }

    uint32_t Reader::getBytesCount() const
    {
        return bytes_count;
    }

    Reader &operator>>(Reader &reader, uint32_t &number)
    {
        uint32_t result = 0;
        uint8_t bits = 4 * CHAR_BIT;
        for (uint8_t i = 0; i < bits; ++i)
        {
            bool bit;
            reader >> bit;
            if (bit)
                result |= (static_cast<uint32_t>(1) << (bits - i - 1));
        }
        number = result;
        return reader;
    }

    Reader &operator>>(Reader &reader, uint8_t &byte)
    {
        uint8_t result = 0;
        uint8_t bits = CHAR_BIT;
        for (uint8_t i = 0; i < bits; ++i)
        {
            bool bit;
            reader >> bit;
            if (bit)
                result |= (static_cast<uint8_t>(1) << (bits - i - 1));
        }
        byte = result;
        return reader;
    }

    Reader &operator>>(Reader &reader, bool &bit)
    {
        if (reader.bits_in_buf == 0)
        {
            reader.buffer = reader.is.get();
            reader.bits_in_buf = CHAR_BIT;
            ++reader.bytes_count;
        }
        bit = reader.buffer & static_cast<uint8_t>(1);
        --reader.bits_in_buf;
        reader.buffer >>= 1;
        return reader;
    }

} // namespace io
