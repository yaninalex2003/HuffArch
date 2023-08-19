#pragma once

#include <iosfwd>
#include <vector>
#include <cstdint>

namespace io
{
    class Writer
    {
    public:
        explicit Writer(std::ostream &os);
        ~Writer();

        uint32_t getBytesCount() const;
        void flush();

        friend Writer &operator<<(Writer &writer, uint32_t bit);
        friend Writer &operator<<(Writer &writer, uint8_t bit);
        friend Writer &operator<<(Writer &writer, bool bit);

    private:
        std::ostream &os;

        uint32_t bytes_count = 0;
        uint8_t buffer = 0;
        uint8_t bits_in_buf = 0;
    };

} // namespace io
