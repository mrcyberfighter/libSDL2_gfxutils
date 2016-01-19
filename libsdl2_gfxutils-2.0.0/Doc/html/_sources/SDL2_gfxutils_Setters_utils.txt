.. _form-setter-functions:

Setters functions
=================

  This functions will permit you to change and so transform and or animating your forms.

  Or to change their colors.

.. _set-form-center-function:

Center
------

.. c:function:: void set_form_center(Form *form, Pixel center, bool translate)

  :param form: The :c:data:`form` to set a new center.
  :type form: :c:type:`Form`
  :param center: The new center to set.
  :type center: :c:type:`Pixel`
  :param translate: Translating all coordinates according the new center.
  :type  translate: :c:type:`bool`
  :rtype: :c:type:`void`
  :return: :c:type:`void`

  This function set a **new** :c:data:`center` to the given :c:data:`form` with or without **translating** all coordinates from the :ref:`Form <Form-type>` according the **new** :c:data:`center`.

.. _set-form-radius-function:

Radius (size)
-------------

.. c:function:: void set_form_radius(Form *form, float radius)

  :param form: The :c:data:`form` to set a new radius.
  :type form: :c:type:`Form`
  :param radius: The new radius to set.
  :type radius: :c:type:`float`
  :rtype: :c:type:`void`
  :return: :c:type:`void`

  This function set a **new** :c:data:`radius` to the given :c:data:`form`.

  What permit to change the :ref:`Form <Form-type>` **size** directly by setting a new :c:data:`radius` by given a value and not a **scaling** :data:`factor` as in the :ref:`scale_form() <scale-form-function>` function.

  :warning: **Use only integers values** or not more than **3 precision** (:c:data:`%.3f`) in the **radius**, :ref:`Form <Form-type>` generating functions, argument.

Color
-----

.. c:function:: void set_form_color(Form *form, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)

  :param  form: The :ref:`Form <Form-type>` to change the color from.
  :type   form: :c:type:`Form`
  :param   red: a value between 0 and 255.
  :type    red: :c:type:`uint8_t`
  :param green: a value between 0 and 255.
  :type  green: :c:type:`uint8_t`
  :param  blue: a value between 0 and 255.
  :type   blue: :c:type:`uint8_t`
  :param alpha: a value between 0 and 255.
  :type  alpha: :c:type:`uint8_t`
  :rtype: :c:type:`void`
  :return: :c:type:`void`

  This function set a **new** color by updating the :ref:`Color <Color-type>` type members from the given :c:data:`form`.

.. c:function:: void set_line_color(Line *line, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)

  :param  form: The :ref:`Line <Line-type>` to change the color from.
  :type   form: :c:type:`Form`
  :param   red: a value between 0 and 255.
  :type    red: :c:type:`uint8_t`
  :param green: a value between 0 and 255.
  :type  green: :c:type:`uint8_t`
  :param  blue: a value between 0 and 255.
  :type   blue: :c:type:`uint8_t`
  :param alpha: a value between 0 and 255.
  :type  alpha: :c:type:`uint8_t`
  :rtype: :c:type:`void`
  :return: :c:type:`void`

  This function set a **new** color by updating the :ref:`Color <Color-type>` type members from the given :c:data:`line`. 