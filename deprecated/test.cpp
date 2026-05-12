#include "Engine.h"

int main(int, char**) {
    Game game(1000, 1000);
    GameObject camera(&game);
    camera.addComponent<Camera>();
}
