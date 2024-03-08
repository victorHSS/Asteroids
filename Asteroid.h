#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include "GameObj.h"
#include "BaseAnimation.h"

class Asteroid : public GameObj
{
    public:
        Asteroid();
        Asteroid(unsigned model, int posX, int posY, int velocity, double FPS);
        virtual ~Asteroid();

        virtual bool init();
        virtual void update(double seconds);
        virtual void draw();

        void setVelocity(int velocity);
        int getVelocity() const;

        void setFPS(double FPS);
        void setDirection(bool dir);

        void setPos(int x, int y);
        int getPosX() const;
        int getPosY() const;

        int getCenterPosX() const;
        int getCenterPosY() const;

        int getHeight() const;
        int getWidth() const;

        Sprite &getSprite();
        const Sprite &getSprite() const;

    private:
        BaseAnimation aAsteroid;
        int velocity;
};


#endif // ASTEROID_H_INCLUDED
