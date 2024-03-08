#include "TextFont.h"

#include <cstring>
#include <iostream>

TextFont::TextFont()
{
    fontPath = nullptr;
    font = nullptr;
    fontSize = 0;

    posX = posY = 0;
    cPosX = cPosY = -100;
    dX = dY = 0;

    alignment = ALLEGRO_ALIGN_LEFT;

    fontColor = al_map_rgba(0,0,0,255);

    showText = true;
}

TextFont::TextFont(const char* fontPath, int size)
{
    this->fontPath = nullptr;
    this->font = nullptr;

    fontSize = size;

    setFont(fontPath);

    posX = posY = 0;
    cPosX = cPosY = -100;
    dX = dY = 0;

    alignment = ALLEGRO_ALIGN_LEFT;

    fontColor = al_map_rgba(0,0,0,255);

    showText = true;
}

TextFont::TextFont(const TextFont& tFont)
{
    this->fontPath = nullptr;
    this->font = nullptr;

    this->fontSize = tFont.fontSize;
    setFont(tFont.fontPath);

    this->posX = tFont.posX;
    this->posY = tFont.posY;
    this->cPosX = tFont.cPosX;
    this->cPosY = tFont.cPosY;

    this->alignment = tFont.alignment;

    this->fontColor = tFont.fontColor;
    this->dX = tFont.dX;
    this->dY = tFont.dY;

    this->showText = tFont.showText;
}

TextFont &TextFont::operator=(const TextFont& tFont)
{
    if (this == &tFont)
        return *this;

    this->fontPath = nullptr;
    this->font = nullptr;

    this->fontSize = tFont.fontSize;

    this->setFont(tFont.fontPath);

    this->posX = tFont.posX;
    this->posY = tFont.posY;
    this->cPosX = tFont.cPosX;
    this->cPosY = tFont.cPosY;

    this->alignment = tFont.alignment;

    this->fontColor = tFont.fontColor;

    this->dX = tFont.dX;
    this->dY = tFont.dY;
    this->showText = tFont.showText;

    return *this;
}

TextFont::~TextFont()
{
    if (fontPath)
        delete fontPath;

    al_destroy_font(font);
}

void TextFont::setFontColor(ALLEGRO_COLOR color)
{
    this->fontColor = color;
}

ALLEGRO_COLOR TextFont::getFontColor() const
{
    return fontColor;
}


bool TextFont::init()
{

}

void TextFont::update(double seconds)
{
    dX = ( (cPosX==-100) ? (posX) : ( cPosX - ( getTextWidth() / 2 ) ) );
    dY = ( (cPosY==-100) ? (posY) : ( cPosY - ( getFontHeight() / 2 ) ) );

}

void TextFont::draw()
{
//    static int c = 0;
//    std::cout << "c: " << c++ << " | " << dX << " " << cPosX << " " << posX << " " << getTextWidth()/2 << std::endl;

    if (showText)
        al_draw_text(font,fontColor,dX,dY,alignment,text.c_str());
}

bool TextFont::setFont(const char* fontPath)
{
    if (this->fontPath)
    {
        if (strcmp(this->fontPath,fontPath) == 0)
            return true;
        else
        {
            delete this->fontPath;
            al_destroy_font(font);
        }
    }

    if (!fontPath || strcmp(fontPath,"") == 0)
    {
        this->fontPath = nullptr;
        this->font = nullptr;

        return true;
    }
    else
    {
        this->fontPath = new char[strlen(fontPath)+1];
        strcpy(this->fontPath,fontPath);

        font = al_load_font(fontPath,fontSize,0);

        return (font != nullptr);
    }

}

int TextFont::getFontSize() const
{
    return fontSize;
}

void TextFont::setFontSize(int size)
{
    /**< por enquanto nada */
}

int TextFont::getFontHeight() const
{
    return al_get_font_line_height(font);
}

int TextFont::getFontAscent() const
{
    return al_get_font_ascent(font);
}

int TextFont::getFontDescent() const
{
    return al_get_font_descent(font);
}

int TextFont::getTextWidth() const
{
    return al_get_text_width(font,text.c_str());
}

int TextFont::getTextHeight() const
{
    return getFontHeight();
}

int TextFont::getTextAscent() const
{
    return getTextAscent();
}

int TextFont::getTextDescent() const
{
    return getTextDescent();
}

void TextFont::setAlignmentLeft()
{
    alignment = ALLEGRO_ALIGN_LEFT;
}

void TextFont::setAlignmentRight()
{
    alignment = ALLEGRO_ALIGN_RIGHT;
}

void TextFont::setAlignmentCenter()
{
    alignment = ALLEGRO_ALIGN_CENTRE;
}

void TextFont::setPos(int x, int y)
{
    setPosX(x);
    setPosY(y);
}

void TextFont::setCenterPos(int x, int y)
{
    setCenterPosX(x);
    setCenterPosY(y);
}

void TextFont::setPosX(int x)
{
    posX = x;
    cPosX = -100;
}

void TextFont::setPosY(int y)
{
    posY = y;
    cPosY = -100;
}

void TextFont::setCenterPosX(int x)
{
    cPosX = x;
}

void TextFont::setCenterPosY(int y)
{
    cPosY = y;
}

int TextFont::getPosX() const
{
    return posX;
}

int TextFont::getCenterPosX() const
{
    return cPosX;
}

int TextFont::getPosY() const
{
    return posY;
}

int TextFont::getCenterPosY() const
{
    return cPosY;
}

void TextFont::setText(const std::string& text)
{
    this->text = text;
}

void TextFont::appendText(const std::string& text)
{
    this->text += text;
}

void TextFont::show()
{
    showText = true;
}

void TextFont::hide()
{
    showText = false;
}

