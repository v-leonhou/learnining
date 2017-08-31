dnl $Id$
dnl config.m4 for extension fastcgi

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(fastcgi, for fastcgi support,
dnl Make sure that the comment is aligned:
dnl [  --with-fastcgi             Include fastcgi support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(fastcgi, whether to enable fastcgi support,
dnl Make sure that the comment is aligned:
dnl [  --enable-fastcgi           Enable fastcgi support])

if test "$PHP_FASTCGI" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-fastcgi -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/fastcgi.h"  # you most likely want to change this
  dnl if test -r $PHP_FASTCGI/$SEARCH_FOR; then # path given as parameter
  dnl   FASTCGI_DIR=$PHP_FASTCGI
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for fastcgi files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       FASTCGI_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$FASTCGI_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the fastcgi distribution])
  dnl fi

  dnl # --with-fastcgi -> add include path
  dnl PHP_ADD_INCLUDE($FASTCGI_DIR/include)

  dnl # --with-fastcgi -> check for lib and symbol presence
  dnl LIBNAME=fastcgi # you may want to change this
  dnl LIBSYMBOL=fastcgi # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $FASTCGI_DIR/$PHP_LIBDIR, FASTCGI_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_FASTCGILIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong fastcgi lib version or lib not found])
  dnl ],[
  dnl   -L$FASTCGI_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(FASTCGI_SHARED_LIBADD)

  PHP_NEW_EXTENSION(fastcgi, fastcgi.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
