#include <XML.hpp>
#include <TextureManager.hpp>
#include <Looper.hpp>
#include <functional>

#include <ScriptClass.hpp>

#ifndef __GUI__H
#define __GUI__H

class GUIObject;

typedef std::function<void(GUIObject*)>  GUIResponce;
void previousMenu(GUIObject* self);

class GUIObject : public ScriptClass, public Looper {
        public:
                std::string                        id;
                Point2D                            position;
                GUIObject*                         parent;
                std::vector<GUIObject*>            children;
                bool                               visible;
                float                              delay;
                GUIResponce                        loopFunction;

                GUIObject();
                GUIObject(XMLNode* nodeIn,GUIObject* parent);

                static void        exportToScript();

                        Point2D    getPositionFromNode(XMLNode* nodeIn);
                        Point2D    getDimensionsFromNode(XMLNode* nodeIn);
                virtual int        width();
                virtual int        height();
                virtual int        x();
                virtual int        y();
                        bool       isMouseInside();
                virtual void       checkMouse();
                        void       hideChild(std::string id);
                        void       showChild(std::string id);
                        void       toggleChild(std::string id);
                        void       addSubMenu(std::string fileName);
                static  GUIObject* fromNode(XMLNode* nodein,GUIObject* parentIn);
                static  GUIObject* fromFile(std::string fileIn);
                        GUIObject* getGUIObjectByID(std::string id);
                        void       processChildren(std::vector<Node*> childrenIn);
                        bool       isMouseInside(Point2D);
               virtual  void       display();




};

enum Thickness {
        Regular = 0,
        Thin,
        Bold
};

class Text : public GUIObject {
        public:
                sf::Font _font;
                sf::Text _text;
                Text();
                Text(XMLNode* nodeIn,GUIObject* parent);
                Text(int x,int y,std::string text);

                static void exportToScript();

                int width();
                int height();
                int x();
                int y();
                virtual void display();
                void setThickness(Thickness thickness);
                void setString(std::string text);
                std::string getString();
};

#define CLICK_DELAY 0.80f

class TextButton : public Text {
                GUIResponce click;
                float       lastClick;
        public:
                TextButton(XMLNode* nodeIn,GUIObject* parent);
                void display();
                void checkMouse();
};

class Image : public GUIObject {
        public:
                sf::Texture  _texture;
                sf::Sprite   _sprite;

                Image();
                Image(XMLNode* nodeIn,GUIObject* parent);

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

class Window : public GUIObject {
        private:
                sf::RenderWindow* _window;
                Console           console;
                Point2D lastMousePosition;

                sf::Clock clock;
        public:
                GUIObject* currentMenu;

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
extern bool menuMode;
#endif
