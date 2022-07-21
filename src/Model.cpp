#include <Common.hpp>

using namespace std;
using namespace chaiscript;

Model::Model() {
	directory = "";
}

void Model::exportToScript() {
	script.add(user_type<Model>(),                      "Model");
        script.add(constructor<Model()>(),                  "Model");

	script.add(fun(&Model::load),                       "load");
	script.add(fun(&Model::render),                     "render");
}

void Model::render() {

}

void Model::load(std::string modelName) {

}
