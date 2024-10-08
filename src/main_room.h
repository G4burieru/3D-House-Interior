#ifndef MAIN_ROOM_H
#define MAIN_ROOM_H

    #include <GL/glut.h>

    extern GLfloat doorPositionX, doorPositionZ; 
    extern int isDoorClosed;

    void drawMainRoom();
    void drawMainDoor();

#endif