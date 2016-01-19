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
#include <SDL2/SDL_ttf.h>
#include <SDL2_gfxutils.h>

/** No need to #include <SDL2/SDL2_gfxPrimitives.h>
  * because <SDL2_gfxutils.h> include it.
  *************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>


#include "./ttf_utils.c"

/**
 * Compilation:
 *
 * $ cc watch.c -lm -lSDL2 -lSDL2_ttf -lSDL2_gfx -lSDL2_gfxutils
 *
 * **************************************************************/

/** This example show you that SDL2_gfxutils can be dynamic using new_form() and free_form()
  * freeing and reallocating, rotating, setting the colors from the watch pointers every 100 ms.
  **********************************************************************************************/

bool loop;

#define set_loop(x) loop=x ;

#define WIDTH  (int16_t) 800
#define HEIGHT (int16_t) 600


#define CENTER_X (int16_t) 800/2
#define CENTER_Y (int16_t) 600/2

int sdl_init(uint32_t flags);
SDL_Window *sdl_create_window(const char *title, int screen_x_pos, int screen_y_pos, int width, int height, int flags);
SDL_Renderer *sdl_create_renderer(SDL_Window * window, int index, int flags);

void get_events(void);
void clear(SDL_Renderer * pRenderer, uint8_t bg_red, uint8_t bg_green, uint8_t bg_blue, uint8_t bg_a);
void display(SDL_Renderer * pRenderer);
void update(SDL_Window * pWindow);
void clean_up(SDL_Renderer * pRenderer, SDL_Window * pWindow);

Polygon *init_pointers(uint8_t width, uint8_t height) {
  /** Initialize a new watch pointer according the given settings. **/
  Polygon *pointer = new_form(4);

  pointer->coords.x[0] = CENTER_X - width / 2;
  pointer->coords.y[0] = CENTER_Y - height;

  pointer->coords.x[1] = CENTER_X + width / 2;
  pointer->coords.y[1] = CENTER_Y - height;

  pointer->coords.x[2] = CENTER_X + width / 2;
  pointer->coords.y[2] = CENTER_Y + width / 2;

  pointer->coords.x[3] = CENTER_X - width / 2;
  pointer->coords.y[3] = CENTER_Y + width / 2;


  /** We Set the center from the pointer
    * for rotating around the watch center
    * and not the polygon center.
    *******************************************/
  pointer->center.x = CENTER_X;
  pointer->center.y = CENTER_Y;

  return (Polygon *) pointer;

}

Polygon *config_hours(void) {
  /** Update the hours pointer position. **/

  /** Getting current local time **/
  struct tm *timing;            /** This will become a static pointer: don't free it or your watch will never more work ! **/
  time_t timer = time(NULL);
  timing = localtime(&timer);   /** Return a static pointer. **/

  Polygon *ret = init_pointers(12, 160);

  set_form_color(ret, 255, 0, 0, 192);

  rotate_form(ret, 360 / 12 * timing->tm_hour + 360 / 60 * timing->tm_min / 12);

  return ret;
}


Polygon *config_minutes(void) {
  /** Update the minutes pointer position. **/

  /** Getting current local time **/
  struct tm *timing;            /** This will become a static pointer: don't free it or your watch will never more work ! **/
  time_t timer = time(NULL);
  timing = localtime(&timer);   /** Return a static pointer. **/

  Polygon *ret = init_pointers(8, 200);

  set_form_color(ret, 0, 255, 0, 160);

  rotate_form(ret, 360 / 60 * timing->tm_min);

  return ret;
}


Polygon *config_seconds(void) {
  /** Update the second pointer position. **/

  /** Getting current local time **/
  struct tm *timing;            /** This will become a static pointer: don't free it or your watch will never more work ! **/
  time_t timer = time(NULL);
  timing = localtime(&timer);   /** Return a static pointer. **/

  Polygon *ret = init_pointers(4, 240);

  set_form_color(ret, 255, 255, 0, 128);

  rotate_form(ret, 360 / 60 * timing->tm_sec);

  return ret;
}



int main(void) {

  /** SDL2 initialized: */
  if (sdl_init(SDL_INIT_VIDEO) != 0) {
    fprintf(stdout, "SDL initialize failed (%s)\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  if (TTF_Init() == -1) {
    fprintf(stdout, "SDL_ttf initialize failed (%s)\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }

  /** Window creation: */
  SDL_Window *pWindow = NULL;
  pWindow = sdl_create_window("Watch", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

  if (pWindow == NULL) {
    fprintf(stderr, "Windows creation error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  /** Renderer creation. */
  SDL_Renderer *pRenderer;
  if ((pRenderer = sdl_create_renderer(pWindow, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
    fprintf(stderr, "SDL Renderer creating error (%s)\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  int16_t c;


  Pixel center;
  center.x = CENTER_X;
  center.y = CENTER_Y;

  /** Watch frames polygons: **/
  Polygon *clock_line_exterior = generate_alternate_inside_half_circle_polygon(12, 240.0f / 2, center, 360.0f / 24.0f, true);
  Polygon *clock_line_interior = generate_alternate_outside_half_circle_polygon(12, 240.0f / 2, center, 360.0f / 24.0f, true);
  Polygon *clock_frame_exterior = generate_alternate_outside_half_circle_polygon(12, 240.0f / 2, center, 360.0f / 24.0f, true);

  Polygon *clock_frame_hours = generate_polygon_radius(48, 140, center, 360.0f / 48.0f / 2.0f);
  Polygon *clock_frame_minutes = generate_polygon_radius(48, 180, center, 360.0f / 48.0f / 2.0f);

  set_form_color(clock_line_exterior, 0, 255, 255, 160);
  set_form_color(clock_line_interior, 0, 255, 255, 160);
  set_form_color(clock_frame_exterior, 0, 127, 127, 160);
  set_form_color(clock_frame_hours, 0, 192, 192, 160);
  set_form_color(clock_frame_minutes, 0, 160, 160, 160);


  /** Watch numbers using SDL2_ttf **/
  SDL_Color text_color;
  text_color.r = 0;
  text_color.g = 192;
  text_color.b = 192;
  text_color.a = 160;

  Text *text_01 = (Text *) malloc(sizeof(Text));
  Text *text_02 = (Text *) malloc(sizeof(Text));
  Text *text_03 = (Text *) malloc(sizeof(Text));
  Text *text_04 = (Text *) malloc(sizeof(Text));
  Text *text_05 = (Text *) malloc(sizeof(Text));
  Text *text_06 = (Text *) malloc(sizeof(Text));
  Text *text_07 = (Text *) malloc(sizeof(Text));
  Text *text_08 = (Text *) malloc(sizeof(Text));
  Text *text_09 = (Text *) malloc(sizeof(Text));
  Text *text_10 = (Text *) malloc(sizeof(Text));
  Text *text_11 = (Text *) malloc(sizeof(Text));
  Text *text_12 = (Text *) malloc(sizeof(Text));

  text_01->font = TTF_OpenFont("FreeMonoBold.ttf", 38);
  text_02->font = TTF_OpenFont("FreeMonoBold.ttf", 38);
  text_03->font = TTF_OpenFont("FreeMonoBold.ttf", 38);
  text_04->font = TTF_OpenFont("FreeMonoBold.ttf", 38);
  text_05->font = TTF_OpenFont("FreeMonoBold.ttf", 38);
  text_06->font = TTF_OpenFont("FreeMonoBold.ttf", 38);
  text_07->font = TTF_OpenFont("FreeMonoBold.ttf", 38);
  text_08->font = TTF_OpenFont("FreeMonoBold.ttf", 38);
  text_09->font = TTF_OpenFont("FreeMonoBold.ttf", 38);
  text_10->font = TTF_OpenFont("FreeMonoBold.ttf", 38);
  text_11->font = TTF_OpenFont("FreeMonoBold.ttf", 38);
  text_12->font = TTF_OpenFont("FreeMonoBold.ttf", 38);

  if (text_01->font == NULL || text_02->font == NULL ||
      text_03->font == NULL || text_04->font == NULL ||
      text_05->font == NULL || text_06->font == NULL ||
      text_07->font == NULL || text_08->font == NULL ||
      text_09->font == NULL || text_10->font == NULL ||
      text_11->font == NULL || text_12->font == NULL) {
 
    fprintf(stdout, "SDL_ttf font creation error (%s)\n", TTF_GetError());
    exit(EXIT_FAILURE);

  }

  /** ./ttf_utils.c function. **/
  configure_text(pRenderer, text_01, (const char *) "1", text_color, 518, 94 + 20);
  configure_text(pRenderer, text_02, (const char *) "2", text_color, 604, 180 + 20);
  configure_text(pRenderer, text_03, (const char *) "3", text_color, 636, 300 + 20);
  configure_text(pRenderer, text_04, (const char *) "4", text_color, 604, 418 + 20);
  configure_text(pRenderer, text_05, (const char *) "5", text_color, 518, 504 + 20);
  configure_text(pRenderer, text_06, (const char *) "6", text_color, 400, 536 + 20);
  configure_text(pRenderer, text_07, (const char *) "7", text_color, 518 - 240, 504 + 20);
  configure_text(pRenderer, text_08, (const char *) "8", text_color, 604 - 408, 418 + 20);
  configure_text(pRenderer, text_09, (const char *) "9", text_color, 636 - 472, 300 + 20);
  configure_text(pRenderer, text_10, (const char *) "10", text_color, 604 - 408, 180 + 20);
  configure_text(pRenderer, text_11, (const char *) "11", text_color, 518 - 238, 94 + 20);
  configure_text(pRenderer, text_12, (const char *) "12", text_color, 400, 62 + 20);

  /** Initialize watch pointers for displaying. **/
  Polygon *hours = config_hours();
  Polygon *minutes = config_minutes();
  Polygon *seconds = config_seconds();


  set_loop(true);
  while (loop) {

    clear(pRenderer, 0, 0, 0, 255);


    /** Displaying the watch frames. **/
    display_filled_polygon(pRenderer, clock_frame_exterior);

    aa_display_polygon(pRenderer, clock_line_exterior);
    aa_display_polygon(pRenderer, clock_line_interior);

    display_filled_polygon(pRenderer, clock_frame_hours);

    display_filled_polygon(pRenderer, clock_frame_minutes);


    /** Displaying the watch numbers using SDL2_ttf. **/
    render_text(pRenderer, text_01);
    render_text(pRenderer, text_02);
    render_text(pRenderer, text_03);
    render_text(pRenderer, text_04);
    render_text(pRenderer, text_05);
    render_text(pRenderer, text_06);
    render_text(pRenderer, text_07);
    render_text(pRenderer, text_08);
    render_text(pRenderer, text_09);
    render_text(pRenderer, text_10);
    render_text(pRenderer, text_11);
    render_text(pRenderer, text_12);

    /** Hours pointer: **/
    free_form(hours);
    hours = config_hours();
    display_filled_polygon(pRenderer, hours);

    /** Minutes pointer: **/
    free_form(minutes);
    minutes = config_minutes();
    display_filled_polygon(pRenderer, minutes);

    /** Seconds pointer: **/
    free_form(seconds);
    seconds = config_seconds();
    display_filled_polygon(pRenderer, seconds);


    display(pRenderer);
    update(pWindow);

    get_events();

    usleep(100000);

    c++;
  }



  clean_up(pRenderer, pWindow);

  /** Cleaning SDL2_gfxutils dynamic allocated forms. **/
  free_form(clock_line_exterior);
  free_form(clock_line_interior);
  free_form(clock_frame_exterior);
  free_form(clock_frame_hours);
  free_form(clock_frame_minutes);
  free_form(hours);
  free_form(minutes);
  free_form(seconds);


  /** SDL2 quit. **/
  TTF_Quit();
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
