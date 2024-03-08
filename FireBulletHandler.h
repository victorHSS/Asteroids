#ifndef FIREBULLETHANDLER_H_INCLUDED
#define FIREBULLETHANDLER_H_INCLUDED

#include "GameObj.h"
#include "Bullet.h"

#include <list>

class FireBulletHandler: public GameObj
{
    public:
        FireBulletHandler() = delete;
        FireBulletHandler(const Bullet &model, unsigned tBullets);
        FireBulletHandler(const FireBulletHandler &) = delete;
        FireBulletHandler &operator=(const FireBulletHandler &) = delete;
        virtual ~FireBulletHandler();

        void newBullet(int cx, int cy);
        void explodeBullet(Bullet *bullet);
        const std::list<Bullet *> &getBulletsFired() const;
        unsigned getNumBulletsFired() const;
        unsigned getNumBulletsCanFire() const;

        bool canFire() const;

        void setNumBullets(unsigned tBullets);
        void increaseNumBullets(unsigned iBullets = 1);

        virtual bool init();
        virtual void update(double seconds);
        virtual void draw();

    private:
        unsigned tBullets;
        std::list<Bullet *> bulletsFired;

        Bullet *model;
};


#endif // FIREBULLETHANDLER_H_INCLUDED
