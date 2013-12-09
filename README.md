# Firmwares for the Costar replacement controllers

Custom firmwares to replace stock Costar controllers allow
you to program your keyboard. Firmwares include:

* The Frosty Flake (for Cooler Master Quick Fire Rapid)
* The Kitten Paw (for Filco Majestouch full size)
* The Black Petal (for Rosewill full size)
* The Pegasus Hoof (for Filco Majestouch Tenkeyless)

For more information, please see WIKI http://deskthority.net/wiki/Costar_replacement_controllers#Build_Instructions

## Compiling

You need to select the correct MODEL and LAYOUT variables in the Makefile

```
MODEL = hoof
LAYOUT = ANSI_ISO_JIS
MCU = atmega32u2
F_CPU = 16000000
B_LOADER = \"jmp\ 0x7000\"
```

Then run the make command in a terminal. Always run a `make clean` first.

```
make clean; make
```

## Flashing the controller

```
dfu-programmer atmega32u2 erase
dfu-programmer atmega32u2 flash binaries/[flake|paw|hoof|petal]_ANSI_ISO_JIS.hex
dfu-programmer atmega32u2 start
```


