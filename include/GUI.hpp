#include <Common.hpp>
#include <XML.hpp>
#include <TextureManager.hpp>
#include <Looper.hpp>
#ifndef __GUI__H
#define __GUI__H

class GUIObject {
        public:
                std::string             id;
                Point2D                 position;
                std::vector<GUIObject*> children;
                bool                    visible;

                GUIObject();
                GUIObject(XMLNode* nodeIn);

                        Point2D    getPositionFromNode(XMLNode* nodeIn);
                virtual int        width();
                virtual int        height();
                        void       hideChild(std::string id);
                        void       showChild(std::string id);
                        void       toggleChild(std::string id);
                        void       addSubMenu(std::string fileName);
                static  GUIObject* fromNode(XMLNode* nodein);
                static  GUIObject* fromFile(std::string fileIn);
                        GUIObject* getGUIObjectByID(std::string id);
                        void       processChildren(std::vector<Node*> childrenIn);
                        bool       isMouseInside(Point2D);
               virtual  void       display();




};

class Text : public GUIObject {

        public:
                sf::Text _text;
                Text();
                Text(XMLNode* nodeIn);
                Text(int x,int y,std::string text);
                int width();
                int height();
                void display();
                void setString(std::string text);
                std::string getString();
};

class Image : public GUIObject {
        public:
                sf::Texture  _texture;
                sf::Sprite   _sprite;

                Image();
                Image(XMLNode* nodeIn);

                int width();
                int height();
                void display();
};

class Button : public Image {

};

class Console : public GUIObject {
        Text contents;
        Text cursor;
        std::string text;
public:

        Console();
        void toggle();
        void display();

};

class Window : public GUIObject,public Looper {
        private:
                sf::RenderWindow* _window;
                Console           console;
                Point2D lastMousePosition;

                bool _menuMode;
                sf::Clock clock;
        public:
                Window(XMLNode* nodeIn);

                void update();
                void draw(Text* textIn);
                void draw(Image* imageIn);
                void pollEvents();
                void display();
                Point2D size();
                void setMousePosition(Point2D);
                Point2D getMousePosition();
                void hideMouse();
                void showMouse();
                int  width();
                int height();
                bool menuMode();
                void toggleMenuMode();
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
