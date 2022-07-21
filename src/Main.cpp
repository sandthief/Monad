#include <Engine.hpp>

int main() {
        Engine engine("resources/scripts/main.chai");

        while (1) {
                engine.step();
        }

    return 0;
}
