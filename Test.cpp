#include "Test.h"

using namespace std;
using namespace sf;

Test::Test()
{
}

Test::~Test()
{
}

bool Test::testFruit_Action()
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Snake", Style::None);
    Map map("", window, false);
    map.updateGameField(0, 0, HEAD_EAST);
    Serpent serpent(true);
    serpent.setHead(map, false);
    map.updateGameField(0, 0, CHERRY);
    int size_init = serpent.getSize();
    Tiles head_tile = HEAD_EAST;
    serpent.fruit_action(map, head_tile);
    int size_fin = serpent.getSize();
    return size_fin-size_init == 1;

}

void Test::runTests()
{
    cout << testFruit_Action();
}