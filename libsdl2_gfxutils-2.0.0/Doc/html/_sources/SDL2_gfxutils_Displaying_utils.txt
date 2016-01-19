.. _displaying-functions:

Displaying forms
================

display functions
-----------------

  Here are describe the Form display utlities.

Line
++++

.. c:function:: int display_line(SDL_Renderer *pRenderer, Line *line)

  :param pRenderer: A SDL_Renderer pointer.
  :param line: The line to display.
  :type  line: :c:type:`Line *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

   :see: :ref:`display line <display-line-image>`.

  This function display the line in the current color and at the current position.

Arc
+++

.. c:function:: int display_arc(SDL_Renderer *pRenderer, Arc *arc)

  :param pRenderer: A SDL_Renderer pointer.
  :param arc: The arc to display.
  :type  arc: :c:type:`Arc *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

   :see: :ref:`display arc <display-arc-image>`.

  This function display the arc in the current color and at the current position.

Polygon
+++++++

.. c:function:: int display_polygon(SDL_Renderer *pRenderer, Form *polygon)

  :param pRenderer: A SDL_Renderer pointer.
  :param polygon: The polygon to display.
  :type  polygon: :c:type:`Form *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

   :see: :ref:`display polygon <display-polygon-image>`.

  This function display the polygon lined in the current color and at the current position.

.. c:function:: int display_strikethrough_polygon(SDL_Renderer *pRenderer, Form *polygon)

  :param pRenderer: A SDL_Renderer pointer.
  :param polygon: The polygon to display.
  :type  polygon: :c:type:`Form *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

   :see: :ref:`display strikethrough polygon <display-strikethrough-polygon-image>`.

  This function display the polygon lined strikethrough in the current color and at the current position.

.. c:function:: display_filled_polygon(SDL_Renderer *pRenderer, Form *polygon)

  :param pRenderer: A SDL_Renderer pointer.
  :param polygon: The polygon to display.
  :type  polygon: :c:type:`Form *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

   :see: :ref:`display filled polygon <display-filled-polygon-image>`.

  This function display the polygon filled in the current color and at the current position.


Pentagram & Hexagram
++++++++++++++++++++

.. c:function:: int display_pentagram(SDL_Renderer *pRenderer, Pentagram *pentagram)

  :param pRenderer: A SDL_Renderer pointer.
  :param pentagram: The pentagram to display.
  :type  pentagram: :c:type:`Pentagram *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

   :see: :ref:`display pentagram <display-pentagram-image>`.

  This function display the pentagram in the current color and at the current position.

.. c:function:: int display_hexagram(SDL_Renderer *pRenderer, Pentagram *hexagram)

  :param pRenderer: A SDL_Renderer pointer.
  :param hexagram: The hexagram to display.
  :type  hexagram: :c:type:`Hexagram *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

   :see: :ref:`display hexagram <display-hexagram-image>`.

  This function display the hexagram in the current color and at the current position.

Star
++++

.. c:function:: int display_star(SDL_Renderer *pRenderer, Star *star)

  :param pRenderer: A SDL_Renderer pointer.
  :param star: The star to display.
  :type  star: :c:type:`Star *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

   :see: :ref:`display star <display-star-image>`.

  This function display the star in the current color and at the current position.

.. c:function:: int display_flower_star(SDL_Renderer *pRenderer, Star *star)

  :param pRenderer: A SDL_Renderer pointer.
  :param star: The star to display.
  :type  star: :c:type:`Star *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

   :see: :ref:`display flower star <display-flower-star-image>`.

  This function display the flower star in the current color and at the current position.

.. c:function:: int display_strikethrough_star(SDL_Renderer *pRenderer, Star *star)

  :param pRenderer: A SDL_Renderer pointer.
  :param star: The star to display.
  :type  star: :c:type:`Star *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

   :see: :ref:`display strikethrough star <display-strikethrough-star-image>`.

  This function display the strikethrough star in the current color and at the current position.

.. c:function:: int display_polygon_star(SDL_Renderer *pRenderer, Star *star)
 
  :param pRenderer: A SDL_Renderer pointer.
  :param star: The star to display.
  :type  star: :c:type:`Star *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

   :see: :ref:`display polygon star <display-polygon-star-image>`.

  This function display the polygon star in the current color and at the current position.
 

.. c:function:: int display_filled_star(SDL_Renderer *pRenderer, Star *star)

  :param pRenderer: A SDL_Renderer pointer.
  :param star: The star to display.
  :type  star: :c:type:`Star *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

    :see: :ref:`display filled star <display-filled-star-image>`.

  This function display the strikethrough star in the current color and at the current position.

Spiral
++++++

.. c:function:: int display_spiral(SDL_Renderer *pRenderer, Spiral *spiral)

  :param pRenderer: A SDL_Renderer pointer.
  :param spiral: The spiral to display.
  :type spiral: :c:type:`Spiral *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

   :see: :ref:`display spiral <display-spiral-image>`.

  This function display the spiral in the current color and at the current position.


.. _anti-aliasing-functions:

Anti-aliasing display functions
-------------------------------

Line
++++

.. c:function:: int aa_display_line(SDL_Renderer *pRenderer, Line *line)

  :param pRenderer: A SDL_Renderer pointer.
  :param line: The line to display.
  :type  line: :c:type:`Line *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the line in the current color and at the current position.

Arc
+++

.. c:function:: int aa_display_arc(SDL_Renderer *pRenderer, Arc *arc)

  :param pRenderer: A SDL_Renderer pointer.
  :param arc: The arc to display.
  :type  arc: :c:type:`Arc *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the arc in the current color and at the current position.

Polygon
+++++++

.. c:function:: int aa_display_polygon(SDL_Renderer *pRenderer, Form *polygon)

  :param pRenderer: A SDL_Renderer pointer.
  :param polygon: The polygon to display.
  :type  polygon: :c:type:`Form *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the polygon lined in the current color and at the current position.

.. c:function:: int aa_display_strikethrough_polygon(SDL_Renderer *pRenderer, Form *polygon)

  :param pRenderer: A SDL_Renderer pointer.
  :param polygon: The polygon to display.
  :type  polygon: :c:type:`Form *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the polygon lined strikethrough in the current color and at the current position.


Pentagram & Hexagram
++++++++++++++++++++

.. c:function:: int aa_display_pentagram(SDL_Renderer *pRenderer, Pentagram *pentagram)

  :param pRenderer: A SDL_Renderer pointer.
  :param pentagram: The pentagram to display.
  :type  pentagram: :c:type:`Pentagram *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the pentagram in the current color and at the current position.

.. c:function:: int aa_display_hexagram(SDL_Renderer *pRenderer, Pentagram *hexagram)

  :param pRenderer: A SDL_Renderer pointer.
  :param hexagram: The hexagram to display.
  :type  hexagram: :c:type:`Hexagram *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the hexagram in the current color and at the current position.

Star
++++

.. c:function:: int aa_display_star(SDL_Renderer *pRenderer, Star *star)

  :param pRenderer: A SDL_Renderer pointer.
  :param star: The star to display.
  :type  star: :c:type:`Star *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the star in the current color and at the current position.

.. c:function:: int aa_display_flower_star(SDL_Renderer *pRenderer, Star *star)

  :param pRenderer: A SDL_Renderer pointer.
  :param star: The star to display.
  :type  star: :c:type:`Star *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the flower star in the current color and at the current position.

.. c:function:: int aa_display_strikethrough_star(SDL_Renderer *pRenderer, Star *star)

  :param pRenderer: A SDL_Renderer pointer.
  :param star: The star to display.
  :type  star: :c:type:`Star *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the strikethrough star in the current color and at the current position.

.. c:function:: int aa_display_polygon_star(SDL_Renderer *pRenderer, Star *star)
 
  :param pRenderer: A SDL_Renderer pointer.
  :param star: The star to display.
  :type  star: :c:type:`Star *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the polygon star in the current color and at the current position.

Spiral
++++++

.. c:function:: int aa_display_spiral(SDL_Renderer *pRenderer, Spiral *spiral)

  :param pRenderer: A SDL_Renderer pointer.
  :param spiral: The spiral to display.
  :type  spiral: :c:type:`Spiral *`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the spiral in the current color and at the current position.


.. _thickness-settable-functions:

Thickness settable display functions
------------------------------------

Line
++++

.. c:function:: int display_line_thick(SDL_Renderer *pRenderer, Line *line, uint8_t thickness)

  :param pRenderer: A SDL_Renderer pointer.
  :param line: The line to display.
  :type  line: :c:type:`Line *`
  :param thickness: The line width.
  :type  thickness: :c:type:`uint8_t`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the line in the current color and at the current position.

Arc
+++

.. c:function:: int display_arc_thick(SDL_Renderer *pRenderer, Arc *arc, uint8_t thickness)

  :param pRenderer: A SDL_Renderer pointer.
  :param arc: The arc to display.
  :type  arc: :c:type:`Arc *`
  :param thickness: The line width.
  :type  thickness: :c:type:`uint8_t`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the arc in the current color and at the current position.

Polygon
+++++++

.. c:function:: int display_polygon_thick(SDL_Renderer *pRenderer, Form *polygon, uint8_t thickness)

  :param pRenderer: A SDL_Renderer pointer.
  :param polygon: The polygon to display.
  :type  polygon: :c:type:`Form *`
  :param thickness: The line width.
  :type  thickness: :c:type:`uint8_t`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the polygon lined in the current color and at the current position.

.. c:function:: int display_strikethrough_polygon_thick(SDL_Renderer *pRenderer, Form *polygon, uint8_t thickness)

  :param pRenderer: A SDL_Renderer pointer.
  :param polygon: The polygon to display.
  :type  polygon: :c:type:`Form *`
  :param thickness: The line width.
  :type  thickness: :c:type:`uint8_t`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the polygon lined strikethrough in the current color and at the current position.


Pentagram & Hexagram
++++++++++++++++++++

.. c:function:: int display_pentagram_thick(SDL_Renderer *pRenderer, Pentagram *pentagram, uint8_t thickness)

  :param pRenderer: A SDL_Renderer pointer.
  :param pentagram: The pentagram to display.
  :type  pentagram: :c:type:`Pentagram *`
  :param thickness: The line width.
  :type  thickness: :c:type:`uint8_t`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the pentagram in the current color and at the current position.

.. c:function:: int display_hexagram_thick(SDL_Renderer *pRenderer, Pentagram *hexagram, uint8_t thickness)

  :param pRenderer: A SDL_Renderer pointer.
  :param hexagram: The hexagram to display.
  :type  hexagram: :c:type:`Hexagram *`
  :param thickness: The line width.
  :type  thickness: :c:type:`uint8_t`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the hexagram in the current color and at the current position.

Star
++++

.. c:function:: int display_star_thick(SDL_Renderer *pRenderer, Star *star, uint8_t thickness)

  :param pRenderer: A SDL_Renderer pointer.
  :param star: The star to display.
  :type  star: :c:type:`Star *`
  :param thickness: The line width.
  :type  thickness: :c:type:`uint8_t`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the star in the current color and at the current position.

.. c:function:: int display_flower_star_thick(SDL_Renderer *pRenderer, Star *star, uint8_t thickness)

  :param pRenderer: A SDL_Renderer pointer.
  :param star: The star to display.
  :type  star: :c:type:`Star *`
  :param thickness: The line width.
  :type  thickness: :c:type:`uint8_t`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the flower star in the current color and at the current position.

.. c:function:: int display_strikethrough_star_thick(SDL_Renderer *pRenderer, Star *star, uint8_t thickness)

  :param pRenderer: A SDL_Renderer pointer.
  :param star: The star to display.
  :type  star: :c:type:`Star *`
  :param thickness: The line width.
  :type  thickness: :c:type:`uint8_t`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the strikethrough star in the current color and at the current position.

.. c:function:: int display_polygon_star_thick(SDL_Renderer *pRenderer, Star *star, uint8_t thickness)
 
  :param pRenderer: A SDL_Renderer pointer.
  :param star: The star to display.
  :type  star: :c:type:`Star *`
  :type  thickness: :c:type:`uint8_t`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the polygon star in the current color and at the current position.

Spiral
++++++

.. c:function:: int display_spiral_thick(SDL_Renderer *pRenderer, Spiral *spiral, uint8_t thickness)

  :param pRenderer: A SDL_Renderer pointer.
  :param spiral: The spiral to display.
  :type  spiral: :c:type:`Spiral *`
  :param thickness: The line width.
  :type  thickness: :c:type:`uint8_t`
  :rtype: :c:type:`int`
  :return: 0 on success, -1 on failure.

  This function display the spiral in the current color and at the current position.

Define your own displaying functions
------------------------------------

.. note:: Define your own displaying functions.

  You can implement your own displaying functions for per example:

    * Display every line from a polygon in an different color.

    * Display severals polygons filled overlaps in differents tones from a color with sinking alpha value.

  And whatever your brain can imagined.
