#include "BaseAnimation.h"

BaseAnimation::BaseAnimation()
{
    FPS = 30;
    tTime = 0.0;

    lastKey = actualKey = "";

    dir = 1;

    ciclical = true;
    endAnimation = false;
    lastFrame = actualFrame = 0;
    animating = false;
}

BaseAnimation::BaseAnimation(const Sprite  &sprite, double FPS, bool animating):sprite(sprite)
{
    //this->sprite = sprite;
    this->FPS = FPS;

    lastKey = actualKey = "";

    dir = 1;

    tTime = 0.0;

    ciclical = true;
    endAnimation = false;
    lastFrame = actualFrame = 0;
    this->animating = animating;
}

void BaseAnimation::setSprite(Sprite &sprite)
{
    this->sprite = sprite;
}

void BaseAnimation::setFPS(double FPS)
{
    this->FPS = FPS;
}

void BaseAnimation::setCiclical(bool ciclical)
{
    this->ciclical = ciclical;
}

void BaseAnimation::setDirection(bool dir)
{
    this->dir = dir?1:-1;
}

void BaseAnimation::setKey(const char* key)
{
    this->actualKey = key;
    sprite.setRect(frames[key][0]);
}

void BaseAnimation::changeKey(const char* key)
{
    this->lastKey = this->actualKey;
    this->actualKey = key;

    sprite.setRect(frames[key][0]);

    /**<  Reinicia toda a simulacao */
    reAnimate();
}

Sprite &BaseAnimation::getSprite()
{
    return sprite;
}

const Sprite &BaseAnimation::getSprite() const
{
    return sprite;
}

void BaseAnimation::reAnimate()
{
    tTime = 0;
    endAnimation = false;
    lastFrame = actualFrame = 0;
    animating = true;
}

bool BaseAnimation::endOfAnimation() const
{
    return endAnimation;
}

void BaseAnimation::addFrame(const char* key, const Rect &rect)
{
    frames[key].push_back(rect);
}

void BaseAnimation::addFrame(const char* key, const Rect &rect, unsigned count)
{
    unsigned tbx = sprite.getImageWidth() / rect.getWidth();
    Rect tRect = rect;
    for (int i = 0 ; i < count ; i++)
    {
        tRect.setRect(rect.getX() + rect.getWidth() * (i%tbx),rect.getY() + rect.getHeight() * (i / tbx),
                      rect.getWidth(),rect.getHeight());
        frames[key].push_back(tRect);
    }
}

void BaseAnimation::addFrame(const char* key, unsigned x, unsigned y, unsigned sy)
{
    unsigned bsx = sprite.getImageWidth() / x;
    unsigned bsy = sprite.getImageHeight() / y;

    for (unsigned i = 0 ; i < x ; i++)
        frames[key].push_back(Rect(bsx * i, bsy * sy, bsx, bsy));
}

bool BaseAnimation::init()
{
/**< nada */
    return true;
}

void BaseAnimation::draw()
{
    sprite.draw();
}

void BaseAnimation::update(double seconds)//tirar essa implementacao daqui e deixar pra implementar nas filhas
{
    double iF = 1.0/FPS;

    if (frames.find(actualKey) == frames.end())/**< evitar tentar acessar uma area que nao existe no mapa */
        return;

    if (ciclical && endAnimation)
        endAnimation = false;

    if (!ciclical && endAnimation)
        return;

    if (!animating)
        return;

    tTime += seconds;
    if (tTime >= iF)
    {
        tTime -= iF;
        lastFrame = actualFrame;
        actualFrame = (frames[actualKey].size() + actualFrame + 1 * dir ) % frames[actualKey].size();
    }

    if (actualFrame == 0 && lastFrame != actualFrame)
    {
        endAnimation = true;
        if (!ciclical) actualFrame = lastFrame; /**< mantem o ultimo frame da animacao */
    }
    sprite.setRect(frames[actualKey][actualFrame]);
}

void BaseAnimation::playAnimation()
{
    animating = true;
}

void BaseAnimation::stopAnimation()
{
    animating = false;
}
