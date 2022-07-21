#include <Common.hpp>

using namespace std;
using namespace chaiscript;

Node::Node() {

}


Node::Node(Node* parentIn) {
        parent = parentIn;
}

void Node::exportToScript() {
        script.add(user_type<Node>(),              "Node");
        script.add(constructor<Node(Node*)>(),     "Node");
        script.add(constructor<Node()>(),          "Point2D");

        script.add(fun(&Node::push),               "push");
        script.add(fun(&Node::pop),                "pop");

        script.add(fun(&Node::parent),             "parent");
        script.add(fun(&Node::children),           "children");
}

void Node::push(Node* child) {
        children.push_back(child);
}
Node* Node::pop() {
        return parent;
}
