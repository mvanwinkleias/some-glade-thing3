AC_INIT([some-glade-thing3], [1.0], [bug-automake@gnu.org])

AC_ARG_VAR(use_project_datadir, Set to 1 to use project-dir/data as the datadir)
AM_CONDITIONAL([conditional_use_project_datadir], [test "$use_project_datadir" -eq "1"])

dnl PKG_CHECK examples
dnl PKG_CHECK_MODULES([SQLITE], [sqlite3])
PKG_CHECK_MODULES([GTK], [gtk+-3.0])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 data/Makefile
 data/glade/Makefile
 data/text/Makefile
 src/Makefile
])
AC_CONFIG_MACRO_DIRS([m4])

LT_INIT
AC_OUTPUT
