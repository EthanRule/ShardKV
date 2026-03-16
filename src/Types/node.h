#ifndef NODE_H_
#define NODE_H_

#include <string>

struct Node {
    std::string value;
    Node* next;

    Node() : value(""), next(nullptr) {}
    Node(std::string val) : value(val), next(nullptr) {}
    Node(std::string val, Node* nextNode) : value(val), next(nextNode) {}
};

#endif // NODE_H_
