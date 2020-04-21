#ifndef GAME_H
#define GAME_H

#include "gba.h"

                    /* TODO: */

            // Create any necessary structs //

typedef struct {
        int r;
        int c;
        int height;
        int width;
} Buzz;

typedef struct {
        int r;
        int c;
        const u16 *image;
        int height;
        int width;
} Tower;

typedef struct {
        int r;
        int c;
        const u16 *image;
        int height;
        int width;
} Ground;

/*
* For example, for a Snake game, one could be:
*
* typedef struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* } Snake;
*
*
* 
*
*
* Example of a struct to hold state machine data:
* 
* typedef struct state {
*   int currentState;
*   int nextState;
* } State
*
*/

#endif
