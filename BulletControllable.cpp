#include "BulletControllable.h"

BulletControllable::BulletControllable(SpaceShip* const _shipFired, int dx, int dy, int velocity):
    Bullet(_shipFired,dx,dy,velocity)
{
    movX = 0;
}

BulletControllable::~BulletControllable()
{

}

void BulletControllable::moveLeft()
{
    movX = -1;
}

void BulletControllable::moveRight()
{
    movX = +1;
}

void BulletControllable::update(double seconds)
{
    Bullet::update(seconds);
    sBullet.move(movX * velocity * seconds, 0);
    movX = 0;
}
