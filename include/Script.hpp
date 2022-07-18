#include <Node.hpp>

#ifndef __SCRIPT__H
#define __SCRIPT__H

class Module {
  public:
    string name;
    Module();
    Module(std::string nameIn);
};

class Script {
        vector<Module> modules;
        public:
                static Script* loadFromFile(std::string fileName);
                void      step();

};

#endif
