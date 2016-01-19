Miscellaneous
=============

  Here are presented the trajectories computing function.
   
.. _compute_trajectory-function:
 
trajectories
------------

.. c:function:: void compute_trajectory(Pixel positions[], Line trajectory, uint32_t steps)

  :param positions: An array from type Pixel from size steps.
  :param trajectory: A line on where settings the pixels along.
  :param steps: The number of pixel to set along the line trajectory.
  :rtype: :c:type:`void`
 
  This function feed the array :c:data:`positions[steps]` by computing the number of pixels :c:data:`steps` along the :ref:`Line line <Line-type>` at equal distance.
 
  .. warning::
   
    You can declare the positions array or allocated it dynamicaly:
   
    .. code-block:: c
     
      uint32_t steps = 32 ;
     
      Pixel positions[steps] ;
     
      /** Or **/
     
      Pixel *positions = (Pixel *) calloc((ssize_t) steps, sizeof(Pixel)) ;
     
  .. note:: Guideline animation.
 
    After executing this function you get an array of pixels with which you can implement an animation with the array of pixels as guideline.
    
   
