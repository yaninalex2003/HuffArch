#include "argparser.h"
#include "archiver.h"
#include "exceptions.h"

#include <iostream>

using namespace huffman;

int main(int argc, char **argv)
{
    try
    {
        ArgParser AP(argc, argv);
        HuffmanArchiver archiver(AP.getInputName(), AP.getOutputName());
        if (AP.getOpKind() == OpKind::archive)
            archiver.archive();
        else
            archiver.unarchive();
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }
    return 0;
}
