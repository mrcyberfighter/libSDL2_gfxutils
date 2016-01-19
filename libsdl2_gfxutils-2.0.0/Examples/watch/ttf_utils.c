/**
  *  Text utils for the SDL2_ttf extension.
  *  Compil with linking
  *
  * $ main.c -SDL2 -SDL2_ttf
  *
  *****************************************/

typedef struct Text_ {

  uint16_t x ;
  uint16_t y ;

  uint16_t width  ;
  uint16_t height ;

  SDL_Texture *font_texture ;

  TTF_Font *font ;

  SDL_Color text_color ;

  char *text ;

} Text ;

void configure_text(SDL_Renderer *pRenderer, Text *text, char *string, SDL_Color color, uint16_t x, uint16_t y) {

  /** Function to configure the text displayed at round end to notify the round winner. **/

  text->text         = string        ;   /**  Text to display. **/
  text->text_color.r = color.r       ;   /**  Red color.       **/
  text->text_color.g = color.g       ;   /**  Green color.     **/
  text->text_color.b = color.b       ;   /**  Blue color.      **/
  text->text_color.a = color.a       ;   /**  Alpha color.     **/
  


  SDL_Surface* text_surface   = TTF_RenderText_Blended(text->font, text->text, color);

  if ( text_surface == NULL ) {
    fprintf(stderr, "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    return ;
  }

  text->font_texture  = SDL_CreateTextureFromSurface( pRenderer, text_surface );

  if( text->font_texture == NULL ) {
    fprintf(stderr,"Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    return ;
  }

  else {

    text->width  = text_surface->w  ;
    text->height = text_surface->h ;

    text->x=  x  - text_surface->w/2  ;  /** X position from text to display. **/
    text->y=  y - text_surface->h    ;  /** Y position from text to display. **/

    SDL_FreeSurface( text_surface );
  }

  return ;

}


void render_text(SDL_Renderer *pRenderer, Text *text) {

  /** Function to render any text given as argument. **/

  SDL_Rect textrect;

  textrect.x = text->x ;
  textrect.y = text->y ;
  textrect.w = text->width  ;
  textrect.h = text->height ;

  SDL_RenderCopy(pRenderer, text->font_texture, NULL, &textrect) ;

  return ;
}
