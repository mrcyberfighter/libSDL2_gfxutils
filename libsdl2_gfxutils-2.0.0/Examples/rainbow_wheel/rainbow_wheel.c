/************************************************************************************
 * SDL2_gfxutils a SDL2_gfx forms generating and manipulating helper functions set. *
 * Copyright (©) 2016 Brüggemann Eddie <mrcyberfighter@gmail.com>.                  *
 *                                                                                  *
 * This file is part of SDL2_gfxutils.                                              *
 * SDL2_gfxutils is free software: you can redistribute it and/or modify            *
 * it under the terms of the GNU General Public License as published by             *
 * the Free Software Foundation, either version 3 of the License, or                *
 * (at your option) any later version.                                              *
 *                                                                                  *
 * SDL2_gfxutils is distributed in the hope that it will be useful,                 *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                     *
 * GNU General Public License for more details.                                     *
 *                                                                                  *
 * You should have received a copy of the GNU General Public License                *
 * along with SDL2_gfxutils. If not, see <http://www.gnu.org/licenses/>             *
 ************************************************************************************/

#include <SDL2/SDL.h>
#include <SDL2_gfxutils.h>

/** No need to #include <SDL2/SDL2_gfxPrimitives.h>
  * because <SDL2_gfxutils.h> include it.
  *************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>


/**
 * Compilation:
 *
 * $ cc -Wall -Wextra rainbow_wheel.c -lSDL2 -lm -lSDL2_gfx -lSDL2_gfxutils
 *
 * ************************************************************************/


bool loop;

#define set_loop(x) loop=x ;

#define WIDTH  (int16_t) 800
#define HEIGHT (int16_t) 600


#define CENTER_X (int16_t) 800/2
#define CENTER_Y (int16_t) 600/2

#define ITERATIONS 360/12


int sdl_init(uint32_t flags);
SDL_Window *sdl_create_window(const char *title, int screen_x_pos, int screen_y_pos, int width, int height, int flags);
SDL_Renderer *sdl_create_renderer(SDL_Window * window, int index, int flags);

void get_events(void);
void clear(SDL_Renderer * pRenderer, uint8_t bg_red, uint8_t bg_green, uint8_t bg_blue, uint8_t bg_a);
void display(SDL_Renderer * pRenderer);
void update(SDL_Window * pWindow);
void clean_up(SDL_Renderer * pRenderer, SDL_Window * pWindow);

void display_polygons(SDL_Renderer * pRenderer, Polygon * polygons[6][6]) {
  /** Polygon displaying function. **/

  int16_t c, cc;

  for (c = 0; c < 6; c++) {

    for (cc = 0; cc < 6; cc++) {
      display_filled_polygon(pRenderer, polygons[c][cc]);
    }

  }

  return;

}

int main(void) {

  /** SDL2 initialized: */
  if (sdl_init(SDL_INIT_VIDEO) != 0) {
    fprintf(stdout, "SDL initialize failed (%s)\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  /** Window creation: */
  SDL_Window *pWindow = NULL;
  pWindow = sdl_create_window("Rainbow wheel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

  if (pWindow == NULL) {
    fprintf(stderr, "Windows creation error: (%s)\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  /** Renderer creation. */
  SDL_Renderer *pRenderer;
  if ((pRenderer = sdl_create_renderer(pWindow, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
    fprintf(stderr, "SDL Renderer creating error (%s)\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  /** Iterators. **/
  int16_t ccc, cc, c, i, ii;

  /** orientation argument value variable. **/
  float offset = 0;

  /** Radius value. **/
  float radius = 25;

  Pixel center;
  center.x = CENTER_X;
  center.y = CENTER_Y;

  /** Define Arc arrays: we need the arcs for the forms construction. **/
  Arc *down_arc[ITERATIONS][6][6];
  Arc *upper_arc[ITERATIONS][6][6];

  for (i = 0, ii = 0; ii < ITERATIONS; i += ITERATIONS, ii++) {
    /** Fill the arcs arrays.
      * Which will be used for the polygons construction.
      ***************************************************/
    for (c = 0; c < 6; c++) {
      radius = 15;    /** We compute circle arcs with growing radius values. **/
      for (cc = 0; cc < 6; cc++) {
        /** Polygon down arc. **/
        down_arc[ii][c][cc] = generate_circle_arc(radius, center, offset + i, 360 / 12);
        /** Polygon upper arc. **/
        upper_arc[ii][c][cc] = generate_circle_arc(radius + 25.0f, center, offset + i, 360 / 12);

        radius += 55.0f;
      }

      offset += 360.0f / 6.0f;  /** We compute every position. **/
    }
  }



  /** Final polygons we construct with the arcs. **/
  Polygon *polygons[ITERATIONS][6][6];

  for (ccc = 0; ccc < ITERATIONS; ccc++) {

    for (cc = 0; cc < 6; cc++) {

      for (c = 0; c < 6; c++) {

        /** Current polygon settings. **/


        /** Allocate new Form and set the count member. **/
        polygons[ccc][cc][c] = new_form(down_arc[ccc][cc][c]->count + upper_arc[ccc][cc][c]->count);


        /** Must set the center value manually. **/
        polygons[ccc][cc][c]->center.x = center.x;
        polygons[ccc][cc][c]->center.y = center.y;


        /** We construct the polygon. **/
        i = 0;
        for (ii = 0; ii < upper_arc[ccc][cc][c]->count; ii++) {
           /** Add every pixel from the arc to the current polygon. **/
          polygons[ccc][cc][c]->coords.x[i] = upper_arc[ccc][cc][c]->coords.x[ii];
          polygons[ccc][cc][c]->coords.y[i] = upper_arc[ccc][cc][c]->coords.y[ii];
          i++;

        }



        for (ii = down_arc[ccc][cc][c]->count - 1; ii >= 0; ii--) {
           /** Add every pixel from the arc to the current polygon. **/
          polygons[ccc][cc][c]->coords.x[i] = down_arc[ccc][cc][c]->coords.x[ii];
          polygons[ccc][cc][c]->coords.y[i] = down_arc[ccc][cc][c]->coords.y[ii];
          i++;
        }



        /** Color setting with gradient support. **/
        switch (cc) {
          case 0:
            /** Red. **/
            set_form_color(polygons[ccc][cc][c], c * 51 + 51, 0, 0, c * 51 + 51);
            break;

          case 1:
            /** Yellow. **/
            set_form_color(polygons[ccc][cc][c], c * 51 + 51, c * 51 + 51, 0, c * 51 + 51);
            break;

          case 2:
           /** Green **/
            set_form_color(polygons[ccc][cc][c], 0, c * 51 + 51, 0, c * 51 + 51);
            break;

          case 3:
           /** turkish. **/
            set_form_color(polygons[ccc][cc][c], 0, c * 51 + 51, c * 51 + 51, c * 51 + 51);
            break;

          case 4:
           /** Blue. **/
            set_form_color(polygons[ccc][cc][c], 0, 0, c * 51 + 51, c * 51 + 51);
            break;

          case 5:
           /** Fuchsia. **/
            set_form_color(polygons[ccc][cc][c], c * 51 + 51, 0, c * 51 + 51, c * 51 + 51);
            break;
        }

      }
    }
  }


  /** Freeing the contruction arcs which coordinates have been copied in the polygons array. **/

  for (c = 0; c < ITERATIONS; c++) {

    for (cc = 0; cc < 6; cc++) {

      for (ccc = 0; ccc < 6; ccc++) {

        free_form(down_arc[c][cc][ccc]);
        free_form(upper_arc[c][cc][ccc]);

      }
    }
  }

  c = 0;

  const int FPS = 30;
  const int FRAME_DELAY = 1000 / FPS;

  set_loop(true);
  while (loop) {

    int frame_start = SDL_GetTicks();

    if (c == ITERATIONS) {
      c = 0;
    }


    clear(pRenderer, 0, 0, 0, 255);

    display_polygons(pRenderer, polygons[c]);

    display(pRenderer);
    update(pWindow);

    get_events();

    c++;

    int frame_end = SDL_GetTicks() - frame_start;

    if (frame_end < FRAME_DELAY) {
      SDL_Delay(FRAME_DELAY - frame_end);
    }


  }


  /** Freeing the (all positions) precomputed polygons. **/

  for (c = 0; c < ITERATIONS; c++) {

    for (cc = 0; cc < 6; cc++) {

      for (ccc = 0; ccc < 6; ccc++) {

        free_form(polygons[c][cc][ccc]);
      }
    }
  }


  clean_up(pRenderer, pWindow);

  SDL_Quit();

  return 0;

}




int sdl_init(uint32_t flags) {
  /**
   * flags:
   * SDL_INIT_TIMER             timer subsystem
   * SDL_INIT_AUDIO             audio subsystem
   * SDL_INIT_VIDEO             video subsystem
   * SDL_INIT_JOYSTICK          joystick subsystem
   * SDL_INIT_HAPTIC            haptic (force feedback) subsystem
   * SDL_INIT_GAMECONTROLLER    controller subsystem
   * SDL_INIT_EVENTS            events subsystem
   * SDL_INIT_EVERYTHING        all of the above subsystems
   * SDL_INIT_NOPARACHUTE       don't catch fatal signals
   *******************************************************************/
  return SDL_Init(flags);
}

SDL_Window *sdl_create_window(const char *title, int screen_x_pos, int screen_y_pos, int width, int height, int flags) {

  /**
   * screen_x_pos && screen_y_pos == SDL_WINDOWPOS_CENTERED or SDL_WINDOWPOS_UNDEFINED ;
   *
   * flags :
   * SDL_WINDOW_FULLSCREEN            fullscreen window
   * SDL_WINDOW_FULLSCREEN_DESKTOP    fullscreen window at the current desktop resolution
   * SDL_WINDOW_OPENGL                window usable with OpenGL context
   * SDL_WINDOW_HIDDEN                window is not visible
   * SDL_WINDOW_BORDERLESS            no window decoration
   * SDL_WINDOW_RESIZABLE             window can be resized
   * SDL_WINDOW_MINIMIZED             window is minimized
   * SDL_WINDOW_MAXIMIZED             window is maximized
   * SDL_WINDOW_INPUT_GRABBED         window has grabbed input focus
   * SDL_WINDOW_ALLOW_HIGHDPI         window should be created in high-DPI mode if supported (>= SDL 2.0.1)
   **********************************************************************************************************/

  return SDL_CreateWindow(title, screen_x_pos, screen_y_pos, width, height, flags);
}

SDL_Renderer *sdl_create_renderer(SDL_Window * window, int index, int flags) {

   /**
    * index : the index of the rendering driver to initialize, or -1 to initialize the first one supporting the requested flags
    *
    * flags:
    * SDL_RENDERER_SOFTWARE         the renderer is a software fallback
    * SDL_RENDERER_ACCELERATED      the renderer uses hardware acceleration
    * SDL_RENDERER_PRESENTVSYNC     present is synchronized with the refresh rate
    * SDL_RENDERER_TARGETTEXTURE    the renderer supports rendering to texture
    *
    * Note that providing no flags gives priority to available SDL_RENDERER_ACCELERATED renderer.
    **********************************************************************************************/

  return SDL_CreateRenderer(window, (index != -1) ? index : -1, (flags == 0) ? SDL_RENDERER_ACCELERATED : flags);
}

void get_events(void) {

  SDL_Event event;

  while (SDL_PollEvent(&event)) { /** Get user events */

    switch (event.type) {

      case SDL_QUIT: /** User quit the application. */
        set_loop(false);
        break;
  
     case SDL_KEYDOWN:
   
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          set_loop(false);
          break;
        }

    }
  }

  return;
}

void clear(SDL_Renderer * pRenderer, uint8_t bg_red, uint8_t bg_green, uint8_t bg_blue, uint8_t bg_a) {
  SDL_SetRenderDrawColor(pRenderer, bg_red, bg_green, bg_blue, bg_a);
  SDL_RenderClear(pRenderer);
}

void display(SDL_Renderer * pRenderer) {
  SDL_RenderPresent(pRenderer);
}

void update(SDL_Window * pWindow) {
  SDL_UpdateWindowSurface(pWindow);
}

void clean_up(SDL_Renderer * pRenderer, SDL_Window * pWindow) {
  SDL_DestroyRenderer(pRenderer);
  SDL_DestroyWindow(pWindow);
}
