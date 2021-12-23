#include "./lib/game.hpp"

int main(int argc, char** argv) {
    Game g = Game();
    bool victory = g.run();
    if (victory) {
        std::cout << "Você venceu!\n";
    } else {
        // Printar derrota
        std::cout << "Você perdeu!\n";
    }

    return 0;
}