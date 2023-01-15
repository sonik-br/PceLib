# PceLib
PC Engine (PCE) input library for Arduino

For Arduino Leonard/Pro Micro (5V 16MHz)

## Controller compatibility

It's been tested and confirmed to work with:

| Accessory        | Notes                                    |
|------------------|------------------------------------------|
| 2-button Pad     |                                          |
| AvenuePad 6      |                                          |
| Multitap         | Model PI-PD003                           |

Multitap notes:
Not possible to detect if a pad is connected or not.<br/>
Lib will report all multitap ports as having a device connected.

## How to use
PCE controllers works with 5V so I recommend to use a 5V Arduino.

This library requires [DigitalIO](https://github.com/greiman/DigitalIO).

I recommend the usage of [SukkoPera's fork of DigitalIO](https://github.com/SukkoPera/DigitalIO) as it supports a few more platforms.


### PCE port pins (mini din)

| PCE | Description | Arduino |
|-----|-------------|---------|
| 1   | VCC/POWER   | 5V      |
| 2   | DATA0       |         |
| 3   | DATA1       |         |
| 4   | DATA2       |         |
| 5   | DATA3       |         |
| 6   | SEL         |         |
| 7   | CLR         |         |
| 8   | GROUND      | GND     |


## Credits

It uses the [DigitalIO](https://github.com/greiman/DigitalIO) from greiman.

I recommend the usage of [SukkoPera's fork of DigitalIO](https://github.com/SukkoPera/DigitalIO) as it supports a few more platforms.

Based on [documentation](https://github.com/dshadoff/PCE_Controller_Info) from David Shadoff.<br/>
And from emulator [NitroGrafx](https://github.com/FluBBaOfWard/NitroGrafx/blob/main/Docs/pcetech_edit.txt).

Special thanks to [MisterAddons](https://github.com/misteraddons) and my friend Lucas Milani.


## Warning
Code and wiring directions are provided to you 'as is' and without any warranties. Use at your own risk.
