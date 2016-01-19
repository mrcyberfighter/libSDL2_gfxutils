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

int display_line_thick(SDL_Renderer * pRenderer, Line * line, uint8_t thickness) {
  /** Display the Line line according to his settings
    * @return 0 on success, -1 on failure.
    *********************************************************/

 

  return thickLineRGBA(pRenderer, (int16_t) roundf(line->xy1.x), (int16_t) roundf(line->xy1.y), (int16_t) roundf(line->xy2.x), (int16_t) roundf(line->xy2.y), thickness, line->color.r, line->color.g, line->color.b, line->color.a);

}

int display_arc_thick(SDL_Renderer * pRenderer, Arc * arc, uint8_t thickness) {

  /** Display the Arc arc according to his settings
    * @return 0 on success, -1 on failure.
    ************************************************/

 

  int c = 0;

  int ret = 0;

  while (c < arc->count - 1) {

    ret = thickLineRGBA(pRenderer, (int16_t) roundf(arc->coords.x[c]), (int16_t) roundf(arc->coords.y[c]), (int16_t) roundf(arc->coords.x[c + 1]), (int16_t) roundf(arc->coords.y[c + 1]), thickness, arc->color.r, arc->color.g, arc->color.b, arc->color.a);

    if (ret != 0) {
      return ret;
    }

    c++;

  }

  return ret;

}


int display_polygon_thick(SDL_Renderer * pRenderer, Form * polygon, uint8_t thickness) {

  /** Display the Form polygon according to his settings
    * @return 0 on success, -1 on failure.
    *********************************************************/

 

  int c = 0;

  int ret = 0;

  while (c < polygon->count - 1) {

    ret = thickLineRGBA(pRenderer, (int16_t) roundf(polygon->coords.x[c]), (int16_t) roundf(polygon->coords.y[c]), (int16_t) roundf(polygon->coords.x[c + 1]), (int16_t) roundf(polygon->coords.y[c + 1]), thickness, polygon->color.r, polygon->color.g, polygon->color.b, polygon->color.a);


    if (ret != 0) {
      return ret;
    }

    c++;

  }

  ret = thickLineRGBA(pRenderer, (int16_t) roundf(polygon->coords.x[c]), (int16_t) roundf(polygon->coords.y[c]), (int16_t) roundf(polygon->coords.x[0]), (int16_t) roundf(polygon->coords.y[0]), thickness, polygon->color.r, polygon->color.g, polygon->color.b, polygon->color.a);

  return ret;
}



int display_strikethrough_polygon_thick(SDL_Renderer * pRenderer, Form * polygon, uint8_t thickness) {

  /** Display the Form polygon according to his settings
    * @return 0 on success, -1 on failure.
    *********************************************************/

 

  int c = 0;

  int ret = 0;

  while (c < polygon->count - 1) {


    ret = thickLineRGBA(pRenderer, (int16_t) roundf(polygon->coords.x[c]), (int16_t) roundf(polygon->coords.y[c]), (int16_t) roundf(polygon->coords.x[c + 1]), (int16_t) roundf(polygon->coords.y[c + 1]), thickness, polygon->color.r, polygon->color.g, polygon->color.b, polygon->color.a);


    if (ret != 0) {
      return ret;
    }

    c++;

  }

  ret = thickLineRGBA(pRenderer, (int16_t) roundf(polygon->coords.x[c]), (int16_t) roundf(polygon->coords.y[c]), (int16_t) roundf(polygon->coords.x[0]), (int16_t) roundf(polygon->coords.y[0]), thickness, polygon->color.r, polygon->color.g, polygon->color.b, polygon->color.a);


  if (ret != 0) {
    return ret;
  }

  c = 0;

  int16_t center_x = (int16_t) roundf(polygon->center.x);
  int16_t center_y = (int16_t) roundf(polygon->center.y);

  while (c < polygon->count) {

    ret = thickLineRGBA(pRenderer, center_x, center_y, (int16_t) roundf(polygon->coords.x[c]), (int16_t) roundf(polygon->coords.y[c]), thickness, polygon->color.r, polygon->color.g, polygon->color.b, polygon->color.a);


    if (ret != 0) {
      return ret;
    }

    c++;

  }

  return ret;

}

int display_pentagram_thick(SDL_Renderer * pRenderer, Pentagram * pentagram, uint8_t thickness) {

  /** Display the Pentagram pentagram according to his settings
    * @return 0 on success, -1 on failure.
    ***********************************************************/

 

  int c = 0;

  int ret = 0;

  while (c < pentagram->count - 1) {

    ret = thickLineRGBA(pRenderer, (int16_t) roundf(pentagram->coords.x[c]), (int16_t) roundf(pentagram->coords.y[c]), (int16_t) roundf(pentagram->coords.x[c + 1]), (int16_t) roundf(pentagram->coords.y[c + 1]), thickness, pentagram->color.r, pentagram->color.g, pentagram->color.b, pentagram->color.a);

    if (ret != 0) {
      return ret;
    }

    c++;

  }

  return ret;
}


int display_hexagram_thick(SDL_Renderer * pRenderer, Pentagram * hexagram, uint8_t thickness) {

  /** Display the Pentagram pentagram according to his settings
    * @return 0 on success, -1 on failure.
    ***********************************************************/

 

  int c = 0;

  int ret = 0;

  while (c < hexagram->count - 1) {

    ret = thickLineRGBA(pRenderer, (int16_t) roundf(hexagram->coords.x[c]), (int16_t) roundf(hexagram->coords.y[c]), (int16_t) roundf(hexagram->coords.x[c + 1]), (int16_t) roundf(hexagram->coords.y[c + 1]), thickness, hexagram->color.r, hexagram->color.g, hexagram->color.b, hexagram->color.a);

    if (ret != 0) {
      return ret;
    }

    c++;

  }

  return ret;
}




int display_star_thick(SDL_Renderer * pRenderer, Star * star, uint8_t thickness) {

  /** Display the star according to his settings
    * @return 0 on success, -1 on failure.
    *********************************************************/

 

  int c = 0;

  int ret = 0;

  while (c < star->count - 1) {

    ret = thickLineRGBA(pRenderer, (int16_t) roundf(star->coords.x[c]), (int16_t) roundf(star->coords.y[c]), (int16_t) roundf(star->coords.x[c + 1]), (int16_t) roundf(star->coords.y[c + 1]), thickness, star->color.r, star->color.g, star->color.b, star->color.a);


    if (ret != 0) {
      return ret;
    }

    c++;

  }

  ret = thickLineRGBA(pRenderer, (int16_t) roundf(star->coords.x[c]), (int16_t) roundf(star->coords.y[c]), (int16_t) roundf(star->coords.x[0]), (int16_t) roundf(star->coords.y[0]), thickness, star->color.r, star->color.g, star->color.b, star->color.a);

  return ret;

  //return polygonRGBA(pRenderer, polygon->coords.x, polygon->coords.y, polygon->count, polygon->color.r, polygon->color.g, polygon->color.b, polygon->color.a) ;
}



int display_flower_star_thick(SDL_Renderer * pRenderer, Star * star, uint8_t thickness) {

 

  int c = 0;

  int ret = 0;

  while (c < star->count - 1) {

    ret = thickLineRGBA(pRenderer, (int16_t) roundf(star->coords.x[c]), (int16_t) roundf(star->coords.y[c]), (int16_t) roundf(star->coords.x[c + 1]), (int16_t) roundf(star->coords.y[c + 1]), thickness, star->color.r, star->color.g, star->color.b, star->color.a);


    if (ret != 0) {
      return ret;
    }

    c++;

  }

  ret = thickLineRGBA(pRenderer, (int16_t) roundf(star->coords.x[c]), (int16_t) roundf(star->coords.y[c]), (int16_t) roundf(star->coords.x[0]), (int16_t) roundf(star->coords.y[0]), thickness, star->color.r, star->color.g, star->color.b, star->color.a);

  if (ret != 0) {
    return ret;
  }

  c = 0;

  int16_t center_x = (int16_t) roundf(star->center.x);
  int16_t center_y = (int16_t) roundf(star->center.y);

  while (c < star->count) {

    ret = thickLineRGBA(pRenderer, center_x, center_y, (int16_t) roundf(star->coords.x[c]), (int16_t) roundf(star->coords.y[c]), thickness, star->color.r, star->color.g, star->color.b, star->color.a);


    if (ret != 0) {
      return ret;
    }

    c += 2;

  }

  return ret;

}


int display_strikethrough_star_thick(SDL_Renderer * pRenderer, Star * star, uint8_t thickness) {

  /** Display the Polygon star according to his settings
    * @return 0 on success, -1 on failure.
    *********************************************************/

 

  int c = 0;

  int ret = 0;

  while (c < star->count - 1) {

    ret = thickLineRGBA(pRenderer, (int16_t) roundf(star->coords.x[c]), (int16_t) roundf(star->coords.y[c]), (int16_t) roundf(star->coords.x[c + 1]), (int16_t) roundf(star->coords.y[c + 1]), thickness, star->color.r, star->color.g, star->color.b, star->color.a);


    if (ret != 0) {
      return ret;
    }

    c++;

  }

  ret = thickLineRGBA(pRenderer, (int16_t) roundf(star->coords.x[c]), (int16_t) roundf(star->coords.y[c]), (int16_t) roundf(star->coords.x[0]), (int16_t) roundf(star->coords.y[0]), thickness, star->color.r, star->color.g, star->color.b, star->color.a);

  if (ret != 0) {
    return ret;
  }

  c = 0;

  int16_t center_x = (int16_t) roundf(star->center.x);
  int16_t center_y = (int16_t) roundf(star->center.y);

  while (c < star->count) {

    ret = thickLineRGBA(pRenderer, center_x, center_y, (int16_t) roundf(star->coords.x[c]), (int16_t) roundf(star->coords.y[c]), thickness, star->color.r, star->color.g, star->color.b, star->color.a);


    if (ret != 0) {
      return ret;
    }

    c++;

  }

  return ret;

}

int display_polygon_star_thick(SDL_Renderer * pRenderer, Star * star, uint8_t thickness) {

 

  int c = 0;

  int ret = 0;


  while (c < star->count - 2) {


    ret = thickLineRGBA(pRenderer, (int16_t) roundf(star->coords.x[c]), (int16_t) roundf(star->coords.y[c]), (int16_t) roundf(star->coords.x[c + 2]), (int16_t) roundf(star->coords.y[c + 2]), thickness, star->color.r, star->color.g, star->color.b, star->color.a);


    if (ret != 0) {
      return ret;
    }

    c += 2;

  }

  ret = thickLineRGBA(pRenderer, (int16_t) roundf(star->coords.x[c]), (int16_t) roundf(star->coords.y[c]), (int16_t) roundf(star->coords.x[0]), (int16_t) roundf(star->coords.y[0]), thickness, star->color.r, star->color.g, star->color.b, star->color.a);


  if (ret != 0) {
    return ret;
  }

  c = 0;

  while (c < star->count - 1) {

    ret = thickLineRGBA(pRenderer, (int16_t) roundf(star->coords.x[c]), (int16_t) roundf(star->coords.y[c]), (int16_t) roundf(star->coords.x[c + 1]), (int16_t) roundf(star->coords.y[c + 1]), thickness, star->color.r, star->color.g, star->color.b, star->color.a);

    if (ret != 0) {
      return ret;
    }

    c++;

  }

  ret = thickLineRGBA(pRenderer, (int16_t) roundf(star->coords.x[c]), (int16_t) roundf(star->coords.y[c]), (int16_t) roundf(star->coords.x[0]), (int16_t) roundf(star->coords.y[0]), thickness, star->color.r, star->color.g, star->color.b, star->color.a);


  if (ret != 0) {
    return ret;
  }

  c = 0;

  int16_t center_x = (int16_t) roundf(star->center.x);
  int16_t center_y = (int16_t) roundf(star->center.y);

  while (c < star->count) {

    ret = thickLineRGBA(pRenderer, center_x, center_y, (int16_t) roundf(star->coords.x[c]), (int16_t) roundf(star->coords.y[c]), thickness, star->color.r, star->color.g, star->color.b, star->color.a);


    if (ret != 0) {
      return ret;
    }

    c += 2;                     // If c++ -> Another strikethrough from center to spike.

  }

  return ret;

}

int display_spiral_thick(SDL_Renderer * pRenderer, Spiral * spiral, uint8_t thickness) {

  /** Display the Spiral spiral according to his settings
    * @return 0 on success, -1 on failure.
    ***********************************************************/

 

  int c = 0;

  int ret = 0;

  while (c < spiral->count - 1) {

    ret = thickLineRGBA(pRenderer, (int16_t) roundf(spiral->coords.x[c]), (int16_t) roundf(spiral->coords.y[c]), (int16_t) roundf(spiral->coords.x[c + 1]), (int16_t) roundf(spiral->coords.y[c + 1]), thickness, spiral->color.r, spiral->color.g, spiral->color.b, spiral->color.a);

    if (ret != 0) {
      return ret;
    }

    c++;

  }

  return ret;
}
