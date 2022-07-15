#include <Node.hpp>

#ifndef __SCRIPT__H
#define __SCRIPT__H

enum SymbolType {
                Function = 0,
                Variable
};

struct Symbol {
        SymbolType type;
        string     value;
};

class ASTNode : public Node {
        Symbol symbol;
};

class Script {
        ASTNode* root;
        public:
                bool      loadFromFile(std::string fileName);
                void      step();

};

#endif
