#include "exceptions.h"

namespace exceptions
{
    ArchiverException::ArchiverException(std::string reason) noexcept : exception(), reason_(reason) {}

    const char *ArchiverException::what() const noexcept
    {
        return reason_.c_str();
    }

} // namespace exceptions
