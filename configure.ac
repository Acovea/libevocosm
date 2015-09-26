<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b

dnl --------------------------------
dnl Initialization macros.
dnl --------------------------------

AC_INIT(libevocosm/evocosm.h)

dnl -----------------------------------------------
dnl Package name and version number (user defined)
dnl -----------------------------------------------
=======
AC_INIT(libevocosm/evocosm.h)
AC_CONFIG_MACRO_DIR([m4])
>>>>>>> version 4.0.2

GENERIC_LIBRARY_NAME=libevocosm

#release versioning
<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
GENERIC_MAJOR_VERSION=3
GENERIC_MINOR_VERSION=1
GENERIC_MICRO_VERSION=0

#shared library versioning
GENERIC_LIBRARY_VERSION=1:0:0
#                       | | |
#                +------+ | +---+
#                |        |     |
#             current:revision:age
#                |        |     |
#                |        |     +- increment if interfaces have been added
#                |        |        set to zero if interfaces have been removed
#                                  or changed
#                |        +- increment if source code has changed
#                |           set to zero if current is incremented
#                +- increment if interfaces have been added, removed or changed


dnl --------------------------------
dnl Package name and version number
dnl --------------------------------
=======
GENERIC_MAJOR_VERSION=4
GENERIC_MINOR_VERSION=0
GENERIC_MICRO_VERSION=2

#shared library versioning
GENERIC_LIBRARY_VERSION=4:0:0
>>>>>>> version 4.0.2

AC_SUBST(GENERIC_LIBRARY_VERSION)

PACKAGE=$GENERIC_LIBRARY_NAME
AC_SUBST(GENERIC_LIBRARY_NAME)

GENERIC_VERSION=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION
GENERIC_RELEASE=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION
AC_SUBST(GENERIC_RELEASE)
AC_SUBST(GENERIC_VERSION)

VERSION=$GENERIC_VERSION

<<<<<<< 53bb9b38239f0b6fb908619d97286ae529277d0b
AM_INIT_AUTOMAKE($PACKAGE, $VERSION, no-define)

dnl -----------------------------------------------
dnl Checks for programs.
dnl -----------------------------------------------

AC_PROG_CC
AC_PROG_CXX
AM_PROG_LIBTOOL
AM_SANITY_CHECK
AC_LANG_CPLUSPLUS

dnl -----------------------------------------------
dnl Check for option programs
dnl -----------------------------------------------
AC_CHECK_PROG(HAVE_DOXYGEN, doxygen, true, false)
	if test $HAVE_DOXYGEN = "false"; then
		AC_MSG_WARN([*** doxygen not found, code documentation will not be built])
	fi
AM_CONDITIONAL(HAVE_DOXYGEN, $HAVE_DOXYGEN)

dnl -----------------------------------------------
dnl Checks for required headers
dnl -----------------------------------------------

AC_HEADER_STDC
AC_HEADER_STDBOOL
AC_CHECK_HEADERS(stdint.h unistd.h fcntl.h)

dnl -----------------------------------------------
dnl Checks for libraries.
dnl -----------------------------------------------

dnl AC_CHECK_LIB(coyotl, sigdig)
AC_CHECK_HEADER(prng.h, mwc1038.h mtwister.h)

dnl -----------------------------------------------
dnl Generates Makefile's, configuration files and scripts
dnl -----------------------------------------------

AC_OUTPUT(Makefile libevocosm.pc libevocosm/Makefile funcopt/Makefile docs/Makefile)

=======
AM_INIT_AUTOMAKE($PACKAGE, $VERSION, [no-define dist-bzip2 dist-zip])

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AM_PROG_LIBTOOL
AM_SANITY_CHECK
AC_LANG_CPLUSPLUS
AC_HEADER_STDC
AC_HEADER_STDBOOL
AC_CHECK_HEADERS(stdint.h unistd.h fcntl.h)
AC_CHECK_LIB(brahe, brahe_prng_init)
AC_CHECK_HEADER(prng.h)

AC_ARG_ENABLE([docgen],
              AS_HELP_STRING([--enable-docgen], [generate documentation with Doxygen]),
              [docgen=$enableval],
              [docgen=no])

if test "x$docgen" = "xyes"
then
    AC_CHECK_PROG(HAVE_DOXYGEN, doxygen, true, false)
        if test $HAVE_DOXYGEN = "false"; then
            AC_MSG_WARN([*** doxygen not found, code documentation will not be built])
        fi
    AM_CONDITIONAL(HAVE_DOXYGEN, $HAVE_DOXYGEN)
else
    AM_CONDITIONAL(HAVE_DOXYGEN, "false")
fi

AC_OUTPUT(Makefile libevocosm.pc libevocosm/Makefile examples/function_optimization/Makefile examples/prisoners_dilemma/Makefile)
>>>>>>> version 4.0.2
