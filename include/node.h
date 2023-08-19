#pragma once
#include <cinttypes>

namespace huffman
{
    struct Node
    {
        explicit Node(uint8_t ch = 0, uint32_t weight = 0, Node *left = nullptr, Node *right = nullptr);
        ~Node();

        uint8_t const ch;
        uint32_t const weight;
        Node *const left;
        Node *const right;
    };

    struct NodeCmp
    {
        bool operator()(Node const *first, Node const *second);
    };

} // namespace huffman
