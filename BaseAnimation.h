#ifndef BASEANIMATION_H_INCLUDED
#define BASEANIMATION_H_INCLUDED

#include <vector>
#include <map>
#include <string>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>

#include "Rect.h"
#include "GameObj.h"
#include "Sprite.h"

class BaseAnimation : public GameObj
{
public:
    BaseAnimation();
    BaseAnimation(const Sprite &sprite, double FPS = 30, bool animating = false);
    virtual ~BaseAnimation(){};

    void setSprite(Sprite &sprite);
    void setFPS(double FPS);
    void setCiclical(bool ciclical);
    void setDirection(bool dir);
    void setKey(const char *key);
    void changeKey(const char *key);

    Sprite &getSprite();
    const Sprite &getSprite() const;

    bool endOfAnimation() const;

    void addFrame(const char *key, const Rect &rect);
    void addFrame(const char *key, const Rect &rect, unsigned count);
    void addFrame(const char *key, unsigned x, unsigned y, unsigned sy);

    void reAnimate();
    void playAnimation();
    void stopAnimation();

    virtual bool init();
    virtual void update(double seconds);
    virtual void draw();
private:

    Sprite sprite;
    std::map<std::string, std::vector <Rect> > frames;
    std::string lastKey;
    std::string actualKey;

    double FPS;

    double tTime;

    int dir;

    bool ciclical;
    bool endAnimation;
    unsigned lastFrame;
    unsigned actualFrame;

    bool animating;

};

#endif // BASEANIMATION_H_INCLUDED_H_INCLUDED
