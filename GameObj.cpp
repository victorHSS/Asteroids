#include "GameObj.h"

GameObj::GameObj()
{
    objType = -1;
}

void GameObj::setGameObjType(unsigned type)
{
    objType = type;
}

unsigned GameObj::getGameObjType() const
{
    return objType;
}
