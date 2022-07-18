#include <Common.hpp>
#include <Renderer.hpp>
#include <GUI.hpp>
#include <XML.hpp>
#include <Map.hpp>
#include <Player.hpp>
#include <Health.hpp>
#include <Script.hpp>

using namespace std;


Player*  player;
Map      scene;
Script   script;


void setup() {
        font   = new Font("raleway");
        gui    = GUIObject::fromFile("resources/menus/main.xml");

        window = gui->getGUIObjectByID("main");
        window->addSubMenu("resources/menus/pause.xml");

        renderer = new Renderer(window->width(),window->height());

        player = new Player();


        Entity* canister = new Entity("resources/models/canister.md5mesh",Capsule( /* radius */ 10,Point3D(-5.0f,10.0f,3.0f),/* height */ 5));
        scene.entities.push_back(canister);
        Entity* health = new Health(Point3D(-5.0f,10.0f,2.0f));
        scene.entities.push_back(health);

        scene.load("resources/models/main.obj");
        scene.entities.push_back(player);

}

float ticks;

int main() {
        /*Script* script = Script::loadFromFile("resources/scripts/main.script");

        while(1) {
                script->step();
        }*/

        setup();

        while (1) {

                window->update();
                renderer->startFrame();
                        scene.updateEntities(-100.0 * ticks);
                        scene.render(player);
                        window->showFPS();
                renderer->endFrame();

        }

    return 0;
}
