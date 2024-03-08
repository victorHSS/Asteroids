#include "ExplosionHandler.h"

#include <iostream>

ExplosionHandler::ExplosionHandler()
{
    model = new BaseAnimation(Sprite(Image("bitmaps/explosion.png")),40);

    model->addFrame("mov",Rect(0,0,model->getSprite().getImageWidth()/8,model->getSprite().getImageHeight()/8),64);
    model->setCiclical(false);
    model->changeKey("mov");
//    std::cout << model->getSprite().getPosX() << " " << model->getSprite().getPosY() << std::endl;
//    std::cout << model->getSprite().getSpriteWidth() << " " << model->getSprite().getSpriteHeight() << std::endl;
//    std::cout << model->getSprite().getCenterPosX() << " " << model->getSprite().getCenterPosY() << std::endl;
}

ExplosionHandler::~ExplosionHandler()
{
    delete model;
    for (std::list<BaseAnimation *>::iterator it = explosions.begin(); it!=explosions.end() ;++it)
        delete (*it);
}

void ExplosionHandler::newExplosion(int cx, int cy)
{
    BaseAnimation *nExplosion = new BaseAnimation(*model);
    //*nExplosion = *model;
    nExplosion->getSprite().setRect(model->getSprite().getRect());//por algum motivo o valor de rect esta se perdendo
    nExplosion->getSprite().setCenterPos(cx,cy);

//    std::cout << nExplosion->getSprite().getPosX() << " " << nExplosion->getSprite().getPosY() << std::endl;
//    std::cout << nExplosion->getSprite().getSpriteWidth() << " " << nExplosion->getSprite().getSpriteHeight() << std::endl;
//    std::cout << nExplosion->getSprite().getCenterPosX() << " " << nExplosion->getSprite().getCenterPosY() << std::endl;

    explosions.push_back(nExplosion);
}

const std::list<BaseAnimation *> &ExplosionHandler::getExplosions() const
{
    return explosions;
}

bool ExplosionHandler::init()
{

}

void ExplosionHandler::update(double seconds)
{
    for (std::list<BaseAnimation *>::iterator it = explosions.begin(); it!=explosions.end() ;)
        if ((*it)->endOfAnimation())
        {
            delete (*it);
            it = explosions.erase(it);//pega o proximo
        }
        else
        {
            (*it)->update(seconds);
            ++it;//proximo
        }
}

void ExplosionHandler::draw()
{
    for (std::list<BaseAnimation *>::iterator it = explosions.begin(); it!=explosions.end() ;++it)
        (*it)->draw();
}
