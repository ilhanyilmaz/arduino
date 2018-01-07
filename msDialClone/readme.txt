2018/01/07

Inspired by GreatScott's "Hacked!: Using and HDD Motor as Rotary Encoder"

Converting an hdd motor as a HID to function as a scroll and similar actions.

Current arduino code only gets analog input from brushless motor. 
Uses A3, A4, A5 input pins and outputs wheater it is rotated clockwise or counterclokwise.

Needs an arduino with 32u4 chip to be used as a HID device (mouse).

A-star 32U4 could be a cheap alternative.

Current prototype configuration:
Red wire: A3
White wire: A4
Green wire: A5
Blue wire: GND
Serial baud rate: 115200

Further:
MCP601 can be used to convert analog to digital. Schematic in the video description (MCP602 used in the video).
