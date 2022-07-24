#include <Engine.hpp>
int main(int argc,char* argv[]) {
        Engine engine("resources/scripts/main.chai");

        while (1) {
                engine.step();
        }

    return 0;
}
