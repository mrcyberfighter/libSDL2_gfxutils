SDL2_gfxutils header file
=========================

.. code-block:: c

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

  #ifndef SDL2_GFXUTILS_HH  /** SDL2_gfxutils inclusion guard **/
  #define SDL2_GFXUTILS_HH  /** SDL2_gfxutils inclusion guard **/

  #include <SDL2/SDL.h>
  #include <SDL2/SDL2_gfxPrimitives.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <stdbool.h>
  #include <stdint.h>
  #include <math.h>

  /* Définition of macro EXTERN_C for C++ compatibility */
  #ifndef EXTERN_C
  #ifdef __cplusplus
  #define EXTERN_C extern "C"
  #else
  #define EXTERN_C
  #endif
  #endif

  typedef struct Color_ {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
  } Color;


  typedef struct Pixel_ {
    float x;
    float y;
  } Pixel;

  typedef struct Segment_ {
    Pixel xy1;
    Pixel xy2;
    Color color;
  } Line;

  typedef struct Coords_ {
    float *x;
    float *y;
  } Coords;

  typedef struct Polygon_ {
    Coords coords;
    Pixel center;
    Color color;
    uint16_t count;
    float length;
    float real_length;
    float orientation;
  } Polygon;

  typedef Polygon Arc;
  typedef Polygon Hexagram;
  typedef Polygon Pentagram;
  typedef Polygon Star;
  typedef Polygon Spiral;


  typedef Polygon Form;
  typedef Arc Form;
  typedef Hexagram Form;
  typedef Pentagram Form;
  typedef Spiral Form;
  typedef Star Form;



  /** Base functions:
    ****************/


  /** This function return an pixel initialized in relationship to the given settings. **/
  EXTERN_C Pixel get_pixel_coords(uint32_t position, uint32_t scale, float length, Pixel center, float orientation);


  /** This function compute the pixel middle point from the given line. **/
  EXTERN_C Pixel get_middle_from_line(Line line);


  /** Return a pointer on a Line starting at start_point, from length length, incline from angle.
    *********************************************************************************************/
  EXTERN_C Line *generate_segment(Pixel start_point, float length, float angle);


  /** Generate an arc from radius radius, from center center,
    * length from part of an circle circle_part,
    * starting at offset start_pos.
    ********************************************************/
  EXTERN_C Arc *generate_circle_arc(float radius, Pixel center, float start_pos, float circle_part);

  /** ************************************************************************************************** **/



  /** Polygons:
    ***********/

  /** Return an regular convex polygon according to the given settings.
    * with sides sides, with radius length radius, having for center center, incline according orientation.
    *******************************************************************************************************/
  EXTERN_C Polygon *generate_polygon_radius(uint32_t sides, float radius, Pixel center, float orientation);

  /** Generated an polygon which corners are arcs
    * with sides sides, with radius length radius, having for center center, incline according orientation.
    *******************************************************************************************************/
  EXTERN_C Polygon *generate_corners_rounded_polygon(uint32_t sides, float radius, Pixel center, float orientation);

  /** Generate an polygon which sides are arcs.
    * with sides sides, with radius length radius, having for center center, incline according orientation.
    *******************************************************************************************************/
  EXTERN_C Polygon *generate_sides_rounded_polygon(uint32_t sides, float radius, Pixel center, float orientation);

  /** Generated an rounded polygon alternating arcs rounded to the outside and to the inside of the polygon.
    * with sides sides, with radius length radius, having for center center, incline according orientation.
    ********************************************************************************************************/
  EXTERN_C Polygon *generate_rounded_inside_out_polygon(uint32_t sides, float radius, Pixel center, float orientation);

  /** Generated an polygon with half-circle rounded to the inside from the half sum from the sides of the polygon
    * and the other half is even an arc or an straight line according to the side_arcs boolean value.
    * with sides sides, with radius length radius, having for center center, incline according orientation.
    *************************************************************************************************************/
  EXTERN_C Polygon *generate_alternate_inside_half_circle_polygon(uint32_t sides, float radius, Pixel center, float orientation, bool side_arcs);

  /** Generated an polygon with half-circle rounded to the outside from the half sum from the sides of the polygon
    * and the other half is even an arc or an straight line according to the side_arcs boolean value.
    * with sides sides, with radius length radius, having for center center, incline according orientation.
    **************************************************************************************************************/
  EXTERN_C Polygon *generate_alternate_outside_half_circle_polygon(uint32_t sides, float radius, Pixel center, float orientation, bool side_arcs);

  /** ******************************************************************************************************************************** **/




  /** Pentagram:
    ************/

  /** Generate an 5 extremity star with an centered pentagon from which every vertex go to the center.
    * From radius radius, having for center center, incline according orientation.
    **************************************************************************************************/
  EXTERN_C Pentagram *generate_pentagram(float radius, Pixel center, float orientation);

  /** Generate an 5 extremity star.
    * With the particularity that the resulting star is not an regular star but an pentagram star.
    * From radius radius, having for center center, incline according orientation.
    **********************************************************************************************/
  EXTERN_C Star *generate_pentagram_star(float radius, Pixel center, float orientation);

  /** ********************************************************************** **/



  /** Hexagram:
    ***********/

  /** Generate an 5 extremity star with an centered hexagon from which every vertex go to the center.
    * From radius radius, having for center center, incline according orientation.
    *************************************************************************************************/
  EXTERN_C Hexagram *generate_hexagram(float radius, Pixel center, float orientation);

  /** Generate an 6 extremity star.
    * With the particularity that the resulting star is not an regular star but an hexagram star.
    * From radius radius, having for center center, incline according orientation.
    *********************************************************************************************/
  EXTERN_C Star *generate_hexagram_star(float radius, Pixel center, float orientation);

  /** ********************************************************************* **/



  /** Stars:
    ********/

  /** generate an simply star with the wanted settings:
   *  with pikes number of pikes,
   *  from radius radius,
   *  having for center center,
   *  incline according orientation.
   ****************************************************/
  EXTERN_C Star *generate_star(uint32_t pikes, float radius, Pixel center, float orientation);

  /** ************************************************************************* **/



  /** Wheels:
   *********/

  /** Generate an pointed wheel accoridng the given settings.
    * With polygon as base polygon, having for center center, from radius radius, incline according orientation.
    ************************************************************************************************************/
  EXTERN_C Polygon *generate_wheel(uint32_t polygon, float radius, Pixel center, float offset, float orientation);

  /** Generate an circular saw like wheel.
    * With polygon as base polygon, having for center center, as points size offset even reversed.
    **********************************************************************************************/
  EXTERN_C Polygon *generate_circular_saw_wheel(uint32_t polygon, float radius, Pixel center, float offset, float orientation, bool reverse);

  /** Generate an wheel (rounded polygon) with peaking as triangles which peaks ate very little arcs.
    * With polygon as base polygon, having for center center, from peak size peak_offset, incline according orientation.
    ********************************************************************************************************************/
  EXTERN_C Polygon *generate_wheel_peaks_trigon(uint32_t sides, float radius, Pixel center, float peak_offset, float orientation);

  /** Generate an wheel (rounded polygon) with peaks looking like a tube but they are only right-angled line to the sides connected trough an arc.
    * With polygon as base polygon, having for center center, from peak size peak_length, incline according orientation.
    **********************************************************************************************************************************************/
  EXTERN_C Polygon *generate_wheel_peaks_rounded_square(uint32_t sides, float radius, Pixel center, float peak_length, float orientation);

  /** **************************************************************************************************************************** **/


  /** Spiral:
    ********/

  /** Generate a spiral.
    * making turns revolutions, having for center center, base rounded, with offset betwen the turns offset_exponent.
    *****************************************************************************************************************/ 
  EXTERN_C Spiral *generate_simple_spiral(Pixel center, uint32_t turns, uint32_t base, float offset_exponent, float orientation, _Bool reverse);

  /** **************************************************************************************************************************** **/

  /** fractal:
    *********/

  /** Generate a star-like fractal.
    * With polygon as base polygon, having for center center, from radius radius, incline according orientation, open change the issue form.
    ****************************************************************************************************************************************/
  EXTERN_C Polygon *generate_fractal(uint32_t polygon, float radius, Pixel center, float orientation, bool open);

  /** ************************************************************************************************ **/



  /** @Pixels operations:
    ********************/

  /** Return a rotate a pixel around a center from the value angle in clock sens.
    *****************************************************************************/
  EXTERN_C Pixel rotate(Pixel center, float angle, Pixel pixel);

  /** Mirror a pixel on an axes.
    * pixel    = the pixel to mirror.
    * center   = the center for mirroring.
    * axes     = the mirror axes ['X'|'Y'].
    *****************************************/
  EXTERN_C Pixel mirror(Pixel pixel, Pixel center, char axes);

  /** Return the new position from pixel scaled by factor:
    * factor < 1 == scaling littler.
    * factor > 1 == scaling greater.
    ******************************************************/
  EXTERN_C Pixel scale(Pixel center, float factor, Pixel pixel);

  /** Return a translated pixel from value x and y.
    ***********************************************/
  EXTERN_C Pixel translate(Pixel pixel, float x, float y);

  /** *********************************************** **/



  /** @Forms operations:
    *******************/

  /** Rotate a form from angles degrees.
    ************************************/
  EXTERN_C void rotate_form(Form * form, float angle);

  /** Mirror a Form through the axes axes ['X'|'Y'].
    ************************************************/
  EXTERN_C void mirror_form(Form * form, Pixel center, char axes);

  /** Scale a Form from factor factor.
    * if factor > 1.0 the size of the form increase.
    * if factor < 1.0 the size from the form decrease.
    **************************************************/
  EXTERN_C void scale_form(Form * form, float factor);

  /** Translate a Form from (x, y) pixels .
    ***************************************/
  EXTERN_C void translate_form(Form * form, float x, float y);

  /** Remove doubles coordinates from Form from.
    ********************************************/
  EXTERN_C Form *remove_doubles_form(Form * form);

  /** ************************************************ **/



  /** Setters:
    **********/

  /** Set a new center to from Form form and
    * even translate all the form according to the new center.
    **********************************************************/
  EXTERN_C void set_form_center(Form * form, Pixel center, bool translate);

  /** Set a new radius to from Form form and
    * scale the form according to the new radius.
    *********************************************/
  EXTERN_C void set_form_radius(Form * form, float radius);

  /** Set the colors of the Form form.
    **********************************/
  EXTERN_C void set_form_color(Form * form, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

  /** Set the colors of the Line line.
    **********************************/
  EXTERN_C void set_line_color(Line * line, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

  /** *********************************************************************************** **/



  /** Getters:
    *********/

  /** Return the current center from the Form form.
    ***********************************************/
  EXTERN_C Pixel get_form_center(Form * form);

  /** Return the current color from the Form form.
    ***********************************************/
  EXTERN_C Color get_form_color(Form * form);

  /** Return the current length from the Form form.
    * The length member is often the radius @see documentation.
    ***********************************************************/
  EXTERN_C float get_form_length(Form * form);

  /** Return the current real length from the Form form.
    * The real length member is the distance between the center and the farest point from it.
    *****************************************************************************************/
  EXTERN_C float get_form_real_length(Form * form);

  /** Return the current orientation from the Form form.
    ****************************************************/
  EXTERN_C float get_form_orientation(Form * form);

  /** ********************************* **/



  /** Geometry utils:
    ****************/

  /** Return the angle for the given arguments.
    *******************************************/
  EXTERN_C float get_angle(int position, float scale, float orientation);

  /** Return the distance between px1(x,y) and px2(x,y).
    ****************************************************/
  EXTERN_C float get_distance_pixels(Pixel px1, Pixel px2);

  /** ******************************************************** **/



  /** Displaying forms:
   *******************/

  /** @Forms normal displaying:
    **************************/

  /** Display the Line line according to his settings
    * @return 0 on success, -1 on failure.
    *************************************************/
  EXTERN_C int display_line(SDL_Renderer * pRenderer, Line * line);

  /** Display the Arc arc according to his settings
    * @return 0 on success, -1 on failure.
    ************************************************/
  EXTERN_C int display_arc(SDL_Renderer * pRenderer, Arc * arc);

  /** Display the Form polygon according to his settings
    * @return 0 on success, -1 on failure.
    ****************************************************/
  EXTERN_C int display_polygon(SDL_Renderer * pRenderer, Form * polygon);

  /** Display the Form polygon strikethrough according to his settings
    * @return 0 on success, -1 on failure.
    ******************************************************************/
  EXTERN_C int display_strikethrough_polygon(SDL_Renderer * pRenderer, Form * polygon);

  /** Display the Form polygon filled according to his settings
    * @return 0 on success, -1 on failure.
    ***********************************************************/
  EXTERN_C int display_filled_polygon(SDL_Renderer * pRenderer, Form * polygon);


  /** Display the Pentagram pentagram according to his settings
    * @return 0 on success, -1 on failure.
    ***********************************************************/
  EXTERN_C int display_pentagram(SDL_Renderer * pRenderer, Pentagram * pentagram);

  /** Display the Hexagram Hexagram according to his settings
    * @return 0 on success, -1 on failure.
    *********************************************************/
  EXTERN_C int display_hexagram(SDL_Renderer * pRenderer, Hexagram * hexagram);

  /** Display the Star star according to his settings
    * @return 0 on success, -1 on failure.
    *************************************************/
  EXTERN_C int display_star(SDL_Renderer * pRenderer, Star * star);

  /** Display the Star star flower-like according to his settings
    * @return 0 on success, -1 on failure.
    **************************************************************/
  EXTERN_C int display_flower_star(SDL_Renderer * pRenderer, Star * star);

  /** Display the Star star strikethrough according to his settings
    * @return 0 on success, -1 on failure.
    ***************************************************************/
  EXTERN_C int display_strikethrough_star(SDL_Renderer * pRenderer, Star * star_striketrough);

  /** Display the Star star polygon according to his settings
    * @return 0 on success, -1 on failure.
    *********************************************************/
  EXTERN_C int display_polygon_star(SDL_Renderer * pRenderer, Star * star);

  /** Display the Star star filled according to his settings
    * @return 0 on success, -1 on failure.
    ********************************************************/
  EXTERN_C int display_filled_star(SDL_Renderer * pRenderer, Star * star);

  /** Display the Spiral spiral according to his settings
    * @return 0 on success, -1 on failure.
    *****************************************************/
  EXTERN_C int display_spiral(SDL_Renderer * pRenderer, Spiral * spiral);

  /** *************************************************************************** **/



  /** @Forms thickness displaying:
    ******************************/

  /** Display the Line line according to his settings
    * @return 0 on success, -1 on failure.
    *************************************************/
  EXTERN_C int display_line_thick(SDL_Renderer * pRenderer, Line * line, uint8_t thickness);

  /** Display the Arc arc according to his settings
    * @return 0 on success, -1 on failure.
    ************************************************/
  EXTERN_C int display_arc_thick(SDL_Renderer * pRenderer, Arc * arc, uint8_t thickness);

  /** Display the Form polygon according to his settings
    * @return 0 on success, -1 on failure.
    ****************************************************/
  EXTERN_C int display_polygon_thick(SDL_Renderer * pRenderer, Form * polygon, uint8_t thickness);

  /** Display the Form polygon strikethrough according to his settings
    * @return 0 on success, -1 on failure.
    ******************************************************************/
  EXTERN_C int display_strikethrough_polygon_thick(SDL_Renderer * pRenderer, Form * polygon, uint8_t thickness);

  /** Display the Pentagram pentagram according to his settings
    * @return 0 on success, -1 on failure.
    ***********************************************************/
  EXTERN_C int display_pentagram_thick(SDL_Renderer * pRenderer, Pentagram * pentagram, uint8_t thickness);

  /** Display the Hexagram Hexagram according to his settings
    * @return 0 on success, -1 on failure.
    *********************************************************/
  EXTERN_C int display_hexagram_thick(SDL_Renderer * pRenderer, Hexagram * hexagram, uint8_t thickness);

  /** Display the Star star according to his settings
    * @return 0 on success, -1 on failure.
    *************************************************/
  EXTERN_C int display_star_thick(SDL_Renderer * pRenderer, Star * star, uint8_t thickness);

  /** Display the Star star flower-like according to his settings
    * @return 0 on success, -1 on failure.
    **************************************************************/
  EXTERN_C int display_flower_star_thick(SDL_Renderer * pRenderer, Star * star, uint8_t thickness);

  /** Display the Star star strikethrough according to his settings
    * @return 0 on success, -1 on failure.
    ***************************************************************/
  EXTERN_C int display_strikethrough_star_thick(SDL_Renderer * pRenderer, Star * star_striketrough, uint8_t thickness);

  /** Display the Star star polygon according to his settings
    * @return 0 on success, -1 on failure.
    *********************************************************/
  EXTERN_C int display_polygon_star_thick(SDL_Renderer * pRenderer, Star * star, uint8_t thickness);

  /** Display the Spiral spiral according to his settings
    * @return 0 on success, -1 on failure.
    *****************************************************/
  EXTERN_C int display_spiral_thick(SDL_Renderer * pRenderer, Spiral * spiral, uint8_t thickness);

  /** **************************************************************************************************** **/



  /** @Forms anti-aliasing displaying:
    *********************************/

  /** Display the Line line according to his settings
    * @return 0 on success, -1 on failure.
    *************************************************/
  EXTERN_C int aa_display_line(SDL_Renderer * pRenderer, Line * line);

  /** Display the Arc arc according to his settings
    * @return 0 on success, -1 on failure.
    ************************************************/
  EXTERN_C int aa_display_arc(SDL_Renderer * pRenderer, Arc * arc);

  /** Display the Form polygon according to his settings
    * @return 0 on success, -1 on failure.
    ****************************************************/
  EXTERN_C int aa_display_polygon(SDL_Renderer * pRenderer, Form * polygon);

  /** Display the Form polygon strikethrough according to his settings
    * @return 0 on success, -1 on failure.
    ******************************************************************/
  EXTERN_C int aa_display_strikethrough_polygon(SDL_Renderer * pRenderer, Form * polygon);

  /** Display the Pentagram pentagram according to his settings
    * @return 0 on success, -1 on failure.
    ***********************************************************/
  EXTERN_C int aa_display_pentagram(SDL_Renderer * pRenderer, Pentagram * pentagram);

  /** Display the Hexagram Hexagram according to his settings
    * @return 0 on success, -1 on failure.
    *********************************************************/
  EXTERN_C int aa_display_hexagram(SDL_Renderer * pRenderer, Pentagram * hexagram);

  /** Display the Star star according to his settings
    * @return 0 on success, -1 on failure.
    *************************************************/
  EXTERN_C int aa_display_star(SDL_Renderer * pRenderer, Star * star);

  /** Display the Star star flower-like according to his settings
    * @return 0 on success, -1 on failure.
    **************************************************************/
  EXTERN_C int aa_display_flower_star(SDL_Renderer * pRenderer, Star * star);

  /** Display the Star star strikethrough according to his settings
    * @return 0 on success, -1 on failure.
    ***************************************************************/
  EXTERN_C int aa_display_strikethrough_star(SDL_Renderer * pRenderer, Star * star);

  /** Display the Star star polygon according to his settings
    * @return 0 on success, -1 on failure.
    *********************************************************/
  EXTERN_C int aa_display_polygon_star(SDL_Renderer * pRenderer, Star * star);

  /** Display the Spiral spiral according to his settings
    * @return 0 on success, -1 on failure.
    *****************************************************/
  EXTERN_C int aa_display_spiral(SDL_Renderer * pRenderer, Spiral * spiral);

  /** *********************************************************************** **/



  /** Memory:
    ********/

  /** Free the given Form form
    * 1. the coordinates arrays.
    * 2. the form.
    * And set the pointer on NULL
    *****************************/
  EXTERN_C void free_form(Form * form);

  /** Allocate space for a new Form:
    *******************************/
  EXTERN_C Form *new_form(uint32_t count);

  /** ************************* **/



  /** Utils:
    *******/

  /** Check if the SDL2_Renderer is valid.
    **************************************/
  EXTERN_C void check_renderer(SDL_Renderer * pRenderer);

  /** Check if form != NULL
    ***********************/
  EXTERN_C void check_form(Form * form);

  /** *************************************** **/


  /** Miscealeanous:
    ***************/

  /** Generate an animation guideline.
    * By filling an Pixel array.
    **********************************/
  EXTERN_C void compute_trajectory(Pixel positions[], Line * trajectory, uint32_t steps);

  #endif  /** SDL2_gfxutils inclusion guard **/
