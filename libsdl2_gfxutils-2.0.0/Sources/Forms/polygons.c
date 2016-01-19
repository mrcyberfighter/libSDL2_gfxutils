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


Polygon *generate_polygon_radius(uint32_t sides, float radius, Pixel center, float orientation) {
   /** Return an polygon on XY:
    *
    *        y
    *        |
    *    ____|____x
    *        |
    *        |
    *
    *  with sides sides with radius length radius side_length starting at orientation. '''
    **************************************************************************************/

  if (sides < 3) {
    fprintf(stderr, "Wrong sides number argument: sides must be > 2 !\n");
    exit(EXIT_FAILURE);
  }

  int c;

  Polygon *polygon = (Polygon *) malloc(sizeof(Polygon));

  polygon->coords.x = (float *) calloc((size_t) sides, sizeof(float));
  polygon->coords.y = (float *) calloc((size_t) sides, sizeof(float));

  for (c = 0; c < sides; c++) {
    Pixel current_point = get_pixel_coords(c + 1, sides, radius, center, orientation);

    polygon->coords.x[c] = current_point.x;
    polygon->coords.y[c] = current_point.y;

  }

  polygon->center = center;

  polygon->count = sides;

  polygon->length = radius;

  polygon->orientation = orientation;

  polygon->real_length = radius;

  return polygon;
}

Polygon *generate_corners_rounded_polygon(uint32_t sides, float radius, Pixel center, float orientation) {
  /** Generated an polygon which corners are arcs which size is in relationship to the number
    * of sides of the polygon.
    *
    * @note: The radius goes from the center to the center of the circle arcs.
    *****************************************************************************************/

  if (sides < 3) {
    fprintf(stderr, "Wrong sides number argument: sides must be >= 3 !\n");
    exit(EXIT_FAILURE);
  }


  int32_t c, i, cc;

  float offset = 360.0f / sides;
  float angle = offset;

  /** Generate a polygon for the place of the arcs centers: **/
  Polygon *arcs_centers = generate_polygon_radius(sides, radius, center, angle);


  Arc *arcs[arcs_centers->count];

  float real_radius = radius;

  for (c = 0; c < arcs_centers->count; c++) {
    /** Generate the polygon corners arcs. **/
    Pixel tmp_center;

    tmp_center.x = arcs_centers->coords.x[c];
    tmp_center.y = arcs_centers->coords.y[c];

    arcs[c] = generate_circle_arc(radius, tmp_center, angle + (offset / 2.0f), offset);

    if (c == 0) {

      real_radius = get_distance_pixels(center, tmp_center) + radius;

    }

    angle += offset;
  }

  /** Polygon to return: **/
  Polygon *corners_rounded_polygon = (Polygon *) malloc(sizeof(Polygon));

  corners_rounded_polygon->count = 0;

  for (c = 0; c < sides; c++) {

    corners_rounded_polygon->count += arcs[c]->count;
  }

  corners_rounded_polygon->coords.x = (float *) calloc((size_t) corners_rounded_polygon->count, sizeof(float));
  corners_rounded_polygon->coords.y = (float *) calloc((size_t) corners_rounded_polygon->count, sizeof(float));

  /** Generate the rounded corners polygon: **/
  i = 0;
  for (c = 0; c < arcs_centers->count; c++) {
    /** We want to add all the arcs to the polygon-> **/
    for (cc = 0; cc < arcs[c]->count; cc++) {
      /** We add each pixel from the arcs to the polygon-> **/
      Pixel tmp, res;

      tmp.x = arcs[c]->coords.x[cc];
      tmp.y = arcs[c]->coords.y[cc];

      /** Even with an orientation offset. **/
      res = rotate(center, orientation, tmp);

      corners_rounded_polygon->coords.x[i] = res.x;
      corners_rounded_polygon->coords.y[i] = res.y;

      i++;
    }
  }


  /** Freeing temporary needed coordinates arrays. **/

  free(arcs_centers->coords.x);
  free(arcs_centers->coords.y);
  free(arcs_centers);

  for (c = 0; c < arcs_centers->count; c++) {
    free(arcs[c]->coords.x);
    free(arcs[c]->coords.y);
    free(arcs[c]);
  }


  corners_rounded_polygon->center = center;

  corners_rounded_polygon->length = radius;

  corners_rounded_polygon->orientation = orientation;

  corners_rounded_polygon->real_length = real_radius;

  return corners_rounded_polygon;

}

Polygon *generate_sides_rounded_polygon(uint32_t sides, float radius, Pixel center, float orientation) {
  /** Generate an polygon which sides are arcs.
    *
    * @note: The radius goes from the center to the center of the circle arcs.
    **************************************************************************/

  if (sides < 3) {
    fprintf(stderr, "Wrong sides number argument: sides must be >= 3 !\n");
    exit(EXIT_FAILURE);
  }

  if (sides % 2 != 0) {
    /** TO BUGFIX: i can only generate odd sides number polygons
      * because i must correct the side argument by divide it per 2.
      * The side rounded polygon is generated by generating 2 arcs arrays.
      ********************************************************************/
    fprintf(stderr, "Can only generate even sides rounded polygons sorry !!!\n");
    exit(EXIT_FAILURE);
  }

  /** Correct sides numbers used for the generation. **/
  sides = sides / 2;

  int32_t c, i, cc;

  float offset = 360.0f / sides;
  float angle = offset;

  float real_radius = radius;

  /** Generate an polygon for the position of the first polygon arcs . **/
  Polygon *first_arcs_position = (Polygon *) malloc(sizeof(Polygon));

  first_arcs_position->coords.x = (float *) calloc((size_t) sides, sizeof(float));
  first_arcs_position->coords.y = (float *) calloc((size_t) sides, sizeof(float));

  for (c = 0; c < sides; c++) {
    /** Compute all pixels positions from the polygon. **/
    Pixel current_point = get_pixel_coords(c + 1, sides, radius, center, angle);

    first_arcs_position->coords.x[c] = current_point.x;
    first_arcs_position->coords.y[c] = current_point.y;
  }

  first_arcs_position->count = sides;


  /** Polygon first arcs. **/
  Arc *first_arcs[first_arcs_position->count];

  for (c = 0; c < first_arcs_position->count; c++) {
    /** Generate the polygon first arcs. **/
    Pixel tmp_center;

    tmp_center.x = first_arcs_position->coords.x[c];
    tmp_center.y = first_arcs_position->coords.y[c];

    first_arcs[c] = generate_circle_arc(radius, tmp_center, angle + (offset / 2.0f), offset);

    if (c == 0) {

      real_radius = get_distance_pixels(center, tmp_center) + radius;

    }

    angle += offset;
  }


  angle = offset;


  /** Generate an polygon for the position of the seconds polygon arcs . **/
  Polygon *seconds_arcs_positions = (Polygon *) malloc(sizeof(Polygon));

  seconds_arcs_positions->coords.x = (float *) calloc((size_t) sides, sizeof(float));
  seconds_arcs_positions->coords.y = (float *) calloc((size_t) sides, sizeof(float));

  for (c = 0; c < sides; c++) {
    /** Compute all pixels positions from the polygon. **/
    Pixel current_point = get_pixel_coords(c + 1, sides, radius, center, angle + (offset / 2.0f));

    seconds_arcs_positions->coords.x[c] = current_point.x;
    seconds_arcs_positions->coords.y[c] = current_point.y;
  }

  seconds_arcs_positions->count = sides;


  /** Polygon seconds arcs. **/
  Arc *seconds_arcs[seconds_arcs_positions->count];

  for (c = 0; c < seconds_arcs_positions->count; c++) {
    /** Generate the polygon seconds arcs. **/

    Pixel tmp_center;

    tmp_center.x = seconds_arcs_positions->coords.x[c];
    tmp_center.y = seconds_arcs_positions->coords.y[c];

    seconds_arcs[c] = generate_circle_arc(radius, tmp_center, angle + offset, offset);

    angle += offset;
  }

  /** Polygon to return: **/
  Polygon *sides_rounded_polygon = (Polygon *) malloc(sizeof(Polygon));

  sides_rounded_polygon->count = 0;

  for (c = 0; c < sides; c++) {

    sides_rounded_polygon->count += first_arcs[c]->count + seconds_arcs[c]->count;
  }

  sides_rounded_polygon->coords.x = (float *) calloc((size_t) sides_rounded_polygon->count, sizeof(float));
  sides_rounded_polygon->coords.y = (float *) calloc((size_t) sides_rounded_polygon->count, sizeof(float));

  /** Generate the rounded sides polygon: **/
  i = 0;
  for (c = 0; c < first_arcs_position->count; c++) {
    /** We want to add all the arcs to the polygon. **/

    for (cc = 0; cc < first_arcs[c]->count; cc++) {
      /** We add each pixel from the arcs to the polygon. **/
      Pixel tmp, res;

      tmp.x = first_arcs[c]->coords.x[cc];
      tmp.y = first_arcs[c]->coords.y[cc];

      res = rotate(center, orientation, tmp);

      sides_rounded_polygon->coords.x[i] = res.x;
      sides_rounded_polygon->coords.y[i] = res.y;

      i++;
    }

    for (cc = 0; cc < seconds_arcs[c]->count; cc++) {
      /** We add each pixel from the arcs to the polygon. **/
      Pixel tmp, res;

      tmp.x = seconds_arcs[c]->coords.x[cc];
      tmp.y = seconds_arcs[c]->coords.y[cc];

      res = rotate(center, orientation, tmp);

      sides_rounded_polygon->coords.x[i] = res.x;
      sides_rounded_polygon->coords.y[i] = res.y;

      i++;
    }

  }

  /** Freeing all temporary needed coordinates arrays. **/

  free(first_arcs_position->coords.x);
  free(first_arcs_position->coords.y);

  free(first_arcs_position);

  for (c = 0; c < first_arcs_position->count; c++) {
    free(first_arcs[c]->coords.x);
    free(first_arcs[c]->coords.y);
    free(first_arcs[c]);
  }

  free(seconds_arcs_positions->coords.x);
  free(seconds_arcs_positions->coords.y);

  free(seconds_arcs_positions);

  for (c = 0; c < seconds_arcs_positions->count; c++) {
    free(seconds_arcs[c]->coords.x);
    free(seconds_arcs[c]->coords.y);
    free(seconds_arcs[c]);
  }

  sides_rounded_polygon->center.x = center.x;
  sides_rounded_polygon->center.y = center.y;

  sides_rounded_polygon->length = radius;

  sides_rounded_polygon->orientation = orientation;

  sides_rounded_polygon->real_length = real_radius;

  return sides_rounded_polygon;
}


Polygon *generate_rounded_inside_out_polygon(uint32_t sides, float radius, Pixel center, float orientation) {
  /** Generated an rounded polygon alternating arcs rounded to the outside and to the inside of
   *  the polygon.
   *
   * @note: The radius goes from the center to the center of the circle arcs.
   *********************************************************************************************/


  if (sides < 3) {
    fprintf(stderr, "Wrong sides number argument: sides must be > 2 !\n");
    exit(EXIT_FAILURE);
  }

  int32_t c, cc, i, ii;

  float offset = 360.0f / sides;
  float angle = offset;

  float real_radius = radius;

  /** Generating the base polygon: **/
  Polygon *arcs_centers = generate_polygon_radius(sides, radius, center, angle + orientation);


  /** Arcs rounded to the outside from the polygon. **/
  Arc *arcs_outside[sides];

  for (c = 0; c < sides; c++) {
    /** Generating the arcs rounded to the outside of the polygon. **/
    Pixel arc_center;

    arc_center.x = arcs_centers->coords.x[c];
    arc_center.y = arcs_centers->coords.y[c];


    arcs_outside[c] = generate_circle_arc(radius, arc_center, angle + (offset / 2.0f) + orientation, offset);

    if (c == 0) {

      real_radius = get_distance_pixels(center, arc_center) + radius;

    }

    angle += offset;

  }

  angle = offset;

  /** Arcs rounded to the inside of the polygon. **/
  Arc *arcs_inside[sides];



  for (c = 0; c < sides; c++) {
    /** Generating the arcs rounded to the inside,
      * by rotate the outside rounded arcs over their extremity,
      * of the polygon. **/

    Pixel arc_center;

    arc_center.x = arcs_outside[c]->coords.x[0];
    arc_center.y = arcs_outside[c]->coords.y[0];


    arcs_inside[c] = (Arc *) malloc(sizeof(Arc));

    arcs_inside[c]->coords.x = (float *) malloc((size_t) arcs_outside[c]->count * sizeof(float));
    arcs_inside[c]->coords.y = (float *) malloc((size_t) arcs_outside[c]->count * sizeof(float));

    arcs_inside[c]->count = (uint16_t) arcs_outside[c]->count;

    for (cc = 0, ii = arcs_outside[c]->count - 1; cc < arcs_outside[c]->count; cc++, ii--) {
       /** We compute every pixel from the arcs: **/

      Pixel tmp, res;

      tmp.x = arcs_outside[c]->coords.x[cc];
      tmp.y = arcs_outside[c]->coords.y[cc];

      res = rotate(arc_center, 180 - offset / 2.0f, tmp);

      arcs_inside[c]->coords.x[ii] = res.x;    /** Note that we reverse the order of the pixels with the ii variable. **/
      arcs_inside[c]->coords.y[ii] = res.y;    /** Note that we reverse the order of the pixels with the ii variable. **/

    }
  }


  Polygon *inside_out_rounded_polygon = (Polygon *) malloc(sizeof(Polygon));

  inside_out_rounded_polygon->count = 0;

  for (c = 0; c < sides; c++) {

    inside_out_rounded_polygon->count += arcs_outside[c]->count + arcs_inside[c]->count;
  }

  inside_out_rounded_polygon->coords.x = (float *) calloc((size_t) inside_out_rounded_polygon->count, sizeof(float));
  inside_out_rounded_polygon->coords.y = (float *) calloc((size_t) inside_out_rounded_polygon->count, sizeof(float));

  i = 0;
  for (c = 0; c < sides; c++) {
    /** Generating the result polygon. **/
    for (cc = 0; cc < arcs_inside[c]->count; cc++) {

      inside_out_rounded_polygon->coords.x[i] = arcs_inside[c]->coords.x[cc];
      inside_out_rounded_polygon->coords.y[i] = arcs_inside[c]->coords.y[cc];

      i++;
    }

    for (cc = 0; cc < arcs_outside[c]->count; cc++) {

      inside_out_rounded_polygon->coords.x[i] = arcs_outside[c]->coords.x[cc];
      inside_out_rounded_polygon->coords.y[i] = arcs_outside[c]->coords.y[cc];

      i++;
    }

  }


  /** Freeing the temporary needed coordinates arrays. **/

  free(arcs_centers->coords.x);
  free(arcs_centers->coords.y);

  free(arcs_centers);

  for (c = 0; c < sides; c++) {

    free(arcs_outside[c]->coords.x);
    free(arcs_outside[c]->coords.y);

    free(arcs_outside[c]);


    free(arcs_inside[c]->coords.x);
    free(arcs_inside[c]->coords.y);

    free(arcs_inside[c]);
  }


  inside_out_rounded_polygon->center.x = center.x;
  inside_out_rounded_polygon->center.y = center.y;

  inside_out_rounded_polygon->length = radius;

  inside_out_rounded_polygon->orientation = orientation;

  inside_out_rounded_polygon->real_length = real_radius;

  return inside_out_rounded_polygon;

}

Polygon *generate_alternate_inside_half_circle_polygon(uint32_t sides, float radius, Pixel center, float orientation, bool side_arcs) {
  /** Generated an rounded polygon with half-circle rounded to the inside
    * from the half sum from the sides length of the polygon
    * and the other is even an arc or an straight line according to the side_arcs boolean value.
    *
    * @note: The radius goes from the center to the center of the circle arcs.
    *
    * The result is an even polygon of the double of the sides values.
    ********************************************************************************************/
  if (sides < 3) {
    fprintf(stderr, "Wrong sides number argument: sides must be > 2 !\n");
    exit(EXIT_FAILURE);
  }

  int32_t c, cc, i;

  float offset = 360.0f / sides;
  float angle = offset;

  float real_radius = radius;


  /** Generating the base polygon. */
  Polygon *arcs_centers = generate_polygon_radius(sides, radius, center, angle + orientation);

  /** Arcs rounded to the outside from the polygon. **/
  Arc *sides_arcs[sides];

  for (c = 0; c < sides; c++) {
    /** Generating the arcs rounded to the outside of the polygon. **/

    Pixel arc_center;

    arc_center.x = arcs_centers->coords.x[c];
    arc_center.y = arcs_centers->coords.y[c];


    sides_arcs[c] = generate_circle_arc(radius, arc_center, angle + (offset / 2.0f) + orientation, offset);



    if (c == 0) {
      real_radius = get_distance_pixels(center, arc_center) + radius;
    }




    angle += offset;

  }

  /** Half-circle arcs rounded to the inside of the polygon. **/
  Arc *inner_arcs[sides];

  angle += (90.0f + offset);

  c = 0;
  while (c < sides) {
    /** Generating the half-circle arcs rounded to the inside of the polygon. **/

    Pixel start, end;

    if (c + 1 < sides) {

      start.x = sides_arcs[c]->coords.x[sides_arcs[c]->count - 1];
      start.y = sides_arcs[c]->coords.y[sides_arcs[c]->count - 1];

      end.x = sides_arcs[c + 1]->coords.x[0];
      end.y = sides_arcs[c + 1]->coords.y[0];

    }
    else {

      start.x = sides_arcs[sides - 1]->coords.x[sides_arcs[c]->count - 1];
      start.y = sides_arcs[sides - 1]->coords.y[sides_arcs[c]->count - 1];

      end.x = sides_arcs[0]->coords.x[0];
      end.y = sides_arcs[0]->coords.y[0];

    }

    /** Compute the distance from an extremity to the middle of an side from the polygon. **/
    float distance = get_distance_pixels(start, end) / 2.0f;

    /** Getting the middle point from an side of the polygon. **/
    Line *middle_inner_arc = generate_segment(start, distance, angle + (offset / 2.0f) + orientation);


    if (c == sides - 1 && !side_arcs) {
      real_radius -= distance / sides;
    }


    /** Generating the half-circle arcs. **/
    inner_arcs[c] = generate_circle_arc(distance, middle_inner_arc->xy2, angle + (offset / 2.0f) + orientation, 180);

    free(middle_inner_arc);

    angle += offset;

    c++;
  }

  /** Result polygon. **/
  Polygon *rounded_alternate_inside_half_circle_polygon = (Polygon *) malloc(sizeof(Polygon));


  rounded_alternate_inside_half_circle_polygon->count = 0;

  for (c = 0; c < sides; c++) {

    if (side_arcs) {

      rounded_alternate_inside_half_circle_polygon->count += sides_arcs[c]->count + inner_arcs[c]->count;

    }
    else {

      rounded_alternate_inside_half_circle_polygon->count += inner_arcs[c]->count;

    }
  }

  rounded_alternate_inside_half_circle_polygon->coords.x = (float *) calloc((size_t) rounded_alternate_inside_half_circle_polygon->count, sizeof(float));
  rounded_alternate_inside_half_circle_polygon->coords.y = (float *) calloc((size_t) rounded_alternate_inside_half_circle_polygon->count, sizeof(float));

  i = 0;
  for (c = 0; c < sides; c++) {
    /** Generating the resulting polygon. **/

    if (side_arcs) {
      /** Even not needed if the user want straight polygon sides. **/
      for (cc = 0; cc < sides_arcs[c]->count; cc++) {

        rounded_alternate_inside_half_circle_polygon->coords.x[i] = sides_arcs[c]->coords.x[cc];
        rounded_alternate_inside_half_circle_polygon->coords.y[i] = sides_arcs[c]->coords.y[cc];

        i++;
      }
    }

    for (cc = inner_arcs[c]->count - 1; cc >= 0; cc--) {

      rounded_alternate_inside_half_circle_polygon->coords.x[i] = inner_arcs[c]->coords.x[cc];
      rounded_alternate_inside_half_circle_polygon->coords.y[i] = inner_arcs[c]->coords.y[cc];

      i++;
    }



  }


  /** Freeing the temporary needed coordinates arrays. **/
  free(arcs_centers->coords.x);
  free(arcs_centers->coords.y);

  free(arcs_centers);

  for (c = 0; c < sides; c++) {
    free(sides_arcs[c]->coords.x);
    free(sides_arcs[c]->coords.y);

    free(sides_arcs[c]);

    free(inner_arcs[c]->coords.x);
    free(inner_arcs[c]->coords.y);

    free(inner_arcs[c]);
  }


  rounded_alternate_inside_half_circle_polygon->center.x = center.x;
  rounded_alternate_inside_half_circle_polygon->center.y = center.y;

  rounded_alternate_inside_half_circle_polygon->length = radius;

  rounded_alternate_inside_half_circle_polygon->orientation = orientation;

  rounded_alternate_inside_half_circle_polygon->real_length = real_radius;

  return rounded_alternate_inside_half_circle_polygon;
}

Polygon *generate_alternate_outside_half_circle_polygon(uint32_t sides, float radius, Pixel center, float orientation, bool side_arcs) {
  /** Generated an rounded polygon with half-circle rounded to the outside
    * from the half sum from the sides of the polygon
    * and the other is even an arc or an straight line according to the side_arcs boolean value.
    *
    * @note: The radius goes from the center to the center of the circle arcs.
    *
    * The result is an even polygon of the double of the sides values.
    ********************************************************************************************/

  if (sides < 3) {
    fprintf(stderr, "Wrong sides number argument: sides must be > 2 !\n");
    exit(EXIT_FAILURE);
  }

  int32_t c, cc, i;

  float offset = 360.0f / sides;
  float angle = offset;

  float real_radius = radius;


  /** Generating the base polygon. */
  Polygon *arcs_centers = generate_polygon_radius(sides, radius, center, angle + orientation);

  /** Arcs rounded to the outside from the polygon. **/
  Arc *sides_arcs[sides];

  for (c = 0; c < sides; c++) {
    /** Generating the arcs rounded to the outside of the polygon. **/

    Pixel arc_center;

    arc_center.x = arcs_centers->coords.x[c];
    arc_center.y = arcs_centers->coords.y[c];


    sides_arcs[c] = generate_circle_arc(radius, arc_center, angle + (offset / 2.0f) + orientation, offset);



    angle += offset;

  }

  /** Half-circle arcs rounded to the outside of the polygon. **/
  Arc *outer_arcs[sides];

  angle += (90.0f + offset);

  c = 0;
  while (c < sides) {
    /** Generating the half-circle arcs rounded to the outside of the polygon. **/

    Pixel start, end;

    if (c + 1 < sides) {

      start.x = sides_arcs[c]->coords.x[sides_arcs[c]->count - 1];
      start.y = sides_arcs[c]->coords.y[sides_arcs[c]->count - 1];

      end.x = sides_arcs[c + 1]->coords.x[0];
      end.y = sides_arcs[c + 1]->coords.y[0];

    }
    else {

      start.x = sides_arcs[sides - 1]->coords.x[sides_arcs[c]->count - 1];
      start.y = sides_arcs[sides - 1]->coords.y[sides_arcs[c]->count - 1];

      end.x = sides_arcs[0]->coords.x[0];
      end.y = sides_arcs[0]->coords.y[0];



    }

    /** Compute the distance from an extremity to the middle of an side from the polygon. **/
    float distance = get_distance_pixels(start, end) / 2.0f;

    /** Getting the middle point from an side of the polygon. **/
    Line *middle_inner_arc = generate_segment(start, distance, angle + (offset / 2.0f) + orientation);

    if (c == 0) {
      real_radius = get_distance_pixels(center, middle_inner_arc->xy2) + distance;
    }


    /** Generating the half-circle arcs. **/
    outer_arcs[c] = generate_circle_arc(distance, middle_inner_arc->xy2, angle + (offset / 2.0f) + orientation + 180, 180);

    free(middle_inner_arc);

    angle += offset;

    c++;
  }

  /** Result polygon. **/
  Polygon *rounded_outside_alternate_half_circle_polygon = (Polygon *) malloc(sizeof(Polygon));

  rounded_outside_alternate_half_circle_polygon->count = 0;

  for (c = 0; c < sides; c++) {

    if (side_arcs) {

      rounded_outside_alternate_half_circle_polygon->count += sides_arcs[c]->count + outer_arcs[c]->count;

    }
    else {

      rounded_outside_alternate_half_circle_polygon->count += outer_arcs[c]->count;

    }
  }

  rounded_outside_alternate_half_circle_polygon->coords.x = (float *) calloc((size_t) rounded_outside_alternate_half_circle_polygon->count, sizeof(float));
  rounded_outside_alternate_half_circle_polygon->coords.y = (float *) calloc((size_t) rounded_outside_alternate_half_circle_polygon->count, sizeof(float));

  i = 0;
  for (c = 0; c < sides; c++) {
    /** Generating the resulting polygon. **/

    if (side_arcs) {
      /** Even not needed if the user want straight polygon sides. **/
      for (cc = 0; cc < sides_arcs[c]->count; cc++) {


        rounded_outside_alternate_half_circle_polygon->coords.x[i] = sides_arcs[c]->coords.x[cc];
        rounded_outside_alternate_half_circle_polygon->coords.y[i] = sides_arcs[c]->coords.y[cc];

        i++;
      }
    }

    for (cc = 0; cc < outer_arcs[c]->count; cc++) {

      rounded_outside_alternate_half_circle_polygon->coords.x[i] = outer_arcs[c]->coords.x[cc];
      rounded_outside_alternate_half_circle_polygon->coords.y[i] = outer_arcs[c]->coords.y[cc];

      i++;
    }



  }


  /** Freeing the temporary needed coordinates arrays. **/
  free(arcs_centers->coords.x);
  free(arcs_centers->coords.y);

  free(arcs_centers);

  for (c = 0; c < sides; c++) {
    free(sides_arcs[c]->coords.x);
    free(sides_arcs[c]->coords.y);

    free(sides_arcs[c]);

    free(outer_arcs[c]->coords.x);
    free(outer_arcs[c]->coords.y);

    free(outer_arcs[c]);
  }


  rounded_outside_alternate_half_circle_polygon->center.x = center.x;
  rounded_outside_alternate_half_circle_polygon->center.y = center.y;

  rounded_outside_alternate_half_circle_polygon->length = radius;

  rounded_outside_alternate_half_circle_polygon->orientation = orientation;

  rounded_outside_alternate_half_circle_polygon->real_length = real_radius;

  return rounded_outside_alternate_half_circle_polygon;
}
