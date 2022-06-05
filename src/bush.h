/**
 * @file bush.h
 * @author Yannick Gibson (gibsoyan@fit.cvut.cz)
 */

#pragma once

#include <iostream>
#include "gameobject.h"
#include "map.h"

//! Object which spreads across the Map if it's lucky, or is killed.
class Bush : public DynamicObject{
    public:
        Bush (const int y, const int x, const int h, const int w);
        std::string getExport() const override;
        bool isDangerous() const override;
        bool isToxic() const override;
    private:
        //! If the odds are right, the method clones the Bush object next to itself. Or dies. Or is stationary. 
        void _update(Map & m) override;
        //! Amount of _updates, after which the object has to cease its existence.
        int _lifespan = 3;
};
