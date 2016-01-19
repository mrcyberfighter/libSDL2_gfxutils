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

Polygon *generate_wheel(uint32_t polygon, float radius, Pixel center, float offset, float orientation) {
  /** Return an pointed wheel **/

  /** @NOTE: you must set an offset greater than 0 because it represent the size of the peaks of the wheel.
    *        Else you will simply generate a normal convex polygon.
    *
    * @TIP: val > 1.0f ; try: @arg offset=radius/val @or offset=radius*val ;
    ***********************************************************************************************************************/

  if (polygon < 3) {
    fprintf(stderr, "Wrong polygon number argument: polygon must be > 2 !\n");
    exit(EXIT_FAILURE);
  }

  if (360 % polygon != 0) {
    fprintf(stderr, "Enter an valid polygon argument:  360 %% polygon == 0 !\n");
    exit(EXIT_FAILURE);
  }

  if (offset < 0.0f) {
    fprintf(stderr, "Enter an valid offset argument:  offset must be > 0 !\n");
    exit(EXIT_FAILURE);
  }

  float angle = 360.0f / polygon;

  float angles_1[polygon], angles_2[polygon];

  int32_t c, i;

  uint32_t angle_iterator = 0;

  for (c = 0; c < polygon; c++) {
    angles_1[c] = angle_iterator;
    angle_iterator += angle;
  }

  angle_iterator = angle / 2.0f;

  for (c = 0; c < polygon; c++) {
    angles_2[c] = angle_iterator;
    angle_iterator += angle;
  }

  Polygon *wheel = (Polygon *) malloc(sizeof(Polygon));

  wheel->count = polygon * 2;

  wheel->coords.x = (float *) calloc((size_t) wheel->count, sizeof(float));
  wheel->coords.y = (float *) calloc((size_t) wheel->count, sizeof(float));

  i = 0;
  for (c = 0; c < polygon; c++) {
    Pixel tmp;

    tmp = get_pixel_coords(0, polygon, radius, center, angles_1[c]);

    wheel->coords.x[i] = tmp.x;
    wheel->coords.y[i] = tmp.y;

    i++;

    tmp = get_pixel_coords(0, polygon, radius + offset, center, angles_2[c]);

    wheel->coords.x[i] = tmp.x;
    wheel->coords.y[i] = tmp.y;

    i++;
  }




  wheel->center.x = center.x;
  wheel->center.y = center.y;

  wheel->length = radius;

  wheel->orientation = orientation;

  wheel->real_length = radius + offset;

  if (orientation != 0.0f) {
    rotate_form(wheel, orientation);
  }

  return wheel;
}


Polygon *generate_circular_saw_wheel(uint32_t polygon, float radius, Pixel center, float offset, float orientation, bool reverse) {
  /** Return an circular saw like wheel **/

  /** @NOTE: you must set an offset greater than 0 because it represent the size of the peaks of the wheel.
    *        Else you will simply generate a normal convex polygon.
    **********************************************************************************************************************/

  if (polygon < 3) {
    fprintf(stderr, "Wrong polygon number argument: polygon must be > 2 !\n");
    exit(EXIT_FAILURE);
  }


  if (360 % polygon != 0) {
    fprintf(stderr, "Enter an valid polygon argument:  360 %% polygon == 0 \n");
    exit(EXIT_FAILURE);
  }

  if (offset > radius) {
    fprintf(stderr, "Invalid argument offset:\nargument offset must be <= radius\nfor generating a circular saw wheel\n");
    exit(EXIT_FAILURE);
  }

  if (offset < 0.0f) {
    fprintf(stderr, "Enter an valid offset argument:  offset must be > 0 !\n");
    exit(EXIT_FAILURE);
  }




  float angle = 360.0f / polygon;

  float angles_1[polygon];

  int32_t c, i;

  uint32_t angle_iterator = 0;

  for (c = 0; c < polygon; c++) {
    angles_1[c] = angle_iterator;
    angle_iterator += angle;
  }

  Polygon *wheel = (Polygon *) malloc(sizeof(Polygon));

  wheel->count = polygon * 2;

  wheel->coords.x = (float *) calloc((size_t) wheel->count, sizeof(float));
  wheel->coords.y = (float *) calloc((size_t) wheel->count, sizeof(float));

  i = 0;

  if (!reverse) {
    for (c = 0; c < polygon; c++) {
      Pixel tmp;

      tmp = get_pixel_coords(0, polygon, radius, center, angles_1[c]);

      wheel->coords.x[i] = tmp.x;
      wheel->coords.y[i] = tmp.y;

      i++;

      tmp = get_pixel_coords(0, polygon, radius - offset, center, angles_1[c]);

      wheel->coords.x[i] = tmp.x;
      wheel->coords.y[i] = tmp.y;

      i++;
    }
  }
  else {
    for (c = polygon - 1; c >= 0; c--) {
      Pixel tmp;

      tmp = get_pixel_coords(0, polygon, radius, center, angles_1[c]);

      wheel->coords.x[i] = tmp.x;
      wheel->coords.y[i] = tmp.y;

      i++;


      tmp = get_pixel_coords(0, polygon, radius - offset, center, angles_1[c]);

      wheel->coords.x[i] = tmp.x;
      wheel->coords.y[i] = tmp.y;

      i++;
    }
  }

  wheel->center.x = center.x;
  wheel->center.y = center.y;

  wheel->length = radius;

  wheel->orientation = orientation;

  wheel->real_length = radius;

  if (orientation != 0.0f) {

    rotate_form(wheel, orientation);
  }

  return wheel;
}

Polygon *generate_wheel_peaks_trigon(uint32_t sides, float radius, Pixel center, float peak_length, float orientation) {
  /** Generate an wheel (rounded polygon) with peaking as trigons which peak is a very little arc.
    *
    * @NOTE: you must set an peak_length greater than 0 because it represent the size of the peaks of the wheel.
    *        Else you will simply generate a normal convex polygon.
    *
    * @TIP: a good value for peak_length is radius/2.
    ********************************************************************************************************************/

  if (sides < 2) {
    fprintf(stderr, "Wrong sides number argument: sides must be > 2 !\n");
    exit(EXIT_FAILURE);
  }

  if (360 % sides != 0) {
    fprintf(stderr, "Wrong sides number argument: sides must be 360 %% sides == 0 !\n");
    exit(EXIT_FAILURE);
  }

  if (peak_length <= 0) {
    fprintf(stderr, "Enter an valid peak_length argument:  peak_length must be > 0 !\n");
    exit(EXIT_FAILURE);
  }


  uint32_t c, cc, i;

  float offset = 360.0f / sides;
  float angle = offset;



  /** Generating the base polygon. */
  Polygon *base_polygon = generate_polygon_radius(sides, radius, center, angle + orientation);

  /** Big arcs from the trigon peaks wheel polygon. **/
  Arc *big_arcs[sides];

  float real_length = radius;

  for (c = 0; c < sides; c++) {
    /** Generating the big arcs from the trigon peaks wheel (rounded) polygon. **/

    Pixel arc_center;

    arc_center.x = base_polygon->coords.x[c];
    arc_center.y = base_polygon->coords.y[c];


    big_arcs[c] = generate_circle_arc(radius, arc_center, angle + (offset / 2.0f) + orientation, offset);

    angle += offset;

  }



  /** Little arcs at peaks top. **/
  Arc *little_arcs[sides];

  angle += (90.0f + offset);

  c = 0;
  while (c < sides) {
    /** Generating the little arcs at peaks top. **/

    Pixel start, end;

    if (c + 1 < sides) {

      start.x = big_arcs[c]->coords.x[big_arcs[c]->count - 1];
      start.y = big_arcs[c]->coords.y[big_arcs[c]->count - 1];

      end.x = big_arcs[c + 1]->coords.x[0];
      end.y = big_arcs[c + 1]->coords.y[0];

    }
    else {

      start.x = big_arcs[sides - 1]->coords.x[big_arcs[c]->count - 1];
      start.y = big_arcs[sides - 1]->coords.y[big_arcs[c]->count - 1];

      end.x = big_arcs[0]->coords.x[0];
      end.y = big_arcs[0]->coords.y[0];

    }

    /** Compute the distance from an extremity to the middle of an side from the polygon. **/
    float distance = get_distance_pixels(start, end) / 2.0f;

    /** Getting the middle point from an side of the polygon. **/
    Line *half_polygon_side = generate_segment(start, distance, angle + (offset / 2.0f) + orientation);

    /** Getting the little arcs segment. **/
    Line *little_arc_side = generate_segment(half_polygon_side->xy2, distance - (distance / offset) + peak_length, angle + (offset / 2.0f) + 270 + orientation);

    /** Generating the little arcs. **/
    little_arcs[c] = generate_circle_arc(distance, little_arc_side->xy2, angle + (offset / 2.) + 270 + orientation, sides);

    if (c == 0) {
      real_length = get_distance_pixels(center, little_arc_side->xy2) + distance;
    }

    free(half_polygon_side);
    free(little_arc_side);

    angle += offset;

    c++;
  }


  /** Result polygon. **/
  Polygon *wheel_trigon_peaks = (Polygon *) malloc(sizeof(Polygon));

  wheel_trigon_peaks->count = 0;

  for (c = 0; c < sides; c++) {

    wheel_trigon_peaks->count += big_arcs[c]->count + little_arcs[c]->count;
  }

  wheel_trigon_peaks->coords.x = (float *) calloc((size_t) wheel_trigon_peaks->count, sizeof(float));
  wheel_trigon_peaks->coords.y = (float *) calloc((size_t) wheel_trigon_peaks->count, sizeof(float));

  i = 0;
  for (c = 0; c < sides; c++) {
    /** Generating the resulting polygon. **/

    for (cc = 0; cc < big_arcs[c]->count; cc++) {
      /** Setting every pixel from the arc. **/

      wheel_trigon_peaks->coords.x[i] = big_arcs[c]->coords.x[cc];
      wheel_trigon_peaks->coords.y[i] = big_arcs[c]->coords.y[cc];

      i++;
    }

    for (cc = 0; cc < little_arcs[c]->count; cc++) {
      /** Setting every pixel from the arc. **/

      wheel_trigon_peaks->coords.x[i] = little_arcs[c]->coords.x[cc];
      wheel_trigon_peaks->coords.y[i] = little_arcs[c]->coords.y[cc];

      i++;
    }

  }

  /** Freeing the temporary needed coordinates arrays. **/
  free(base_polygon->coords.x);
  free(base_polygon->coords.y);

  free(base_polygon);

  for (c = 0; c < sides; c++) {

    free(big_arcs[c]->coords.x);
    free(big_arcs[c]->coords.y);

    free(big_arcs[c]);

    free(little_arcs[c]->coords.x);
    free(little_arcs[c]->coords.y);

    free(little_arcs[c]);
  }


  wheel_trigon_peaks->center.x = center.x;
  wheel_trigon_peaks->center.y = center.y;

  wheel_trigon_peaks->length = radius;

  wheel_trigon_peaks->orientation = orientation;

  wheel_trigon_peaks->real_length = real_length;

  return wheel_trigon_peaks;

}

Polygon *generate_wheel_peaks_rounded_square(uint32_t sides, float radius, Pixel center, float peak_length, float orientation) {
  /** Generate an wheel (rounded polygon) with peaks looking like a tube but
    * they are only right-angled line to the sides connected trough an arc.
    *
    * @NOTE: you must set an offset peak_length than 0 because it represent the size of the peaks of the wheel.
    *        Else you will simply generate a normal convex polygon.
    *
    * @TIP: a good value for peak_length is radius/2.
    *************************************************************************/

  if (360 % sides != 0 || sides > 24) {
    fprintf(stderr, "Wrong sides value argument: sides must be 360 %% sides == 0 && sides <= 24 !\n");
    exit(EXIT_FAILURE);
  }

  if (peak_length <= 0) {
    fprintf(stderr, "Enter an valid peak_length argument:  peak_length must be > 0 !\n");
    exit(EXIT_FAILURE);
  }

  uint32_t c, cc, i;

  float offset = 360.0f / sides;
  float angle = offset;

  float real_length = radius;

  /** Base polygon: **/
  Polygon *base_polygon = generate_polygon_radius(sides, radius, center, angle + orientation);


  /** Trigons top arcs. **/
  Arc *little_arcs[sides];

  for (c = 0; c < sides; c++) {
    /** Generating trigons top very little arcs: **/
    Pixel tmp;

    tmp.x = base_polygon->coords.x[c];
    tmp.y = base_polygon->coords.y[c];

    little_arcs[c] = generate_circle_arc(radius, tmp, angle + (offset / 2.0f) + orientation, sides);

    angle += offset;
  }


  /** Polygon sides arcs. **/
  Arc *polygon_sides_arcs[sides];

  angle += 90.0f + offset;

  c = 0;
  while (c < sides) {
    /** Generating polygon sides arcs: **/

    Pixel start, end;

    if (c + 1 < sides) {
      start.x = little_arcs[c]->coords.x[little_arcs[c]->count - 1];
      start.y = little_arcs[c]->coords.y[little_arcs[c]->count - 1];

      end.x = little_arcs[c + 1]->coords.x[0];
      end.y = little_arcs[c + 1]->coords.y[0];
    }
    else {
      start.x = little_arcs[sides - 1]->coords.x[little_arcs[c]->count - 1];
      start.y = little_arcs[sides - 1]->coords.y[little_arcs[c]->count - 1];

      end.x = little_arcs[0]->coords.x[0];
      end.y = little_arcs[0]->coords.y[0];
    }

    float distance = get_distance_pixels(start, end) / 2.0f;
    Line *half_polygon_side = generate_segment(start, distance, angle + (offset / 2.0f) + orientation);

    float cosine = distance / cosf(offset / 2.0f / 180.0f * M_PI);
    distance = sinf(offset / 2.0f / 180.0f * M_PI) * cosine;

    Line *segment = generate_segment(half_polygon_side->xy2, distance, angle + (offset / 2.0f) + 270.0f + orientation);

    polygon_sides_arcs[c] = generate_circle_arc(peak_length, segment->xy2, angle + 270.0f + orientation, offset);


    if (c == 0) {

      real_length = get_distance_pixels(center, segment->xy2) + peak_length;
    }

    free(half_polygon_side);
    free(segment);

    angle += offset;
    c++;
  }

  /** Result polygon. **/
  Polygon *wheel_peaks_rounded_square = (Polygon *) malloc(sizeof(Polygon));

  wheel_peaks_rounded_square->count = 0;

  for (c = 0; c < sides; c++) {

    wheel_peaks_rounded_square->count += little_arcs[c]->count + polygon_sides_arcs[c]->count;
  }

  wheel_peaks_rounded_square->coords.x = (float *) calloc((size_t) wheel_peaks_rounded_square->count, sizeof(float));
  wheel_peaks_rounded_square->coords.y = (float *) calloc((size_t) wheel_peaks_rounded_square->count, sizeof(float));


  i = 0;
  for (c = 0; c < sides; c++) {
    /** Generating all the arcs from the wheel: **/
    for (cc = 0; cc < little_arcs[c]->count; cc++) {
      /** Setting all the pixels from the litlle arcs. **/

      wheel_peaks_rounded_square->coords.x[i] = little_arcs[c]->coords.x[cc];
      wheel_peaks_rounded_square->coords.y[i] = little_arcs[c]->coords.y[cc];

      i++;
    }

    for (cc = 0; cc < polygon_sides_arcs[c]->count; cc++) {
      /** Setting all the pixels from the rounded polygon. **/

      wheel_peaks_rounded_square->coords.x[i] = polygon_sides_arcs[c]->coords.x[cc];
      wheel_peaks_rounded_square->coords.y[i] = polygon_sides_arcs[c]->coords.y[cc];

      i++;
    }
  }


  /** Freeing temporary needed coordinates arrays. **/

  free(base_polygon->coords.x);
  free(base_polygon->coords.y);

  free(base_polygon);

  for (c = 0; c < sides; c++) {
    free(little_arcs[c]->coords.x);
    free(little_arcs[c]->coords.y);

    free(little_arcs[c]);

    free(polygon_sides_arcs[c]->coords.x);
    free(polygon_sides_arcs[c]->coords.y);

    free(polygon_sides_arcs[c]);

  }

  wheel_peaks_rounded_square->center.x = center.x;
  wheel_peaks_rounded_square->center.y = center.y;

  wheel_peaks_rounded_square->length = radius;

  wheel_peaks_rounded_square->orientation = orientation;
  wheel_peaks_rounded_square->real_length = real_length;

  return wheel_peaks_rounded_square;

}
