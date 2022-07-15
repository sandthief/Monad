#include <Node.hpp>

#ifndef __XML__H
#define __XML__H


class XMLNode : public Node {
        public:
                std::string             name;
                std::string             contents;
                std::map<string,string> attributes;

                XMLNode(XMLNode* parent,std::string);
                XMLNode();

                XMLNode* getElementByID(std::string idIn);
                XMLNode* getElementByName(std::string nameIn);
};

class XMLDocument : public XMLNode {
        public:

                XMLDocument();

                static XMLDocument* fromFile(std::string fileName);


};

#endif
