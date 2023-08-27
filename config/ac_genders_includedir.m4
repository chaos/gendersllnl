##*****************************************************************************
## $Id: ac_genders_includedir.m4,v 1.1 2007-01-17 00:52:10 chu11 Exp $
##*****************************************************************************

# Used to specify the location of the genders header file and test that it
# is usable
AC_DEFUN([AC_GENDERS_INCLUDEDIR],
[
  AC_MSG_CHECKING(for --with-genders-includedir)
  AC_ARG_WITH(genders-includedir,
     AS_HELP_STRING([--with-genders-includedir=path], 
                    [define directory for genders header file]),
     [ case "$withval" in
     yes)
         withgendersincludedir=yes
         ;;
     no)
         ;;
     *)
         withgendersincludedir=yes
         GENDERS_INCLUDEDIR="-I$withval"
         ;;
     esac ]
  )
  AC_MSG_RESULT(${withgendersincludedir=no})
  save_genders_includedir_CPPFLAGS="$CPPFLAGS"
  CPPFLAGS="$CPPFLAGS $GENDERS_INCLUDEDIR"
  AC_CHECK_HEADERS(genders.h, ,
                   AC_MSG_ERROR([missing required header file]))
  CPPFLAGS="$save_genders_includedir_CPPFLAGS"
  AC_SUBST(GENDERS_INCLUDEDIR)
])
