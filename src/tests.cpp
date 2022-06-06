/**
 * @file test.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <iostream>
#include <sstream>
#include <cassert>
#include "player.h"
#include "map.h"
#include "myWindow.h"
#include "loader.h"
#include "tests.h"
#include "staticObjects.h"

using namespace std;


//! Tests necessary Object methods.
void Tests::objectTest() {
    Wall w = Wall(0, 0, 10, 10);
    assert(w.isDangerous() == false);
    Brick b = Brick(0, 0, 10, 10);
    MyWindow win = MyWindow();
    win.initLevel();
    int score;
    Map m = Map(&win, 10, 10, &score);
    b.kill(m);
    assert(w.isDead() == false);
    assert(b.isDead() == true);
    win.endLevel();

}
//! Tests necessary MyWindow methods.
void Tests::windowTest() {
    MyWindow w1 = MyWindow();
    w1.initLevel();
    w1.resize(1,1);
    int height, width;
    w1.getSize(height, width);
    assert(height == 1);
    assert(width == 1);
    w1.endLevel();
    MyWindow w2 = MyWindow();
    w2.initLevel();
    w2.resize(30,30);
    w2.getSize(height, width);
    assert(height == 30);
    assert(width == 30);
    w2.endLevel();  
}
//! Tests necessary Loader methods.
void Tests::loaderTest() {
    MyWindow w = MyWindow();
    w.initLevel();
    Loader l = Loader();
    int score;
    Map * m = l.load(1, score, w);
    Player * p = l.getPlayer();
    assert(p != nullptr);
    w.endLevel();
    delete p;
    delete m;
}
//! Tests save Loader method.
void Tests::loaderTest2() {
    MyWindow w = MyWindow();
    w.initLevel();
    Loader l = Loader();
    int score;
    Map * m = l.load(-1, score, w); 
    Player * p = l.getPlayer();
    
    try{
        m = l.load(9999, score, w);
    }
    catch ( exception &e ){
        ostringstream oss;
        oss << e.what();
        assert(oss.str() == "Error loading file");
    }

    w.endLevel();
    delete p;
    delete m;
}
//! Tests necessary Map methods.
void Tests::mapTest() {
    MyWindow w = MyWindow();
    w.initLevel();
    Loader l = Loader();
    int score;
    Map * m = l.load(-1, score, w); 
    try
    {
        m->get(-1, -1);
    }
    catch( exception &e )
    {
        ostringstream oss;
        oss << e.what();
        assert(oss.str() == "Indices out of range");
    }
    w.endLevel();
}
//! Tests necessary Player methods.
void Tests::playerTest() {
    MyWindow w = MyWindow();
    w.initLevel();
    Loader l = Loader();
    int score;
    Map * m = l.load(1, score, w);
    Player * p = l.getPlayer();

    assert(p != nullptr);
    int x = p->x;
    p->moveLeft(*m);
    assert(p->x == x); // there is a wall

    w.endLevel();
    delete p;
    delete m; 
}