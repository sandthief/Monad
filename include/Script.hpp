#include <Node.hpp>

#ifndef __SCRIPT__H
#define __SCRIPT__H

enum SymbolType {
                Function = 0,
                Number,
                Atom,
                List
};

struct Symbol {
        SymbolType type;
        string     value;
};

class ASTNode : public Node {
        Symbol symbol;
};

class Statement {
public:
        std::vector<std::string> tokens;
        std::string print();
};

class Script {
        ASTNode* root;
        public:
                static Script* loadFromFile(std::string fileName);
                void      step();

};

#endif
