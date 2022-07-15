#include <Common.hpp>

#include <Point.hpp>

#ifndef __NODE__H
#define __NODE__H

using namespace std;

class Node{
        private:
                void* data;
        public:
                Node();
                Node(Node* parentIn);
                void push(Node* data);
                Node* pop();

                Node*         parent;
                vector<Node*> children;


};

#endif
