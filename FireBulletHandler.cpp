#include "FireBulletHandler.h"

FireBulletHandler::FireBulletHandler(const Bullet &model, unsigned tBullets)
{
    this->model = new Bullet(model);
    this->tBullets = tBullets;
}

FireBulletHandler::~FireBulletHandler()
{
    for (std::list<Bullet *>::iterator it = bulletsFired.begin() ; it != bulletsFired.end() ; ++it)
        delete *it;

    delete model;
}

void FireBulletHandler::newBullet(int cx, int cy)
{
    Bullet *nBullet = new Bullet(*model);
    nBullet->getSprite().setCenterPos(cx,cy);
    bulletsFired.push_back(nBullet);
}

void FireBulletHandler::explodeBullet(Bullet* bullet)
{
    bulletsFired.remove(bullet);
    delete bullet;
}

const std::list<Bullet*> &FireBulletHandler::getBulletsFired() const
{
    return bulletsFired;
}

unsigned FireBulletHandler::getNumBulletsFired() const
{
    return bulletsFired.size();
}

unsigned FireBulletHandler::getNumBulletsCanFire() const
{
    return tBullets - bulletsFired.size();
}

void FireBulletHandler::setNumBullets(unsigned tBullets)
{
    this->tBullets = tBullets;
}

void FireBulletHandler::increaseNumBullets(unsigned iBullets)
{
    tBullets += iBullets;
}

bool FireBulletHandler::init()
{

}

void FireBulletHandler::update(double seconds)
{
    for (std::list<Bullet *>::iterator it = bulletsFired.begin() ; it != bulletsFired.end() ; ++it)
        (*it)->update(seconds);
}

void FireBulletHandler::draw()
{
    for (std::list<Bullet *>::iterator it = bulletsFired.begin() ; it != bulletsFired.end() ; ++it)
        (*it)->draw();
}

bool FireBulletHandler::canFire() const
{
    return tBullets > bulletsFired.size();
}
