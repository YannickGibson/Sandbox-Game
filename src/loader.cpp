/**
 * @file loader.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#include "loader.h"

#include "enemy.h"
#include "bush.h"
#include "staticObjects.h"


Player * Loader::getPlayer() const {
    return _player;
}

void Loader::_writeObjects(Map & m, ofstream & out) const{
    for (size_t y = 0; y < m.getHeight(); y++)
        for (size_t x = 0; x < m.getWidth(); x++){
            if (m.isEmpty(y, x) == false){
                Object * o = m.get(y, x);
                out << o->getExport() << " " << o->y << " " << o->x << endl;
            }
        }
}

void Loader::save(Map & m, const int score) const {
    std::ofstream out("assets/save");
    if (!out){
        throw invalid_argument("Error writing to save file");
    }
    out << m.getHeight() << " " << m.getWidth() << " " << score << endl;
    _writeObjects(m, out);
    out << "End 0 0";
    out.close();
}

void Loader::_addObject(string name, const int y, const int x, Map & m){
    int height = m.getHeight();
    int width = m.getWidth();
    if (name == "Spawn")
        _player = new Player(y, x, height, width);
    else if (name == "Wall")
        m.addNow((StaticObject *) new Wall(y, x, height, width));
    else if (name == "Lava")
        m.addNow((StaticObject *) new Lava(y, x, height, width));
    else if (name == "Enemy")
        m.addNow((DynamicObject *) new Enemy(y, x, height, width));
    else if (name == "Brick")
        m.addNow((StaticObject *) new Brick(y, x, height, width));
    else if (name == "Bush")
        m.addNow((DynamicObject *) new Bush(y, x, height, width));
    else
        throw invalid_argument("Corrupted reading fxile");
}


Map * Loader::load(int index, int & score, MyWindow & win){
    string loadPath;
    if (index == -1) // load save
        loadPath = "assets/save";
    else
        loadPath = "assets/levels/level" + to_string(index);
    ifstream myfile(loadPath);
    bool endCheck = false;
    if (myfile.is_open() == false)
        throw invalid_argument("Error loading file");

    int height, width;;
    myfile >> height >> width >> score;
    win.resize(height, width); // resize win before game object inicialization
    Map * m = new Map(&win, height, width, &score);

    string line;
    while (getline(myfile, line))
    {
        if (myfile.is_open() == false)
            break; // cannot read in middle of read, -> throw error
        string name;
        int x, y;
        myfile >> name >> y >> x;
        if (name == "End")
        {
            endCheck = true;
            break;
        }
        _addObject(name, y, x , *m);
    }
    myfile.close();

    if (endCheck == false)
        throw invalid_argument("Error loading file");
    
    m->updateStatic();

    return m;
}