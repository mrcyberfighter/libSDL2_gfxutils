Base functions
==============

  Here are describe the geometric, base functions functions, from **SDL2_gfxutils** used from the differents forms generating functions.

Angles
------
.. c:function:: float get_angle(int position, float scale, float orientation)

  :param position: Needed for positional purpose: number of scaling units.
  :type position: :c:type:`int`
  :param scale: Scaling of the angle.
  :type scale: :c:type:`float`
  :param orientation: An additionnal offset to add.
  :type orientation: :c:type:`float`
  :rtype: float
  :return: An angle in degrees.

  This function return an angle value according to the given settings,

  by applying following formel:

  .. code-block:: python

    360.0/scale * position + orientation

.. _get_distance_pixels:

Distance
--------

.. c:function:: float get_distance_pixels(Pixel px1, Pixel px2)

  :param px1: The start pixel from the distance.
  :type  px1: :c:type:`float`
  :param px2: The end pixel from the distance.
  :type  px2: :c:type:`Pixel`
  :rtype: float
  :return: The distance between :c:data:`px1` and :c:data:`px2`.

  .. note: Advices:

    Convert coordinates from **forms** into :ref:`Pixel <Pixel-type>`:

    .. code-block: c
  
      Pixel px ;
  
      px.x = form->coords.x[c] ;
      px.y = form->coords.y[c] ;
  
    :warning: **Use only integers values** or not more than **3 precision** (:c:data:`%.3f`) if you set it into a :ref:`Form <Form-type>` :c:type:`coords` member.


Pixel
-----

.. c:function:: Pixel get_pixel_coords(uint32_t position, uint32_t scale, float length, Pixel center, float orientation)

  :param position: An unsigned integer needed for positional purpose.
  :type position: :c:type:`uint32_t`
  :param scale: Scaling of the angle.
  :type scale: :c:type:`uint32_t`
  :param length: radius.
  :type length: :c:type:`float`
  :param center: center.
  :type center: :c:type:`Pixel`
  :param orientation: An additionnal offset to add.
  :type orientation: :c:type:`float`
  :rtype: :ref:`Pixel <Pixel-type>`
  :return: The pixel initialized in relationship to the given settings.

  This function return an pixel initialized in relationship to the given settings,

  by first getting the angle:

  .. code-block:: python

    float angle_degrees = get_angle(position, scale, orientation)   ;
    float radians = angle_degrees / 180.0 * PI  ;

  and applying the following formel to get the :c:data:`x` and :c:data:`y` values:

  .. code-block:: c

    Pixel.x = cosf(radians) * length + center.x ;
    Pixel.y = sinf(radians) * length + center.y ;

.. _get_middle_from_line:

.. c:function:: Pixel get_middle_from_line(Line line)

  :param line: The line to get the middle point from.
  :type line: :c:data:`Line`
  :rtype: :ref:`Pixel <Pixel-type>`
  :return: The pixel middle point from the given line.



.. _generate_segment:

Line
----

.. c:function:: Line *generate_segment(Pixel start_point, float length, float angle)

  :param start_point: The segment start point.
  :type start_point: :c:type:`Pixel`
  :param length: The length of the segment.
  :type length: :c:type:`float`
  :param angle: segment incline :ref:`angle <angle-settings-definition>`.
  :type angle: :c:type:`float`
  :rtype: :ref:`Line * <Line-type>`
  :return: An line starting at :c:data:`start_point` from length :c:data:`length` incline from :ref:`angle <angle-settings-definition>`.



Arc
---

.. c:function:: Arc *generate_circle_arc(float radius, Pixel center, float start_pos, float circle_part)

  :param radius: the radius starting from the center argument.
  :type radius: :c:type:`float`
  :param center: The center from where generate the circle arc.
  :type center: :c:type:`Pixel`
  :param start_pos: The start position given as an :ref:`angle in degress <angle-settings-definition>`.
  :type start_pos: :c:type:`float`
  :param circle_part: An angle value, in degrees, representing the part of an entire circle of the arc and so the length of the arc in relationship to the radius.
  :type circle_part: :c:type:`float`
  :rtype: :ref:`Arc * <Arc-type>`.
  :return: A pointer on an :ref:`Arc <Arc-type>`.

           + from radius :c:data:`radius`.
     
           + from center :c:data:`center`.
     
           + length from part of an circle :c:data:`circle_part`.
     
           + starting at offset :c:data:`start_pos` which will give the start point from the arc.