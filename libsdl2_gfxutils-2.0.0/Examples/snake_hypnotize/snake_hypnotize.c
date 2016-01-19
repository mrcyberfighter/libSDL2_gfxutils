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
#include <inttypes.h> // <stdint.h>
#include <unistd.h>
#include <sys/time.h>



/**
 * Compilation:
 *
 * $ cc -Wall -Wextra snake_hypnotize.c -lm -lSDL2 -lSDL2_gfx -lSDL2_gfxutils
 *
 * *********************************************************************/

_Bool loop ;

#define set_loop(x) loop=x ;

#define WIDTH  (int16_t) 800
#define HEIGHT (int16_t) 600


#define CENTER_X (int16_t) 800/2
#define CENTER_Y (int16_t) 600/2

int sdl_init(uint32_t flags) ;
SDL_Window* sdl_create_window(const char *title,int screen_x_pos, int screen_y_pos, int width, int height,int flags) ;
SDL_Renderer* sdl_create_renderer(SDL_Window *window,int index,int flags) ;

void get_events(void) ;
void clear(SDL_Renderer *pRenderer,uint8_t bg_red, uint8_t bg_green, uint8_t bg_blue,uint8_t bg_a) ;
void display(SDL_Renderer *pRenderer) ;
void update(SDL_Window *pWindow) ;
void clean_up(SDL_Renderer *pRenderer, SDL_Window *pWindow) ;






int main(void) {

  /** SDL2 initialized: */
  if (sdl_init(SDL_INIT_VIDEO) != 0 ) {
    fprintf(stdout,"SDL initialize failed (%s)\n",SDL_GetError());
    exit(EXIT_FAILURE) ;
  }

  /** Window creation: */
  SDL_Window* pWindow = NULL;
  pWindow = sdl_create_window("Snake hypnotizing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN) ;

  if( pWindow == NULL) {
    fprintf(stderr,"Windows creation error: %s\n",SDL_GetError());
    exit(EXIT_FAILURE) ;
  }

  /** Renderer creation. */
  SDL_Renderer *pRenderer  ;
  if ((pRenderer = sdl_create_renderer(pWindow,-1,SDL_RENDERER_ACCELERATED)) == NULL) {
    fprintf(stderr,"SDL Renderer creating error (%s)\n",SDL_GetError());
    exit(EXIT_FAILURE) ;
  }

  /** Iterators. **/
  int16_t c,cc ;

  /** Define the display center Pixel: **/
  Pixel center ;
  center.x = CENTER_X ;
  center.y = CENTER_Y ;

  /** Generate the snake head animation guideline: a spiral. **/
  Spiral *spiral = generate_simple_spiral(center, 6, 120, 0.85/3, 0, false) ;

  /** Snake head with 25 colors gradient. **/
  Polygon *snake_head[25] ;

  /** Define biggest radius from the rounded trigons colors gradient. **/
  float radius=100.0f ;

  for (c=0 ; c < 25 ; c++) {
    /** Generate colors gradient snakehead (rounded trigon). **/
    snake_head[c] = generate_corners_rounded_polygon(3, radius/2.0f, center, 90.0f) ;
    /** Make a color gradient: **/
    set_form_color(snake_head[c], 0, c*10 + 15, c*10 + 15, 255) ;
    radius -= 2 ;
  }

  c=0  ;
  cc=0 ;

  set_loop(true) ;
  while (loop) {
      /** SDL2 mainloop. **/



      if (cc == spiral->count) {
        /** End of the hypnotizing. **/
        cc=0 ;
        usleep(2500000) ;
        clear(pRenderer,0, 0, 0, 255) ;
      }

      for (c=0 ; c < 25 ; c++) {
        /** rounded trigon new center. **/
        Pixel snake_head_center ;
        snake_head_center.x = spiral->coords.x[cc] ;
        snake_head_center.y = spiral->coords.y[cc] ;

        /** Set the new center and translate all the pixels from the rounded trigon.  **/
        set_form_center(snake_head[c], snake_head_center, true) ;

     

      }

      for (c=0 ; c < 25 ; c++) {
        display_filled_polygon(pRenderer, snake_head[c]) ;
      }

      cc++ ;

      display(pRenderer);
      update(pWindow);

      get_events() ;

      usleep(25000) ;

  }

  /** Freeing all coordinates arrays: **/

  free_form(spiral) ;
  for (c=0 ; c < 25 ; c++) {
    free_form(snake_head[c]) ;
  }


  clean_up(pRenderer, pWindow) ;

  SDL_Quit();

  return 0;

}

int sdl_init(uint32_t flags) {
  /**
   * flags:
   * SDL_INIT_TIMER           timer subsystem
   * SDL_INIT_AUDIO           audio subsystem
   * SDL_INIT_VIDEO           video subsystem
   * SDL_INIT_JOYSTICK        joystick subsystem
   * SDL_INIT_HAPTIC          haptic (force feedback) subsystem
   * SDL_INIT_GAMECONTROLLER  controller subsystem
   * SDL_INIT_EVENTS          events subsystem
   * SDL_INIT_EVERYTHING      all of the above subsystems
   * SDL_INIT_NOPARACHUTE     don't catch fatal signals
   *******************************************************************/
  return SDL_Init(flags);
}

SDL_Window *sdl_create_window(const char *title, int screen_x_pos, int screen_y_pos, int width, int height, int flags) {

  /**
   * screen_x_pos && screen_y_pos == SDL_WINDOWPOS_CENTERED or SDL_WINDOWPOS_UNDEFINED ;
   *
   * flags :
   * SDL_WINDOW_FULLSCREEN          fullscreen window
   * SDL_WINDOW_FULLSCREEN_DESKTOP  fullscreen window at the current desktop resolution
   * SDL_WINDOW_OPENGL              window usable with OpenGL context
   * SDL_WINDOW_HIDDEN              window is not visible
   * SDL_WINDOW_BORDERLESS          no window decoration
   * SDL_WINDOW_RESIZABLE           window can be resized
   * SDL_WINDOW_MINIMIZED           window is minimized
   * SDL_WINDOW_MAXIMIZED           window is maximized
   * SDL_WINDOW_INPUT_GRABBED       window has grabbed input focus
   * SDL_WINDOW_ALLOW_HIGHDPI       window should be created in high-DPI mode if supported (>= SDL 2.0.1)
   **********************************************************************************************************/

  return SDL_CreateWindow(title, screen_x_pos, screen_y_pos, width, height, flags);
}

SDL_Renderer *sdl_create_renderer(SDL_Window * window, int index, int flags) {

   /**
    * index : the index of the rendering driver to initialize, or -1 to initialize the first one supporting the requested flags
    *
    * flags:
    * SDL_RENDERER_SOFTWARE       the renderer is a software fallback
    * SDL_RENDERER_ACCELERATED    the renderer uses hardware acceleration
    * SDL_RENDERER_PRESENTVSYNC   present is synchronized with the refresh rate
    * SDL_RENDERER_TARGETTEXTURE  the renderer supports rendering to texture
    *
    * Note that providing no flags gives priority to available SDL_RENDERER_ACCELERATED renderer.
    **********************************************************************************************/

  return SDL_CreateRenderer(window, (index != -1) ? index : -1, (flags <= 0) ? SDL_RENDERER_ACCELERATED : flags);
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
  return;
}

void display(SDL_Renderer * pRenderer) {
  SDL_RenderPresent(pRenderer);
  return;
}

void update(SDL_Window * pWindow) {
  SDL_UpdateWindowSurface(pWindow);
  return;
}

void clean_up(SDL_Renderer * pRenderer, SDL_Window * pWindow) {
  SDL_DestroyRenderer(pRenderer);
  SDL_DestroyWindow(pWindow);
  return;
}
