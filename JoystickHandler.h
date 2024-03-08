#ifndef JOYSTICKHANDLER_H
#define JOYSTICKHANDLER_H

#include <allegro5/allegro.h>
#include <vector>
#include "Joystick.h"

class Joystick;

class JoystickHandler
{
    public:
        JoystickHandler() = delete;
        JoystickHandler(const JoystickHandler &) = delete;
        ~JoystickHandler() = delete;

        static bool init();
        static unsigned getNumJoysticks();
        static Joystick &getJoystick(unsigned j);
    private:
        static std::vector<Joystick> joysticks;
};

#endif // JOYSTICKHANDLER_H
