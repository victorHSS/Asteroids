#!/bin/bash

g++ -std=c++17 *.cpp -o spaceInvaders `pkg-config --libs allegro{-5,_acodec-5,_audio-5,_color-5,_dialog-5,_font-5,_image-5,_main-5,_memfile-5,_physfs-5,_primitives-5,_ttf-5,_video-5}`

