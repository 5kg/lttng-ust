AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/tests/utils

LIBTAP=$(top_builddir)/tests/utils/libtap.la

noinst_PROGRAMS = prog
prog_SOURCES = prog.c
prog_LDADD = $(top_builddir)/snprintf/libustsnprintf.la \
	$(LIBTAP)

dist_noinst_SCRIPTS = test_snprintf
