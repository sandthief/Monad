#ifndef __ENGINE__HPP
#define __ENGINE__HPP

#include <Common.hpp>
#include <Renderer.hpp>
#include <GUI.hpp>
#include <XML.hpp>
#include <Scene.hpp>
#include <Player.hpp>
#include <Health.hpp>

extern chaiscript::ChaiScript  script;

class Engine {
  Player*                 player;
  Scene                   scene;
  Renderer*               renderer;

  public:
    Engine(std::string scriptIn);
    void step();
};

#endif
