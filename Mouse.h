#ifndef MOUSE_H_INCLUDED

#define MOUSE_H_INCLUDED

#include <allegro5/allegro.h>

class Mouse
{
public:
    Mouse();
    ~Mouse(){}

    void update();

    int getXPosition() const;
    int getYPosition() const;

    bool hasMoved() const;
    bool hasMovedLeft() const;
    bool hasMovedRight() const;
    bool hasMovedUp() const;
    bool hasMovedDown() const;

    bool leftIsPressed() const;
    bool centerIsPressed() const;
    bool rightIsPressed() const;

    bool leftHasBeenPressed() const;
    bool centerHasBeenPressed() const;
    bool rightHasBeenPressed() const;

    bool leftHasBeenReleased() const;
    bool centerHasBeenReleased() const;
    bool rightHasBeenReleased() const;


private:
    ALLEGRO_MOUSE_STATE actual, previous;

};

#endif // MOUSE_H_INCLUDED
