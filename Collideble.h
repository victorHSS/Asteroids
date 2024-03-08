#ifndef COLLIDEBLE_H_INCLUDED
#define COLLIDEBLE_H_INCLUDED

#include "Sprite.h"

class Collideble
{
    public:
        Collideble(){}
        ~Collideble(){}

        virtual bool collideWith(const Sprite &sp2) = 0;

    protected:
        bool collideWith(const Sprite &sp1, const Sprite &sp2);
};

bool CollideWith(const Sprite& sp1, const Sprite& sp2);

#endif // COLLIDEBLE_H_INCLUDED
