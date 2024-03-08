#include "SpaceShip.h"

SpaceShip::SpaceShip(unsigned life):
    aShip(Sprite(Image("bitmaps/spaceship1-1.png")),9,true)
{
    this->life = life;
    state = ALIVE;

    velocity = 180;
    movX = movY = 0;

    aShip.getSprite().generateMask();

    aShip.addFrame("center",Rect(0,0,95,101),4);

    aShip.addFrame("left",Rect(0,202,95,101),4);
    aShip.addFrame("left-more",Rect(0,303,95,101),4);
    aShip.addFrame("right",Rect(0,404,95,101),4);
    aShip.addFrame("right-more",Rect(0,505,95,101),4);

    aShip.changeKey("center");
    aShip.getSprite().setCenterPos(400,400);
    aShip.setCiclical(true);
}

bool SpaceShip::init()
{

}

void SpaceShip::update(double seconds)
{
    switch(state)
    {
    case ALIVE:

        aShip.getSprite().move(velocity*seconds*movX , velocity*seconds*movY);
        movX = movY = 0;

        aShip.update(seconds);

        break;
    case EXPLODED:
        break;
    }
}

void SpaceShip::draw()
{
    switch(state)
    {
    case ALIVE:
        aShip.draw();
        break;
    case EXPLODED:
        break;
    }
}

void SpaceShip::moveUp()
{
    if (state==ALIVE)
    {
        movY = -1;
    }
}

void SpaceShip::moveLeft()
{
    if (state==ALIVE)
    {
        aShip.setKey("left-more");
        movX = -1;
    }
}

void SpaceShip::moveRight()
{
    if (state==ALIVE)
    {
        aShip.setKey("right-more");
        movX = 1;
    }
}

void SpaceShip::moveDown()
{
    if (state==ALIVE)
    {
        movY = 1;
    }
}

void SpaceShip::moveStop()
{
    if (state==ALIVE)
    {
        aShip.setKey("center");
        movX = movY = 0;
    }
}

void SpaceShip::setLife(unsigned life)
{
    this->life = life;
}

unsigned SpaceShip::getLife() const
{
    return life;
}

bool SpaceShip::hasLife() const
{
    return life > 0;
}

void SpaceShip::increaseLife()
{
    life++;
}

void SpaceShip::decreaseLife()
{
    life--;
}

void SpaceShip::reborn()
{
    aShip.getSprite().show();
    aShip.setKey("center");
    aShip.reAnimate();

    state = ALIVE;
}

void SpaceShip::explode()
{
    aShip.getSprite().hide();
    decreaseLife();

    state = EXPLODED;
}

void SpaceShip::setVelocity(unsigned velocity)
{
    this->velocity = velocity;
}

unsigned SpaceShip::getVelocity() const
{
    return velocity;
}

int SpaceShip::getPosX() const
{
    return aShip.getSprite().getPosX();
}

int SpaceShip::getPosY() const
{
    return aShip.getSprite().getPosY();
}

int SpaceShip::getCenterPosX() const
{
    return aShip.getSprite().getCenterPosX();
}

int SpaceShip::getCenterPosY() const
{
    return aShip.getSprite().getCenterPosY();
}

Sprite &SpaceShip::getSprite()
{
    return aShip.getSprite();
}


const Sprite &SpaceShip::getSprite() const
{
    return aShip.getSprite();
}

bool SpaceShip::isExploded() const
{
    return state == EXPLODED;
}

