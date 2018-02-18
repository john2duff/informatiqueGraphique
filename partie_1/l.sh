#!/bin/bash
gcc $1 -framework OpenGL -framework GLUT
if  [ $? = 0 ] 
then
    ./a.out
else
    echo "erreur compilation"
fi