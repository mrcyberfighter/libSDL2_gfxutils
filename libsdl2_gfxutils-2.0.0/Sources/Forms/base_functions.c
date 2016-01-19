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

Pixel get_pixel_coords(uint32_t position, uint32_t scale, float length, Pixel center, float orientation) {

  Pixel res_px;

  /** Get the angle from position in the circle where 3 o'clock
    * is orientation == 0  ; divided in scale units.             **/
  float angle_degrees = get_angle(position, scale, orientation);


  /** Conversion angle in degrees to radians **/
  float radians = angle_degrees / 180.0 * M_PI;

  res_px.x = cosf(radians) * length + center.x;
  res_px.y = sinf(radians) * length + center.y;

  return res_px;

}

Pixel get_middle_from_line(Line line) {

  Pixel res_px;

  res_px.x = (line.xy1.x + line.xy2.x) / 2.0;
  res_px.y = (line.xy1.y + line.xy2.y) / 2.0;


  return res_px;
}


Line *generate_segment(Pixel start_point, float length, float angle) {
  /** Return an Line starting at start_point from length length incline from angle.
    * @angle: 3 o'clock is zero degree.
    *******************************************************************************/

  Line *res = (Line *) malloc(sizeof(Line));

  res->xy1.x = start_point.x;
  res->xy1.y = start_point.y;

  float degrees = 360.0f + angle;

  float radians = (float) (degrees / 180.0f * M_PI);

  res->xy2.x = cosf(radians) * length + start_point.x;
  res->xy2.y = sinf(radians) * length + start_point.y;



  return res;

}

Arc *generate_circle_arc(float radius, Pixel center, float start_pos, float circle_part) {
  /** Generate an arc from radius radius
    * from center center
    * length from part of an circle circle_part
    * starting at offset start_pos.
    *******************************************/

  if (circle_part == 0.0f) {

    fprintf(stderr, "Wrong argument circle_part: circle_part != 0.0f !\n");
    return NULL;
  }

  Arc *res = (Arc *) malloc(sizeof(Arc));



  res->count = (uint16_t) roundf(360.0f / (360.0f / circle_part));

  res->count = (res->count <= 0) ? 1 : res->count;

  res->coords.x = (float *) calloc((size_t) res->count, sizeof(float));
  res->coords.y = (float *) calloc((size_t) res->count, sizeof(float));

  int i = 0;
  while (i < (int) res->count) {

    Pixel tmp;

    tmp = get_pixel_coords(i, 360.0f, radius, center, start_pos);

    res->coords.x[i] = tmp.x;
    res->coords.y[i] = tmp.y;

    i += 1;
  }

  res->center.x = center.x;
  res->center.y = center.y;

  Arc *ret = remove_doubles_form(res);

  res = NULL;

  return ret;

}
