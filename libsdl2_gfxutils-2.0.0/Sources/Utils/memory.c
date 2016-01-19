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

void free_form(Form * form) {

  /** Free a form. */

  free(form->coords.x);
  free(form->coords.y);

  free(form);

  form = NULL;

  return;
}

Form *new_form(uint32_t count) {

  /** Allocate the dynamic space for a count accoding a count value.
    *
    * You must set the:
    *
    *   form->radius
    *   form->length
    *   form->orientation
    *
    * Yourself.
    ****************************************************************/


  Form *form = (Form *) malloc(sizeof(Form));

  form->coords.x = (float *) calloc((size_t) count, sizeof(float));
  form->coords.y = (float *) calloc((size_t) count, sizeof(float));

  form->count = count;

  return form;

}
