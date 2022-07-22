#include <GUI.hpp>
#include <Player.hpp>

using namespace std;
using namespace chaiscript;

void GUIObject::exportToScript() {
        script.add(user_type<GUIObject>(),                        "GUIObject");
        script.add(constructor<GUIObject(XMLNode*,GUIObject*)>(), "GUIObject");
        script.add(constructor<GUIObject()>(),                    "GUIObject");

        script.add(fun(&GUIObject::width),                    "width");
        script.add(fun(&GUIObject::height),                   "height");

        script.add(fun(&GUIObject::hideChild),                "hideChild");
        script.add(fun(&GUIObject::showChild),                "showChild");
        script.add(fun(&GUIObject::toggleChild),              "toggleChild");
        script.add(fun(&GUIObject::addSubMenu),               "addSubMenu");
        script.add(fun(&GUIObject::getGUIObjectByID),         "getGUIObjectByID");

        script.add(fun(&GUIObject::id),                       "id");
        script.add(fun(&GUIObject::position),                 "position");
        script.add(fun(&GUIObject::parent),                   "parent");
        script.add(fun(&GUIObject::children),                 "children");
        script.add(fun(&GUIObject::visible),                  "visible");




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

GUIObject::GUIObject() {
        visible = true;
}

GUIObject::GUIObject(XMLNode* nodeIn,GUIObject* parentIn){
    parent = parentIn;
    timeElaped = 0.0;
    if(nodeIn->attributes.count("loop")) {
            loopFunction = script.eval<GUIResponce>(nodeIn->attributes["loop"]);
            if(nodeIn->attributes.count("delay")) {
                delay = stof(nodeIn->attributes["delay"]);
            }
            else
                delay = 60.0/15.0;
    }




        if(nodeIn->attributes["visible"] == "true")
          visible = true;
        else if(nodeIn->attributes["visible"] == "false")
          visible = false;
        else
          visible = true;

        id = nodeIn->attributes["id"];
        processChildren(nodeIn->children);
}

void       GUIObject::checkMouse() {
        for(int c = 0; c < children.size(); c++) {
                children[c]->checkMouse();
        }
}

int GUIObject::x() {
        return 0;
}

int GUIObject::y() {
        return 0;
}
bool GUIObject::isMouseInside() {
        Point2D mouse = window->getMousePosition();
        if(mouse.x >= x() && mouse.x <= x()+width()) {
                if(mouse.y >= y() && mouse.y <= y()+height()) {
                        return true;
                }
        }

        return false;
}

GUI::GUI(XMLNode* nodeIn) : GUIObject(nodeIn,NULL) {

}

GUIObject* GUIObject::fromFile(string fileIn) {
        XMLDocument doc("resources/menus/main.xml");
        XMLNode* embeddedScript = doc.getElementByName("Script");
        if(embeddedScript != NULL) {
                script.eval(embeddedScript->contents);
        }
        return GUIObject::fromNode(doc.getElementByName("GUI"),NULL);
}

GUIObject* GUIObject::fromNode(XMLNode* nodeIn,GUIObject* parent) {
        if(nodeIn->name == "GUI") {
                return new GUI(nodeIn);
        }
        if(nodeIn->name == "Menu") {
                return new GUIObject(nodeIn,parent);
        }
        else if(nodeIn->name == "Window") {
                return new Window(nodeIn);
        }
        else if(nodeIn->name == "Text") {
                return new Text(nodeIn,parent);
        }
        else if(nodeIn->name == "TextButton") {
                return new TextButton(nodeIn,parent);
        }
        else if(nodeIn->name == "Image") {
                return new Image(nodeIn,parent);
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
        //cout << "id: " << id << " timeElaped: " << timeElaped << " delay: " << delay << endl;


        if(timeElaped > delay) {
                if(loopFunction) {
                        loopFunction(this);
                }

                loop();
        }



        if(visible) {
                for(int c = 0; c < children.size(); c++) {
                        children[c]->display();
                }
        }

        timeElaped = timeElaped + ticks;
}

void GUIObject::processChildren(std::vector<Node*> childrenIn) {
        for(int c = 0; c < childrenIn.size(); c++) {
                if(((XMLNode*)childrenIn[c])->name != "Script")
                        children.push_back(GUIObject::fromNode((XMLNode*)childrenIn[c],this));
        }
}

int GUIObject::width() {
        return parent->width();
}
int GUIObject::height() {
        return parent->height();
}

Point2D GUIObject::getPositionFromNode(XMLNode* nodeIn) {
        Point2D out;
        if(nodeIn->attributes.count("x")){
                string value = nodeIn->attributes["x"];
                if(value.back() == '%') {
                  string percent = value.substr(0, value.size()-1);
                  out.x =(stof(percent)/100.0f) * parent->width();

                }
                else
                  out.x  = stoi(value);
        }
        else
                out.x = 0;
        if(nodeIn->attributes.count("y")) {
          string value = nodeIn->attributes["y"];
          if(value.back() == '%') {
            string percent = value.substr(0, value.size()-1);
            out.y = (stof(percent)/100.0f) * parent->height();

          }
          else
            out.y  = stoi(value);
        }

        else
                out.y = 0;
        return out;
}

Point2D GUIObject::getDimensionsFromNode(XMLNode* nodeIn) {
        Point2D out;
        if(nodeIn->attributes.count("width")){
                string value = nodeIn->attributes["width"];
                if(value.back() == '%') {
                  string percent = value.substr(0, value.size()-1);
                  out.x = (stof(percent)/100.0f) * parent->width();

                }
                else
                  out.x  = stoi(value);
        }
        else
                out.x = 0;
        if(nodeIn->attributes.count("height")) {
          string value = nodeIn->attributes["height"];
          if(value.back() == '%') {
            string percent = value.substr(0, value.size()-1);
            out.y = (1.0f/stof(percent)) * parent->height();

          }
          else
            out.y  = stoi(value);
        }

        else
                out.y = 0;
        return out;
}


void GUIObject::addSubMenu(std::string fileName) {
        XMLDocument doc(fileName);
        XMLNode* embeddedScript = doc.getElementByName("Script");
        if(embeddedScript != NULL) {
                script.eval(embeddedScript->contents);
        }
        processChildren(doc.children);
}


Image::Image() {

}
Image::Image(XMLNode* nodeIn,GUIObject* parentIn) {
        parent = parentIn;
        visible = true;
        _texture = TextureManager::get(nodeIn->attributes["src"]);
        _sprite.setTexture(_texture);

        Point2D position = getPositionFromNode(nodeIn);
        Point2D dimensions = getDimensionsFromNode(nodeIn);

        _sprite.setPosition(position.x,position.y);
        _sprite.setScale(dimensions.x,dimensions.y);
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


Text::Text(XMLNode* nodeIn,GUIObject* parentIn) : GUIObject(nodeIn,parentIn){

        visible = true;
        if(nodeIn->attributes.count("style")) {
          string style = nodeIn->attributes["style"];
          if(style == "thin") {
            setThickness(Thin);
            _font = font->thin;
          }
          else if(style == "regular") {
            setThickness(Regular);
            _font = font->regular;
          }
          else if(style == "bold") {
           setThickness(Bold);
           _font = font->bold;
          }
          else {
            cout << "Invalid font style \"" << style << "\"" << endl;
            setThickness(Regular);
            _font = font->regular;
          }
        }
        else {
          setThickness(Regular);
          _font = font->regular;
        }


        if(nodeIn->attributes.count("size")) {
                string value = nodeIn->attributes["size"];

                if(value.back() == '%') {
                  string percent = value.substr(0, value.size()-1);
                  int size =(stof(percent)/100.0f) * parent->width();
                  _text.setCharacterSize(size);

                }
                else
                  _text.setCharacterSize(stoi(nodeIn->attributes["size"]));
        }
        else
                _text.setCharacterSize(30);
        _text.setString(nodeIn->contents);

        Point2D position = getPositionFromNode(nodeIn);

        _text.setPosition(position.x,position.y);
}

void Text::setThickness(Thickness thickness) {
        if(thickness == Regular)
                _text.setFont(font->regular);
        else if(thickness == Thin)
                _text.setFont(font->thin);
        else if(thickness == Bold)
                _text.setFont(font->bold);
}

Text::Text(int x,int y,std::string text) {
        _text.setFont(font->regular);
        _text.setPosition(x,y);
        _text.setString(text);

}

void Text::exportToScript() {
        script.add(base_class<GUIObject, Text>());
        script.add(user_type<Text>(),                            "Text");
        script.add(constructor<Text(XMLNode*,GUIObject*)>(),     "Text");
        script.add(constructor<Text()>(),                        "Text");

        script.add(fun(&Text::width),                            "width");
        script.add(fun(&Text::height),                           "height");

        script.add(fun(&Text::setString),                        "setString");
        script.add(fun(&Text::getString),                        "getString");
}

void Text::display() {
        GUIObject::display();

        if(visible)
                window->draw(this);
}

int Text::x() {
        return _text.getPosition().x;
}
int Text::y() {
        return _text.getPosition().y;
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

TextButton::TextButton(XMLNode* nodeIn,GUIObject* parentIn) : Text(nodeIn,parentIn) {
        lastClick = 0.0f;
        if(nodeIn->attributes.count("click")) {
                click = script.eval<GUIResponce>(nodeIn->attributes["click"]);
        }
}

void TextButton::checkMouse() {
        if(isMouseInside() && visible) {
                if(lastClick > CLICK_DELAY) {

                        if(click) {
                                click(this);
                        }
                        lastClick = 0.0f;
                }
        }

        GUIObject::checkMouse();
}

void TextButton::display() {
        if(isMouseInside()) {
                setThickness(Regular);
        }
        else
                _text.setFont(_font);

        Text::display();
        lastClick = lastClick + ticks;

        if(lastClick > 100000)
                lastClick = CLICK_DELAY;
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


Window::Window(XMLNode* nodeIn) : GUIObject(nodeIn,NULL) {
        string title  = nodeIn->attributes["title"];
        int    width  = stoi(nodeIn->attributes["width"]);
        int    height = stoi(nodeIn->attributes["height"]);
        _window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Fullscreen, sf::ContextSettings(32));
        _window->setVerticalSyncEnabled(true);
        currentMenu = NULL;
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
            else if (event.type == sf::Event::MouseButtonPressed) {
                            checkMouse();

            }
            else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        if(currentMenu == NULL) {
                                menuMode = true;
                                currentMenu = getGUIObjectByID("pause");
                                currentMenu->visible = true;
                        }
                        else {
                                currentMenu->visible = false;

                                if(currentMenu->parent == this) {
                                        currentMenu = NULL;
                                        menuMode = false;
                                }
                                else
                                        currentMenu = currentMenu->parent;
                        }
                    }
               /*if (event.key.code == sf::Keyboard::Escape) {
                   toggleChild("pause");
                   toggleMenuMode();
               }
               if (event.key.code == sf::Keyboard::Tab) {
                   console.toggle();
                   toggleMenuMode();
                }*/
            }
        }
}

void Window::update() {
        ticks = clock.restart().asSeconds();
        pollEvents();

        if(menuMode)
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
