AC_INIT(temper_query, 0.1, ansel@horn.name)
AC_CONFIG_SRCDIR(src)
AM_INIT_AUTOMAKE(foreign)
AC_PROG_CC
AC_CHECK_HEADERS(hidapi/hidapi.h)
AC_SEARCH_LIBS(hid_init, [hidapi-hidraw hidapi-libusb])
AC_OUTPUT(Makefile src/Makefile)
