#include <Node.hpp>

#ifndef __XML__H
#define __XML__H


class XMLNode : public Node {
        public:
                std::string                       name;
                std::string                       contents;
                std::map<std::string,std::string> attributes;

                XMLNode(XMLNode* parent,std::string);
                XMLNode();

                static void exportToScript();

                XMLNode* getElementByID(std::string idIn);
                XMLNode* getElementByName(std::string nameIn);
};

class XMLDocument : public XMLNode {
        public:
                XMLDocument();
                XMLDocument(std::string fileName);
                static void exportToScript();
};

#endif
