#include "writer.h"

#include <fstream>
#include <climits>

namespace io
{
    Writer::Writer(std::ostream &os) : os(os)
    {
        os.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    }

    uint32_t Writer::getBytesCount() const
    {
        return bytes_count;
    }

    Writer::~Writer()
    {
        flush();
    }

    void Writer::flush()
    {
        if (bits_in_buf == 0)
            return;
        os << buffer;
        bits_in_buf = 0;
        buffer = 0;
        ++bytes_count;
    }

    Writer &operator<<(Writer &writer, uint32_t number)
    {
        uint8_t bits = 4 * CHAR_BIT;
        for (uint8_t i = 0; i < bits; ++i)
            writer << static_cast<bool>((number >> (bits - i - 1)) & static_cast<uint32_t>(1));
        return writer;
    }

    Writer &operator<<(Writer &writer, uint8_t number)
    {
        uint8_t bits = CHAR_BIT;
        for (uint8_t i = 0; i < bits; ++i)
            writer << static_cast<bool>((number >> (bits - i - 1)) & static_cast<uint8_t>(1));
        return writer;
    }

    Writer &operator<<(Writer &writer, bool bit)
    {
        if (writer.bits_in_buf == CHAR_BIT)
            writer.flush();
        if (bit)
            writer.buffer |= (1 << writer.bits_in_buf);
        ++writer.bits_in_buf;
        return writer;
    }

} // namespace io
