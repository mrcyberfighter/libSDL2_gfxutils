Getters functions
=================

  This functions are **convienence** functions to get the **current value** of the **generic** :ref:`Form <Form-type>` type **members**.

  :note: But you can easily access the members directly with the `->` pointer notation.

----------------------------------------------------------------------------------------------------------------------------------------

Center
------

.. c:function:: Pixel get_form_center(Form *form)

  :param form: The :c:data:`form` to get the center from.
  :type form: :c:type:`Form`
  :rtype: :c:type:`Pixel`
  :return: The current center :ref:`Pixel <Pixel-type>` member of the given :c:data:`form` from type :ref:`Form <Form-type>`.

Color
-----

.. c:function:: Color get_form_color(Form *form)

  :param form: The :c:data:`form` to get the :c:type:`Color` from.
  :type form: :c:type:`Form`
  :rtype: :c:type:`Color`
  :return: The current :ref:`Color <Color-type>` member of the given :c:data:`form` from type :ref:`Form <Form-type>`.

Length
------

.. c:function:: float get_form_length(Form *form)

  :param form: The :c:data:`form` to get the length from.
  :type form: :c:type:`Form`
  :rtype: :c:type:`float`
  :return: The current :c:data:`length` member of the given :c:data:`form` from type :ref:`Form <Form-type>`.

  .. note::
 
    The member named :c:data:`length` is very often the **radius** from the form.
  
    See the :ref:`Forms generating functions <Forms-generating-functions>` page for the what the :c:data:`length` member represent.
  
    Or in other words how it is compute from the often, :c:data:`radius` argument value.

Real length
-----------

.. c:function:: float get_form_real_length(Form *form)

  :param form: The :c:data:`form` to get the real length from.
  :type form: :c:type:`Form`
  :rtype: :c:type:`float`
  :return: The current :c:data:`real_length` member of the given :c:data:`form` from type :ref:`Form <Form-type>`.
 
  .. note::
   
    The member named :c:data:`real_length` is the distance between the **center** and the **farest** *coordinates* from the **center**.
   
    :note: It can be used per example to build a bounding box from a polygon for collision detection or the purpose you want.

  :warning: The member name :c:data:`real_length` is not always exactly after executing :ref:`set_form_radius() <set-form-radius-function>` but nearly approximate. 
     
Orientation
-----------  
   
.. c:function:: float get_form_orientation(Form *form)

  :param form: The :c:data:`form` to get the length from.
  :type form: :c:type:`Form`
  :rtype: :c:type:`float`
  :return: The current :c:data:`orientation` member of the given :c:data:`form` from type :ref:`Form <Form-type>`.

  .. note:: The member and argument named :c:data:`orientation` is always given as argument.

    It represent the incline of the forms according :ref:`the angle measurement convention <angle-settings-definition>`.
  
    You can use the :c:data:`orientation` argument value to rotate a form if you generate and destroy the :ref:`Form <Form-type>`.
   