/**
 * @file gameobject.cpp
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once

#include <iostream>
#include <curses.h>
#include "myWindow.h"

class Map;

//! An polymorphic abstract class for renderable objects
class Object {
     public:
        //! Y coordinate in the map.
        int y;
        //! X coordinate in the map.
        int x;
        //! Inicializes core Object properties.
        Object(const int yy, const int xx, const int h, const int w, const char cl, const char cr, const int clr);
        virtual ~Object () {};
        //! Marks object as dead, removes it from the map and removes traces.
        void kill(Map & m);        
        bool isDead() const;
        //! Tells if object is dangerous.
        virtual bool isDangerous() const = 0;
        //! Tells if object is toxic.
        virtual bool isToxic() const = 0;
        //! Tells how to export object.
        virtual std::string getExport() const = 0; 
    protected:
        //! Display characters that represents the object to the window.
        void _display(MyWindow & w) const;
        //! Puts blank characters (spaces) to where the object is currently located in the window.
        void _removeTraces(MyWindow & w) const;
        //! Represents height of the map.
        int height;
        //! Represents width of the map.
        int width;
        //! Marks object as killed.
        bool _killed;
    private:
        //! Left character representation for object.
        char charLeft;
        //! Right character representation for object.
        char charRight;
        //! Color representation representation for object.
        int color;
};
//! Object which needs to be updated only once and that is after inicialization.
class StaticObject : public Object{
    public:
        StaticObject(const int yy, const int xx, const int h, const int w, const char cl, const char cr, const int clr);
        virtual ~StaticObject () {};
        //! Displays the object.
        void update(MyWindow & w);
};

//! Object which needs to be updated only every frame.
class DynamicObject : public Object{
    public:
        DynamicObject(const int yy, const int xx, const int h, const int w, const char cl, const char cr, const int clr
            , const int uSpeed, const bool updateInstantly = true);
        virtual ~DynamicObject () {};
        //! update that depends on a update logic, calls _update if the logic is satisfied
        void update(Map & m, MyWindow & w);
    private:
        //! Actual update.
        virtual void _update(Map & m) = 0;
        //! Speed of updating.
        int updateSpeed = 3;
    protected:
        //! Index which iterates from zero to updateSpeed.
        int _updateIndex = 0;
};
