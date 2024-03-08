#ifndef BULLETCONTROLLABLE_H_INCLUDED
#define BULLETCONTROLLABLE_H_INCLUDED

#include "Bullet.h"
#include "SpaceShip.h"

class SpaceShip;

class BulletControllable : public Bullet
{
    public:
        BulletControllable(SpaceShip *const _shipFired, int dx, int dy, int velocity = 500);
        virtual ~BulletControllable();

        void moveLeft();
        void moveRight();
        virtual void update(double seconds);
    private:
        int movX;
};


#endif // BULLETCONTROLLABLE_H_INCLUDED
