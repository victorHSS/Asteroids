#ifndef TEXTFONT_H_INCLUDED
#define TEXTFONT_H_INCLUDED

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <string>

#include "GameObj.h"

class TextFont: public GameObj
{
    public:
        TextFont();
        TextFont(const char* fontPath, int size);
        TextFont(const TextFont &tFont);
        TextFont &operator=(const TextFont &tFont);
        ~TextFont();

        virtual bool init();
        virtual void update(double seconds);
        virtual void draw();

        bool setFont(const char* fontPath);
        int getFontSize() const;
        void setFontSize(int size);

        void setFontColor(ALLEGRO_COLOR color);
        ALLEGRO_COLOR getFontColor() const;

        int getFontHeight() const;
        int getFontAscent() const;
        int getFontDescent() const;

        int getTextWidth() const;
        int getTextHeight() const;
        int getTextAscent() const;
        int getTextDescent() const;

        void setAlignmentLeft();
        void setAlignmentRight();
        void setAlignmentCenter();

        void setPos(int x, int y);
        void setPosX(int x);
        void setPosY(int y);

        void setCenterPos(int x, int y);
        void setCenterPosX(int x);
        void setCenterPosY(int y);

        int getPosX() const;
        int getPosY() const;

        int getCenterPosX() const;
        int getCenterPosY() const;

        void setText(const std::string &text);
        void appendText(const std::string &text);

        void show();
        void hide();

    private:
        char *fontPath;
        ALLEGRO_FONT *font;
        int fontSize;
        ALLEGRO_COLOR fontColor;

        std::string text;

        int posX, posY;
        int cPosX, cPosY;
        int dX,dY;

        int alignment;

        bool showText;
};


#endif // TEXTFONT_H_INCLUDED
