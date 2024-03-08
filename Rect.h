#ifndef RECT_H_INCLUDED
#define RECT_H_INCLUDED

template <class T>
class RectType
{
    public:
        RectType():RectType(T(0),T(0),T(0),T(0)){}
        RectType(T xi, T yi, T width, T height){this->xi = xi;this->yi=yi;this->width = width;this->height = height;}
        ~RectType(){}

        void setRect(T xi, T yi, T width, T height){this->xi = xi;this->yi=yi;this->width = width;this->height = height;}

        T getX() const {return xi;}
        T getY() const {return yi;}
        T getWidth() const {return width;}
        T getHeight() const {return height;}

    private:
        T xi,yi;
        T width, height;
};

using Rect = RectType<int>;
//typedef RectType<int> Rect;


#endif // RECT_H_INCLUDED
