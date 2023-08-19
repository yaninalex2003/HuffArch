#pragma once

#include <string>

namespace huffman
{
    enum class OpKind
    {
        archive,
        unarchive
    };

    class ArgParser
    {
    public:
        ArgParser(int argc, char **argv);
        OpKind getOpKind() const;
        std::string getInputName() const;
        std::string getOutputName() const;

    private:
        int _argc = 6;
        char **_argv;
    };

}