#include <Script.hpp>

using namespace std;

bool Script::loadFromFile(std::string fileName) {
        ifstream ScriptFile(fileName);
        cout << "Loading \"" << fileName << "\"" << endl;
        if(ScriptFile.is_open()) {
                stringstream ss;
                string       token;

                ss << ScriptFile.rdbuf();
                root = new ASTNode;
                ASTNode* currentNode = root;

                while (ss >> token) {
                        for(int i = 0; i < token.length(); i++) {
                                        //currentNode.symbol.value 
                        }
                }
        }
}

void Script::step() {

}
