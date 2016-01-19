#include "../SDL2_gfxutils.h"

Pixel get_pixel_coords(uint32_t position, uint32_t scale, float length, Pixel center, float orientation) {

  Pixel res_px ;

  /** Get the angle from position in the circle where 3 o'clock
    * is orientation == 0  ; divided in scale units.             **/
  float angle_degrees = get_angle(position, scale, orientation)   ;


  /** Conversion angle in degrees to radians **/
  float radians = angle_degrees / 180.0 * M_PI  ;

  res_px.x = cosf(radians) * length + center.x  ;
  res_px.y = sinf(radians) * length + center.y  ;

  return res_px ;

}

Pixel get_middle_from_line(Line line) {

  Pixel res_px ;

  res_px.x = (line.xy1.x + line.xy2.x) / 2.0  ;
  res_px.y = (line.xy1.y + line.xy2.y) / 2.0  ;


  return res_px ;
}


Line generate_segment(Pixel start_point, float length, float angle) {
  /** Return an Line starting at start_point from length length incline from angle.
    * @angle: 3 o'clock is zero degree.
    *******************************************************************************/

  Line res ;

  res.xy1.x=start_point.x ;
  res.xy1.y=start_point.y ;

  float degrees = 360.0 + angle ;

  float radians = degrees / 180.0 * M_PI ;

  res.xy2.x = round( cosf(radians) * length + start_point.x) ;
  res.xy2.y = round( sinf(radians) * length + start_point.y) ;



  return res ;

}

Arc *generate_circle_arc(float radius, Pixel center, float start_pos, float circle_part) {
  /** Generate an arc from radius radius
    * from center center
    * length from part of an circle circle_part
    * starting at offset start_pos.
    *******************************************/

  if (circle_part == 0.0f) {

    fprintf(stderr,"You cannot givezero as circle_part argument !\n") ;
    return NULL ;
  }

  Arc *res = (Arc *) malloc(sizeof(Arc)) ;



  res->count = (uint16_t) roundf(360.0f/(360.0f/circle_part)) ;

  res->count = res->count == 0 ? 1 : res->count ;

  res->coords_calc.x= (float *) calloc((size_t) res->count,sizeof(float)) ;
  res->coords_calc.y= (float *) calloc((size_t) res->count,sizeof(float)) ;

  res->coords.x= (int16_t *) calloc((size_t) res->count,sizeof(int16_t)) ;
  res->coords.y= (int16_t *) calloc((size_t) res->count,sizeof(int16_t)) ;

  int i=0 ;
  while (i < (int) res->count) {

    Pixel tmp ;

    tmp=get_pixel_coords(i, 360.0f, radius, center , start_pos) ;

    res->coords_calc.x[i] = tmp.x ;
    res->coords_calc.y[i] = tmp.y ;

    res->coords.x[i] = (int16_t) roundf(tmp.x) ;
    res->coords.y[i] = (int16_t) roundf(tmp.y) ;

    i += 1 ;
  }

  res->center.x=center.x ;
  res->center.y=center.y ;

  //Arc *arc = remove_doubles_form(res) ;

  return res ;

  //return res ;

}

