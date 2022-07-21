
#include <vector>
#include <Point.hpp>
#include <ScriptClass.hpp>

#ifndef __NODE__H
#define __NODE__H

class Node : public ScriptClass {
        private:
                void* data;
        public:
                Node();
                Node(Node* parentIn);

                static void exportToScript();

                void push(Node* data);
                Node* pop();

                Node*              parent;
                std::vector<Node*> children;


};

#endif
