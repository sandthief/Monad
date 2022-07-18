#include <Script.hpp>

using namespace std;

Module::Module() {

}

Module::Module(std::string nameIn) {
  name = nameIn;
}

Script* Script::loadFromFile(std::string fileName) {
        ifstream ScriptFile(fileName);
        cout << "Loading \"" << fileName << "\"" << endl;
        if(ScriptFile.is_open()) {


                ScriptFile.close();
        }
        return NULL;
}

void Script::step() {

}
