#ifndef CON_SETTINGS_HPP
#define CON_SETTINGS_HPP

#include <vector>
#include "PlayerConfig.hpp"

namespace con
{


class Settings
{
    public:
        Settings ();
        std::vector<PlayerConfig> controls;

    private:
};

}

#endif
