##*****************************************************************************
## $Id: ac_genders_libdir.m4,v 1.1 2007-01-17 00:52:10 chu11 Exp $
##*****************************************************************************

# Used to specify the location of the genders library file and test that it
# is usable
AC_DEFUN([AC_GENDERS_LIBDIR],
[
  AC_MSG_CHECKING(for --with-genders-libdir)
  AC_ARG_WITH(genders-libdir,
     AS_HELP_STRING([--with-genders-libdir=path],
                    [define directory for genders library file]),
     [ case "$withval" in
     yes)
         withgenderslibdir=yes
         ;;
     no)
         ;;
     *)
         withgenderslibdir=yes
         GENDERS_LIBDIR="-L$withval"
         ;;
     esac ]
  )
  AC_MSG_RESULT(${withgenderslibdir=no})
  save_genders_libdir_LDFLAGS="$LDFLAGS"
  save_genders_libdir_LIBS="$LIBS"
  LDFLAGS="$LDFLAGS $GENDERS_LIBDIR"
  AC_CHECK_LIB(genders, genders_handle_create, ,
               AC_MSG_ERROR([libgenders must be installed]))
  LDFLAGS="$save_genders_libdir_LDFLAGS"
  LIBS="$save_genders_libdir_LIBS"
  AC_SUBST(GENDERS_LIBDIR)
])
