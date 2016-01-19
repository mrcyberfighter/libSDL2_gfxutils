.. _Forms-generating-functions:

Forms generating functions
==========================

Polygons
--------

.. c:function:: Polygon *generate_polygon_radius(uint32_t sides, float radius, Pixel center, float orientation)

  :param sides: The number of sides of the polygon to generate.
  :type  sides: :c:type:`uint32_t`
  :param radius: The radius of the polygon to generate.
  :type  radius: :c:type:`float`
  :param center: The wants center of the polygon.
  :type center: :c:type:`Pixel`
  :param orientation: An offset in degrees to add to influence the incline of the polygon.
  :type  orientation: :c:type:`float`
  :rtype: :ref:`Polygon * <Polygon-type>`
  :return: A regular convex polygon .

   :note: This result in a regular polygon with :c:data:`sides` sides with radius length :c:data:`radius` starting at :c:data:`orientation`.

   :see: :ref:`A blue 12 sides polygon convex <polygon-images>`.

   :note: An polygon is convex if all vertex from the polygon are on the same side from every edge of the polygon.

.. c:function:: Polygon *generate_corners_rounded_polygon(uint32_t sides, float radius, Pixel center, float orientation)

  :param sides: The number of sides of the polygon to generate.
  :type  sides: :c:type:`uint32_t`
  :param radius: The radius of the polygon to generate.
  :type  radius: :c:type:`float`
  :param center: The wanted center of the polygon.
  :type center: :c:type:`Pixel`
  :param orientation: An offset in degrees to add to influence the incline of the polygon.
  :type  orientation: :c:type:`float`
  :rtype: :ref:`Polygon * <Polygon-type>`
  :return: A polygon which corners are arcs which size is in relationship to the number of sides of the polygon.

   :see: :ref:`A blue 12 sides rounded corners polygon <rounded-corners-polygon-images>`.

  :note: The radius goes from the center to the center of the circle arcs: the rounded corners.

.. c:function:: Polygon *generate_sides_rounded_polygon(uint32_t sides, float radius, Pixel center, float orientation)

  :param sides: The number of sides of the polygon to generate.
  :type  sides: :c:type:`uint32_t`
  :param radius: The radius of the polygon to generate.
  :type  radius: :c:type:`float`
  :param center: The wanted center of the polygon.
  :type center: :c:type:`Pixel`
  :param orientation: An offset in degrees to add to influence the incline of the polygon.
  :type  orientation: :c:type:`float`
  :rtype: :ref:`Polygon * <Polygon-type>`
  :return: A polygon which sides are rounded according the number of sides of the polygon.

   :see: :ref:`A blue 12 sides rounded corners polygon <sides-rounded-polygon-images>`.
 
  :note: The radius goes from the center to the center of the circle arcs.
 
   .. warning::

     The parameter sides must be conform to:

       .. code-block:: python

         sides % 2 != 0

     I can only generate odd sides numbered sides rounded polygons.

.. c:function:: Polygon *generate_rounded_inside_out_polygon(uint32_t sides, float radius, Pixel center, float orientation)

  :param sides: The number of arcs of the polygon to generate.
  :type  sides: :c:type:`uint32_t`
  :param radius: The radius of the polygon to generate.
  :type  radius: :c:type:`float`
  :param center: The wanted center of the polygon.
  :type center: :c:type:`Pixel`
  :param orientation: An offset in degrees to add to influence the incline of the polygon.
  :type  orientation: :c:type:`float`
  :rtype: :ref:`Polygon * <Polygon-type>`
  :return: A polygon alternating inside nad outside arcs the number of sides of the polygon.

   :see: :ref:`A blue 12 sides rounded inside out polygon <rounded-inside-out-polygon-images>`.
 
  :note: The radius goes from the center to the center of the circle arcs.
 
   .. warning::

     The sides number is multiply per 2 to obtains an even numbered polygon.


.. c:function:: Polygon *generate_alternate_inside_half_circle_polygon(uint32_t sides, float radius, Pixel center, float orientation)

  :param sides: The number of sides of the polygon to generate.
  :type  sides: :c:type:`uint32_t`
  :param radius: The radius of the polygon to generate.
  :type  radius: :c:type:`float`
  :param center: The wanted center of the polygon.
  :type center: :c:type:`Pixel`
  :param orientation: An offset in degrees to add to influence the incline of the polygon.
  :type  orientation: :c:type:`float`
  :rtype: :ref:`Polygon * <Polygon-type>`
  :return: A rounded polygon alternating arcs rounded to the outside and to the inside of the polygon.

   :see: :ref:`A blue 12 sides alternate inside half circle polygon <alternate-inside-half-circle-polygon-images>`.

  :note: The radius goes from the center to the center of the circle arcs.

   .. warning::

     The result is an even polygon of the double of the sides values.

.. c:function:: Polygon *generate_alternate_outside_half_circle_polygon(uint32_t sides, float radius, Pixel center, float orientation, bool side_arcs)

  :param sides: The number of sides of the polygon to generate.
  :type  sides: :c:type:`uint32_t`
  :param radius: The radius of the polygon to generate.
  :type  radius: :c:type:`float`
  :param center: The wanted center of the polygon.
  :type center: :c:type:`Pixel`
  :param orientation: An offset in degrees to add to influence the incline of the polygon.
  :type  orientation: :c:type:`float`
  :param sides_arcs: Boolean value determine if the sides which are not half-cirlce arcs should be rounded.
  :type  sides_arcs: :c:type:`bool`
  :rtype: :ref:`Polygon * <Polygon-type>`
  :return: A polygon with half-circle rounded to the inside from the half sum from the sides of the polygon and the other is even an arc or an straight line according to the :c:data:`side_arcs` boolean value.

   :see: :ref:`A blue 12 sides alternate outside half circle polygon <alternate-outside-half-circle-polygon-images>`.
 
  :note: The radius goes from the center to the center of the circle arcs.
 
   .. warning::

     The result is an even polygon of the double of the sides values.

Stars
-----

.. c:function:: Star *generate_star(uint32_t pikes, float radius, Pixel center, float orientation)

  :param pikes: The number of pikes of the star.
  :type  pikes: :c:type:`uint32_t`
  :param radius: The radius of the star base polygon not the spike.
  :type  radius: :c:type:`float`
  :param center: The wants center from the star.
  :type center: :c:type:`Pixel`
  :param orientation: An offset in degrees to add to influence the incline of the star.
  :type  orientation: :c:type:`float`
  :rtype: :ref:`Star * <Star-type>`
  :return: A star with the number of wants pikes according to the given settings.
  
   :note: This function generate a star based on a regular polygon.

   :see: :ref:`A blue 24 peaks star <star-images>`.
 
  :note: The radius value is the radius of the base polygon.
 
.. c:function:: Star *generate_pentagram_star(float radius, Pixel center, float orientation)

  :param radius: An base value for the generation of the 5 pikes star.
  :type  radius: :c:type:`float`
  :param center: The wants center from the 5 pikes star.
  :type center: :c:type:`Pixel`
  :param orientation: An offset in degrees to add to influence the incline of the star.
  :type  orientation: :c:type:`float`
  :rtype: :ref:`Star * <Star-type>`
  :return: A not a regular 5 pikes star but a pentagram star or pentacle.
  
   :note: This function generate a simply 5 extremity star with the particularity that the resulting star is not a regular star but a pentagram star.

   :see: :ref:`A blue pentagram star <pentagram-star-images>`.

  :note: The radius value is the radius of the base polygon.

.. c:function:: Star *generate_hexagram_star(float radius, Pixel center, float orientation)

  :param radius: An base value for the generation of the 6 pikes star.
  :type  radius: :c:type:`float`
  :param center: The wants center from the 6 pikes star.
  :type center: :c:type:`Pixel`
  :param orientation: An offset in degrees to add to influence the incline of the star.
  :type  orientation: :c:type:`float`
  :rtype: :ref:`Star * <Star-type>`
  :return: A not a regular 6 pikes star but a hexagram star or star of David.
  
   :note: This function generate a simply 6 extremity star, with the particularity that the resulting star is not a regular star but an hexagram star or star of David.

   :see: :ref:`A blue hexagram star <hexagram-star-images>`.

  :note: The radius value is the radius of the base polygon.

pentagram
---------

.. c:function:: Pentagram *generate_pentagram(float radius, Pixel center, float orientation)

  :param radius: An base value for the generation of the 5 pikes star.
  :type  radius: :c:type:`float`
  :param center: The wants center from the 5 pikes star.
  :type center: :c:type:`Pixel`
  :param orientation: An offset in degrees to add to influence the incline of the star.
  :type  orientation: :c:type:`float`
  :rtype: :ref:`Pentagram * <Pentagram-type>`
  :return: A pentagram or named pentacle.
  
   :note: This function generate an 5 extremity star with an centered pentagon from which every vertex go to the center.

   :see: :ref:`A blue pentagram <pentagram-images>`.

  :note: The radius value is the radius of the base polygon.

hexagram
--------

.. c:function:: Hexagram *generate_hexagram(float radius,Pixel center, float orientation)

  :param radius: An base value for the generation of the 6 pikes star.
  :type  radius: :c:type:`float`
  :param center: The wants center from the 6 pikes star.
  :type center: :c:type:`Pixel`
  :param orientation: An offset in degrees to add to influence the incline of the star.
  :type  orientation: :c:type:`float`
  :rtype: :ref:`Hexagram * <Hexagram-type>`
  :return: A hexagram.
  
   :note: This function generate a 6 extremity star with an centered hexagon from which every vertex go to the center.

   :see: :ref:`A blue hexagram <hexagram-images>`.

  :note: The radius value is the radius of the base polygon.

Fractal
-------

.. c:function:: Polygon *generate_fractal(uint32_t polygon, float radius, Pixel center, float orientation, bool open)

  :param polygon: Base polygon from the fractal.
  :type  polygon: :c:type:`uint32_t`
  :param radius: The radius from the base polygon.
  :type  radius: :c:type:`float`
  :param center: The wants center from the fractal.
  :type center: :c:type:`Pixel`
  :param orientation: An offset in degrees to add to influence the incline of the fractal.
  :type  orientation: :c:type:`float`
  :param open: Change the fractal pikes.
  :type  open: :c:type:`bool`
  :rtype: :ref:`Polygon * <Polygon-type>`
  :return: A strange fractal form coming from an crazy brain. :)
 
  :note: The radius goes from the center to the farest point of the fratcal (so equal to the :c:data:`real_length` value) .

Spiral
------

.. c:function:: Spiral *generate_simple_spiral(Pixel center, uint32_t turns, uint32_t base, float offset_exponent, float orientation,  bool reverse)

  :param center: The center from the spiral.
  :type center: :c:type:`Pixel`
  :param turns: The number of revolution of the spiral.
  :type  turns: :c:type:`uint32_t`
  :param base: the base number of points to make one turn (roundness).
  :type  base: :c:type:`uint32_t`
  :param offset_exponent: The factor to compute the distance between 2 points a turn offset.
  :type  offset_exponent: :c:type:`float`
  :param orientation: An offset in degrees to add to influence the incline of the spiral.
  :type  orientation: :c:type:`float`
  :param reverse: Reverse the spiral.
  :type  reverse: :c:type:`bool`
  :rtype: :ref:`Spiral * <Spiral-type>`
  :return: A spiral according to the given settings.

   :see: :ref:`A blue rounded 3 turns spiral <spiral-images>`.

  :note: The radius goes from the center to the end of the first entire revolution of the spiral.

   .. note::

      The :c:data:`base` and the :c:data:`offset_exponent` parameters values will influente of the size of the spiral.

      You cannot set an radius but the generating function does it.
  
      :note: The value from the :c:data:`base` parameter will be divided per two in the resulting spiral.
  
   .. warning::

      The :c:data:`turns` parameter value will be multiply per 2 to obtains the number of revolutions of the spiral.
   
      The :c:data:`base` parameter will be divided per two in the resulting spiral.
   
      I can only generate even spirals.

Wheels
------

.. c:function:: Polygon *generate_wheel(uint32_t polygon, float radius, Pixel center, float offset, float orientation)

  :param polygon: Number of sides of the wheel (base polygon).
  :type  polygon: :c:type:`uint32_t`
  :param radius: The radius of the wheel.
  :type  radius: :c:type:`float`
  :param center: The center from the wheel.
  :type center: :c:type:`Pixel`
  :param offset: Size of the peaks of the wheel.
  :type  offset: :c:type:`float`
  :rtype: :ref:`Polygon * <Polygon-type>`
  :return: A pointed wheel according to the given settings.
  
   :note: The peaks of the wheel are trigons like a star.

   :see: :ref:`A blue 24 peaks wheel <wheel-images>`.

  :note: The radius value is the radius of the base polygon.

   .. note::

     You must set an offset value other than 0 because it represent the size of the peaks of the wheel.

     The difference betwenn this wheel and a normal star is that is regular.

   :note: the radius Polygon member from this wheel is the radius of the base polygon from this wheel (interior).


   .. warning::

     The parameter polygon have a value conform to:

       .. code-block:: python

         360 % polygon == 0



.. c:function:: Polygon *generate_circular_saw_wheel(uint32_t polygon, float radius, Pixel center, float offset, float orientation, bool reverse)

  :param polygon: Number of sides of the circular saw (base polygon).
  :type  polygon: :c:type:`uint32_t`
  :param radius: The radius from the points of the circular saw like wheel.
  :type  radius: :c:type:`float`
  :param center: The center from the circular saw like wheel.
  :type center: :c:type:`Pixel`
  :param offset: Size of the points.
  :type  offset: :c:type:`float`
  :param reverse: Reverse the shift from the circular saw like wheel.
  :type  reverse: :c:type:`bool`
  :rtype: :ref:`Polygon * <Polygon-type>`
  :return: A circular saw like pointed wheel.
  
   :note: This function generate an circular saw like wheel. This is only an polygon with an rectangle triangle on the top of the edges.

   :see: :ref:`A blue 24 peaks circular saw <circular-saw-images>`.

  :note: The radius goes from the center to the end of the pikes (it's equal to the :c:data:`real_length` value).

   .. warning::

     The parameter polygon have a value conform to:

       .. code-block:: python

         360 % polygon == 0

.. c:function:: Polygon *generate_wheel_peaks_trigon(uint32_t sides, float radius, Pixel center, float peak_offset, float orientation)

  :param sides: Number of sides of the base polygon.
  :type  sides: :c:type:`uint32_t`
  :param radius: An base value for generating the wheel (rounded polygon).
  :type  radius: :c:type:`float`
  :param center: Center from the wheel (rounded polygon).
  :type center: :c:type:`Pixel`
  :param peak_offset: Peak offset.
  :type  peak_offset: :c:type:`float`
  :param orientation: An offset in degrees to add to influence the incline of the wheel (rounded polygon).
  :type  orientation: :c:type:`float`
  :rtype: :ref:`Polygon * <Polygon-type>`
  :return: A pointed wheel (rounded polygon) with peaks implemented as trigon which ends are mini arcs.
  
   :note: This function generate an wheel (rounded polygon) with peaking as trigons.

   :see: :ref:`A blue 24 trigon peaks wheel <trigon-peaks-wheel-images>`.
 
  :note: The radius value is the radius of the base polygon.

   .. warning::

     The parameter polygon have a value conform to:

       .. code-block:: python

         360 % polygon == 0



.. c:function:: Polygon *generate_wheel_peaks_rounded_square(uint32_t sides, float radius, Pixel center, float peak_length, float orientation)

  :param sides: Number of sides from the wheel (rounded polygon).
  :type  sides: :c:type:`uint32_t`
  :param radius: Radius from the wheel (rounded polygon).
  :type  radius: :c:type:`float`
  :param center: Center from the wheel (rounded polygon).
  :type center: :c:type:`Pixel`
  :param peak_length: Size of the peaks.
  :type  peak_length: :c:type:`float`
  :param orientation: An offset in degrees to add to influence the incline of the wheel (rounded polygon).
  :type  orientation: :c:type:`float`
  :rtype: :ref:`Polygon * <Polygon-type>`
  :return: A pointed wheel with peaks looking like a tube.
  
   :note: This function generate an pointed wheel (rounded polygon) with peaks looking like a tube but they are only right-angled line to the sides and connected trough an arc.

   :see: :ref:`A blue 24 rounded square peaks wheel <rounded-square-peaks-images>`.

  :note: The radius value is the radius of the base polygon.

   .. warning::

     The parameter sides have a value conform to:

       .. code-block:: python

         360 % sides == 0 and sides <= 24

