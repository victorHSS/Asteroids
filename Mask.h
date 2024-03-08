#ifndef MASK_H_INCLUDED
#define MASK_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "Rect.h"

class Mask //depois atualizar mask para aceitar uma cor como transparencia
{
    public:
        Mask();
        Mask(const ALLEGRO_BITMAP *bitmap);
        Mask(const Mask &mask, const Rect &rect);
        Mask(const Mask &mask);
        Mask(Mask &&mask);
        Mask &operator=(const Mask &mask);
        Mask &operator=(Mask &&mask);
        ~Mask();

        Mask getSubMask(const Rect &rect);
        bool overlapWith(const Mask &mask) const;

    private:
        bool *bitMask;
        unsigned width;
        unsigned height;

};


#endif // MASK_H_INCLUDED
