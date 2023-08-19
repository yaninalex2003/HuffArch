#include "tree.h"
#include "exceptions.h"

#include <queue>

namespace huffman
{
    Tree::Tree(LettersTable const &data) : root(nullptr), current(nullptr)
    {
        init(data);
    }

    void Tree::init(const LettersTable &data)
    {
        if (data.empty())
            return;
        std::priority_queue<Node *, std::vector<Node *>, NodeCmp> buffer;
        for (const auto &[ch, weight] : data)
            buffer.push(new Node(ch, weight));
        while (buffer.size() > 1)
        {
            Node *left = buffer.top();
            buffer.pop();
            Node *right = buffer.top();
            buffer.pop();
            buffer.push(new Node(0, left->weight + right->weight, left, right));
        }
        root = buffer.top();
        current = root;
    }

    Tree::~Tree()
    {
        delete root;
    }

    Tree::Codes Tree::getCodes()
    {
        std::map<uint8_t, Code> data;
        Code code = {};
        dfs(root, code, data);
        return data;
    }

    bool Tree::moveToChild(bool flag)
    {
        if (!current)
            return false;
        if (flag)
            current = current->right;
        else
            current = current->left;
        return current->left || current->right;
    }

    void Tree::moveToRoot()
    {
        current = root;
    }

    uint8_t Tree::getChar() const
    {
        if (!current)
            throw exceptions::ArchiverException("getChar error");
        return current->ch;
    }

    void Tree::dfs(const Node *start, Code &code, Codes &data)
    {
        if (!start)
            return;
        if (!start->left && !start->right)
            data[start->ch] = code;
        code.push_back(false);
        dfs(start->left, code, data);
        code.pop_back();
        code.push_back(true);
        dfs(start->right, code, data);
        code.pop_back();
    }

} // namespace huffman
