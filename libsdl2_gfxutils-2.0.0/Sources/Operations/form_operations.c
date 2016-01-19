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

void rotate_form(Form * form, float angle) {
 /** Rotate an form from angles degrees around his @center.
   ********************************************************/

  check_form(form);

  uint32_t c;

  for (c = 0; c < form->count; c++) {
    Pixel px, cur;

    cur.x = form->coords.x[c];
    cur.y = form->coords.y[c];

    px = rotate(form->center, angle, cur);

    form->coords.x[c] = px.x;
    form->coords.y[c] = px.y;

  }

  form->orientation = ((form->orientation + angle) >= 360.0f) ? form->orientation - 360.0f + angle : form->orientation + angle;

  return;
}


void mirror_form(Form * form, Pixel center, char axes) {
 /** Mirror an Form through the axes axes ['X'|'Y'].
   *
   * Your form must be absolute entire on a side of the defined center.
   *
   * No points must be over the center.x value if argument axes is 'X'.
   *
   * No points must be over the center.y value if argument axes is 'Y'.
   *
   * Else the result will be undefined.
   ********************************************************************/


  check_form(form);



  switch (axes) {

    case 'X':
      break;

    case 'Y':
      break;

    default:
      fprintf(stderr, "Wrong axe argument: 'X' or 'Y'\n");
      exit(EXIT_FAILURE);
  }

  uint32_t c;

  for (c = 0; c < form->count; c++) {
    Pixel px, cur;

    cur.x = form->coords.x[c];
    cur.y = form->coords.y[c];

    px = mirror(cur, center, axes);

    form->coords.x[c] = px.x;
    form->coords.y[c] = px.y;

  }

  Pixel px = mirror(form->center, center, axes);

  form->center.x = px.x;
  form->center.y = px.y;

  return;
}


void scale_form(Form * form, float factor) {
 /** Scale an Form from factor factor.
   * if factor > 1.0 the size of the form increase.
   * if factor < 1.0 the size from the form decrease.
   **************************************************/

  check_form(form);

  uint32_t c;

  for (c = 0; c < form->count; c++) {
    Pixel px, cur;

    cur.x = form->coords.x[c];
    cur.y = form->coords.y[c];

    px = scale(form->center, factor, cur);

    form->coords.x[c] = px.x;
    form->coords.y[c] = px.y;

  }

  form->length *= factor;
  form->real_length *= factor;  // ???

  return;
}


void translate_form(Form * form, float x, float y) {
 /** Translate a Form from (x, y) pixels .
   ***************************************/

  check_form(form);

  uint32_t c;

  for (c = 0; c < form->count; c++) {
    Pixel px, cur;

    cur.x = form->coords.x[c];
    cur.y = form->coords.y[c];

    px = translate(cur, x, y);

    form->coords.x[c] = px.x;
    form->coords.y[c] = px.y;

  }



  form->center.x = form->center.x + x;
  form->center.y = form->center.y + y;

  return;
}

Form *remove_doubles_form(Form * form) {

  int c;

  uint32_t count = 0;

  for (c = 0; c < form->count - 1; c++) {

    if (roundf(form->coords.x[c]) == roundf(form->coords.x[c + 1]) && roundf(form->coords.y[c]) == roundf(form->coords.y[c + 1])) {
      count++;
    }
  }

  if (count == 0) {

    return form;
  }

  uint32_t new_count = form->count - count;

  Form *ret = (Form *) malloc(sizeof(Form));

  ret->coords.x = (float *) calloc((size_t) new_count, sizeof(float));
  ret->coords.y = (float *) calloc((size_t) new_count, sizeof(float));

  int i = 0;

  bool is_double = false;

  uint32_t counter = 0;

  for (c = 0; c < form->count - 1; c++) {



    if (!is_double && counter < 1) {

      ret->coords.x[i] = form->coords.x[c];
      ret->coords.y[i] = form->coords.y[c];

      i++;

    }

    if (roundf(form->coords.x[c]) == roundf(form->coords.x[c + 1]) && roundf(form->coords.y[c]) == roundf(form->coords.y[c + 1])) {
      counter++;
      is_double = true;
    }
    else {
      counter = 0;
      is_double = false;
    }
  }

  if (!is_double) {

    ret->coords.x[new_count - 1] = form->coords.x[c];
    ret->coords.y[new_count - 1] = form->coords.y[c];
  }


  ret->count = new_count;


  ret->center.x = form->center.x;
  ret->center.y = form->center.y;

  ret->length = form->length;
  ret->orientation = form->orientation;

  free_form(form);

  form = NULL;

  return ret;
}
