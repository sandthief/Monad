#include <GUI.hpp>
#include <Player.hpp>

using namespace std;

GUIObject* GUIObject::getGUIObjectByID(string idIn) {
        if(id == idIn)
                return this;
        else {
                for(int c = 0; c < children.size(); c++) {
                        if(children[c]->getGUIObjectByID(idIn))
                                return children[c];
                }
                return NULL;
        }
}

GUIObject::GUIObject(XMLNode* nodeIn){
        id = nodeIn->attributes["id"];
        processChildren(nodeIn->children);
}

GUI::GUI(XMLNode* nodeIn) : GUIObject(nodeIn) {

}

GUIObject* GUIObject::fromFile(string fileIn) {
        XMLDocument* doc = XMLDocument::fromFile("resources/menus/main.xml");
        return GUIObject::fromNode(doc->getElementByName("GUI"));
}

GUIObject* GUIObject::fromNode(XMLNode* nodeIn) {
        if(nodeIn->name == "GUI") {
                return new GUI(nodeIn);
        }
        else if(nodeIn->name == "Window") {
                return new Window(nodeIn);
        }
        else if(nodeIn->name == "Text") {
                return new Text(nodeIn);
        }
        else {
                cout << "unknown GUIObject \"" << nodeIn->name << "\"" << endl;
                return NULL;
        }

}
void GUIObject::display() {
        for(int c = 0; c < children.size(); c++) {
                children[c]->display();
        }
}
void GUIObject::processChildren(std::vector<Node*> childrenIn) {
        for(int c = 0; c < childrenIn.size(); c++) {
                children.push_back(GUIObject::fromNode(childrenIn[c]));
        }
}

int GUIObject::width() {
        return 0;
}
int GUIObject::height() {
        return 0;
}

Text::Text(XMLNode* nodeIn) : GUIObject(nodeIn){
        _text.setFont(font->regular);
        if(nodeIn->attributes.count("size"))
                _text.setCharacterSize(stoi(nodeIn->attributes["size"]));
        else
                _text.setCharacterSize(30);
        _text.setString(nodeIn->contents);
        int x,y;
        if(nodeIn->attributes.count("x"))
                x  = stoi(nodeIn->attributes["x"]);
        else
                x = 0;
        if(nodeIn->attributes.count("y"))
                 y  = stoi(nodeIn->attributes["y"]);
        else
                y = 0;

        _text.setPosition(x,y);
}

void Text::display() {
        window->draw(this);
}

Window::Window(XMLNode* nodeIn) : GUIObject(nodeIn) {
        string title  = nodeIn->attributes["title"];
        int    width  = stoi(nodeIn->attributes["width"]);
        int    height = stoi(nodeIn->attributes["height"]);
        _window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Default, sf::ContextSettings(32));

}

void Window::display() {
        _window->pushGLStates();

        GUIObject::display();

        _window->popGLStates();

        _window->display();
}
extern Player* player;
void Window::pollEvents() {
        sf::Event event;
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                // end the program
                exit(0);
            }
            else if (event.type == sf::Event::Resized){
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
            else if (event.type == sf::Event::KeyPressed) {
               if (event.key.code == sf::Keyboard::Escape) {
                   exit(0);
               }
            }
        }
}

void Window::setMousePosition(Point2D position)  {
        sf::Mouse::setPosition(sf::Vector2i(position.x,position.y), *_window);
}
void Window::hideMouse() {
        _window->setMouseCursorVisible(false);
}
void Window::showMouse() {
        _window->setMouseCursorVisible(true);
}

void Window::draw(Text* textIn) {
        _window->draw(textIn->_text);
}

Point2D Window::getMousePosition() {
        sf::Vector2i position = sf::Mouse::getPosition(*_window);
        return Point2D(position.x,position.y);
}
int Window::width() {
        return _window->getSize().x;
}
int Window::height() {
        return _window->getSize().y;
}

Font::Font(string fileName) {
        string thinTTF    = "resources/fonts/" + fileName + "_thin.ttf";
        string boldTTF    = "resources/fonts/" + fileName + "_bold.ttf";
        string regularTTF = "resources/fonts/" + fileName + ".ttf";
        regular.loadFromFile(regularTTF);
        thin.loadFromFile(thinTTF);
        bold.loadFromFile(boldTTF);
}

GUI*    gui;
Window* window;
Font*   font;
