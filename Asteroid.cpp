#include "Asteroid.h"

Asteroid::Asteroid()
{
    velocity = 0;
}

Asteroid::Asteroid(unsigned model, int posX, int posY, int velocity, double FPS)
{
    this->velocity = velocity;

    Sprite sprite;
    switch(model)
    {
    case 0:
        {
            sprite.loadImage(Image("bitmaps/asteroid-1-96.png"));
            break;
        }
    case 1:
        {
            sprite.loadImage(Image("bitmaps/asteroid-2-96.png"));
            break;
        }
    case 2:
        {

        }
    default:
        {
            sprite.loadImage(Image("bitmaps/asteroid-3-96.png"));
        }
        break;
    }

    sprite.setPos(posX,posY);
    sprite.generateMask();

    aAsteroid.setSprite(sprite);
    aAsteroid.setCiclical(true);
    aAsteroid.setFPS(FPS);

    aAsteroid.addFrame("mov",Rect(0,0,sprite.getImageWidth()/21,sprite.getImageHeight()/7),143);
    aAsteroid.changeKey("mov");
    aAsteroid.playAnimation();
}

Asteroid::~Asteroid()
{

}

bool Asteroid::init()
{

}

void Asteroid::update(double seconds)
{
    aAsteroid.getSprite().move(0, abs(velocity * seconds));
    aAsteroid.update(seconds);
}

void Asteroid::draw()
{
    aAsteroid.draw();
}

void Asteroid::setVelocity(int velocity)
{
    this->velocity = velocity;
}

int Asteroid::getVelocity() const
{
    return velocity;
}

int Asteroid::getPosX() const
{
    return aAsteroid.getSprite().getPosX();
}

int Asteroid::getPosY() const
{
    return aAsteroid.getSprite().getPosY();
}

int Asteroid::getCenterPosX() const
{
    return aAsteroid.getSprite().getCenterPosX();
}

int Asteroid::getCenterPosY() const
{
    return aAsteroid.getSprite().getCenterPosY();
}

int Asteroid::getHeight() const
{
    return aAsteroid.getSprite().getSpriteHeight();
}

int Asteroid::getWidth() const
{
    return aAsteroid.getSprite().getSpriteWidth();
}

void Asteroid::setPos(int x, int y)
{
    aAsteroid.getSprite().setPos(x,y);
}

void Asteroid::setFPS(double FPS)
{
    aAsteroid.setFPS(FPS);
}

void Asteroid::setDirection(bool dir)
{
    aAsteroid.setDirection(dir);
}

Sprite &Asteroid::getSprite()
{
    return aAsteroid.getSprite();
}

const Sprite &Asteroid::getSprite() const
{
    return aAsteroid.getSprite();
}
