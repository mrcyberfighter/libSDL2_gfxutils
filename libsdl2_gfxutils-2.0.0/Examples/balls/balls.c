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
#include <sys/time.h>



/**
 * Compilation:
 *
 * $ cc -Wall -Wextra balls.c -lm -lSDL2 -lSDL2_gfx -lSDL2_gfxutils
 *
 * *********************************************************************/

bool loop;

#define set_loop(x) loop=x ;

#define WIDTH  (int16_t) 800
#define HEIGHT (int16_t) 600


#define CENTER_X (int) WIDTH/2
#define CENTER_Y (int) HEIGHT/2


int sdl_init(uint32_t flags);
SDL_Window *sdl_create_window(const char *title, int screen_x_pos, int screen_y_pos, int width, int height, int flags);
SDL_Renderer *sdl_create_renderer(SDL_Window * window, int index, int flags);

void get_events(void);
void clear(SDL_Renderer * pRenderer, uint8_t bg_red, uint8_t bg_green, uint8_t bg_blue, uint8_t bg_a);
void display(SDL_Renderer * pRenderer);
void update(SDL_Window * pWindow);
void clean_up(SDL_Renderer * pRenderer, SDL_Window * pWindow);



typedef struct Ball_ {
  /** Ball data holding structure. **/

  Polygon *ball[25];

  int16_t incr_x;   /** x increment position changing value. **/
  int16_t incr_y;   /** y increment position changing value. **/

} Ball;


inline uint8_t get_color_gradient(uint8_t c) {
  return (c + 1) * (51 / 5) + 5;
}

inline int get_rand(int modulo) {
  /** Return a random value. **/
  uint32_t random ;
  return ((random=rand() % modulo) == 0) ? 3 : random ;
}

Ball *init_ball(char color) {

  Ball *ball = (Ball *) malloc(sizeof(Ball));

  Pixel center;
  center.x = CENTER_X;
  center.y = CENTER_Y;

  uint8_t c;

  float radius = 25.0f;

  for (c = 0; c < 25; c++) {

    ball->ball[c] = generate_polygon_radius(24, radius, center, 0);

    switch (color) {

      case 'r':  /** Red **/
        set_form_color(ball->ball[c], get_color_gradient(c), 0, 0, 255);
        break;

      case 'g':  /** Green **/
        set_form_color(ball->ball[c], 0, get_color_gradient(c), 0, 255);
        break;

      case 'b':  /** Blue **/
        set_form_color(ball->ball[c], 0, get_color_gradient(c), 0, 255);
        break;

      case 'y':  /** Yellow **/
        set_form_color(ball->ball[c], get_color_gradient(c), get_color_gradient(c), 0, 255);
        break;

      case 'p':  /** Pink **/
        set_form_color(ball->ball[c], get_color_gradient(c), 0, get_color_gradient(c), 255);
        break;

      case 't':  /** Turquoise **/
        set_form_color(ball->ball[c], 0, get_color_gradient(c), get_color_gradient(c), 255);
        break;

    }

    radius -= 1.0f;

  }

  ball->incr_x = get_rand(8);
  ball->incr_y = get_rand(8);

  return ball;
}

void translate_ball(Ball * ball) {

  /** Move a ball forward in the current direction.
    ***********************************************/

  uint8_t c;

  for (c = 0; c < 25; c++) {
    translate_form(ball->ball[c], ball->incr_x, ball->incr_y);
  }

  return;
}


void check_collide_borders(Ball * ball) {

  /** Check if the ball collide a border.
    * If yes change the value from the incr_x and incr_y members.
    *************************************************************/

  if (ball->ball[0]->center.x <= 64) {
    ball->incr_x = get_rand(16);
    int random = get_rand(16);
    ball->incr_y = (random % 2) ? random : -random;
    return;
  }
  else if (ball->ball[0]->center.x >= 800 - 64) {
    ball->incr_x = -get_rand(16);
    int random = get_rand(16);
    ball->incr_y = (random % 2) ? random : -random;
    return;
  }

  if (ball->ball[0]->center.y <= 64) {
    ball->incr_y = get_rand(16);
    int random = get_rand(16);
    ball->incr_x = (random % 2) ? random : -random;
    return;
  }
  else if (ball->ball[0]->center.y >= 600 - 64) {
    ball->incr_y = -get_rand(16);
    int random = get_rand(16);
    ball->incr_x = (random % 2) ? random : -random;
    return;
  }

  return;

}

void display_ball(SDL_Renderer * pRenderer, Ball * ball) {

  /** Ball displaying function. **/

  uint8_t c;
  for (c = 0; c < 25; c++) {
    display_filled_polygon(pRenderer, ball->ball[c]);
  }

  return;

}



void free_ball(Ball * ball) {

  /** Free a Ball **/

  uint8_t c;
  for (c = 0; c < 25; c++) {
    /** Free the Form member. **/
    free_form(ball->ball[c]);
  }

  /** Free Ball type pointer. **/
  free(ball);

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
  pWindow = sdl_create_window("Balls", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

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

  /** Random seed initialized. **/
  struct timeval tv;
  gettimeofday(&tv, NULL);

  srand((unsigned int) tv.tv_usec);


  /** Define the balls and initialized the balls. **/
  Ball *red_ball = init_ball('r');
  Ball *green_ball = init_ball('g');
  Ball *blue_ball = init_ball('b');
  Ball *yellow_ball = init_ball('y');
  Ball *pink_ball = init_ball('p');
  Ball *turquoise_ball = init_ball('t');

  const int FPS = 90;
  const int FRAME_DELAY = 1000 / FPS;

  set_loop(true);
  while (loop) {

    /** SDL2 mainloop. **/

    int frame_start = SDL_GetTicks();

    /** Check if a ball collide the border rounded box: **/
    check_collide_borders(red_ball);
    check_collide_borders(green_ball);
    check_collide_borders(blue_ball);
    check_collide_borders(yellow_ball);
    check_collide_borders(pink_ball);
    check_collide_borders(turquoise_ball);


    /** Increment the balls positions: **/
    translate_ball(red_ball);
    translate_ball(green_ball);
    translate_ball(blue_ball);
    translate_ball(yellow_ball);
    translate_ball(pink_ball);
    translate_ball(turquoise_ball);


    clear(pRenderer, 127, 127, 127, 127);


    /** Displaying the interior black boxe using a SDL2_gfx function. **/
    boxRGBA(pRenderer, 32, 32, WIDTH - 32, HEIGHT - 32, 0, 0, 0, 255);

    /** Display the balls: **/
    display_ball(pRenderer, red_ball);
    display_ball(pRenderer, green_ball);
    display_ball(pRenderer, blue_ball);
    display_ball(pRenderer, yellow_ball);
    display_ball(pRenderer, pink_ball);
    display_ball(pRenderer, turquoise_ball);


    display(pRenderer);
    update(pWindow);

    get_events();

    int frame_end = SDL_GetTicks() - frame_start;

    if (frame_end < FRAME_DELAY) {
      SDL_Delay(FRAME_DELAY - frame_end);
    }

  }


  free_ball(red_ball);
  free_ball(green_ball);
  free_ball(blue_ball);
  free_ball(yellow_ball);
  free_ball(pink_ball);
  free_ball(turquoise_ball);


  clean_up(pRenderer, pWindow);

  SDL_Quit();

  exit(EXIT_SUCCESS);

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
