#include "Image.h"
#include <exception>

std::map<std::string,ALLEGRO_BITMAP*> Image::loaded;
unsigned Image::tImages = 0;

Image::Image(const std::string &fileN):fileName(fileN)
{
    it = loaded.find(fileName);
    if (it == loaded.end()) //se nao existir
    {
        image = al_load_bitmap(fileName.c_str());
        if (!image) throw std::exception();

        it = loaded.insert(std::make_pair(fileName,image)).first;//insert retorna um pair cujo primeiro elemento é um iterator
    }
    else
    {
        image = it->second;
    }
    tImages++;
}

Image::~Image()
{
    if (image && --tImages == 0)
        for (auto it = loaded.cbegin() ; it != loaded.cend() ; ++it)
            al_destroy_bitmap(it->second);
}

Image::Image(const Image& other):fileName(other.fileName),it(other.it)
{
    image = other.image;
    tImages++;
}

Image::Image(Image&& other):fileName(other.fileName),it(other.it)
{
    image = other.image;
    tImages++;
    other.image = nullptr;
}

Image& Image::operator=(const Image& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

    if (image == 0)
        al_destroy_bitmap(image);

    image = rhs.image;
    fileName = rhs.fileName;
    it = rhs.it;
    tImages++;

    return *this;
}

Image& Image::operator=(Image&& rhs)
{
    if (image)
        al_destroy_bitmap(image); //decrementa o contador do objeto alvo

    image = rhs.image;

    rhs.image = nullptr;

    fileName = rhs.fileName;
    it = rhs.it;
    tImages++;

    return *this;
}
