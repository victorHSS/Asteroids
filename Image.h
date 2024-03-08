#ifndef IMAGE_H
#define IMAGE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <memory>
#include <map>
#include <string>

class Image
{
    public:
        Image(){image = nullptr;it = loaded.end();}
        explicit Image(const std::string &fileN);
        ~Image();

        Image(const Image& other);
        Image(Image&& other);
        Image& operator=(const Image& other);
        Image& operator=(Image&& other);

        float getWidth() const {return al_get_bitmap_width(image);}
        float getHeight() const {return al_get_bitmap_height(image);}

        explicit operator const ALLEGRO_BITMAP*() const //converte Image para allegro_bitmap. Ponteiro valido enquanto durar o objeto
        {return image;}

        void draw(float xd, float yd, float xi, float yi, float width, float height) const
        {al_draw_bitmap_region(image, xi, yi, width, height, xd, yd, 0);}

        void draw(float xd, float yd) const
        {al_draw_bitmap_region(image, 0.0, 0.0, al_get_bitmap_width(image), al_get_bitmap_height(image), xd, yd, 0);}

    private:
        std::string fileName;
        ALLEGRO_BITMAP *image;

        //mapear nome arquivo ao endereço do bitmap na memoria
        static std::map<std::string,ALLEGRO_BITMAP*> loaded;
        static unsigned tImages;
        std::map<std::string,ALLEGRO_BITMAP*>::iterator it;

};

#endif // IMAGE_H
