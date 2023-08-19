#include "argparser.h"
#include "exceptions.h"

#include <cstring>

namespace huffman
{
    ArgParser::ArgParser(int argc, char **argv)
    {
        if (argc != 6)
            throw exceptions::ArchiverException("incorrect number of arguments");
        _argv = argv;
    }

    OpKind ArgParser::getOpKind() const
    {
        for (int i = 1; i < _argc; ++i)
        {
            if (strcmp(_argv[i], "-u") == 0)
                return OpKind::unarchive;
            if (strcmp(_argv[i], "-c") == 0)
                return OpKind::archive;
        }
        throw exceptions::ArchiverException("unknown operation");
    }

    std::string ArgParser::getInputName() const
    {
        for (int i = 1; i < _argc - 1; ++i)
            if (strcmp(_argv[i], "-f") == 0 || strcmp(_argv[i], "--file") == 0)
                return _argv[i + 1];
        throw exceptions::ArchiverException("input file undefined");
    }

    std::string ArgParser::getOutputName() const
    {
        for (int i = 1; i < _argc - 1; ++i)
            if (strcmp(_argv[i], "-o") == 0 || strcmp(_argv[i], "--output") == 0)
                return _argv[i + 1];
        throw exceptions::ArchiverException("output file undefined");
    }

} // namespace huffman