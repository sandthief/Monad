#ifndef __ENGINE__HPP
#define __ENGINE__HPP

#include <Renderer.hpp>
#include <GUI.hpp>
#include <XML.hpp>
#include <Player.hpp>
#include <Scene.hpp>
#include <chaiscript/chaiscript.hpp>


extern chaiscript::ChaiScript  script;

class Engine {
  Player*                 player;
  Scene             scene;
  Renderer*               renderer;

  public:
    Engine(std::string scriptIn);
    void step();
};

#endif
