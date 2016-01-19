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

Pentagram *generate_pentagram(float radius, Pixel center, float orientation) {
  /** Generate a 5 extremity star with an centered
    * pentagon from which every vertex go to the center.
    ****************************************************/

  /** @NOTE: for display a filled pentagram, use the generate_pentagram_star and the display_filled_polygon function.
   */

  /** Correct the orientation. **/
  orientation = orientation + 72.0f / 4.0f;

  /** Generate the pentagon center. **/
  Polygon *polygon_1 = generate_polygon_radius(5, radius, center, orientation);

  Pixel px1, px2;
  px1.x = polygon_1->coords.x[0];
  px1.y = polygon_1->coords.y[0];
  px2.x = polygon_1->coords.x[1];
  px2.y = polygon_1->coords.y[1];

  /** Compute an pentagon side middle point. and his length. **/
  float side_length = get_distance_pixels(px1, px2);
  Line *side_middle = generate_segment(px1, side_length / 2.0f, orientation + ((360.0f / 5) / 2) + 90.0f + (360.0f / 5));

  /** Compute the distance from the center to an pentagon side middle point. **/
  float distance_center_side_middle = get_distance_pixels(center, side_middle->xy2);


  /** Generate the star end points according to the pentagon size. **/
  Polygon *polygon_2 = generate_polygon_radius(5, radius + (distance_center_side_middle * 2.0f), center, ((360.0f / 5) / 2) + orientation);



  Pentagram *pentagram = (Pentagram *) malloc(sizeof(Pentagram));

  pentagram->coords.x = (float *) calloc((size_t) (5 * polygon_1->count + 1), sizeof(float));
  pentagram->coords.y = (float *) calloc((size_t) (5 * polygon_1->count + 1), sizeof(float));

  pentagram->count = 5 * polygon_1->count + 1;

  int i = 0;
  int ii = 0;
  while (i < polygon_1->count) {

    /** Generate the pentagram-> **/

    pentagram->coords.x[ii] = polygon_1->coords.x[i];
    pentagram->coords.y[ii] = polygon_1->coords.y[i];


    ii++;

    if (i + 1 == polygon_1->count) {

      pentagram->coords.x[ii] = polygon_1->coords.x[0];
      pentagram->coords.y[ii] = polygon_1->coords.y[0];
    }
    else {

      pentagram->coords.x[ii] = polygon_1->coords.x[i + 1];
      pentagram->coords.y[ii] = polygon_1->coords.y[i + 1];
    }

    ii++;

    pentagram->coords.x[ii] = center.x;
    pentagram->coords.y[ii] = center.y;

    ii++;

    pentagram->coords.x[ii] = polygon_1->coords.x[i];
    pentagram->coords.y[ii] = polygon_1->coords.y[i];

    ii++;

    pentagram->coords.x[ii] = polygon_2->coords.x[i];
    pentagram->coords.y[ii] = polygon_2->coords.y[i];


    ii++;

    if (i + 1 == polygon_1->count) {

      pentagram->coords.x[ii] = polygon_1->coords.x[0];
      pentagram->coords.y[ii] = polygon_1->coords.y[0];
    }
    else {

      pentagram->coords.x[ii] = polygon_1->coords.x[i + 1];
      pentagram->coords.y[ii] = polygon_1->coords.y[i + 1];
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

  pentagram->center.x = center.x;
  pentagram->center.y = center.y;

  pentagram->length = radius;

  pentagram->orientation = orientation;
  pentagram->real_length = radius;

  pentagram->real_length = get_distance_pixels(center, px);

  return pentagram;
}

Star *generate_pentagram_star(float radius, Pixel center, float orientation) {
  /** Generate an simply 5 extremity star.
    * With the particularity that the resulting star
    * is not an regular star but an pentagram star.
    *
    * @NOTE: if you want make a filled penta star use me.
    *****************************************************/

  /** Correct the orientation. **/
  orientation = orientation + 72.0f / 4.0f;

  /** Generate the pentagon center. **/
  Polygon *polygon_1 = generate_polygon_radius(5, radius, center, orientation);

  Pixel px1, px2;
  px1.x = polygon_1->coords.x[0];
  px1.y = polygon_1->coords.y[0];
  px2.x = polygon_1->coords.x[1];
  px2.y = polygon_1->coords.y[1];

  /** Compute an pentagon side middle point. and his length. **/
  float side_length = get_distance_pixels(px1, px2);
  Line *side_middle = generate_segment(px1, side_length / 2.0f, orientation + ((360.0f / 5) / 2) + 90.0f + (360.0f / 5));

  /** Compute the distance from the center to an pentagon side middle point. **/
  float distance_center_side_middle = get_distance_pixels(center, side_middle->xy2);

  /** Generate the star end points according to the pentagon size. **/
  Polygon *polygon_2 = generate_polygon_radius(5, radius + (distance_center_side_middle * 2.0f), center, ((360.0f / 5) / 2) + orientation);



  Star *penta_star = (Star *) malloc(sizeof(Star));

  penta_star->coords.x = (float *) calloc((size_t) (2 * polygon_1->count), sizeof(float));
  penta_star->coords.y = (float *) calloc((size_t) (2 * polygon_1->count), sizeof(float));

  penta_star->count = 2 * polygon_1->count;

  int i = 0;
  int ii = 0;
  while (i < polygon_1->count) {

      /** Generate the pentagram based star. **/

    penta_star->coords.x[ii] = polygon_1->coords.x[i];
    penta_star->coords.y[ii] = polygon_1->coords.y[i];

    ii++;

    penta_star->coords.x[ii] = polygon_2->coords.x[i];
    penta_star->coords.y[ii] = polygon_2->coords.y[i];

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

  penta_star->center.x = center.x;
  penta_star->center.y = center.y;

  penta_star->length = radius;

  penta_star->orientation = orientation;

  penta_star->real_length = get_distance_pixels(center, px);


  return penta_star;
}
