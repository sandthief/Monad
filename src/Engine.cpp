#include <Engine.hpp>

using namespace std;
using namespace chaiscript;

float       ticks;
ChaiScript  script;

float fps() {
        return 1.f / ticks;
}

Engine::Engine(string scriptIn) {
        // expose functions to script
                script.add(fun(fps), "fps");


        // expose classes to script

                // Points
                Point2D::exportToScript();
                Point3D::exportToScript();

                // Nodes
                Node::exportToScript();
                XMLNode::exportToScript();
                XMLDocument::exportToScript();

                // Models
                Model::exportToScript();

                // GUI
                GUIObject::exportToScript();
                Text::exportToScript();

                // Collisions
                Collision::exportToScript();

                // Shapes
                Sphere::exportToScript();
                Capsule::exportToScript();

                // Entities
                Entity::exportToScript();


        font   = new Font("raleway");
        gui    = (GUI*)GUIObject::fromFile("resources/menus/main.xml");

        window = (Window*)gui->getGUIObjectByID("main");
        window->addSubMenu("resources/menus/pause.xml");

        renderer = new Renderer(window->width(),window->height());
        player = new Player();

        // call script
        script.use(scriptIn);

}

void Engine::step() {
        window->update();
        renderer->startFrame();
                scene.updateEntities(-100.0f);
                scene.render(player);
        renderer->endFrame();
}
