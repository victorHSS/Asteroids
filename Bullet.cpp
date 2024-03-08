#include "Bullet.h"

Bullet::Bullet(const SpaceShip *const _shipFired, int dx, int dy, int velocity):sBullet(Image("bitmaps/bullet.png")),shipFired(_shipFired)
{
    sBullet.setCenterPos(dx,dy);
    sBullet.generateMask();

    this->velocity = velocity;

}

Bullet::~Bullet()
{

}

bool Bullet::init()
{

}

void Bullet::update(double seconds)
{
    sBullet.move(0, - velocity * seconds);
}

void Bullet::draw()
{
    sBullet.draw();
}

int Bullet::getPosX() const
{
    return sBullet.getPosX();
}

int Bullet::getPosY() const
{
    return sBullet.getPosY();
}

Sprite &Bullet::getSprite()
{
    return sBullet;
}

const Sprite &Bullet::getSprite() const
{
    return sBullet;
}
