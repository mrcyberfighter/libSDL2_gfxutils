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

Pixel rotate(Pixel center, float angle, Pixel pixel) {
  /** Function to rotate a pixel around a center from the value angle in clock sens. **/

  Pixel res;

  float angle_radians = angle / 180.0 * M_PI;

  res.x = pixel.x * cosf(angle_radians) - pixel.y * sinf(angle_radians) + center.x * (1.0f - cosf(angle_radians)) + center.y * sinf(angle_radians);
  res.y = pixel.x * sinf(angle_radians) + pixel.y * cosf(angle_radians) + center.y * (1.0f - cosf(angle_radians)) - center.x * sinf(angle_radians);

  return res;

}

Pixel mirror(Pixel pixel, Pixel center, char axes) {
  /** pt       = the pixel to mirror.
    * distance = the distance for mirroring.
    * axes     = the mirror axes ['X'|'Y'].
    *****************************************/

  Pixel res;

  float distance_x = fabsf(center.x - pixel.x);
  float distance_y = fabsf(center.y - pixel.y);

  switch (axes) {

    case 'X':
      res.x = pixel.x;
      res.y = (pixel.y > center.y) ? center.y - distance_y : center.y + distance_y;
      break;

    case 'Y':
      res.x = (pixel.x > center.x) ? center.x - distance_x : center.x + distance_x;
      res.y = pixel.y;
      break;

    default:
      fprintf(stderr, "Wrong axe argument: 'X' or 'Y'\n");
      exit(EXIT_FAILURE);
  }

  return res;
}

Pixel scale(Pixel center, float factor, Pixel pixel) {
  /** Return the new position from pixel scaled by factor:
    * factor < 1 == scaling littler.
    * factor > 1 == scaling greater.
    ******************************************************/

  Pixel res, ret;

  res = translate(pixel, -center.x, -center.y);

  res.x *= factor;
  res.y *= factor;

  ret = translate(res, center.x, center.y);



  return ret;
}

Pixel translate(Pixel pixel, float x, float y) {
  /** Function to translate from value x and y. **/

  Pixel res;

  res.x = pixel.x + x;
  res.y = pixel.y + y;

  return res;

}
