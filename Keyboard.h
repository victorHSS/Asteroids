#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include <allegro5/allegro.h>

class Keyboard
{
    public:
        Keyboard();

        //Keyboard(const Keyboard &) = delete;/**< impedindo que o objeto seja copiado */
        Keyboard & operator=(const Keyboard &) = delete;/**< impedindo que o objeto seja copiado */
        inline ~Keyboard(){}


        void update();

        bool hasBeenPressed(unsigned key) const;
        bool hasBeenReleased(unsigned key) const;
        bool isPressed(unsigned key) const;

        const char* getKeyName(unsigned key) const;

    private:
        ALLEGRO_KEYBOARD *keyboard;
        ALLEGRO_KEYBOARD_STATE actualState;
        ALLEGRO_KEYBOARD_STATE previousState;

};

#endif // KEYBOARD_H_INCLUDED
