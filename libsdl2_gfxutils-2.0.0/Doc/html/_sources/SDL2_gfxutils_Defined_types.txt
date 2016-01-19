SDL2_gfxutils defined types
===========================

.. _sdl2_gfxutils-types:

Following types are define by **SDL2_gfxutils**:

.. code-block:: c

  typedef struct Color_ {
    uint8_t r ;
    uint8_t g ;
    uint8_t b ;
    uint8_t a ;
  } Color ;


  typedef struct Pixel_ {
    float x ;
    float y ;
  } Pixel ;

  typedef struct Segment_ {
    Pixel xy1   ;
    Pixel xy2   ;
    Color color ;
  } Line ;

  typedef struct Coords_ {
    float *x ;
    float *y ;
  } Coords ;

  typedef struct Polygon_ {
    Coords         coords      ;
    Pixel          center      ;
    Color          color       ;
    uint16_t       count       ;
    float          length      ;
    float          real_length ;
    float          orientation ;
  } Polygon ;

  typedef Polygon Arc          ;
  typedef Polygon Hexagram     ;
  typedef Polygon Pentagram    ;
  typedef Polygon Star         ;
  typedef Polygon Spiral       ;


  typedef Polygon         Form ;
  typedef Arc             Form ;
  typedef Hexagram        Form ;
  typedef Pentagram       Form ;
  typedef Spiral          Form ;
  typedef Star            Form ;

.. _Color-type:

The Color type
--------------

The :c:type:`Color` is used for holding datas about colors channels:

.. code-block:: c

  typedef struct Color_ {
    uint8_t r ;
    uint8_t g ;
    uint8_t b ;
    uint8_t a ;
  } Color ;



.. _Pixel-type:

The Pixel type
--------------

The :c:type:`Pixel` type is used for holding the datas about an pixel:

    the :c:data:`x` and :c:data:`y` coordinate values.

The :c:type:`Pixel` type is used by functions which return a single pixel.

.. code-block:: c

  typedef struct Pixel_ {
    float x ;
    float y ;
  } Pixel ;


Like the function :ref:`get_middle_from_line() <get_middle_from_line>`.

.. _Line-type:

The Line type
-------------

The :c:type:`Line` type is used for holding the datas about a line:

  * The line start :c:type:`Pixel`.

  * The line end :c:type:`Pixel`.

  * The color of the line as **red**, **green**, **blue** and **alpha** values.

The :c:type:`Line` type is used by functions which return a segment.

.. code-block:: c

  typedef struct Segment_ {
    Pixel xy1   ;
    Pixel xy2   ;
    Color color ;
  } Line ;

Like the function :ref:`generate_segment() <generate_segment>`.

Or as argument from a function per example to get the middle of a line.




The Coords type
---------------

The :c:type:`Coords` type in only used internally to be a member of the :c:type:`Polygon` type.

.. code-block:: c

  typedef struct Coords_ {
    float *x ;
    float *y ;
  } Coords ;


The :c:type:`Coords` is used for performing computation.


.. note::

  By displaying operations the :c:type:`float` array members are converted to :c:type:`int16_t` (the **SDL2_gfx** coordinates arrays standart type for displaying) in this way:

  .. code-block:: c
  
    int c ;
  
    for (c=0 ; c < form->count-2 ; c++) {
  
      ret=lineRGBA(pRenderer,
                   (int16_t) roundf(form->coords.x[c]),
                   (int16_t) roundf(form->coords.y[c]),
                   (int16_t) roundf(form->coords.x[c+1]),
                   (int16_t) roundf(form->coords.y[c+1]),
                   form->color.r,
                   form->color.g,
                   form->color.b,
                   form->color.a) ;
    }
  
  



:note: After using a Form, Wenn you do not need it in the future, you can free the form.


.. _Form-type:

.. _Polygon-type:

The Polygon type
----------------

The :c:type:`Polygon` is used for holding all datas about a form.

    * The **coordinates** for *computing* the form generation and used by the animation functions: the :c:type:`Coords` :c:type:`struct`.

    * The **center** of the form: the :c:type:`Pixel` :c:type:`struct`.

    * The **color** of the form: the :c:data:`r`, :c:data:`g`, :c:data:`b`, :c:data:`a` members.

    * The **count** of coordinates number: the :c:data:`count` member.

    * The **length** often the *radius* needed from the animating functions: the :c:data:`length` member.
 
    * The **length** between the :c:data:`center` and the most distant **coordinate** from the :c:data:`center`: the :c:data:`real_length` member.
 
    * The **offset** defining the incline of a form: the :c:data:`orientation`.

.. code-block:: c

  typedef struct Polygon_ {
    Coords         coords      ;
    Pixel          center      ;
    Color          color       ;
    uint16_t       count       ;
    float          length      ;
    float          real_length ;
    float          orientation ;
  } Polygon ;

:note: All derived types are define as an :ref:`Form <Form-type>` type so that you don't need to cast it if you use a :c:type:`Form` generic function.

.. note:: Dynamically settings.

  All forms generating functions set the :c:data:`count`, :c:data:`length`, :c:data:`center`, :c:data:`orientation` and the :c:data:`real_length` member from the :c:type:`Polygon` type.

.. _Pentagram-type:

.. _Hexagram-type:

.. _Spiral-type:

.. _Arc-type:

.. _Star-type:

Generic Form type.
------------------

There are many forms representing derivated types from the :ref:`Polygon <Polygon-type>` type.

  .. code-block:: c

     typedef Polygon Arc          ;
     typedef Polygon Hexagram     ;
     typedef Polygon Pentagram    ;
     typedef Polygon Star         ;
     typedef Polygon Spiral       ;


All derivated types are define as a generic :c:type:`Form` type.

  .. code-block:: c

    typedef Polygon         Form ;
    typedef Arc             Form ;
    typedef Hexagram        Form ;
    typedef Pentagram       Form ;
    typedef Spiral          Form ;
    typedef Star            Form ;

.. _sdl2_gfxutils-others:
                   
Notice
------

.. note:: Compatiblity with others libraries than **SDL2**:

  The only purpose of the **SDL2_gfx** library is the form displaying functionality.
 
  So I think it's possible to adapt easily **SDL2_gfxutils** to be resusable with others libraries.
 
  You only have to implement the displaying functions adapted to the target library.
 
  If the coordinates arrays from type :c:type:`float` does it for the target library, because
 
  it's easy to **round** and **cast** the :c:type:`float` in the target type, like this:
 
  .. code-block:: c
   
    int x = (int) roundf(form->coords.x[c]) ;
    int y = (int) roundf(form->coords.y[c]) ;   
 
  Else the :ref:`colors <Color-type>` are coded on :c:type:`uint8_t` values.
 
  And the other members from the :ref:`Form <Form-type>` structure are used for computing.
 
  Thank's to notify me at <mrcyberfighter@gmail.com> if you want to do so.          
