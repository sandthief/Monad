#include <Node.hpp>

Node::Node() {

}


Node::Node(Node* parentIn) {
        parent = parentIn;
}
void Node::push(Node* child) {
        children.push_back(child);
}
Node* Node::pop() {
        return parent;
}


Node*         parent;
vector<Node*> children;
