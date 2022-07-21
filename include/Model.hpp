#ifndef __MODEL__H
#define __MODEL__H

#include <iostream>
#include <ScriptClass.hpp>

class Engine;

class Model : public ScriptClass {
	public:
		std::string  directory;
		Model();
		static void exportToScript();
		virtual void render();
		virtual void load(std::string modelName);

};

#endif
