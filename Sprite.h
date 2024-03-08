#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>

#include "GameObj.h"
#include "Rect.h"
#include "Image.h"
#include "Mask.h"

class Sprite: public GameObj
{
    public:
        Sprite();
        Sprite(const Image& img);
        Sprite(const Image& img, ALLEGRO_COLOR transparency);
        Sprite(const Sprite &sp);
        Sprite(Sprite &&sp);
        Sprite & operator=(const Sprite &sp);
        Sprite & operator=(Sprite &&sp);
        virtual ~Sprite();

        bool loadImage(const Image& img);
        bool loadImage(const Image& img, ALLEGRO_COLOR transparency);

        void show();
        void hide();

        bool isShown() const;

        /**<  Relativos ao corte do sprite*/
        void setPos(int dx, int dy);
        void setPosX(int dx);
        void setPosY(int dy);
        void move(int x, int y);

        int getPosX() const;
        int getPosY() const;

        void setCenterPos(int cx, int cy);
        void setCenterX(int cx);
        void setCenterY(int cy);

        int getCenterPosX() const;
        int getCenterPosY() const;

        void setRect(const Rect &rect);
        const Rect &getRect() const;
        void setRectFullImage();

        unsigned getSpriteWidth() const;
        unsigned getSpriteHeight() const;

        /**< Relativa a imagem completa */
        unsigned getImageWidth() const;
        unsigned getImageHeight() const;

        void setTransparencyColor(ALLEGRO_COLOR transparency);
        bool hasImage() const;

        /**< Mascara */
        void generateMask();//da imagem toda
        //const *Mask getImageMask();//da imagem toda
        Mask getSpriteMask() const;//do sprite corrente

        /**< Outros */
        virtual bool init();
        virtual void update(double seconds);
        virtual void draw();

    private:
        Image image;
        Mask *mask;

        int dx,dy;
        Rect rect;
        bool canShow;
};

#endif // SPRITE_H_INCLUDED
