#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
#include <cstring>
#include <vector>
#include <map>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>

#include <chaiscript/chaiscript.hpp>

#include <ScriptClass.hpp>
#include <Point.hpp>
#include <Collision.hpp>
#include <Sphere.hpp>
#include <Capsule.hpp>
#include <Model.hpp>
#include <Node.hpp>
#include <XML.hpp>
#include <Scene.hpp>
#include <Engine.hpp>
#include <MD5.hpp>

class GUI;
class Window;

extern GUI*                   gui;
extern Window*                window;
extern float                  ticks;
extern chaiscript::ChaiScript script;
float randomNumber(float Min, float Max);
