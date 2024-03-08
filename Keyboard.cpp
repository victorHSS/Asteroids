#include "Keyboard.h"

Keyboard::Keyboard()
{
    if(!al_is_keyboard_installed())
        al_install_keyboard();

    al_get_keyboard_state(&actualState);
    previousState = actualState;
}

void Keyboard::update()
{
    previousState = actualState;
    al_get_keyboard_state(&actualState);
}

bool Keyboard::hasBeenPressed(unsigned key) const
{
    return (!al_key_down(&previousState, key) && al_key_down(&actualState, key));
}

bool Keyboard::hasBeenReleased(unsigned key) const
{
    return (al_key_down(&previousState, key) && !al_key_down(&actualState, key));
}

bool Keyboard::isPressed(unsigned key) const
{
    return al_key_down(&actualState, key);
}

const char *Keyboard::getKeyName(unsigned key) const
{
    return al_keycode_to_name(key);
}
