#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libSDL2_gfxutils], [2.0.0], [mrcyberfighter@gmail.com], [], [http://www.open-source-projects.net/libSDL2_gfxutils/libSDL2_gfxutils_presentation.html])

${CFLAGS= -Wall -O2}

AC_CONFIG_SRCDIR([.])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE
AM_PROG_AR

LT_INIT

AM_PROG_CC_C_O



AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MKDIR_P



# Checks for libraries.
AC_CHECK_LIB([SDL2],
             [SDL_CreateRenderer],
             ,
             AC_MSG_ERROR(
                  SDL2 library required from library: SDL2_gfxutils.
                  Install the SDL2 library trough your package-manager or
                  from source. Then try to install SDL2_gfxutils again.,  1)           
                        
                         
             )


AC_CHECK_LIB([SDL2_gfx],
             [polygonRGBA],
             ,
             AC_MSG_ERROR(
                  SDL2_gfx library required from library: SDL2_gfxutils.
                  Install the SDL2_gfx library trough your package-manager or
                  from source. Then try to install SDL2_gfxutils again.         )
             )
       
AC_CHECK_LIB([m],
             [sqrtf],
             ,
             AC_MSG_ERROR(
                  Math library required from library: SDL2_gfxutils.),
              )

      
         
         
         
# Checks for header files.
AC_CHECK_HEADERS([stdio.h stdlib.h stdbool.h stdint.h math.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([powf sqrtf cosf sinf calloc])

AC_CONFIG_FILES([Makefile
                 Sources/Makefile])

prefix=/usr
           
AC_OUTPUT

echo "
      *** Package: ${PACKAGE_STRING} ***

      ${PACKAGE_NAME} Version ${PACKAGE_VERSION}
      Prefix: ${prefix}
      Compiler: ${CC} ${CFLAGS} ${CPPFLAGS}
      libraries: ${LIBS}

      System checks OK, now run:
      $ make
      $ sudo make install

      Enjoy to use ${PACKAGE_NAME} !!!
      "
