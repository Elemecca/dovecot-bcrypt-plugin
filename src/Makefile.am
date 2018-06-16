auth_moduledir = $(moduledir)/modules/auth
auth_module_LTLIBRARIES = libbcrypt_plugin.la

libbcrypt_plugin_la_CFLAGS = $(LIBDOVECOT_INCLUDE)
libbcrypt_plugin_la_LIBADD = $(LIBDOVECOT)
libbcrypt_plugin_la_LDFLAGS = -module -avoid-version
libbcrypt_plugin_la_SOURCES = \
    bcrypt-plugin.c \
    crypt_blowfish.c

noinst_HEADERS = \
    crypt_blowfish.h
