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

#include "../SDL2_gfxutils.h"

Spiral *generate_simple_spiral(Pixel center, uint32_t turns, uint32_t base, float offset_exponent, float orientation, _Bool reverse) {
  /** Generate an spiral according following settings:
    *
    * center:          the center of the spiral starts from.
    * turns:           the number of turns around the center the spiral make.
    * base:            the base number of points to make one turn (divided per 2).
    * offset_exponent: the distance of space for the spiral progression.
    * orientation:     start position in degrees angle values.
    * reverse:         drive the spiral reversed.
    *
    * @NOTE: if you generate too much vertice your application will block.
    *        So use only 1 or few spirals from reasonable size(s).
    *        By setting a new radius (a spiral doesn't really have a radius) take care of size limits.
    *        The radius from the spiral is computed as the distance between the center and the endpoint.
    *        // This limitations are due of the int16_t type used from the SDL2_gfx standart.
    *        // @see the display function from SDL2_gfx.
    *************************************************************************************************************/

  /** @NOTE: the radius is the end of the first entire revolution of the spiral.
   *****************************************************************************/


  if (base <= 11) {
    fprintf(stderr, "base argument value to little: base must be base > 11 !\n");
    exit(EXIT_FAILURE);
  }

  if (turns <= 0) {
    fprintf(stderr, "turns argument value to little: turns must be turns > 0 !\n");
    exit(EXIT_FAILURE);
  }

  /** Compute the angle between 2 points from the spiral **/
  float round_offset = 360.0f / base;

  int32_t c, cc, ii;

  uint32_t points_count = (uint32_t) 360.0f / round_offset;

  /** Array of relative angles between 2 points from one turn. **/
  float base_point_range[points_count];

  float turn_iterator;

  for (turn_iterator = 0.0f, c = 0; turn_iterator <= 360.0f; turn_iterator += round_offset, c++) {
    /** Generate the angles offsets. **/
    base_point_range[c] = turn_iterator;
  }


  c = 0;
  cc = points_count;
  while (c < points_count) {
    /** Reverse the angles offsets array. **/

    float tmp;
    tmp = base_point_range[c];
    base_point_range[c] = base_point_range[cc];
    base_point_range[cc] = tmp;

    c++;
    cc--;
  }

  /** Result spiral **/
  Spiral *spiral = (Spiral *) malloc(sizeof(Spiral));

  spiral->count = turns * points_count;

  spiral->coords.x = (float *) calloc((size_t) spiral->count, sizeof(float));
  spiral->coords.y = (float *) calloc((size_t) spiral->count, sizeof(float));

  float distance = offset_exponent;
  float incr = offset_exponent;

  Pixel radius;

  ii = 0;
  if (!reverse) {
    c = 0;
    while (c < turns) {
      /** Generate a turn from the spiral **/
      cc = 0;
      while (cc < points_count) {
        /** Setting every pixel from the turn: **/
        Pixel res;

        res = get_pixel_coords(cc, base, distance, center, base_point_range[cc]);

        spiral->coords.x[ii] = res.x;
        spiral->coords.y[ii] = res.y;

        if (cc == points_count - 1 && c == 0) {

          radius = res;
        }


        cc++;
        ii++;
        distance += incr;



      }
      c++;
    }
  }
  else {
    c = 0;
    ii = 0;
    while (c < turns) {
        /** Generate a turn from the spiral **/
      cc = points_count - 1;
      while (cc >= 0) {
          /** Setting every pixel from the turn: **/

        Pixel res;

        res = get_pixel_coords(cc, base, distance, center, base_point_range[cc]);

        spiral->coords.x[ii] = res.x;
        spiral->coords.y[ii] = res.y;

        if (cc == 0 && c == 0) {
          radius = res;
        }


        ii++;
        cc--;

        distance += incr;

      }
      c++;
    }
  }

  c = 0;

  if (orientation) {
    rotate_form(spiral, orientation);

  }

  Pixel px;
  px.x = spiral->coords.x[spiral->count - 1];
  px.y = spiral->coords.y[spiral->count - 1];

  spiral->center.x = center.x;
  spiral->center.y = center.y;

  spiral->length = get_distance_pixels(spiral->center, radius);

  spiral->orientation = orientation;

  spiral->real_length = get_distance_pixels(spiral->center, px);

  return spiral;

}
