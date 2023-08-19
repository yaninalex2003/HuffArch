#pragma once
#include "node.h"
#include "letterstable.h"
#include <vector>
#include <map>

namespace huffman
{
    class Tree
    {
    public:
        explicit Tree(LettersTable const &frequencies);
        ~Tree();

        using Code = std::vector<bool>;
        using Codes = std::map<uint8_t, Code>;
        Codes getCodes();

        bool moveToChild(bool flag);
        void moveToRoot();
        uint8_t getChar() const;

    private:
        Node *root;
        Node *current;

        void init(LettersTable const &data);
        void dfs(Node const *root, Code &code, Codes &data);
    };

} // namespace huffman
