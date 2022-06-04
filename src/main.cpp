/**
 * @file main.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <iostream>
//#include <locale.h>
#include <curses.h>
#include <fstream>
#include <map>

#include "wall.h"
#include "player.h"
#include <vector>
#include <tuple>
#include "map.h"
#include "projectile.h"
#include "enemy.h"
#include "myWindow.h"

using namespace std;

void loadMap(vector<StaticObject *> &staticObjects, vector<DynamicObject *> &dynamicObjects, Player *&p, int &height, int &width, MyWindow & myWindow, const int index)
{
    string line;
    ifstream myfile("assets//levels/level" + to_string(index));
    bool endCheck = false;
    if (myfile.is_open())
    {

        myfile >> height >> width;
        myWindow.resize(height, width); // resize win before game object inicialization

        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                string name;
                int x;
                int y;
                myfile >> name >> y >> x;
                if (name == "Spawn")
                {
                    p = new Player(y, x, height, width);
                }
                else if (name == "Wall")
                {
                    staticObjects.push_back(new Wall(y, x, height, width));
                }
                else if (name == "Lava")
                {
                    staticObjects.push_back(new Lava(y, x, height, width));
                }
                else if (name == "Enemy")
                {
                    dynamicObjects.push_back(new Enemy(y, x, height, width));
                }
                else if (name == "Goal")
                {
                    staticObjects.push_back(new Checkpoint(y, x, height, width));
                }
                else if (name == "Bush"){
                    dynamicObjects.push_back(new Bush(y, x, height, width));
                }
                else if (name == "End")
                {
                    endCheck = true;
                    break;
                }
                else
                {
                    throw invalid_argument("Corrupted reading fxile");
                }
            }
        }

        myfile.close();
        if (endCheck == false)
        {
            throw invalid_argument("Error loading file");
        }
    }
}

void updateStatusBar(const int index, const int score)
{
    mvprintw(0, 0, "Score: %d", score);
    mvprintw(1, 0, "Level: %d", index);
}


int playLevel(int & index, int & score, MyWindow & myWindow)
{
    vector<DynamicObject *> dynamicObjects;
    vector<StaticObject *> staticObjects;
    Player *p;
    int height;
    int width;
    myWindow.initLevel();
    loadMap(staticObjects, dynamicObjects, p, height, width, myWindow, index);


    Map matrix(height, width, &staticObjects, &dynamicObjects, &myWindow);
    matrix.loadMap();
    
    matrix.add(staticObjects);
    matrix.add(dynamicObjects);
    

    for (auto it = staticObjects.begin(); it != staticObjects.end(); it++)
    {
        (*it)->update(myWindow);
    }

    // refreshing loop
    char key;
    do
    {
        //updateStatusBar(index, score);

        state pState = p->update(matrix, myWindow);

        switch (pState)
        {
        case GG:
            score -= 1;
            myWindow.endLevel();
            return 0;
        case NextLevel:
            score += 5;
            index += 1;
             myWindow.endLevel();
            return 0;
        case StateShootingLeft:
        case StateShootingRight:
        case StateShootingUp:
        case StateShootingDown:
        {
            Projectile *sh = p->shoot(pState);
            sh->update(matrix, myWindow);
            dynamicObjects.push_back(sh);
        }
        break;

        default:
            break;
        }
        for (auto it = dynamicObjects.begin(); it != dynamicObjects.end();)
        {
            //cerr << "hello" << endl;
            state st = (*it)->update(matrix, myWindow);
            if (st == GG)
            {
                delete *it;
                it = dynamicObjects.erase(it);
            }
            else
                it++;
        }
        matrix.addUpdate();
        myWindow.refreshWindow();
        timeout(70);
        key = p->getKey();
        
    } while (key != 'x' && key != 'y');
    myWindow.endLevel();
    if (key == 'y'){
        return -1;
    }
    return -2;
    
}


void saveGame(const int index, const int score){
    std::ofstream out("assets/save");
    out << index << " " << score;
    out.close();
    cout << "Game Saved" << endl;
}

void importCheckpoint(const int & index, const int & score){
    
    //int stdHeight, stdWidth;
    //getmaxyx(stdscr, stdHeight, stdWidth);
    mvprintw(2, 20 - 10  - 10 , "Game Loaded");

}

int main()
{

    int index = 4;
    /* cout << "Pick A Map (1-10) or Load Recent By Pressing 'S' | Then Enter" << endl;
    while(true){
        string c;
        cin >> c;
        if (c == ""){

        }
        else if (c == "S" || c == "s"){
            break;
        }
        else if (c[0] >= '1' && c[0] <= '9'){
            index = c[0] - '0';
            break;
        }
        cout << "Incorrect Input Try Again." << endl;
    } */

    int score = 0;
    MyWindow myWindow = MyWindow();



    importCheckpoint(index, score);
    int gameStatus = 0;
    do
    {
        gameStatus = playLevel(index, score, myWindow);   
    } while (gameStatus >= 0);

    endwin();
    if (gameStatus == -1){ // save game
        saveGame(index, score);
    }
}