#include <iostream>
#include "gtest/gtest.h"
#include "Serpent.h"
#include "Map.h"
#include "Main.h"

using namespace std;
using namespace sf;

/*
 Cette classe de tests regroupe différents tests unitaires pour la classe Serpent.
 Nous ne testons que les méthodes publiques.
 */

class Serpent_test_fixture: public ::testing::Test
{


public:
    Serpent* serpent_test;
    Map* map_test;
    
    Serpent_test_fixture(){
        serpent_test = new Serpent(true);
        RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "SnakeTest", Style::None);
        map_test = new Map("", window, false);
    }
    virtual void SetUp(){
        map_test->updateGameField(5, 5, HEAD_EAST);
        serpent_test->setHead(*map_test, false);
    }
    virtual void TearDown(){
    }
    ~Serpent_test_fixture(){
        delete serpent_test;
        delete map_test;
    }
};

TEST_F(Serpent_test_fixture, test_cherry_action)
{
    map_test->updateGameField(5,5,CHERRY);
    Tiles head_tile_test = HEAD_EAST;
    int size_init = serpent_test->getSize();
    serpent_test->fruit_action(*map_test, head_tile_test);
    int size_fin = serpent_test->getSize();
    EXPECT_EQ(size_fin-size_init, 1);
}

TEST_F(Serpent_test_fixture, test_banana_action)
{
    
    map_test->updateGameField(5,5,CHERRY);
    Tiles head_tile_test = HEAD_EAST;
    serpent_test->fruit_action(*map_test, head_tile_test);
    int size_init = serpent_test->getSize();
    map_test->updateGameField(5, 5, BANANA);
    serpent_test->fruit_action(*map_test, head_tile_test);
    int size_fin = serpent_test->getSize();
    EXPECT_TRUE(size_fin-size_init== -1);
}


TEST_F(Serpent_test_fixture, test_grape_action)
{
    map_test->updateGameField(5,5,CHERRY);
    Tiles head_tile_test = HEAD_EAST;
    serpent_test->fruit_action(*map_test, head_tile_test);
    serpent_test->fruit_action(*map_test, head_tile_test);
    serpent_test->fruit_action(*map_test, head_tile_test);
    EXPECT_TRUE(serpent_test->getSize()==4);
    map_test->updateGameField(5, 5, GRAPE);
    serpent_test->fruit_action(*map_test, head_tile_test);
    EXPECT_TRUE(serpent_test->getSize()==1);
}



TEST_F(Serpent_test_fixture, test_strawberry_action)
{
    map_test->updateGameField(5,5,STRAWBERRY);
    EXPECT_FALSE(serpent_test->isreverse());
    Tiles head_tile_test = HEAD_EAST;
    serpent_test->fruit_action(*map_test, head_tile_test);
    EXPECT_TRUE(serpent_test->isreverse());
}

int main(int argc, char * argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}