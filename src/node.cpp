#include "node.h"
#include "exceptions.h"

namespace huffman
{
    Node::Node(uint8_t ch, uint32_t weight, Node *left, Node *right) : ch(ch), weight(weight), left(left), right(right) {}

    Node::~Node()
    {
        delete left;
        delete right;
    }

    bool NodeCmp::operator()(const Node *first, const Node *second)
    {
        if (!first || !second)
            throw exceptions::ArchiverException("NodeCmp error");
        return first->weight > second->weight;
    }

} // namespace huffman
