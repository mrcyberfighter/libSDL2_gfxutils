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

Star *generate_star(uint32_t pikes, float radius, Pixel center, float orientation) {
  /** generate an simply star with the wanted settings. **/

  /** @NOTE: for generating a star with a self setted pikes length use the generate_wheel() function.
    *************************************************************************************************/

  if (pikes <= 4) {
    fprintf(stderr, "Wrong pikes number argument: pikes must be > 4 !\n");
     /** @BUGFIX: Cannot generate 4 or 3 polygons based stars...
       *********************************************************/
    exit(EXIT_FAILURE);
  }


  /** Generate the star inner points. **/
  Polygon *inner_points = generate_polygon_radius(pikes, radius, center, orientation);

  Pixel px1, px2;

  px1.x = inner_points->coords.x[0];
  px1.y = inner_points->coords.y[0];

  px2.x = inner_points->coords.x[1];
  px2.y = inner_points->coords.y[1];

  /** Compute the side length from the star inner points polygon. **/
  float pikes_middle_length = get_distance_pixels(px1, px2);

  /** Compute the middle point from the star inner points polygon. **/
  Line *side_middle = generate_segment(px1, pikes_middle_length / 2.0f, orientation + ((360.0f / pikes) / 2) + 90.0f + (360.0f / pikes));

  Pixel line_end;

  line_end.x = side_middle->xy2.x;
  line_end.y = side_middle->xy2.y;

  /** Compute the distance between the center and the middle point from inner points polygon. **/
  float middle_length = get_distance_pixels(center, line_end);

  /** Generate the star pikes points. **/
  Polygon *outter_points = generate_polygon_radius(pikes, middle_length * 2.0f, center, 0 + ((360 / pikes) / 2) + orientation);

  Star *res = (Star *) malloc(sizeof(Polygon));

  res->count = pikes * 2;

  res->coords.x = (float *) calloc((size_t) res->count, sizeof(float));
  res->coords.y = (float *) calloc((size_t) res->count, sizeof(float));

  int32_t i = 0;
  int32_t ii = 0;
  while (i < pikes) {

    /** Generate the star with the given settings. **/

    res->coords.x[ii] = inner_points->coords.x[i];
    res->coords.y[ii] = inner_points->coords.y[i];

    ii++;


    res->coords.x[ii] = outter_points->coords.x[i];
    res->coords.y[ii] = outter_points->coords.y[i];
    ii++;
    i++;
  }

  /** Freeing the temporary polygons coordinates arrays. **/

  Pixel px;

  px.x = outter_points->coords.x[0];
  px.y = outter_points->coords.y[0];

  //float real_length = middle_length*2.0f ;
  float real_length = get_distance_pixels(center, px);

  free(side_middle);

  free(inner_points->coords.x);
  free(inner_points->coords.y);

  free(inner_points);

  free(outter_points->coords.x);
  free(outter_points->coords.y);

  free(outter_points);

  res->center.x = center.x;
  res->center.y = center.y;

  res->length = radius;

  res->orientation = orientation;
  res->real_length = real_length;

  return res;
}
