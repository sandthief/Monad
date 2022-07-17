#include <XML.hpp>

using namespace std;

XMLDocument::XMLDocument() {

}
XMLNode::XMLNode() {

}
XMLNode::XMLNode(XMLNode* parentIn,std::string nameIn){
        parent = parentIn;
        name   = nameIn;
}
XMLNode* XMLNode::getElementByName(string nameIn) {
        if(nameIn == name) {
                return this;
        }
        else {
                for(int c = 0; c < children.size(); c++) {
                        XMLNode* result = ((XMLNode*)children[c])->getElementByName(nameIn);

                        if(result != NULL)
                                return result;
                }
        }
        return NULL;
}
XMLNode* XMLNode::getElementByID(std::string idIn){
        if(attributes["id"] == idIn)
                return this;

        for(int c = 0; c < children.size(); c++) {
                XMLNode* result = ((XMLNode*)children[c])->getElementByID(idIn);

                if(result != NULL)
                        return result;
        }

        return NULL;

}

XMLDocument* XMLDocument::fromFile(string fileName) {

        ifstream XMLFile(fileName);
        cout << "Loading \"" << fileName << "\"" << endl;
        if(XMLFile.is_open()) {
                XMLDocument* out = new XMLDocument();
                XMLNode* currentNode = out;

                string token;
                bool   inside;
                stringstream ss;
                ss << XMLFile.rdbuf();

                while (ss >> token) {

                        if(token.front() == '<') {
                                inside = true;
                                if(token.at(1) == '/') {
                                        currentNode = (XMLNode*) currentNode->pop();
                                }
                                else {
                                        if(token.back() == '>') {
                                                token.erase(token.size() -1,1);
                                                inside = false;
                                        }
                                        token.erase(0,1);
                                        XMLNode* child = new XMLNode(currentNode, token);
                                        currentNode->push(child);
                                        currentNode = child;
                                }
                        }
                        else if(inside)  {
                                string key = token;
                                string tmp;
                                string value;

                                ss >> tmp >> value;

                                if(value.front() == '\"' && value.back() == '>') {
                                        value.erase(0,1);
                                        value.erase(value.size()-2,2);
                                        currentNode->attributes[key] = value;
                                        inside = false;
                                }

                                else if(value.front() == '\"' && value.back() == '\"') {
                                        value.erase(0,1);
                                        value.erase(value.size()-1,1);
                                        currentNode->attributes[key] = value;
                                }
                                else if(value.front() == '\"') {
                                        string word = "";
                                        value.erase(0,1);

                                        bool adding = true;
                                        while(adding) {
                                                ss >> word;
                                                if(word.back() == '\"') {
                                                        word.erase(word.size() - 1, 1);
                                                        value = value + " " + word;
                                                        adding = false;
                                                }
                                                else {
                                                        value = value + " " + word;
                                                }

                                        }

                                        currentNode->attributes[key] = value;
                                        value = "";


                                }

                        }
                        else {
                                if(currentNode->contents.empty())
                                        currentNode->contents = token;
                                else
                                        currentNode->contents = currentNode->contents + " " + token;
                        }
                }
                XMLFile.close();
                return out;
        }
        else {
                cout << "Could not load \"" << fileName <<"\"." << endl;
                return NULL;
        }
}
