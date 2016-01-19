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

void set_form_center(Form * form, Pixel center, bool translate) {

  /** Set a new center from the Form form and eventually translate all coordinates. **/

  check_form(form);

  uint32_t c;

  if (translate) {
    for (c = 0; c < form->count; c++) {
      Pixel cur;

      cur.x = form->coords.x[c];
      cur.y = form->coords.y[c];

      form->coords.x[c] = cur.x + (center.x - form->center.x);
      form->coords.y[c] = cur.y + (center.y - form->center.y);

    }
  }

  form->center.x = center.x;
  form->center.y = center.y;

  return;

}

void set_form_radius(Form * form, float radius) {

  /** Set a new radius from the Form form. **/

  /** Don't use too much precision values after the floating-point ( 3 (%.3f) is enough precision).
    *
    *   It desn't make sens to set a new size in a display with too much precision coordinates.
    *
    *   @Otherwise your request doesn't be @exactly satisfy !!!
    *
    **********************************************************************************************/

  check_form(form);

  if (form->length == radius) {

    return;
  }


  float factor;


  factor = radius / form->length;

  scale_form(form, factor);

  return;

}

void set_form_color(Form * form, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {

  /** Set the colors from the Form form **/

  check_form(form);

  form->color.r = red;
  form->color.g = green;
  form->color.b = blue;
  form->color.a = alpha;

  return;
}

void set_line_color(Line * line, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {

  /** Set the colors from the Line line **/

  line->color.r = red;
  line->color.g = green;
  line->color.b = blue;
  line->color.a = alpha;

  return;

}
