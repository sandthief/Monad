#include <Common.hpp>
#include <Renderer.hpp>
#include <GUI.hpp>
#include <XML.hpp>
#include <Map.hpp>
#include <Player.hpp>
#include <Health.hpp>

using namespace std;
using namespace chaiscript;

Player*     player;
Map         scene;
ChaiScript  script;



void setup() {
        font   = new Font("raleway");
        gui    = (GUI*)GUIObject::fromFile("resources/menus/main.xml");

        window = (Window*)gui->getGUIObjectByID("main");
        window->addSubMenu("resources/menus/pause.xml");

        renderer = new Renderer(window->width(),window->height());

        player = new Player();

        /*
        Entity* canister = new Entity("resources/models/canister.md5mesh",Capsule(10,Point3D(-5.0f,10.0f,3.0f),5));
        scene.entities.push_back(canister);
        Entity* health = new Health(Point3D(-5.0f,10.0f,2.0f));
        scene.entities.push_back(health);

        scene.load("resources/models/main.obj");
        scene.entities.push_back(player);
        */

}

float ticks;

int main() {

        setup();

        //chai.add(fun(print));
        script.use("resources/scripts/main.chai");
        /*
        while (1) {

                window->update();
                renderer->startFrame();
                        scene.updateEntities(-100.0f);
                        scene.render(player);
                        window->showFPS();
                renderer->endFrame();

        }*/

    return 0;
}
