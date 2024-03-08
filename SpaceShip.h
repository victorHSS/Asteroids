#ifndef SPACESHIP_H_INCLUDED
#define SPACESHIP_H_INCLUDED

#include "BaseAnimation.h"

#include <list>

class SpaceShip : public GameObj
{
    public:
        SpaceShip(unsigned life = 0);
        virtual ~SpaceShip(){}

        virtual bool init();
        virtual void update(double seconds);
        virtual void draw();

        /**< movimentos */
        void moveUp();
        void moveLeft();
        void moveRight();
        void moveDown();
        void moveStop();

        /**< life */
        void setLife(unsigned life);
        unsigned getLife() const;
        bool hasLife() const;
        void increaseLife();
        void decreaseLife();

        /**< explode & reborn */
        void reborn();
        void explode();
        bool isExploded() const;

        /**< Velocity */
        void setVelocity(unsigned velocity);
        unsigned getVelocity() const;

        /**< Posicao */
        int getPosX() const;
        int getPosY() const;

        int getCenterPosX() const;
        int getCenterPosY() const;

        /**< outros */
        Sprite &getSprite();
        const Sprite &getSprite() const;

    private:
        BaseAnimation aShip;

        unsigned life;
        unsigned velocity;

        int movX;
        int movY;

        enum _STATE
        {
            ALIVE = 0,
            EXPLODED
        } state;

};


#endif // SPACESHIP_H_INCLUDED
