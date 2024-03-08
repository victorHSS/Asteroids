#include "Mouse.h"

Mouse::Mouse()
{
    if (!al_is_mouse_installed())
        al_install_mouse();

    al_get_mouse_state(&actual);
    previous = actual;
}

void Mouse::update()
{
    previous = actual;
    al_get_mouse_state(&actual);
}

int Mouse::getXPosition() const
{
    return actual.x;
}

int Mouse::getYPosition() const
{
    return actual.y;
}

bool Mouse::hasMoved() const
{
    return (actual.x != previous.x || actual.y != previous.y);
}

bool Mouse::hasMovedLeft() const
{
    return (actual.x < previous.x);
}

bool Mouse::hasMovedRight() const
{
    return (actual.x > previous.x);
}

bool Mouse::hasMovedUp() const
{
    return (actual.y < previous.y);
}

bool Mouse::hasMovedDown() const
{
    return (actual.y > previous.y);
}

bool Mouse::leftIsPressed() const
{
    return bool(actual.buttons&1);
}

bool Mouse::centerIsPressed() const
{
    return bool(actual.buttons&4);
}

bool Mouse::rightIsPressed() const
{
    return bool(actual.buttons&2);
}

bool Mouse::leftHasBeenPressed() const
{
    return bool( !(previous.buttons&1) && (actual.buttons&1));
}

bool Mouse::centerHasBeenPressed() const
{
    return bool( !(previous.buttons&4) && (actual.buttons&4));
}

bool Mouse::rightHasBeenPressed() const
{
    return bool( !(previous.buttons&2) && (actual.buttons&2));
}

bool Mouse::leftHasBeenReleased() const
{
    return bool( (previous.buttons&1) && !(actual.buttons&1));
}

bool Mouse::centerHasBeenReleased() const
{
    return bool( (previous.buttons&4) && !(actual.buttons&4));
}

bool Mouse::rightHasBeenReleased() const
{
    return bool( (previous.buttons&2) && !(actual.buttons&2));
}
