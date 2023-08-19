#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "tree.h"
#include "writer.h"
#include "reader.h"
#include "archiver.h"
#include "letterstable.h"
#include "argparser.h"
#include "exceptions.h"

TEST_CASE("Huffman tree")
{
    huffman::LettersTable freqs;
    SUBCASE("Get code")
    {
        freqs['a'] = 1;
        freqs['b'] = 2;
        freqs['c'] = 3;
        freqs['d'] = 3;
        freqs['e'] = 4;
        freqs['f'] = 5;
        huffman::Tree tree(freqs);
        auto codes = tree.getCodes();

        CHECK_EQ(codes['a'].size(), 3);
        CHECK_EQ(codes['a'][0], 0);
        CHECK_EQ(codes['a'][1], 0);
        CHECK_EQ(codes['a'][2], 0);

        CHECK_EQ(codes['b'].size(), 3);
        CHECK_EQ(codes['b'][0], 0);
        CHECK_EQ(codes['b'][1], 0);
        CHECK_EQ(codes['b'][2], 1);

        CHECK_EQ(codes['c'].size(), 3);
        CHECK_EQ(codes['c'][0], 1);
        CHECK_EQ(codes['c'][1], 1);
        CHECK_EQ(codes['c'][2], 0);

        CHECK_EQ(codes['d'].size(), 3);
        CHECK_EQ(codes['d'][0], 1);
        CHECK_EQ(codes['d'][1], 1);
        CHECK_EQ(codes['d'][2], 1);

        CHECK_EQ(codes['e'].size(), 2);
        CHECK_EQ(codes['e'][0], 0);
        CHECK_EQ(codes['e'][1], 1);

        CHECK_EQ(codes['f'].size(), 2);
        CHECK_EQ(codes['f'][0], 1);
        CHECK_EQ(codes['f'][1], 0);
    }
    SUBCASE("Get char")
    {
        freqs['a'] = 1;
        freqs['b'] = 2;
        freqs['c'] = 3;
        freqs['d'] = 3;
        freqs['e'] = 4;
        freqs['f'] = 5;
        huffman::Tree tree(freqs);
        auto codes = tree.getCodes();

        tree.moveToRoot();
        tree.moveToChild(0);
        tree.moveToChild(0);
        tree.moveToChild(0);
        CHECK_EQ(tree.getChar(), 'a');

        tree.moveToRoot();
        tree.moveToChild(0);
        tree.moveToChild(0);
        tree.moveToChild(0);
        CHECK_EQ(tree.getChar(), 'a');

        tree.moveToRoot();
        tree.moveToChild(0);
        tree.moveToChild(0);
        tree.moveToChild(1);
        CHECK_EQ(tree.getChar(), 'b');

        tree.moveToRoot();
        tree.moveToChild(1);
        tree.moveToChild(1);
        tree.moveToChild(0);
        CHECK_EQ(tree.getChar(), 'c');

        tree.moveToRoot();
        tree.moveToChild(1);
        tree.moveToChild(1);
        tree.moveToChild(1);
        CHECK_EQ(tree.getChar(), 'd');

        tree.moveToRoot();
        tree.moveToChild(0);
        tree.moveToChild(1);
        CHECK_EQ(tree.getChar(), 'e');

        tree.moveToRoot();
        tree.moveToChild(1);
        tree.moveToChild(0);
        CHECK_EQ(tree.getChar(), 'f');
    }
    SUBCASE("One letter")
    {
        freqs['a'] = 10;
        huffman::Tree tree(freqs);
        auto codes = tree.getCodes();
        CHECK_EQ(codes.size(), 1);
        CHECK_EQ(codes['a'].size(), 0);
        CHECK_EQ(tree.getChar(), 'a');
    }
    SUBCASE("Empty text")
    {
        huffman::Tree tree(freqs);
        auto codes = tree.getCodes();
        CHECK_EQ(codes.size(), 0);
    }
}

TEST_CASE("Letters Table")
{
    SUBCASE("Complex")
    {
        huffman::LettersTable freqs;
        freqs['a'] = 1;
        freqs['b'] = 2;
        freqs['c'] = 3;
        freqs['d'] = 4;
        CHECK_EQ(freqs.getCharsCount(), 10);
        CHECK_EQ(freqs.getCompressSize(), 24);
    }
    SUBCASE("One letter")
    {
        huffman::LettersTable freqs;
        freqs['a'] = 15;
        CHECK_EQ(freqs.getCharsCount(), 15);
        CHECK_EQ(freqs.getCompressSize(), 9);
    }
}

TEST_CASE("IO")
{
    SUBCASE("Writer Read bool")
    {
        bool in1 = true, in2 = false;
        bool out1, out2;

        std::stringstream s;

        io::Writer writer(s);
        writer << in1;
        writer << in2;
        writer.flush();
        CHECK_EQ(writer.getBytesCount(), 1);

        io::Reader reader(s);
        reader >> out1 >> out2;
        CHECK_EQ(reader.getBytesCount(), 1);

        CHECK_EQ(out1, in1);
        CHECK_EQ(out2, in2);
    }
    SUBCASE("Writer Read uin8_t")
    {
        uint8_t in1 = 1, in2 = 2;
        uint8_t out1, out2;

        std::stringstream s;

        io::Writer writer(s);
        writer << in1;
        writer << in2;
        writer.flush();
        CHECK_EQ(writer.getBytesCount(), 2);

        io::Reader reader(s);
        reader >> out1 >> out2;
        CHECK_EQ(reader.getBytesCount(), 2);

        CHECK_EQ(out1, in1);
        CHECK_EQ(out2, in2);
    }
    SUBCASE("Writer Read uin32_t")
    {
        uint32_t in1 = 1234, in2 = 2345;
        uint32_t out1, out2;

        std::stringstream s;

        io::Writer writer(s);
        writer << in1;
        writer << in2;
        writer.flush();
        CHECK_EQ(writer.getBytesCount(), 8);

        io::Reader reader(s);
        reader >> out1 >> out2;
        CHECK_EQ(reader.getBytesCount(), 8);

        CHECK_EQ(out1, in1);
        CHECK_EQ(out2, in2);
    }
    SUBCASE("Complex")
    {
        bool in_bool = true;
        uint8_t in_8 = 121;
        uint32_t in_32 = 123321;
        bool out_bool = 0;
        uint8_t out_8 = 0;
        uint32_t out_32 = 0;

        std::stringstream s;

        io::Writer writer(s);
        writer << in_bool;
        writer << in_8;
        writer << in_32;
        writer.flush();
        CHECK_EQ(writer.getBytesCount(), 6);

        io::Reader reader(s);
        reader >> out_bool;
        reader >> out_8;
        reader >> out_32;
        CHECK_EQ(reader.getBytesCount(), 6);

        CHECK_EQ(in_bool, out_bool);
        CHECK_EQ(in_8, out_8);
        CHECK_EQ(in_32, in_32);
    }
}

TEST_CASE("Argparser")
{
    SUBCASE("Correct arguments")
    {
        int argc = 6;
        const char *argv[6];
        argv[0] = "./hw-02_huffman";
        argv[1] = "-c";
        argv[2] = "-f";
        argv[3] = "in";
        argv[4] = "-o";
        argv[5] = "out";
        huffman::ArgParser AP(argc, const_cast<char **>(argv));
        CHECK_EQ(AP.getInputName(), argv[3]);
        CHECK_EQ(AP.getOutputName(), argv[5]);
        CHECK_EQ(AP.getOpKind(), huffman::OpKind::archive);
    }
    SUBCASE("Incorrect argc")
    {
        int argc = 5;
        const char *argv[5];
        argv[0] = "./hw-02_huffman";
        argv[1] = "-q";
        argv[2] = "-f";
        argv[3] = "in";
        argv[4] = "-o";
        CHECK_THROWS_WITH(huffman::ArgParser(argc, const_cast<char **>(argv)), "incorrect number of arguments");
    }
    SUBCASE("Incorrect operation")
    {
        int argc = 6;
        const char *argv[6];
        argv[0] = "./hw-02_huffman";
        argv[1] = "-q";
        argv[2] = "-f";
        argv[3] = "in";
        argv[4] = "-o";
        argv[5] = "out";
        huffman::ArgParser AP(argc, const_cast<char **>(argv));
        CHECK_THROWS_WITH(AP.getOpKind(), "unknown operation");
    }
    SUBCASE("Incorrect input")
    {
        int argc = 6;
        const char *argv[6];
        argv[0] = "./hw-02_huffman";
        argv[1] = "-c";
        argv[2] = "in";
        argv[3] = "in";
        argv[4] = "-o";
        argv[5] = "out";
        huffman::ArgParser AP(argc, const_cast<char **>(argv));
        CHECK_THROWS_WITH(AP.getInputName(), "input file undefined");
    }
    SUBCASE("Incorrect output")
    {
        int argc = 6;
        const char *argv[6];
        argv[0] = "./hw-02_huffman";
        argv[1] = "-c";
        argv[2] = "-f";
        argv[3] = "in";
        argv[4] = "out";
        argv[5] = "out";
        huffman::ArgParser AP(argc, const_cast<char **>(argv));
        CHECK_THROWS_WITH(AP.getOutputName(), "output file undefined");
    }
}