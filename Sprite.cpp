#include "Sprite.h"

Sprite::Sprite()
{
    mask = nullptr;
    dx = dy = 0;

    canShow = true;
}

Sprite::Sprite(const Image& img):image(img)
{
    mask = nullptr;
    dx = dy = 0;
    canShow = true;

    setRectFullImage();
}

Sprite::Sprite(const Sprite &sp):GameObj(sp),image(sp.image),rect(sp.rect)
{
    if (sp.mask)
        mask = new Mask(*sp.mask);
    else
        mask = nullptr;

    dx = sp.dx;
    dy = sp.dy;

    canShow = true;
}

Sprite::Sprite(Sprite &&sp):GameObj(sp),image(sp.image),rect(sp.rect)
{
    mask = sp.mask;
    sp.mask = nullptr;

    dx = sp.dx;
    dy = sp.dy;

    canShow = true;
}

Sprite &Sprite::operator=(const Sprite &sp)
{
    if (this == &sp)
        return *this;

    GameObj::operator=(sp);

    image = sp.image;

    if (mask)
        delete mask;

    if (sp.mask)
        mask = new Mask(*sp.mask);
    else
        mask = nullptr;

    dx = sp.dx;
    dy = sp.dy;
    this->rect = rect;
    canShow = true;

    return *this;
}

Sprite &Sprite::operator=(Sprite &&sp)
{
    if (this == &sp)
        return *this;

    GameObj::operator=(sp);

    image = sp.image;

    delete mask;

    mask = sp.mask;
    sp.mask = nullptr;

    dx = sp.dx;
    dy = sp.dy;
    this->rect = rect;
    canShow = true;

    return *this;
}

Sprite::~Sprite()
{
    if (mask)
        delete mask;
}

bool Sprite::loadImage(const Image &img)
{
    image = img;

    setRectFullImage();

    return true;
}

void Sprite::setPos(int dx, int dy)
{
    this->dx = dx;
    this->dy = dy;
}

void Sprite::move(int x, int y)
{
    dx += x;
    dy += y;
}

void Sprite::setPosX(int dx)
{
    this->dx = dx;
}

void Sprite::setPosY(int dy)
{
    this->dy = dy;
}

void Sprite::setRect(const Rect &rect)
{
    this->rect = rect;
}

void Sprite::setRectFullImage()
{
    rect.setRect(0, 0, image.getWidth(), image.getHeight());
}

unsigned Sprite::getSpriteWidth() const
{
    return rect.getWidth();
}

unsigned Sprite::getSpriteHeight() const
{
    return rect.getHeight();
}

bool Sprite::hasImage() const
{
    return true;
}

bool Sprite::init()
{
    /**< nada a fazer */
}

void Sprite::update(double seconds)
{
    /**< nada a fazer */
}

void Sprite::draw()
{
    if (canShow)
        image.draw(dx,dy,rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
}

void Sprite::setTransparencyColor(ALLEGRO_COLOR transparency)
{
    al_convert_mask_to_alpha(const_cast<ALLEGRO_BITMAP*>((const ALLEGRO_BITMAP*)(image)), transparency);
}

Sprite::Sprite(const Image& img, ALLEGRO_COLOR transparency):image(img)
{
    dx = dy = 0;
    setTransparencyColor(transparency);
}

bool Sprite::loadImage(const Image& img, ALLEGRO_COLOR transparency)
{
    image = img;

    setTransparencyColor(transparency);
    return true;
}


int Sprite::getPosX() const
{
    return dx;
}

int Sprite::getPosY() const
{
    return dy;
}

const Rect &Sprite::getRect() const
{
    return rect;
}

int Sprite::getCenterPosX() const
{
    return (dx + rect.getWidth()/2);
}

int Sprite::getCenterPosY() const
{
    return (dy + rect.getHeight()/2);
}

void Sprite::show()
{
    canShow = true;
}

void Sprite::hide()
{
    canShow = false;
}

bool Sprite::isShown() const
{
    return canShow;
}

void Sprite::setCenterPos(int cx, int cy)
{
    setCenterX(cx);
    setCenterY(cy);
}

void Sprite::setCenterX(int cx)
{
    dx = cx - rect.getWidth()/2;
}

void Sprite::setCenterY(int cy)
{
    dy = cy - rect.getHeight()/2;
}

unsigned Sprite::getImageWidth() const
{
    return image.getWidth();
}

unsigned Sprite::getImageHeight() const
{
    return image.getHeight();
}

void Sprite::generateMask()
{
    if ((const ALLEGRO_BITMAP*)(image) == nullptr)
        return;

    mask = new Mask((const ALLEGRO_BITMAP*)(image));
}

Mask Sprite::getSpriteMask() const
{
    if (!mask)
        return Mask{};
    return mask->getSubMask(rect);
}
