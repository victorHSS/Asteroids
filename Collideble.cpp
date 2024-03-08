#include "Collideble.h"

#include "Mask.h"

#include <algorithm>

bool Collideble::collideWith(const Sprite& sp1, const Sprite& sp2)
{
    int x1i = sp1.getPosX();
    int x1f = sp1.getPosX() + sp1.getSpriteWidth();
    int x2i = sp2.getPosX();
    int x2f = sp2.getPosX() + sp2.getSpriteWidth();

    int y1i = sp1.getPosY();
    int y1f = sp1.getPosY() + sp1.getSpriteHeight();
    int y2i = sp2.getPosY();
    int y2f = sp2.getPosY() + sp2.getSpriteHeight();

    if (x1i < x2f && x1f > x2i &&
        y1i < y2f && y1f > y2i)
    {
        int pxi = std::max(x1i,x2i);
        int pxf = std::min(x1f,x2f);
        int pyi = std::max(y1i,y2i);
        int pyf = std::min(y1f,y2f);

        Rect rect1 = Rect(pxi-x1i,pyi-y1i,pxf-pxi,pyf-pyi);
        Rect rect2 = Rect(pxi-x2i,pyi-y2i,pxf-pxi,pyf-pyi);

        Mask mask1 = sp1.getSpriteMask().getSubMask(rect1);
        Mask mask2 = sp2.getSpriteMask().getSubMask(rect2);

        return mask1.overlapWith(mask2);
    }
    return false;
}

bool CollideWith(const Sprite& sp1, const Sprite& sp2)
{
    int x1i = sp1.getPosX();
    int x1f = sp1.getPosX() + sp1.getSpriteWidth();
    int x2i = sp2.getPosX();
    int x2f = sp2.getPosX() + sp2.getSpriteWidth();

    int y1i = sp1.getPosY();
    int y1f = sp1.getPosY() + sp1.getSpriteHeight();
    int y2i = sp2.getPosY();
    int y2f = sp2.getPosY() + sp2.getSpriteHeight();

    if (x1i < x2f && x1f > x2i &&
        y1i < y2f && y1f > y2i)
    {
        int pxi = std::max(x1i,x2i);
        int pxf = std::min(x1f,x2f);
        int pyi = std::max(y1i,y2i);
        int pyf = std::min(y1f,y2f);

        Rect rect1 = Rect(pxi-x1i,pyi-y1i,pxf-pxi,pyf-pyi);
        Rect rect2 = Rect(pxi-x2i,pyi-y2i,pxf-pxi,pyf-pyi);

        Mask mask1 = sp1.getSpriteMask().getSubMask(rect1);
        Mask mask2 = sp2.getSpriteMask().getSubMask(rect2);

        return mask1.overlapWith(mask2);
    }
    return false;
}
