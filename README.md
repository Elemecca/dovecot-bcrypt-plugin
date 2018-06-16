# bcrypt password hashing for Dovecot

[bcrypt] is an adaptive password hashing function originally designed
for OpenBSD and is used as the default hash for the system password
database in OpenBSD and some Linux distributions. On these systems
Dovecot supports bcrypt under the name `BLF-CRYPT` via the libc
`crypt(3)` function.

However, bcrypt is also available as a library in many languages,
and is used by many applications on systems whose libc does not
support it. Of particular note, bcrypt is the default password hash
used by the PHP standard library. On these systems Dovecot's built-in
support does not work and patching the system libc to add support
is not a viable solution.

This project is a Dovecot plugin that integrates the [crypt_blowfish]
library used by PHP under the name `BCRYPT`. It therefore allows the
use of a consistent implementation of bcrypt across all systems,
regardless of whether the system libc supports it.

[bcrypt]: https://en.wikipedia.org/wiki/Bcrypt
[crypt_blowfish]: http://www.openwall.com/crypt/


## Installing

This package uses autoconf, and thus follows the standard procedure:

```
autoreconf -i  # only when working from git
./configure
make
sudo make install
```

If you installed Dovecot from your system package manager you may
need to adjust the installation prefix. For example:

```
./configure --prefix=/usr
```


## Using

Configure Dovecot to use the `BCRYPT` password scheme, e.g. by
setting `default_pass_scheme = BCRYPT` in your SQL or LDAP configuration
file or `scheme=BCRYPT` in the args to `passwd-file`. You can also
prefix hashes with `{BCRYPT}` to set the scheme for just that hash.
See [the Dovecot wiki][dc-pass-schemes] for more information.

The `doveadm` utility can be used to generate bcrypt hashes:

```
doveadm pw -s BCRYPT
```

You can also test that Dovecot can verify your hashes with `doveadm`:

```
doveadm auth test <username>
```

[dc-pass-schemes]: https://wiki2.dovecot.org/Authentication/PasswordSchemes


## Contributing

Please report vulnerabilities privately by email to <sam@maltera.com>.
If you want to encrypt your message, my PGP public key can be found
[on keybase](https://keybase.io/elemecca) and has the fingerprint
`7EB4 F2D2 C841 27D7 7822 4445 BE2E 6CB5 DC3F D519`.

Non-security bugs and feature requests may be submitted via GitHub
issues. Pull requests are of course appreciated.


## Copying

Written by Sam Hanes <sam@maltera.com> in 2018.

No copyright is claimed, and the software is hereby placed in the
public domain. In case this attempt to disclaim copyright and place
the software in the public domain is deemed null and void, then the
software is Copyright (c) 2018 Sam Hanes and it is hereby released to
the general public under the following terms:

Redistribution and use in source and binary forms, with or without
modification, are permitted.

There's ABSOLUTELY NO WARRANTY, express or implied.

It is my intent that you should be able to use this on your system,
as part of a software package, or anywhere else to improve security,
ensure compatibility, or for any other purpose. I would appreciate
it if you give credit where it is due and keep your modifications in
the public domain as well, but I don't require that in order to let
you place this code and any modifications you make under a license
of your choice.
