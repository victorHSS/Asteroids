#include "Scene.h"

bool Scene::init()
{
/**< Nada */
}

void Scene::update(double seconds)
{
    for (std::list<GameObj * >::iterator it = objects.begin() ; it != objects.end() ; ++it)
        (*it)->update(seconds);
}

void Scene::draw()
{
    for (std::list<GameObj * >::iterator it = objects.begin() ; it != objects.end() ; ++it)
        (*it)->draw();
}

void Scene::addObject(GameObj *obj)
{
    objects.push_back(obj);
}

bool Scene::remObject(GameObj *obj)
{
    unsigned pSize = objects.size();

    objects.remove(obj);

    return objects.size() < pSize;
}
