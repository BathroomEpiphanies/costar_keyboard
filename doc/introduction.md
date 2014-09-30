## Introduction

Many computer keyboards consist of a number of mechanical switches
wired up in a matrix to a microcontroller. The microcontroller senses
which keys are pressed and reports this to the computer. The keyboards
from the manufacturer Costar which the controllers this firmware is
intended to be run on are of this type.

Microcontroller generally have what is called GPIO pins (General
Purpose Input/Output), these may be able to read digital (or analogue)
values, or output digital (or analogue values). A mechanical switch
keyboard will only need to deal with digital signals. These pins when
set to input mode also generally have internal "pull-up
resistors". These resistors ensure that the logic level at the input
pin is held at "1" (usually VCC, the supply voltage, +5V in case of
USB) as long as there is nothing connecting the pin to the "0" level
(usually GND, ground, 0V).

It would be impractical to have a microcontroller with the number of
input pins required to connect every key of a keyboard to its own
pin. The solution to this is to arrange the keys in a matrix. 

Each row of the matrix is connected to an input pin. The input pins
have their pull-up resistors activated. Each columns of the matrix is
connected to an output pin. All columns are normally kept at "1". Each
column is then, one at a time, "pulled" to "0" one at a time. If there
is a key of the currently activated column pressed the input at that
keys row pin will be pulled to "0".

To "scan the matrix" the microcontroller needs to pull one column low,
read which rows that have been pulled low, and move on to the next
column pin until all keys have been read. To avoid a phenomenon called
ghosting where it looks like keys that aren't in fact pressed looks
like they are, diodes are usually added to the matrix. Ghosting will
not be explained here.

