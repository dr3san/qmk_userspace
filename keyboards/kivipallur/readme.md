# kivipallur

![kivipallur](imgur.com image replace me!)

*A short description of the keyboard/project*
Kivipallur is a 38-key split ergo keyboard with a 25 mm thumb trackball.
It uses Kailh Choc V1 switches.
The design of Kivipallur was inspired by Keyball, KLOR and TOTEM keyboards.

* Keyboard Maintainer: [Andres Sakk](https://github.com/dr3san)
* Hardware Supported: Since the keyboard is diodeless and therefore requires a specific amount of pins, it only supports the 0xCB Helios. Not pro-micro compatible.
* Hardware Availability: [KeebSupply](https://keeb.supply/) sells the Helios

Make example for this keyboard (after setting up your build environment):

    make kivipallur:default

Flashing example for this keyboard:

    make kivipallur:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

* **Physical reset button**: Press the button on the Helios PCB for 1 second - some may have pads you must short instead
