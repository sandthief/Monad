#include <Script.hpp>

using namespace std;

string Statement::print() {
        for(int t = 0; t < tokens.size() -1; t++) {
                cout << tokens[t] << " ";
        }
        cout << tokens[tokens.size() -1];
}

Script* Script::loadFromFile(std::string fileName) {
        ifstream ScriptFile(fileName);
        cout << "Loading \"" << fileName << "\"" << endl;
        if(ScriptFile.is_open()) {
                stringstream ss;
                string       token;
                string       fileContents;
                bool         insideString = false;

                ss << ScriptFile.rdbuf();

                fileContents = ss.str();


                vector<Statement> statements;
                Statement         currentStatement;
                for(int c = 0; c < fileContents.length(); c++){
                        char letter = fileContents.at(c);

                        if(letter == '.' && !insideString) {
                                currentStatement.tokens.push_back(token);
                                token = "";
                                statements.push_back(currentStatement);
                                currentStatement = Statement();
                        }
                        else if(!insideString && letter == '\"') {
                                insideString = true;
                        }
                        else if(insideString) {
                                if(letter == '\"') {
                                        insideString = false;
                                }
                                else {
                                        currentStatement.tokens[currentStatement.tokens.size()-1].push_back(letter);
                                }
                        }
                        else if (letter == ' '){
                                currentStatement.tokens.push_back(token);
                                token = "";
                        }
                        else if (letter != '\n') {
                                token.push_back(letter);
                        }
                }

                for(int s = 0; s < statements.size(); s++) {
                        cout << "\"";
                        statements[s].print();
                        cout << "\"" << endl;
                }
                ScriptFile.close();
        }
        return NULL;
}

void Script::step() {

}
