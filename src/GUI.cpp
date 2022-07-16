#include <GUI.hpp>
#include <Player.hpp>

using namespace std;

GUIObject::GUIObject() {
        visible = true;
}

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
        if(nodeIn->name == "Menu") {
                return new GUIObject(nodeIn);
        }
        else if(nodeIn->name == "Window") {
                return new Window(nodeIn);
        }
        else if(nodeIn->name == "Text") {
                return new Text(nodeIn);
        }
        else if(nodeIn->name == "Image") {
                return new Image(nodeIn);
        }
        else {
                cout << "unknown GUIObject \"" << nodeIn->name << "\"" << endl;
                return NULL;
        }
}

void GUIObject::toggleChild(string id) {
        getGUIObjectByID(id)->visible = !getGUIObjectByID(id)->visible;
}

void       GUIObject::hideChild(string id) {
        getGUIObjectByID(id)->visible = false;
}
void       GUIObject::showChild(string id) {
        getGUIObjectByID(id)->visible = true;
}


void GUIObject::display() {
        if(visible) {
                for(int c = 0; c < children.size(); c++) {
                        children[c]->display();
                }
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

Point2D GUIObject::getPositionFromNode(XMLNode* nodeIn) {
        Point2D out;
        if(nodeIn->attributes.count("x"))
                out.x  = stoi(nodeIn->attributes["x"]);
        else
                out.x = 0;
        if(nodeIn->attributes.count("y"))
                out.y  = stoi(nodeIn->attributes["y"]);
        else
                out.y = 0;
        return out;
}


void GUIObject::addSubMenu(std::string fileName) {
        XMLDocument* doc = XMLDocument::fromFile(fileName);
        cout << doc->children.size();
        processChildren(doc->children);
}


Image::Image() {

}
Image::Image(XMLNode* nodeIn) {
        visible = true;
        _texture = TextureManager::get(nodeIn->attributes["src"]);
        _sprite.setTexture(_texture);

        Point2D position = getPositionFromNode(nodeIn);

        _sprite.setPosition(position.x,position.y);
}

int Image::width() {

}

int Image::height() {

}

void Image::display() {
        if(visible)
                window->draw(this);
}

Text::Text() {
}

Text::Text(XMLNode* nodeIn) : GUIObject(nodeIn){
        visible = true;
        _text.setFont(font->regular);
        if(nodeIn->attributes.count("size"))
                _text.setCharacterSize(stoi(nodeIn->attributes["size"]));
        else
                _text.setCharacterSize(30);
        _text.setString(nodeIn->contents);

        Point2D position = getPositionFromNode(nodeIn);

        _text.setPosition(position.x,position.y);
}
Text::Text(int x,int y,std::string text) {
        _text.setFont(font->regular);
        _text.setPosition(x,y);
        _text.setString(text);

}
void Text::display() {
        if(visible)
                window->draw(this);
}

int Text::width() {
        return _text.getLocalBounds().width;
}
int Text::height() {
        return _text.getLocalBounds().height;
}

void Text::setString(string text) {
        _text.setString(text);
}
string Text::getString() {
        return _text.getString().toAnsiString();
}

Console::Console() {
        visible  = false;
        cursor   = Text(0,0,"> ");
        text     = "";
        contents = Text(cursor.width(),0,text);
}

void Console::display() {

        if(contents.getString() != text)
                contents.setString(text);
        if(visible) {
                cursor.display();
                contents.display();
        }

}

void Console::toggle() {
        visible = !visible;
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
        console.display();

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
                   toggleChild("pause");
                   toggleMenuMode();
               }
               if (event.key.code == sf::Keyboard::Tab) {
                   console.toggle();
                   toggleMenuMode();
               }
            }
        }
}

void Window::toggleMenuMode() {
        if(!menuMode())
             lastMousePosition = getMousePosition();
        else
             setMousePosition(lastMousePosition);

        _menuMode = !_menuMode;

}

void Window::update() {
        pollEvents();
        if(menuMode())
                window->showMouse();
        else
                window->hideMouse();

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

void Window::draw(Image* imageIn) {
        _window->draw(imageIn->_sprite);
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

bool Window::menuMode() {
        return _menuMode;
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
