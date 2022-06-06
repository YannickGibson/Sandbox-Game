/**
 * @file main.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <iostream>

#include "player.h"
#include "map.h"
#include "myWindow.h"
#include "loader.h"
#include "tests.h"

using namespace std;

//! Inicializes a level to play.
int playLevel(int & index, MyWindow & myWindow)
{
    int score = 0;
    Loader loader = Loader();
    Map * matrix = loader.load(index, score, myWindow);

    Player * p = loader.getPlayer();
    myWindow.updateBottomBar();

    char key;
    do
    {
        myWindow.updateStatusBar(index, score);
        p->update(*matrix, myWindow);
        matrix->update(p->y, p->x);
        myWindow.refreshWindow();
        timeout(70);

        if (p->isDead()){
            myWindow.endLevel();
            delete p;
            delete matrix;
            return 0;
        }
        key = p->getKey();
        
    } while (key != 'x' && key != 'y');
    if (key == 'y'){
        loader.save(*matrix, score);
        delete p;
        delete matrix;
        cout << "Game Saved" << endl;
        return -1;
    }
    delete p;
    delete matrix;

    return -1;
    
}

//! Gives user option to load game or open a new presaved world/map.
int menu(){
    int index = 1;
    cout << "Pick A Map (1-6) or Load Recent By Pressing 'S' | Then Enter" << endl;
    while(true){
        string c;
        getline(std::cin, c);
        
        if(std::cin.eof())
            return -2;
        else if (c == "S" || c == "s"){
            index = -1;
            break;
        }
        else if (c[0] >= '1' && c[0] <= '6'){
            index = c[0] - '0';
            break;
        }
        cout << "Incorrect Input Try Again." << endl;
        std::cin.clear();
    }
    return index;
}

#ifndef __SEMESTRAL__TEST__
int main()
{
    
    
    int index = menu();
    if (index == -2){
        cout << "Program ended by Ctrl + D" << endl;
        return 0; // ctrl + D
    }
    

    MyWindow myWindow = MyWindow();

    int gameStatus = 0;
    do
    {
        myWindow.initLevel();
        gameStatus = playLevel(index, myWindow);   
        myWindow.endLevel();
    } while (gameStatus >= 0);
    return 0;
}
#endif



#ifdef __SEMESTRAL__TEST__
//! \brief Runs tests from Tests class.
int main() {
    Tests::objectTest();
    Tests::windowTest();
    Tests::loaderTest();
    Tests::loaderSaveTest();
    Tests::mapTest();
    Tests::playerTest();
    cout << "Tests passed successfuly" << endl;
}
#endif
