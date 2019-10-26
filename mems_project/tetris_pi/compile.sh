#!/bin/bash
g++ code/*.cpp -w -o tetris_pi -L/usr/include/mysql -I/usr/include/mysql -lmysqlclient -lSDL2
