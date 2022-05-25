/**
 * @file main.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include <iostream>
#include <locale.h>
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

using namespace std;

void initGame()
{
    initscr();
    setlocale(LC_ALL, "");
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    refresh();
    curs_set(0); // hide cursor
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    //scrollok(stdscr, TRUE);
}
WINDOW *initLevel()
{
    int stdHeight, stdWidth;
    getmaxyx(stdscr, stdHeight, stdWidth);
    // + 2 because of the borders, and 2x for width because thats the tile width
    WINDOW *win = newwin(1 , 1, (stdHeight / 2) - 10, 10);
    //WINDOW *win = newwin(height + 2, width * 2 + 2, (stdHeight / 2) - 10, 10);
    nodelay(win, TRUE);
    return win;
}

void loadMap(vector<StaticObject *> &staticObjects, vector<DynamicObject *> &dynamicObjects, Player *&p, int &height, int &width, WINDOW *const win, const int index)
{
    string line;
    ifstream myfile("assets//levels/level" + to_string(index));
    bool endCheck = false;
    if (myfile.is_open())
    {

        myfile >> height >> width;
        wresize(win, height + 2, width * 2 + 2); // resize win before game object inicialization

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
                    p = new Player(y, x, win);
                }
                else if (name == "Wall")
                {
                    staticObjects.push_back(new Wall(y, x, win));
                }
                else if (name == "Lava")
                {
                    staticObjects.push_back(new Lava(y, x, win));
                }
                else if (name == "Enemy")
                {
                    dynamicObjects.push_back(new Enemy(y, x, win));
                }
                else if (name == "Goal")
                {
                    staticObjects.push_back(new Checkpoint(y, x, win));
                }
                else if (name == "Bush"){
                    dynamicObjects.push_back(new Bush(y, x, win));
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


int playLevel(int & index, int & score)
{


    vector<DynamicObject *> dynamicObjects;
    vector<StaticObject *> staticObjects;
    Player *p;
    int height;
    int width;
    WINDOW * win = initLevel();
    loadMap(staticObjects, dynamicObjects, p, height, width, win, index);

    box(win, '|', '-');

    Map matrix(height, width, &staticObjects, &dynamicObjects);
    matrix.add(staticObjects);
    matrix.add(dynamicObjects);

    start_color();
    init_pair(1, 1, 0);
    init_pair(2, 0, 13);         // ENEMY
    init_pair(3, 0, COLOR_BLUE); // WALL
    init_pair(4, 0, 9);          // LAVA
    init_pair(5, 0, 11);         // CHECKPOINT
    init_pair(6, 0, COLOR_GREEN);         // BUSH
    init_pair(10, 0, COLOR_CYAN);        // BULLET
    /*
    0. Black
    1. Blue
    2. Green
    3. Cyan
    4. Red
    5. Magenta
    6. Brown
    7. White ("Light Gray")
    8. Bright Black ("Gray")
    9. Bright Blue
    10. Bright Green
    11. Bright Cyan
    12. Bright Red
    13. Bright Magenta
    14. Yellow
    15. Bright White
    */

    // refreshing loop
    char key;
    do
    {
        updateStatusBar(index, score);

        state pState = p->update(matrix);

        switch (pState)
        {
        case GG:
            score -= 1;
            delwin(win);
            return 0;
        case NextLevel:
            score += 5;
            index += 1;
            delwin(win);
            return 0;
        case StateShootingLeft:
        case StateShootingRight:
        case StateShootingUp:
        case StateShootingDown:
        {
            Projectile *sh = p->shoot(pState);
            sh->update(matrix);
            dynamicObjects.push_back(sh);
        }
        break;

        default:
            break;
        }
        for (auto it = dynamicObjects.begin(); it != dynamicObjects.end();)
        {
            //cerr << "hello" << endl;
            state st = (*it)->update(matrix);
            if (st == GG)
            {
                delete *it;
                it = dynamicObjects.erase(it);
            }
            else
                it++;
        }
        matrix.addUpdate();

        mvwaddch(win, height - 1, width - 1, '┘');
        refresh();
        wrefresh(win);
        timeout(70);
        key = p->getKey();
        
    } while (key != 'x' && key != 'y');
    delwin(win);
    if (key == 'y'){
        return -1;
    }
    return -2;
    
}


void saveGame(const int index, const int score){
    cout << "Game Saved" << endl;
}

void importCheckpoint(const int & index, const int & score){
    
    int stdHeight, stdWidth;
    getmaxyx(stdscr, stdHeight, stdWidth);
    mvprintw(3, 20 - 10  - 10 , "Game Loaded");
}

int main()
{
    initGame();


    int index = 4;
    int score = 0;
    importCheckpoint(index, score);
    do
    {
        
    } while (playLevel(index, score) >= 0);

    endwin();
    if (index == -1){ // save game
        saveGame(index, score);
    }
}