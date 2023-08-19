#pragma once
#include <exception>
#include <string>

namespace exceptions
{
    class ArchiverException : public std::exception
    {
    public:
        explicit ArchiverException(std::string reason) noexcept;
        ~ArchiverException() noexcept override = default;

        const char *what() const noexcept override;

    private:
        const std::string reason_;
    };

} // namespace exceptions
