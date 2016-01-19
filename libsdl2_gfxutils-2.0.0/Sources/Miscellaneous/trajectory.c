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

void compute_trajectory(Pixel positions[], Line * trajectory, uint32_t steps) {
  /** Compute an array of Pixels within each representing an position between the start and end point.
   *  To get an guideline for animating an trajectory between 2 points from steps steps.
   * *************************************************************************************************/


  /** Compute an Pixel used as unit, in relationship to the number of steps, between 2 point.     **/
  Pixel unit;
  /** from start to end   factor < 1.0        ;    from start to end  =    factor < 1.0     ;     **/

  float factor = ((float) steps / (float) (steps * steps));

  unit.x = (trajectory->xy2.x - trajectory->xy1.x) * factor;
  unit.y = (trajectory->xy2.y - trajectory->xy1.y) * factor;

  /** Current position vector initialize with the start point coordinates. **/
  Pixel position;
  position.x = trajectory->xy1.x;
  position.y = trajectory->xy1.y;

  positions[0].x = position.x;     /** Store the first position. **/
  positions[0].y = position.y;     /** Store the first position. **/



  uint32_t c;

  for (c = 1; c < steps; c++) {

    /** Add an unit to the Current position pixel **/
    position.x += unit.x;
    position.y += unit.y;

    /** Store the current vector. **/
    positions[c].x = position.x;
    positions[c].y = position.y;
  }

  return;
}
