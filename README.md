`temper_query`
==============

Keep It Simple, Stupid, (KISS) userspace driver for the TEMPer_Gold_v3.1
temperature sensor.

Goals
-----

Built to support querying the temperature from the TEMPer_Gold_v3.1 sensor on a
embedded Linux environment (like the Raspberry Pi) with minimal dependencies
(only [HIDAPI](https://github.com/signal11/hidapi)).  Though untested, it should
be readily cross-platform amongst POSIX systems and easily ported to Windows
systems.

Due to nuanced variations in various TEMPer devices, it is unlikely to, but may,
support other TEMPer sensor versions.

Build
-----

`temper_query` can be built using the standard POSIX build procedure:

    $ cd temper_query
    $ mkdir build && cd build
    $ ../configure
    $ make

The resulting executable can then be installed to the system:

    $ sudo make install

### HIDAPI Dependency

`temper_query` depends on HIDAPI to query and receive the temperature response
from the TEMPer sensor.  It can be pulled from its
[GitHub](https://github.com/signal11/hidapi) repo and compiled from source or
downloaded in binary form via the appropriate system package manager.

Run
---

The `temper_query` can then be run (with elevated privileges to allow direct USB
access to the TEMPer sensor):

    $ sudo temper_query

If successful, `termper_query` will print the current temperature in degrees
Celsius to standard output.

Acknowledgements
----------------

As my first project working directly with raw HID USB, I would not have been
able to hack together this program without standing on the shoulders of previous
work:

* [This](https://github.com/padelt/temper-python/issues/84) forum thread on the
  [temper-python](https://github.com/padelt/temper-python) repository
* [This](https://github.com/edorfaus/TEMPered/issues/51) forum thread on the
  [TEMPered](https://github.com/edorfaus/TEMPered) repository
* The [source code](https://github.com/edorfaus/TEMPered/blob/master/utils/hid-query.c)
  of the `hid-query` utility

