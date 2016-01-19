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

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * Compilation:
 *
 * $ cc -Wall -Wextra spiderweb.c -lSDL2 -lm -lSDL2_gfx -lSDL2_gfxutils
 *
 ***********************************************************************/

bool loop;

#define set_loop(x) (loop=(x))

#define WIDTH   (1024)
#define HEIGHT  ( 768)

#define MAX_RADIUS  ( HEIGHT / 2.0f)
#define MIN_RADIUS  ( 32.0f  / 2.0f)

#define MAX_SPEED   (8)


Pixel center;


int sdl_init(uint32_t flags);
SDL_Window *sdl_create_window(const char *title, int screen_x_pos, int screen_y_pos, int width, int height, int flags);
SDL_Renderer *sdl_create_renderer(SDL_Window * window, int index, int flags);

void get_events(void);
void clear(SDL_Renderer * pRenderer, uint8_t bg_red, uint8_t bg_green, uint8_t bg_blue, uint8_t bg_a);
void display(SDL_Renderer * pRenderer);
void update(SDL_Window * pWindow);
void clean_up(SDL_Renderer * pRenderer, SDL_Window * pWindow);


Form *rand_new_fractal(Form * fractal) {

  /** Getting the settings before freeing the Form. **/
  float radius = get_form_length(fractal);

  float orientation = get_form_orientation(fractal);

  /** Free the form and set the pointer on NULL. **/
  free_form(fractal);

  uint8_t poly_counter;

  while (((poly_counter = rand() % 37) < 4) || (360 % poly_counter != 0)) {;}

  fractal = generate_fractal(poly_counter, radius, center, orientation, rand() % 2);

  return fractal; /** If i don't return the pointer it crash ??? (C++ references &brainwash ?). **/

}


void form_new_colors(Form * form) {

  uint8_t red;
  uint8_t green;
  uint8_t blue;

  /** I want vivid colors !!! **/
  red = (rand() % 2 == 0) ? 255 : 127;
  green = (rand() % 2 == 0) ? 255 : 127;
  blue = (rand() % 2 == 0) ? 255 : 127;

  if (red == green && red == 255) {
    blue = 0;
  }
  else if (red == blue && red == 255) {
    green = 0;
  }
  else if (green == blue && green == 255) {
    red = 0;
  }

  set_form_color(form, red, green, blue, 255);

  return;
}


int main(void) {

  if (sdl_init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL2 initialize failure: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }


  SDL_Window *pWindow = NULL;
  pWindow = sdl_create_window("spiderweb", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

  if (pWindow == NULL) {
    fprintf(stderr, "Fail to create SDL window: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_Renderer *pRenderer;
  if ((pRenderer = sdl_create_renderer(pWindow, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
    fprintf(stderr, "SDL Renderer creating error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }



  srand(time(NULL));

  float fractal_radius = MAX_RADIUS;

  float circle_radius = MAX_RADIUS;

  center.x = (float) WIDTH / 2;
  center.y = (float) HEIGHT / 2;

  Star *poly_fractal = generate_fractal(5, fractal_radius, center, 0.0f, false);        //generate_pentagram_fractal(fractal_radius, center, 0.0f) ;

  Polygon *poly_circle = generate_polygon_radius(120, circle_radius, center, 0.0f);

  set_form_color(poly_fractal, 255, 0, 0, 255);
  set_form_color(poly_circle, 255, 255, 0, 255);






  bool go_lt_fractal = true;    /** Direction. **/
  bool go_lt_circle = true;     /** Direction. **/


  float speed_fractal = 2.0f;   /** Speed. **/
  float speed_circle = 2.0f;    /** Speed. **/

  /** If the fractal and the circle stick together. **/
  bool stick = true;

  /** Star rotation speed. **/
  float rotation_speed = 0.0f;


  const int FPS = 30;
  const int FRAME_DELAY = 1000 / FPS;
  set_loop(true);
  while (loop) {

    int frame_fractalt = SDL_GetTicks();

    if (roundf(get_form_length(poly_circle)) == roundf(get_form_length(poly_fractal)) && (roundf(get_form_length(poly_circle)) <= MIN_RADIUS || roundf(get_form_length(poly_circle)) >= MAX_RADIUS) && go_lt_circle == go_lt_fractal && !stick) {


      poly_fractal = rand_new_fractal(poly_fractal);    /** Generate a new fractal between 5-12 pikes. **/



      stick = true;             /** The fractal stick inside the circle at the interiors vertex.  **/

      go_lt_circle = go_lt_fractal = (go_lt_circle) ? false : true;     /** Invert direction. **/

      /** Set the same speed so that the circle and the fractal stay sticky. **/
      speed_fractal = 2.0f;
      speed_circle = 2.0f;

      /** Set new vivid random colors. **/
      form_new_colors(poly_fractal);
      form_new_colors(poly_circle);

      goto sticky;

    }

    /** The circle MAX and MIN polygons boundaries checks ! **/
    if (get_form_length(poly_circle) < MIN_RADIUS) {
      /** The circle minimal boundary check with the radius getter. **/
      go_lt_circle = false;
      speed_circle = 4.0f;
    }

    if (get_form_length(poly_circle) > MAX_RADIUS) {
      /** The circle maximal boundary check with the radius getter. **/
      if (stick) {
        /** Case the fractal and the circle stick together. **/
        stick = false;
        /** Random no zero loop technic. **/
        while (((rotation_speed) = rand() % MAX_SPEED) <= 0) {;}
      }

      go_lt_circle = true;
      speed_circle = 2.0f;
    }


    /** The fractal MAX and MIN polygons boundaries checks ! **/
    if (get_form_length(poly_fractal) < MIN_RADIUS) {
      /** The fractal minimal boundary check with the radius getter. **/

      /** Random no zero loop technic. **/
      while (((rotation_speed) = rand() % MAX_SPEED) <= 0) {;}

      go_lt_fractal = false;
      speed_fractal = 2.0f;
    }

    if (get_form_length(poly_fractal) > MAX_RADIUS) {
      /** The fractal maximal boundary check with the radius getter. **/

      if (stick) {
        /** Case the fractal and the circle stick together. **/
        stick = false;
        /** Random no zero loop technic. **/
        while (((rotation_speed) = rand() % MAX_SPEED) <= 0) {;}
      }

      go_lt_fractal = true;
      speed_fractal = 4.0f;
    }


  sticky:

    clear(pRenderer, 0, 0, 0, 0);
  
    display_polygon(pRenderer, poly_circle);
  
    display_polygon(pRenderer, poly_fractal);

    if (go_lt_fractal) {
      fractal_radius -= speed_fractal;
    }
    else {
      fractal_radius += speed_fractal;
    }

    if (go_lt_circle) {
      circle_radius -= speed_circle;
    }
    else {
      circle_radius += speed_circle;
    }


    set_form_radius(poly_fractal, fractal_radius);
    set_form_radius(poly_circle, circle_radius);

    if (!stick || speed_fractal != speed_circle) {
      rotate_form(poly_fractal, rotation_speed);
    }


    get_events();

    display(pRenderer);

    update(pWindow);

    int frame_end = SDL_GetTicks() - frame_fractalt;

    if (frame_end < FRAME_DELAY) {
      SDL_Delay(FRAME_DELAY - frame_end);
    }

  }

  /** Cleaning. **/
  free_form(poly_fractal);
  free_form(poly_circle);

  clean_up(pRenderer, pWindow);

  /** Quit SDL. **/
  SDL_Quit();

  exit(EXIT_SUCCESS);

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
