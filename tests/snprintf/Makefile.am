AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/tests/utils

LIBTAP=$(top_builddir)/tests/utils/tap/libtap.la

noinst_PROGRAMS = prog
prog_SOURCES = prog.c
prog_LDADD = $(top_builddir)/snprintf/libustsnprintf.la \
	$(LIBTAP)

noinst_SCRIPT = test_snprintf
EXTRA_DIST = test_snprintf
