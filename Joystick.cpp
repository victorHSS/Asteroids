#include "Joystick.h"

Joystick::Joystick(ALLEGRO_JOYSTICK* joystick)
{
    if (!al_is_joystick_installed())
        al_install_joystick();

    this->joystick = joystick;
    al_get_joystick_state(joystick, &actualState);
    previusState = actualState;

    defaultStick = 0;
}

Joystick::Joystick(Joystick &&j):actualState(j.actualState),previusState(j.previusState)
{
    this->joystick = j.joystick;
    j.joystick = nullptr;           /**< tranferencia de ownership */

    this->defaultStick = j.defaultStick;
}

void Joystick::update()
{
    previusState = actualState;
    al_get_joystick_state(joystick, &actualState);
}

bool Joystick::hasBeenPressed(unsigned button) const
{
    return (!previusState.button[button] && actualState.button[button]);
}

bool Joystick::hasBeenReleased(unsigned button) const
{
    return (previusState.button[button] && !actualState.button[button]);
}

bool Joystick::isPressed(unsigned button) const
{
    return actualState.button[button];
}

unsigned Joystick::getNumButtons() const
{
    return al_get_joystick_num_buttons(joystick);
}

unsigned Joystick::getNumSticks() const
{
    return al_get_joystick_num_sticks(joystick);
}

unsigned Joystick::getNumAxes(int stick) const
{
    return al_get_joystick_num_axes(joystick,stick);
}

const char *Joystick::getButtonName(int button) const
{
    return al_get_joystick_button_name(joystick,button);
}

const char *Joystick::getAxisName(int stick, int axis) const
{
    return al_get_joystick_axis_name(joystick,stick,axis);
}

void Joystick::setDefaultStick(int defaultStick)
{
    this->defaultStick = defaultStick;
}

bool Joystick::centerHasBeenPressed() const
{
    return ((previusState.stick[defaultStick].axis[0] != 0 ||
            previusState.stick[defaultStick].axis[1] != 0) &&
            actualState.stick[defaultStick].axis[0] == 0 &&
            actualState.stick[defaultStick].axis[1] == 0);
}

bool Joystick::centerHasBeenReleased() const
{
    return (previusState.stick[defaultStick].axis[0] == 0 &&
            previusState.stick[defaultStick].axis[1] == 0 &&
            (actualState.stick[defaultStick].axis[0] != 0 ||
            actualState.stick[defaultStick].axis[1] != 0));
}

bool Joystick::centerIsPressed() const
{
    return (actualState.stick[defaultStick].axis[0] == 0 &&
            actualState.stick[defaultStick].axis[1] == 0);
}

bool Joystick::leftHasBeenPressed() const
{
    return (previusState.stick[defaultStick].axis[0] > -0.5 &&
            actualState.stick[defaultStick].axis[0] <= -0.5);
}

bool Joystick::leftHasBeenReleased() const
{
    return (previusState.stick[defaultStick].axis[0] <= -0.5 &&
            actualState.stick[defaultStick].axis[0] > -0.5);
}

bool Joystick::leftIsPressed() const
{
    return (actualState.stick[defaultStick].axis[0] <= -0.5);
}

bool Joystick::rightHasBeenPressed() const
{
    return (previusState.stick[defaultStick].axis[0] < 0.5 &&
            actualState.stick[defaultStick].axis[0] >= 0.5);
}

bool Joystick::rightHasBeenReleased() const
{
    return (previusState.stick[defaultStick].axis[0] >= 0.5 &&
            actualState.stick[defaultStick].axis[0] < 0.5);
}

bool Joystick::rightIsPressed() const
{
    return (actualState.stick[defaultStick].axis[0] >= 0.5);
}

bool Joystick::upHasBeenPressed() const
{
    return (previusState.stick[defaultStick].axis[1] > -0.5 &&
            actualState.stick[defaultStick].axis[1] <= -0.5);
}

bool Joystick::upHasBeenReleased() const
{
    return (previusState.stick[defaultStick].axis[1] <= -0.5 &&
            actualState.stick[defaultStick].axis[1] > -0.5);
}

bool Joystick::upIsPressed() const
{
    return (actualState.stick[defaultStick].axis[1] <= -0.5);
}

bool Joystick::downHasBeenPressed() const
{
    return (previusState.stick[defaultStick].axis[1] < 0.5 &&
            actualState.stick[defaultStick].axis[1] >= 0.5);
}

bool Joystick::downHasBeenReleased() const
{
    return (previusState.stick[defaultStick].axis[1] >= 0.5 &&
            actualState.stick[defaultStick].axis[1] < 0.5);
}

bool Joystick::downIsPressed() const
{
    return (actualState.stick[defaultStick].axis[1] >= 0.5);
}

