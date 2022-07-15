#include <Common.hpp>
#include <Renderer.hpp>
#include <GUI.hpp>
#include <XML.hpp>
#include <Map.hpp>
#include <Player.hpp>
#include <Script.hpp>

using namespace std;

Player* player;
Map     scene;
Script  script;


void setup() {
        font   = new Font("raleway");
        gui    = GUIObject::fromFile("resources/menus/main.xml");

        window = gui->getGUIObjectByID("main");
        window->hideMouse();
        renderer = new Renderer(window->width(),window->height());

        player = new Player();


        Entity* canister = new Entity("resources/models/Canister.md5mesh",Capsule( /* radius */ 10,Point3D(-5.0f,10.0f,-5.0f),/* height */ 5));
        scene.entities.push_back(canister);
        scene.load("resources/models/main.obj");
        scene.entities.push_back(player);

}

int main() {
        setup();
        while (1) {
                window->pollEvents();

                renderer->startFrame();
                        scene.updateEntities(-1.0f);
                        scene.render(player);
                renderer->endFrame();
        }

    return 0;
}
