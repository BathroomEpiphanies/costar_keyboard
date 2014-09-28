# Firmwares for keyboard controllers

Custom firmwares to replace stock Costar controllers allowing you to
program your keyboard.

Firmwares include:

* The Frosty Flake (for Cooler Master Quick Fire Rapid)
* The Kitten Paw (for Filco Majestouch full size)
* The Black Petal (for Rosewill full size)
* The Pegasus Hoof (for Filco Majestouch Tenkeyless)

For more information, please see the [Costar replacement controllers page
on the Deskthority Wiki](http://deskthority.net/wiki/Costar_replacement_controllers).

## Intentions

One goal of this project is to make a keyboard firmware for ATmega32U2 based
daughter boards as simple (within reason) as possible. It is supposed to be a
first introduction to how a keyboard works.

Features will be limited to the following topics:

* Basic keyboard (nothing mouse or other devices)
* Simplified layout definitions
* Timer interrupt matrix scans
* Basic de-bouncing
* PWM control for LEDs

For more advanced features there are other keyboard firmwares already way ahead
of this project. If you want to contribute by increasing clarity,
understandability or simplicity, please do.
Also feel free to fork, clone or copy selected parts to diverge however
you like from the constraints of this project.

## Other keyboard firmwares

Some other noteworthy keyboard firmware projects are:

* https://github.com/tmk/tmk_keyboard
* (add more here..)

Forks from this project:

* https://github.com/pa3zo6/costar_keyboard
* (add more here..)

## Compiling firmwares

In order to compile firmwares, [`avr-gcc`](http://www.nongnu.org/avr-libc/) is
required. Please ensure you have it installed before moving to next step.

You need to select the correct `MODEL` and `LAYOUT` variables in the Makefile

```make
MODEL = [flake|paw|hoof|petal]
LAYOUT = [ANSI_ISO_JIS|DVORAK]
MCU = atmega32u2
F_CPU = 16000000
B_LOADER = \"jmp\ 0x7000\"
```

Then run the `make` command in a terminal. Always run a `make clean` first.

```sh
$ make clean; make
```

If the process is successful, you would find binary firmware with
extension `.hex` inside the binaries folder.

## Flashing the controller

Make sure you install [`dfu-programmer`](http://dfu-programmer.github.io/) first.

```sh
$ dfu-programmer atmega32u2 erase
$ dfu-programmer atmega32u2 flash binaries/[flake|paw|hoof|petal]_ANSI_ISO_JIS.hex
$ dfu-programmer atmega32u2 start
```

## License

`costar_keyboard` is free software released under the MIT license.

See the `COPYING.MIT` file or <http://opensource.org/licenses/MIT>
for more details.

Some files distributed as part of `costar_keyboard` are licensed under
different licenses:

* portions of `Makefile`: Public domain (by Eric B. Weddington, Jörg
  Wunsch et al.);
* `lib/keycode.h`: GPL v2 or later (by Jun Wako);
* `lib/usb_keyboard_debug.c`: MIT (by PJRC.COM, LLC).
