#include <Common.hpp>
#include <XML.hpp>

#ifndef __GUI__H
#define __GUI__H

class GUIObject {
        public:
                std::string        id;
                Point2D            position;
                virtual int width();
                virtual int height();
                std::vector<GUIObject*> children;
                        GUIObject(XMLNode* nodeIn);
                static GUIObject* fromNode(XMLNode* nodein);
                static GUIObject* fromFile(std::string fileIn);
                        GUIObject* getGUIObjectByID(std::string id);
               //virtual void       setProperties(XMLNode* nodeIn);
                       void       processChildren(std::vector<Node*> childrenIn);
                       bool       isMouseInside(Point2D);
              // virtual void       loop();
               virtual void       display();




};

class Text : public GUIObject {

        public:
                sf::Text _text;
                Text(XMLNode* nodeIn);
                void display();
};

class Image : public GUIObject {
        private:

        public:
};

class Button : public Image {

};

class Window : public GUIObject {
        private:
                sf::RenderWindow* _window;
        public:
                Window(XMLNode* nodeIn);


                void draw(Text* textIn);
                void pollEvents();
                void display();
                Point2D size();
                void setMousePosition(Point2D);
                Point2D getMousePosition();
                void hideMouse();
                void showMouse();
                int  width();
                int height();
};

class GUI : public GUIObject {
        public:
                GUI(XMLNode* nodeIn);
};

class Font {
        public:
                sf::Font regular;
                sf::Font bold;
                sf::Font thin;
                Font(std::string fileName);
};
extern GUI* gui;
extern Font* font;
#endif
