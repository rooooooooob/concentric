#ifndef CON_SETTINGS_HPP
#define CON_SETTINGS_HPP

#include <vector>
#include "Controller.hpp"

namespace con
{

class Level;

class Settings
{
    public:
        Settings ();
        std::vector<je::Controller> controls;

    private:
};

}

#endif
