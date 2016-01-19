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
#include <time.h>

/**
 * Compilation:
 *
 * $ cc -Wall -Wextra gfxutils-screensaver.c -lm -lSDL2 -lSDL2_gfx -lSDL2_gfxutils
 *
 * ********************************************************************************/

const float factor_polygons_nb_winsize = 0.1171875f;  /** Adapt number of polygons factor in relationship to the resolution. **/
const float factor_polygons_max_size = 14.210526f;    /** Adapt size of polygons in relationship to the resolution.          **/

bool loop;

#define set_loop(x) (loop=(x))

#define MIN_SIZE  (17)

#define MIN_SPEED  (3)

#define MAX_SIDE  (25)

int sdl_init(uint32_t flags);
SDL_Window *sdl_create_window(const char *title, int screen_x_pos, int screen_y_pos, int width, int height, int flags);
SDL_Renderer *sdl_create_renderer(SDL_Window * window, int index, int flags);

void get_events(void);
void clear(SDL_Renderer * pRenderer, uint8_t bg_red, uint8_t bg_green, uint8_t bg_blue, uint8_t bg_a);
void display(SDL_Renderer * pRenderer);
void update(SDL_Window * pWindow);
void clean_up(SDL_Renderer * pRenderer, SDL_Window * pWindow);


float randomf(int max_val, float mult);

int main(int argc, char *argv[]) {

  int type_of_polygons = 1;

  int nb_of_polygon = 8;

  int max_anim_speed = 14;

  const char *usage_string = "usage: %s [polygon type [1-10]] [number of polygons] [max_speed]\n";

  fprintf(stdout, usage_string, argv[0]);

  if (argc > 1) {
 
    /** Thread commandline argument(s) if given: **/
 
    if (((type_of_polygons = (int) strtof(argv[1], NULL)) <= 0) || (type_of_polygons > 10)) {
      exit(EXIT_FAILURE);
    }


    if (argc > 2) {

      if ((nb_of_polygon = (int) strtof(argv[2], NULL)) <= 0) {
        exit(EXIT_FAILURE);
      }

      if (argc > 3) {

        if ((max_anim_speed = (int) strtof(argv[3], NULL)) <= 0) {
          exit(EXIT_FAILURE);
        }
      }
    }

  }



  if (sdl_init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL2 initialize failure: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }


  SDL_Window *pWindow = NULL;
  pWindow = sdl_create_window("gfxutils-screensaver", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, -1, -1, SDL_WINDOW_FULLSCREEN_DESKTOP);

  if (pWindow == NULL) {
    fprintf(stderr, "Fail to create SDL window: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_Renderer *pRenderer;
  if ((pRenderer = sdl_create_renderer(pWindow, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
    fprintf(stderr, "SDL Renderer creating error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }


  SDL_DisplayMode mode;

  SDL_GetCurrentDisplayMode(0, &mode);

  const int WIDTH = (int) mode.w;
  const int HEIGHT = (int) mode.h;

  if (argc < 3) {
    nb_of_polygon = (int) roundf(factor_polygons_nb_winsize * (float) (HEIGHT / 2));
  }

  const int MAX_SIZE = mode.h / factor_polygons_max_size;

  const int MAX_SPEED = max_anim_speed;

  const int MAX_POLYGON = nb_of_polygon;


  srand(time(NULL));


  int speed[MAX_POLYGON];     /** Speed of polygons containers. (change every out of screen form) **/

  Polygon *pol[MAX_POLYGON];  /** Main polygons container.      **/

  int c;

  for (c = 0; c < MAX_POLYGON; c++) {
  
    /** Start size ofthe polygons. (change every out of screen form) **/
    float size;
    if (type_of_polygons == 1 || type_of_polygons == 10 || type_of_polygons == 4 || type_of_polygons == 5) {
      while (((size = (float) (rand() % MAX_SIZE)) < MIN_SIZE) || (size <= 0.0f)) {;}
    }
    else {
      while (((size = (float) (rand() % (MAX_SIZE / 2))) < MIN_SIZE) || (size <= 0.0f)) {;}
    }
 
    /** Number of sides of the polygons (stay constant). **/
    uint32_t sides = 3;
    if ((type_of_polygons >= 4 && type_of_polygons <= 6)) {
      if (type_of_polygons == 4) {
        while (((sides = rand() % MAX_SIDE) < 6) || (360 % sides != 0)) {;}
      }
      else {
        while (((sides = rand() % MAX_SIDE) < 3) || (360 % sides != 0)) {;}
      }
    }
    else if (type_of_polygons == 2) {
      while (((sides = rand() % MAX_SIDE / 2 + 1) < 3) || (sides % 2 != 0)) {;}
    }
    else if (type_of_polygons == 7) {
      while ((sides = rand() % MAX_SIDE) < 5) {;}
    }
    else if (type_of_polygons == 10) {
      while (((sides = rand() % MAX_SIDE) < 7) || (360 % sides != 0)) {;}
    }
    else {
      while ((sides = rand() % MAX_SIDE) < 3) {;}
    }
 
    /** Start center position of the polygons. (change every out of screen form) **/
    float height;
    while ((height = (float) (rand() % (HEIGHT - ((int) (size * 2))))) <= (size * 2)) {;}

    float width;
    while (((width = (float) (rand() % WIDTH)) <= 0.0f)) {;}

    Pixel center;
    center.x = width;
    center.y = height;
 
 
    int random;
 
    /** Big switch for differents polygons types. **/
    switch (type_of_polygons) {

      case 1:

        pol[c] = generate_polygon_radius(sides, size, center, 0.0f);
        break;

      case 2:

        random = rand() % 3;

        if (random == 0) {
          pol[c] = generate_corners_rounded_polygon(sides, size, center, 0.0f);
        }
        else if (random == 1) {
          pol[c] = generate_sides_rounded_polygon(sides, size, center, 0.0f);
        }
        else if (random == 2) {
          pol[c] = generate_rounded_inside_out_polygon(sides, size, center, 0.0f);
        }

        break;

      case 3:

        random = rand() % 2;

        if (random) {
          pol[c] = generate_alternate_inside_half_circle_polygon(sides, size, center, 0.0f, false);
        }
        else {
          pol[c] = generate_alternate_outside_half_circle_polygon(sides, size, center, 0.0f, false);
        }

        break;

      case 4:

        pol[c] = generate_wheel(sides, size, center, size / 2.0f, 0.0f);
        break;

      case 5:

        pol[c] = generate_circular_saw_wheel(sides, size, center, size / 2.0f, 0.0f, rand() % 2);
        break;

      case 6:

        random = rand() % 2;

        if (random) {
          pol[c] = generate_wheel_peaks_trigon(sides, size, center, size / 2.0f, 0.0f);
        }
        else {
          pol[c] = generate_wheel_peaks_rounded_square(sides, size, center, size / 2.0f, 0.0f);
        }

        break;

      case 7:

        random = rand() % 2;

        if (random) {

          pol[c] = generate_star(sides, size, center, 0.0f);

        }
        else {

          random = rand() % 2;

          if (random) {
            pol[c] = generate_hexagram_star(size, center, 0.0f);
          }
          else {
            pol[c] = generate_pentagram_star(size, center, 0.0f);
          }

        }

        break;



      case 8:

        pol[c] = generate_hexagram(size, center, 0.0f);
        break;

      case 9:

        pol[c] = generate_pentagram(size, center, 0.0f);
        break;

      case 10:

        pol[c] = generate_fractal(sides, size, center, 0.0f, rand() % 2);
        break;

      default:
        fprintf(stderr, usage_string, argv[0]);
        exit(EXIT_FAILURE);
    }
 
 
    /** Store the start speed. **/
    uint32_t speed_anim;
    while ((speed_anim = rand() % MAX_SPEED) < MIN_SPEED) {;}
    speed[c] = speed_anim;

  }

  const int FPS = 30;
  const int FRAME_DELAY = 1000 / FPS;
  set_loop(true);
  while (loop) {

    int frame_start = SDL_GetTicks();

    clear(pRenderer, 0, 0, 0, 0);


    for (c = 0; c < MAX_POLYGON; c++) {


      if (pol[c]->center.x <= 0.0f) {
      
        /** Polygon (center) out of screen. **/
      
        float new_size;
        if (type_of_polygons == 1 || type_of_polygons == 10 || type_of_polygons == 4 || type_of_polygons == 5) {
          while ((new_size = (float) (rand() % (MAX_SIZE))) < MIN_SIZE) {;}
        }
        else {
          while ((new_size = (float) (rand() % (MAX_SIZE / 2))) < MIN_SIZE) {;}
        }
 
 
        set_form_radius(pol[c], new_size);


        float height;
        while ((height = (float) (rand() % (HEIGHT - (int) roundf(get_form_real_length(pol[c]))))) < (int) roundf(get_form_real_length(pol[c]))) {;}


        Pixel center;
        center.x = (float) (WIDTH - (int) roundf(get_form_real_length(pol[c])));
        center.y = height;
     
     
        set_form_center(pol[c], center, true);

        set_form_color(pol[c], rand() % 256, rand() % 256, rand() % 256, 255);


        uint32_t speed_anim;
        while ((speed_anim = rand() % MAX_SPEED) < MIN_SPEED) {;}
        speed[c] = speed_anim;

      }
      else {
      
        /** Polygons rotate and translate to the left at costant speed. **/        
        translate_form(pol[c], -speed[c], 0.0f);
        rotate_form(pol[c], randomf(5, 1.1f));
      }

      /** Display differents polygons types functions. **/

      if (type_of_polygons < 7 && type_of_polygons != 2) {

        uint8_t random_display = rand() % 3;

        if (random_display == 0) {
          display_polygon(pRenderer, pol[c]);
        }
        else if (random_display == 1) {
          display_strikethrough_polygon(pRenderer, pol[c]);
        }
        else if (random_display == 2) {
          display_filled_polygon(pRenderer, pol[c]);
        }
      }
      else if (type_of_polygons == 2) {

        uint8_t random_display = rand() % 2;

        if (random_display == 0) {
          display_polygon(pRenderer, pol[c]);
        }
        else if (random_display == 1) {
          display_filled_polygon(pRenderer, pol[c]);
        }
      }
      else if (type_of_polygons == 7) {

        uint8_t random_display = rand() % 2;
        if (random_display == 0) {
          display_polygon_star(pRenderer, pol[c]);
        }
        else if (random_display == 1) {
          display_filled_star(pRenderer, pol[c]);
        }
      }
      else if (type_of_polygons == 8) {
        display_hexagram(pRenderer, pol[c]);
      }
      else if (type_of_polygons == 9) {
        display_pentagram(pRenderer, pol[c]);
      }
      else if (type_of_polygons == 10) {
        display_polygon(pRenderer, pol[c]);
      }


    }

    get_events();

    display(pRenderer);

    update(pWindow);

    int frame_end = SDL_GetTicks() - frame_start;

    if (frame_end < FRAME_DELAY) {
      SDL_Delay(FRAME_DELAY - frame_end);
    }



  }

  for (c = 0; c < MAX_POLYGON; c++) {
    /** Free all polygons. **/
    free_form(pol[c]);
  }

  clean_up(pRenderer, pWindow);

  /** Quit SDL. **/
  SDL_Quit();

  exit(EXIT_SUCCESS);

}

inline float randomf(int max_val, float mult) {

  max_val++;

  float ret = (float) (rand() % max_val) * mult;

  return ret;

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

  return SDL_CreateRenderer(window, (index != -1) ? index : -1, (flags <= 0) ? SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC : flags);
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
