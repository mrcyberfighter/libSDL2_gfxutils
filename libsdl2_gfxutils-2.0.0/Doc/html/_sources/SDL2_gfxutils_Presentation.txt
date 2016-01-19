SDL2_gfxutils presentation
==========================

:library: **SDL2_gfxutils**
:version: 2.0.0
:platform: Linux, Windows, (Posix Compliant not tested).
:compiler: gcc, g++, clang, mingw32, mingw-w64-686, mingw-w64-x86_64.
:synopsis: **SDL2_gfxutils** a **SDL2_gfx** forms generating and manipulating helper functions set
:Licence: GPLv3
:author: Eddie Brüggemann <mrcyberfighter@gmail.com>

SDL2_gfxutils brief history
---------------------------

**SDL2_gfxutils** is issue from an collection of functions that i have implemented over the years, everytime i had a idea of a form to generate i try to implemented it as a function generating the sequence of coordinates or performing operations on a form.
At start i implemented my ideas with the *python pygame* module, which is based on the **SDL** library, by start i get only the functions to set a pixel according the a radius and an angle offset, so **SDL2_gfxutils** is a translation of *python* functions into the **C** language and the **SDL2_gfx** standart.


**SDL2_gfxutils** has been entirely rewritten after the first version release which suffers under severals bugs and was not handy to use, mostly for animations.

:note: After the disaster everything are right.

The new implementation from SDL2_gfxutils
+++++++++++++++++++++++++++++++++++++++++

All forms generating functions now return a **pointer** on a specific **SDL2_gfxutils** type compatible with the generic **SDL2_gfxutils** :ref:`Form <Form-type>` type.

The **pointers** permit to **manipulate** the forms for **transforming** or **animating** (*rotating*, *scaling*, *translating*, *mirroring*) functions **easily**.

The **pointers** can be destroyed at your convienence of course. And this mechanic is massively used in form generating functions. So that no memory space is lost.

The generic :ref:`Form <Form-type>` type has been change to contains coordinates from type :c:type:`float`, instead of type :c:type:`int16_t`, so that the **computation** like *rotating*, *scaling*, *translating*, *mirroring* are now exactly executed.

The subtype :c:type:`Pixel` members are now from type :c:type:`float`.

+ Some functions have been removed because they become useless, because of the new pointers system.

+ Some functions have been added for replacing the missing features, with many advantages, mostly for transforming or animating forms in the SDL2 mainloop.

+ All functions have been improved, favor of the pointers mechanic.

SDL2_gfxutils presentation
--------------------------

**SDL2_gfxutils** is en extension for the **SDL2_gfx** library helping you for the creation of the fantastics drawing your brain can imagined.

**SDL2_gfxutils** provide severals functions for severals usages:

  + A lot of forms generating functions, from the simple **polygons**, through **stars**, to the fantastic **fractals**.

  + High-level Transforming or animating functions (*rotating*, *scaling*, *translating* and *mirroring*) acting on an entire :ref:`Form <Form-type>`.

  + Low-level Transforming or animating functions (*rotating*, *scaling*, *translating* and *mirroring*) acting on a single :ref:`Pixel <Pixel-type>`.

  + Memory management and check functions.

:note: :ref:`I think it's easy to adapt the SDL2_gfxutils library to be compatible with others libraries than the SDL2 library <sdl2_gfxutils-others>`.

Operations functions which transform a form:
++++++++++++++++++++++++++++++++++++++++++++

- **Rotation** of a :ref:`Form <Form-type>` around his center from the wanted **degrees**.

- **Scaling** of a :ref:`Form <Form-type>` from the wanted **factor**.

- **Translation** of a :ref:`Form <Form-type>` from the wanted :data:`x` and :data:`y` values.

- **Mirroring** over the :data:`X` or :data:`Y` **axes** according to an :data:`center` **point**.


Form setters functions which change the settings of a form
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

- Setting a new :c:data:`center` of a :ref:`Form <Form-type>` with optionally translating all coordinates.

- Setting a new :c:data:`radius` what equal to scaling a :ref:`Form <Form-type>` except that instead a factor you can set a new size directly.

- Setting a new :c:data:`color` for the :ref:`Form <Form-type>` or a :ref:`Line <Line-type>`.

Form getters functions to get settings of a form
++++++++++++++++++++++++++++++++++++++++++++++++

- Getting the current :ref:`Form <Form-type>` :c:data:`center` value.

- Getting the current :ref:`Form <Form-type>` :c:data:`color`.

- Getting the current :ref:`Form <Form-type>` :c:data:`length` (often the **radius**).

- Getting the current :ref:`Form <Form-type>` :c:data:`orientation` (**offset** defining the incline of a :ref:`Form <Form-type>`).

- Getting the current :ref:`Form <Form-type>` :c:data:`real_length` (value defining the **distance** between the :data:`center` and the **most distant coordinate** from the :data:`center`).

  .. note:: You can use this member to build bounding boxes for collision detection per example.

Displaying forms functions
++++++++++++++++++++++++++

Each :ref:`Form <Form-type>` type has specific displaying functions.

Use each :ref:`Form <Form-type>` specific displaying function else the result will be undefined.

:note: But you can use the displaying function you want to display a :ref:`Form <Form-type>`, something the output is surprising.

.. note::

  For every displaying function it exist a :ref:`thickness setttable displaying function <thickness-settable-functions>` and an :ref:`anti-aliasing displaying function <anti-aliasing-functions>` except for the filled forms functions.

Length and middle Between 2 Pixels
++++++++++++++++++++++++++++++++++

- :ref:`Measure of the length of a Line <get_distance_pixels>`.

- :ref:`Get the Middle Pixel of a Line <get_middle_from_line>`.

.. _angle-settings-definition:

Angles
------

In the 2D display from SDL2: the **X axes** goes from left to right and the **Y axes** from up to down.

For the multiple used :data:`orientation` parameter from type :c:type:`float`. Sea the following image to become acquainted with the values and with the conventional angle values.

.. image:: ./_images/mark.png

:note: You can sea that 3 o'clock represent 0 degrees.

.. _Animations-advices:

Animations advice
-----------------

Polygon and forms are not only displayable object but can also be an guideline for the execution of an animation which moving a form trough the way of the lines from the polygon or the form.

**SDL2_gfxutils** provide an function :ref:`compute_trajectory() <compute_trajectory-function>` with which you can construct an moving line
by moving a form through the pixels of the :data:`positions` array by translating it with the :ref:`translate_form() <translate-form-function>` function.


SDL2_gfxutils Documentation License
-----------------------------------

This 'SDL2_gfxutils Documentation' is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.

To view a copy of this license, visit <http://creativecommons.org/licenses/by-nc/4.0/>.

.. image:: ./_images/by-nc.png

SDL2_gfxutils License
---------------------

.. note:: SDL2_gfxutils is under copyright from the GNU General Public License.


**SDL2_gfxutils** a **SDL2_gfx** forms generating and manipulating helper functions set.

Copyright (©) 2016 Brüggemann Eddie <mrcyberfighter@gmail.com>.            
                                                                         
**SDL2_gfxutils** is free software: you can redistribute it and/or modify          

it under the terms of the GNU General Public License as published by     

the Free Software Foundation, either version 3 of the License, or        

(at your option) any later version.                                      
                                                                         
**SDL2_gfxutils** is distributed in the hope that it will be useful,               

but WITHOUT ANY WARRANTY; without even the implied warranty of           

MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the             

GNU General Public License for more details.                              
                                                                         
You should have received a copy of the GNU General Public License        

along with **SDL2_gfxutils**. If not, see <http://www.gnu.org/licenses/>           


Credits
-------

.. topic:: Thank's

    Thank's to my **mother**, **my family** and **the doctors**.

    **Stay away from drugs:** drugs **destroy** your *brain* and your *life*.
