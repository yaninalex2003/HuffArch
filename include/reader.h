#pragma once

#include <fstream>
#include <type_traits>
#include <climits>

namespace io
{
    class Reader
    {
    public:
        explicit Reader(std::istream &is);
        ~Reader() = default;

        uint32_t getBytesCount() const;

        friend Reader &operator>>(Reader &reader, bool &bit);
        friend Reader &operator>>(Reader &reader, uint8_t &byte);
        friend Reader &operator>>(Reader &reader, uint32_t &number);

    private:
        std::istream &is;

        uint32_t bytes_count = 0;
        uint8_t buffer = 0;
        uint8_t bits_in_buf = 0;
    };

} // namespace io
