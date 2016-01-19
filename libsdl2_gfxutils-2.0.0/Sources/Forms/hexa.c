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

Hexagram *generate_hexagram(float radius, Pixel center, float orientation) {
  /** Generate a 6 extremity star with an centered
    * hexagon from which every vertex go to the center.
    ****************************************************/

  Polygon *polygon_1 = generate_polygon_radius(6, radius, center, orientation);


  Pixel px1, px2;
  px1.x = polygon_1->coords.x[0];
  px1.y = polygon_1->coords.y[0];
  px2.x = polygon_1->coords.x[1];
  px2.y = polygon_1->coords.y[1];

  /** Generate the hexagon center. **/
  float side_length = get_distance_pixels(px1, px2);
  Line *side_middle = generate_segment(px1, side_length / 2.0f, orientation + ((360.0f / 6) / 2) + 90. + (360.0f / 6));

  /** Compute the distance from the center to an hexagon side middle point. **/
  float distance_center_side_middle = get_distance_pixels(center, side_middle->xy2);

  /** Generate the star end points according to the hexagon size. **/
  Polygon *polygon_2 = generate_polygon_radius(6, distance_center_side_middle * 2., center, ((360 / 6) / 2) + orientation);


  Hexagram *hexagram = (Hexagram *) malloc(sizeof(Hexagram));

  hexagram->coords.x = (float *) calloc((size_t) (5 * polygon_1->count + 1), sizeof(float));
  hexagram->coords.y = (float *) calloc((size_t) (5 * polygon_1->count + 1), sizeof(float));

  hexagram->count = 5 * polygon_1->count + 1;

  int i = 0;
  int ii = 0;
  while (i < polygon_1->count) {

    /** Generate the hexagram-> **/

    hexagram->coords.x[ii] = polygon_1->coords.x[i];
    hexagram->coords.y[ii] = polygon_1->coords.y[i];

    ii += 1;

    if (i + 1 == polygon_1->count) {

      hexagram->coords.x[ii] = polygon_1->coords.x[0];
      hexagram->coords.y[ii] = polygon_1->coords.y[0];
    }
    else {

      hexagram->coords.x[ii] = polygon_1->coords.x[i + 1];
      hexagram->coords.y[ii] = polygon_1->coords.y[i + 1];
    }

    ii++;


    hexagram->coords.x[ii] = center.x;
    hexagram->coords.y[ii] = center.y;

    ii++;

    hexagram->coords.x[ii] = polygon_1->coords.x[i];
    hexagram->coords.y[ii] = polygon_1->coords.y[i];

    ii++;

    hexagram->coords.x[ii] = polygon_2->coords.x[i];
    hexagram->coords.y[ii] = polygon_2->coords.y[i];

    ii++;

    if (i + 1 == polygon_1->count) {

      hexagram->coords.x[ii] = polygon_1->coords.x[0];
      hexagram->coords.y[ii] = polygon_1->coords.y[0];
    }
    else {

      hexagram->coords.x[ii] = polygon_1->coords.x[i + 1];
      hexagram->coords.y[ii] = polygon_1->coords.y[i + 1];
    }

    i++;
  }

  Pixel px;
  px.x = polygon_2->coords.x[0];
  px.y = polygon_2->coords.y[0];

  /** Freeing the temporary polygons coordinates arrays. **/

  free(side_middle);

  free(polygon_1->coords.x);
  free(polygon_1->coords.y);

  free(polygon_1);

  free(polygon_2->coords.x);
  free(polygon_2->coords.y);

  free(polygon_2);

  hexagram->center.x = center.x;
  hexagram->center.y = center.y;

  hexagram->length = radius;

  hexagram->orientation = orientation;

  hexagram->real_length = get_distance_pixels(center, px);

  return hexagram;
}

Star *generate_hexagram_star(float radius, Pixel center, float orientation) {
  /** Generate an simply 6 extremity star.
    * With the particularity that the resulting star
    * is not an regular star but an hexagram star.
    ************************************************/

  Polygon *polygon_1 = generate_polygon_radius(6, radius, center, orientation);


  Pixel px1, px2;
  px1.x = polygon_1->coords.x[0];
  px1.y = polygon_1->coords.y[0];
  px2.x = polygon_1->coords.x[1];
  px2.y = polygon_1->coords.y[1];

  /** Generate the hexagon center. **/
  float side_length = get_distance_pixels(px1, px2);
  Line *side_middle = generate_segment(px1, side_length / 2.0f, orientation + ((360.0f / 6) / 2) + 90. + (360.0f / 6));

  /** Compute the distance from the center to an hexagon side middle point. **/
  float distance_center_side_middle = get_distance_pixels(center, side_middle->xy2);

  /** Generate the star end points according to the hexagon size. **/
  Polygon *polygon_2 = generate_polygon_radius(6, distance_center_side_middle * 2., center, ((360 / 6) / 2) + orientation);


  Star *hexa_star = (Star *) malloc(sizeof(Star));

  hexa_star->coords.x = (float *) calloc((size_t) (2 * polygon_1->count), sizeof(float));
  hexa_star->coords.y = (float *) calloc((size_t) (2 * polygon_1->count), sizeof(float));

  hexa_star->count = 2 * polygon_1->count;

  int i = 0;
  int ii = 0;
  while (i < polygon_1->count) {

    /** Generate the hexagram star. **/

    hexa_star->coords.x[ii] = polygon_1->coords.x[i];
    hexa_star->coords.y[ii] = polygon_1->coords.y[i];

    ii++;

    hexa_star->coords.x[ii] = polygon_2->coords.x[i];
    hexa_star->coords.y[ii] = polygon_2->coords.y[i];

    ii++;

    i++;
  }

  Pixel px;
  px.x = polygon_2->coords.x[0];
  px.y = polygon_2->coords.y[0];

  /** Freeing the temporary polygons coordinates arrays. **/

  free(side_middle);

  free(polygon_1->coords.x);
  free(polygon_1->coords.y);

  free(polygon_1);

  free(polygon_2->coords.x);
  free(polygon_2->coords.y);

  free(polygon_2);

  hexa_star->center.x = center.x;
  hexa_star->center.y = center.y;

  hexa_star->length = radius;

  hexa_star->orientation = orientation;

  hexa_star->real_length = get_distance_pixels(center, px);

  return hexa_star;
}
