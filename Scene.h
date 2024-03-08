#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <list>
#include "GameObj.h"

class Scene: public GameObj
{
    public:
        Scene(){}
        virtual ~Scene(){}

        virtual bool init();
        virtual void update(double seconds);
        virtual void draw();

        void addObject(GameObj *obj);
        bool remObject(GameObj *obj);

    private:
        std::list<GameObj *> objects;
};


#endif // SCENE_H_INCLUDED
