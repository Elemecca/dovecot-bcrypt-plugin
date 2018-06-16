AC_INIT([dovecot-bcrypt-plugin], [1.0])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([no-define foreign tar-ustar])
AM_MAINTAINER_MODE

AC_PROG_CC
AC_PROG_LIBTOOL

DC_DOVECOT
DC_DOVECOT_MODULEDIR

AC_CONFIG_FILES([
    Makefile
    src/Makefile
])
AC_OUTPUT
