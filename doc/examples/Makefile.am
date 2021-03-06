doc_examplesdir = ${docdir}/examples
doc_examples_easy_ustdir = ${docdir}/examples/easy-ust
doc_examples_gen_tpdir = ${docdir}/examples/gen-tp
doc_examples_demodir = ${docdir}/examples/demo
doc_examples_hello_static_libdir = ${docdir}/examples/hello-static-lib
doc_examples_demo_tracefdir = ${docdir}/examples/demo-tracef

if BUILD_JNI_INTERFACE
doc_examples_java_juldir = ${docdir}/examples/java-jul
dist_doc_examples_java_jul_DATA = java-jul/Makefile \
								  java-jul/Hello.java \
								  java-jul/run
SUBDIRS_JUL = java-jul
endif

dist_doc_examples_DATA = README

dist_doc_examples_easy_ust_DATA = easy-ust/Makefile \
	easy-ust/sample.c \
	easy-ust/sample_component_provider.h easy-ust/tp.c

dist_doc_examples_gen_tp_DATA = gen-tp/Makefile \
	gen-tp/sample.c  gen-tp/sample_tracepoint.tp

dist_doc_examples_demo_DATA = demo/demo.c \
	demo/demo-trace \
	demo/Makefile \
	demo/README \
	demo/tp2.c \
	demo/tp3.c \
	demo/tp.c \
	demo/ust_tests_demo2.h \
	demo/ust_tests_demo3.h \
	demo/ust_tests_demo.h

dist_doc_examples_hello_static_lib_DATA = hello-static-lib/Makefile \
	hello-static-lib/hello.c \
	hello-static-lib/README \
	hello-static-lib/ust_tests_hello.h \
	hello-static-lib/tp.c

dist_doc_examples_demo_tracef_DATA = demo-tracef/Makefile \
	demo-tracef/demo-tracef.c \
	demo-tracef/README

if NO_SHARED
# Don't build examples if shared libraries support was explicitly
# disabled.
else
# Copies are for VPATH build support
SUBDIRS_PROXY = easy-ust demo hello-static-lib demo-tracef

if BUILD_GEN_TP_EXAMPLES
SUBDIRS_PROXY += gen-tp
endif

all-local:
	@if [ x"$(srcdir)" != x"$(builddir)" ]; then \
		for subdir in $(SUBDIRS_PROXY) $(SUBDIRS_JUL); do \
			cp -fR $(srcdir)/$$subdir $(builddir); \
		done; \
	fi; \
	if [ x"$(shell echo "$(top_srcdir)" | grep "^/" | wc -l)" = x"1" ]; then \
		echo "Examples: absolute top_srcdir path $(top_srcdir)"; \
		rel_src_subdir=""; \
	else \
		echo "Examples: relative top_srcdir path $(top_srcdir)"; \
		rel_src_subdir="../"; \
	fi; \
	if [ x"$(shell echo "$(top_builddir)" | grep "^/" | wc -l)" = x"1" ]; then \
		echo "Examples: absolute top_builddir path $(top_builddir)"; \
		rel_build_subdir=""; \
	else \
		echo "Examples: relative top_builddir path $(top_builddir)"; \
		rel_build_subdir="../"; \
	fi; \
	for subdir in $(SUBDIRS_PROXY); do \
		(cd $$subdir && $(MAKE) AM_CC="$(CC)" AM_CPPFLAGS="$(CPPFLAGS) -I$$rel_src_subdir$(top_srcdir)/include/ -I$$rel_build_subdir$(top_builddir)/include/" AM_CFLAGS='$(CFLAGS)' AM_LDFLAGS='$(LDFLAGS) -L../../../liblttng-ust/.libs/ -Wl,-rpath="$(PWD)/../../liblttng-ust/.libs/"' LTTNG_GEN_TP_PATH="../../../tools/" $(AM_MAKEFLAGS) all && cd ..) || exit 1; \
	done; \
	if [ x"$(SUBDIRS_JUL)" != x"" ]; then \
		for subdir in $(SUBDIRS_JUL); do \
			(cd $(SUBDIRS_JUL) && $(MAKE) JAVA_CLASSPATH_OVERRIDE="../../../liblttng-ust-jul" JAVA_JARFILE_OVERRIDE="liblttng-ust-jul.jar" $(AM_MAKEFLAGS) all && cd ..) || exit 1; \
		done; \
	fi;

clean-local:
	@for subdir in $(SUBDIRS_PROXY); do \
		if [ -d $$subdir ]; then \
			(cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) clean && cd ..) || exit 1; \
		fi; \
	done; \
	if [ x"$(SUBDIRS_JUL)" != x"" ]; then \
		for subdir in $(SUBDIRS_JUL); do \
			if [ -d $$subdir ]; then \
				(cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) clean && cd ..) || exit 1; \
			fi; \
		done; \
	fi; \
	if [ x"$(srcdir)" != x"$(builddir)" ]; then \
		for subdir in $(SUBDIRS_PROXY) $(SUBDIRS_JUL); do \
			rm -rf $(builddir)/$$subdir; \
		done; \
	fi;
endif
