/*
 * raycaster.h
 *
 * Header file for a simple raycasting engine using SDL2.
 *
 * Defines core constants, data structures, and function prototypes for
 * initializing graphics, handling player movement, and rendering frames.
 *
 * Structures:
 *   - Player: Holds player position and direction.
 *   - Graphics: Manages SDL window, renderer, texture, and pixel buffer.
 *
 * Functions:
 *   - int init_graphics(Graphics *gfx): Initializes SDL graphics subsystem.
 *   - void shutdown_graphics(Graphics *gfx): Cleans up and releases graphics resources.
 *   - void render_frame(Graphics *gfx, Player *player, int map[8][8]): Renders a single frame based on player state and map.
 *   - void handle_input(Player *player, const Uint8 *keystate, int map[8][8]): Processes keyboard input and updates player state.
 *
 * Constants:
 *   - SCREEN_WIDTH, SCREEN_HEIGHT: Dimensions of the rendering window.
 *   - MOVE_SPEED, ROT_SPEED: Player movement and rotation speeds.
 *
 * Dependencies:
 *   - SDL2 library for graphics and input handling.
 *
 * Usage:
 *   Include this header in your main application source files to access
 *   raycasting engine functionality.
 */

#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MOVE_SPEED 0.1f
#define ROT_SPEED 0.05f

typedef struct {
    float x, y;
    float dirX, dirY;
    float planeX, planeY;
} Player;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    Uint32 *pixels;
} Graphics;

int init_graphics(Graphics *gfx);
void shutdown_graphics(Graphics *gfx);
void render_frame(Graphics *gfx, Player *player, int map[8][8]);
void handle_input(Player *player, const Uint8 *keystate, int map[8][8]);

#endif
