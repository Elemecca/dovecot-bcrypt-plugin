/* Written by Sam Hanes <sam@maltera.com> in 2018.
 *
 * No copyright is claimed, and the software is hereby placed in the
 * public domain. In case this attempt to disclaim copyright and place
 * the software in the public domain is deemed null and void, then the
 * software is Copyright (c) 2018 Sam Hanes and it is hereby released to
 * the general public under the following terms:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted.
 *
 * There's ABSOLUTELY NO WARRANTY, express or implied.
 *
 * It is my intent that you should be able to use this on your system,
 * as part of a software package, or anywhere else to improve security,
 * ensure compatibility, or for any other purpose. I would appreciate
 * it if you give credit where it is due and keep your modifications in
 * the public domain as well, but I don't require that in order to let
 * you place this code and any modifications you make under a license
 * of your choice.
 */

#include <string.h>
#include <stdio.h>

#include <dovecot/lib.h>
#include <dovecot/module-dir.h>
#include <dovecot/password-scheme.h>

#include "crypt_blowfish.h"

#define OUTPUT_LEN 7 + 22 + 31 + 1


static int bcrypt_verify(
    const char *plaintext,
    const char *user ATTR_UNUSED,
    const unsigned char *raw_password,
    size_t size,
    const char **error_r ATTR_UNUSED
) {
    char output[OUTPUT_LEN];
    char *crypt_res;
    size_t hash_len;
    int res, i;

    memset(output, 0, OUTPUT_LEN);
    crypt_res = php_crypt_blowfish_rn(
        plaintext, raw_password, output, OUTPUT_LEN
    );

    if (!crypt_res) {
        res = -1;
    } else if (strlen(output) != (hash_len = strlen(raw_password))) {
        res = -1;
    } else {
        // constant-time compare
        res = 0;
        for (i = 0; i < hash_len; i++) {
            res |= (output[i] ^ raw_password[i]);
        }
    }

    memset(output, 0, OUTPUT_LEN);
    return (res == 0);
}


static void bcrypt_generate(
    const char *plaintext,
    const char *user ATTR_UNUSED,
    const unsigned char **raw_password_r,
    size_t *size_r
) {
    char *output;
    char options[OUTPUT_LEN];
    char *crypt_res;
    const char *salt;
    int cost;

    cost = 10;
    salt = password_generate_salt(22);
    snprintf(options, OUTPUT_LEN, "$2y$%02u$%s", cost, salt);

    output = t_malloc(OUTPUT_LEN);
    crypt_res = php_crypt_blowfish_rn(
        plaintext, options, output, OUTPUT_LEN
    );

    if (!crypt_res) {
        // this seems weird, but dovecot-libsodium-plugin does it
        // and the interface doesn't seem to have a way to return errors
        abort();
    } else {
        *raw_password_r = output;
        *size_r = OUTPUT_LEN;
    }
}


static const struct password_scheme bcrypt_scheme =
    { "BCRYPT", PW_ENCODING_NONE, 0, bcrypt_verify, bcrypt_generate };

void bcrypt_plugin_init(struct module *module ATTR_UNUSED)
{
    password_scheme_register(&bcrypt_scheme);
}

void bcrypt_plugin_deinit(void)
{
    password_scheme_unregister(&bcrypt_scheme);
}

const char *password_scheme_version = DOVECOT_ABI_VERSION;
