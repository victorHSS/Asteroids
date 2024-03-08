#ifndef EXPLOSIONHANDLER_H_INCLUDED
#define EXPLOSIONHANDLER_H_INCLUDED

#include "GameObj.h"
#include "BaseAnimation.h"

#include <list>

class ExplosionHandler : public GameObj
{
    public:
        ExplosionHandler();
        ExplosionHandler(const ExplosionHandler &) = delete;
        ExplosionHandler &operator=(const ExplosionHandler &) = delete;
        virtual ~ExplosionHandler();

        void newExplosion(int cx, int cy);
        const std::list<BaseAnimation *> &getExplosions() const;

        virtual bool init();
        virtual void update(double seconds);
        virtual void draw();

    private:
        std::list<BaseAnimation *> explosions;
        BaseAnimation *model;
};

#endif // EXPLOSIONHANDLER_H_INCLUDED
