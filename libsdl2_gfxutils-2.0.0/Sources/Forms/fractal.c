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

Polygon *generate_fractal(uint32_t polygon, float radius, Pixel center, float orientation, bool open) {
  /** Generate a fractal **/

  if (polygon < 3) {
    fprintf(stderr, "Wrong polygon number argument: polygon must be > 5 !\n");
    exit(EXIT_FAILURE);
  }

  if (360 % polygon != 0) {
    fprintf(stderr, "Enter an valid polygon argument:  360 %% polygon == 0 \n");
    exit(EXIT_FAILURE);
  }


  float offset = radius * 2.0f; // You can play with this value to build more complex fractals but not surely not regular.


  float angle = 360.0f / polygon;

  float angles_1[polygon];

  uint32_t c, i;

  uint32_t angle_iterator = 0;

  for (c = 0; c < polygon; c++) {
    angles_1[c] = angle_iterator;
    angle_iterator += angle;
  }

  Polygon *fractal = (Polygon *) malloc(sizeof(Polygon));

  fractal->count = polygon * 2;


  fractal->coords.x = (float *) calloc((size_t) fractal->count, sizeof(float));
  fractal->coords.y = (float *) calloc((size_t) fractal->count, sizeof(float));


  i = 0;
  for (c = 0; c < polygon; c++) {
    Pixel tmp;

    tmp = get_pixel_coords(0, polygon, radius, center, angles_1[c]);

    fractal->coords.x[i] = tmp.x;
    fractal->coords.y[i] = tmp.y;

    i++;

    if (!open) {

      if (c != polygon - 1) {
        tmp = get_pixel_coords(0, polygon, radius - offset, center, angles_1[c + 1]);
      }
      else {
        tmp = get_pixel_coords(0, polygon, radius - offset, center, angles_1[0]);
      }

    }
    else {

      if (c == 0) {
        tmp = get_pixel_coords(0, polygon, radius - offset, center, angles_1[polygon - 1]);
      }
      else {
        tmp = get_pixel_coords(0, polygon, radius - offset, center, angles_1[c - 1]);
      }
    }

    fractal->coords.x[i] = tmp.x;
    fractal->coords.y[i] = tmp.y;

    i++;

  }

  if (orientation) {

    rotate_form(fractal, orientation);
  }

  fractal->center.x = center.x;
  fractal->center.y = center.y;

  fractal->length = radius;

  fractal->orientation = orientation;
  fractal->real_length = radius;

  return fractal;
}
