#include "JoystickHandler.h"

std::vector<Joystick> JoystickHandler::joysticks;

bool JoystickHandler::init()
{
    if (!al_install_joystick())
        return false;

    int nJ = al_get_num_joysticks();

    for (int j = 0 ; j < nJ ; j++)
    {
          joysticks.push_back(Joystick(al_get_joystick(j)));
    }

    return true;
}

unsigned JoystickHandler::getNumJoysticks()
{
    return joysticks.size();
}

Joystick &JoystickHandler::getJoystick(unsigned j)
{
    if (j >= joysticks.size())
        return joysticks[0];

    return joysticks[j];
}
