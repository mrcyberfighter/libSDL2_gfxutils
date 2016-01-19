Utils
=====

Check
-----

.. c:function:: void check_renderer(SDL_Renderer *pRenderer)
 
  :param pRenderer: The SDL2 Renderer
  :type  pRenderer: SDL_Renderer
  :rtype: :c:type:`void`
  :return: :c:type:`void`
 
  Check the validity of the :c:type:`SDL_Renderer`.
 
  .. Exit failure if the test fail.
 
  .. code-block:: c
   
    if (pRenderer == NULL) {
      fprintf(stderr,"SDL Renderer error (%s)\n",SDL_GetError());
      exit(EXIT_FAILURE) ;
    }
 
  .. note::
 
    Function used in all :ref:`displaying functions <displaying-functions>`.
 
.. c:function:: void check_form(Form *form)
 
  :param form: the :c:data:`form` to check.
  :type  form: :c:type:`Form`
  :rtype: :c:type:`void`
  :return: :c:type:`void`
 
  Check only if the given parameter is equal to :c:type:`NULL`.
 
  .. code-block:: c
   
    if (form == NULL) {
      fprintf(stderr,"Invalid form argument !\n");
      exit(EXIT_FAILURE) ;
    }
 
 
  .. note::
 
    Function used in all :ref:`forms setters functions <form-setter-functions>` and all :ref:`forms operations functions <form-operation-functions>`. 
  
Memory
------

.. c:function:: Form *new_form(uint32_t count)
 
  :param pRenderer: the number of coordinates pair to allocate.
  :type  pRenderer: :c:type:`uint32_t`
  :rtype: :ref:`Form <Form-type>`
  :return: A new allocated :ref:`Form <Form-type>`
 
  This function allocate the required space for the given :c:data:`count` argument number of coordinates arrays.
 
  And set the :c:data:`count` member from the returned :ref:`Form <Form-type>`.
 
  :warning: The other members must you set yourself.
 
.. c:function:: void free_form(Form *form)
 
  :param form: the :c:data:`form` to free.
  :type  form: :c:type:`Form`
  :rtype: :c:type:`void`
  :return: :c:type:`void`
 
  This function free the allocated coordinates arrays from the  :ref:`Form <Form-type>`, free the :c:data:`form` pointer and set it on :c:type:`NULL`.
 