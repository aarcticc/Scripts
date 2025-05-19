/*
 * main.c - Entry point for a simple raycaster demo using SDL2.
 *
 * This file sets up an 8x8 map for a basic raycasting engine, initializes
 * graphics and player state, and runs the main game loop. The player can move
 * and rotate within the map, and the scene is rendered each frame using
 * raycasting techniques.
 *
 * Key Components:
 * - 8x8 integer map: 1 represents a wall, 0 represents empty space.
 * - Player struct: Holds player position and direction.
 * - Graphics struct: Manages SDL2 window and renderer.
 * - Main loop: Handles input, updates player state, renders the scene, and
 *   manages frame timing.
 *
 * External Functions (defined elsewhere):
 * - int init_graphics(Graphics *gfx): Initializes SDL2 graphics.
 * - void handle_input(Player *player, const Uint8 *keystate, int map[8][8]): Handles player movement and rotation.
 * - void render_frame(Graphics *gfx, Player *player, int map[8][8]): Renders the current frame using raycasting.
 * - void shutdown_graphics(Graphics *gfx): Cleans up SDL2 resources.
 */

#include "raycaster.h"
#include <SDL2/SDL.h>

// 8x8 map: 1 = wall, 0 = empty space
int map[8][8] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,0,1},
    {1,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1}
};

int main(void) {
    Graphics gfx;
    // Initialize graphics (window, renderer, etc.)
    if (init_graphics(&gfx) != 0) return -1;

    // Initialize player at center of map, facing left
    Player player = {4.5f, 4.5f, -1.0f, 0.0f, 0.0f, 0.66f}; // dir and FOV

    int running = 1;
    SDL_Event event;

    // Main game loop
    while (running) {
        // Handle SDL events (window close, etc.)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
        }

        // Get current keyboard state
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);
        // Handle player input (movement, rotation)
        handle_input(&player, keystate, map);

        // Clear screen with a color (e.g., dark gray)
        SDL_SetRenderDrawColor(gfx.renderer, 30, 30, 30, 255);
        SDL_RenderClear(gfx.renderer);

        // Render the current frame (draw scene)
        render_frame(&gfx, &player, map);

        // Present the renderer (show the frame)
        SDL_RenderPresent(gfx.renderer);

        // Cap frame rate (~60 FPS)
        SDL_Delay(16);
    }

    // Clean up and shut down graphics
    shutdown_graphics(&gfx);
    return 0;
}
