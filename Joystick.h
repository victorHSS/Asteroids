#ifndef JOYSTICK_H_INCLUDED
#define JOYSTICK_H_INCLUDED

#include <allegro5/allegro.h>
#include <vector>
#include "JoystickHandler.h"

class Joystick
{
    friend class JoystickHandler;
    public:
        Joystick() = delete;

        Joystick(Joystick &&j);

        Joystick(const Joystick &) = delete;                /**< impedindo que o objeto seja copiado */
        Joystick &operator=(const Joystick &) = delete;     /**< impedindo que o objeto seja copiado */

        ~Joystick(){}

        void update();

        bool hasBeenPressed(unsigned button) const;
        bool hasBeenReleased(unsigned button) const;
        bool isPressed(unsigned button) const;

        void setDefaultStick(int defaultStick);

        bool centerHasBeenPressed() const;
        bool centerHasBeenReleased() const;
        bool centerIsPressed() const;

        bool leftHasBeenPressed() const;
        bool leftHasBeenReleased() const;
        bool leftIsPressed() const;

        bool rightHasBeenPressed() const;
        bool rightHasBeenReleased() const;
        bool rightIsPressed() const;

        bool upHasBeenPressed() const;
        bool upHasBeenReleased() const;
        bool upIsPressed() const;

        bool downHasBeenPressed() const;
        bool downHasBeenReleased() const;
        bool downIsPressed() const;

        unsigned getNumButtons() const;
        unsigned getNumSticks() const;
        unsigned getNumAxes(int stick) const;
        const char *getButtonName(int button) const;
        const char *getAxisName(int stick, int axis) const;

    private:
        Joystick(ALLEGRO_JOYSTICK *joystick);/**< unico construtor disponivel */

        ALLEGRO_JOYSTICK *joystick;
        ALLEGRO_JOYSTICK_STATE actualState;
        ALLEGRO_JOYSTICK_STATE previusState;

        int defaultStick;
};


#endif // JOYSTICK_H_INCLUDED
