#include "Mask.h"

#include <cstring>

Mask::Mask()
{
    bitMask = nullptr;
    width = height = 0;
}

Mask::Mask(const Mask& mask, const Rect& rect) // assumindo que rect esta totalmente dentro da mask
{
    width = rect.getWidth();
    height = rect.getHeight();
    bitMask = new bool[width * height];
    //memset(bitMask,false,sizeof(bool)*width * height);

    for (int y = 0 ; y < height ; y++)
        for (int x = 0 ; x < width ; x++ )
            bitMask[y * width + x] = mask.bitMask[(y + rect.getY())*mask.width + x + rect.getX()];
}

Mask::Mask(const ALLEGRO_BITMAP* bitmap)
{
    width = al_get_bitmap_width(const_cast<ALLEGRO_BITMAP*>(bitmap));
    height = al_get_bitmap_height(const_cast<ALLEGRO_BITMAP*>(bitmap));
    bitMask = new bool[ width * height ];

    al_lock_bitmap(const_cast<ALLEGRO_BITMAP*>(bitmap),al_get_bitmap_format(const_cast<ALLEGRO_BITMAP*>(bitmap)),ALLEGRO_LOCK_READONLY);

    for (int y = 0 ; y < height ; y++)
        for (int x = 0 ; x < width ; x++)
        {
            unsigned char r,g,b,a;
            al_unmap_rgba(al_get_pixel(const_cast<ALLEGRO_BITMAP*>(bitmap), x, y),&r,&g,&b,&a);
            bitMask[y*width + x] = (a != 0);
        }

    al_unlock_bitmap(const_cast<ALLEGRO_BITMAP*>(bitmap));
}

Mask::Mask(const Mask& mask)
{
    this->width = mask.width;
    this->height = mask.height;

    if (mask.bitMask == nullptr)
        this->bitMask = nullptr;
    else
    {
        this->bitMask = new bool[mask.width * mask.height];
        this->bitMask = (bool*)memcpy(this->bitMask,mask.bitMask,mask.width*mask.height * sizeof(bool));
    }
}

Mask::Mask(Mask &&mask)
{
    this->width = mask.width;
    this->height = mask.height;
    this->bitMask = mask.bitMask;

    mask.bitMask = nullptr;
}

Mask &Mask::operator=(const Mask& mask)
{
    if (this == &mask)
        return *this;

    this->width = mask.width;
    this->height = mask.height;

    delete [] bitMask;

    if (mask.bitMask == nullptr)
        this->bitMask = nullptr;
    else
        {
            this->bitMask = new bool[mask.width * mask.height];
            this->bitMask = (bool*)memcpy(this->bitMask,mask.bitMask,mask.width*mask.height * sizeof(bool));
        }

    return *this;
}

Mask &Mask::operator=(Mask &&mask)
{
    if (this == &mask)
        return *this;

    this->width = mask.width;
    this->height = mask.height;

    delete [] this->bitMask;

    this->bitMask = mask.bitMask;
    mask.bitMask = nullptr;

    return *this;
}

Mask::~Mask()
{
    delete [] bitMask;
}

Mask Mask::getSubMask(const Rect& rect)
{
    Mask subMask(*this,rect);
    return subMask;
}

bool Mask::overlapWith(const Mask& mask) const
{
    for (int y = 0 ; (y < height && y < mask.height); y++)
        for (int x = 0 ; (x < width && x < mask.width); x++)
            if (bitMask[y*width + x] && mask.bitMask[y*mask.width + x])
                return true;

    return false;
}
