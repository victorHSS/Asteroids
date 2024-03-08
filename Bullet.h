#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "GameObj.h"
#include "Sprite.h"
#include "SpaceShip.h"

class SpaceShip;

class Bullet : public GameObj
{
    public:
        Bullet(const SpaceShip *const _shipFired, int dx, int dy, int velocity = 500);
        virtual ~Bullet();

        virtual bool init();
        virtual void update(double seconds);
        virtual void draw();

        int getPosX() const;
        int getPosY() const;

        Sprite &getSprite();
        const Sprite &getSprite() const;

    protected:
        Sprite sBullet;
        const SpaceShip *const shipFired;

        int velocity;
};


#endif // BULLET_H_INCLUDED
