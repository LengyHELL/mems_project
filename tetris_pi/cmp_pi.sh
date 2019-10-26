#!/bin/bash
g++ *.cpp -o tetris_pi `sdl2-config --cflags --libs`
