# Controller for a DC 12V 2 Channel Serial Port RS232 Relay Board

The code for this is slowing being released in several different languages
and flavours...

## Device:
https://www.flyrobo.in/dc-12v-2-channel-serial-port-rs232-relay-module-board
https://www.amazon.com.au/WQBYCBC-Universal-2-Channel-Professional-Portable/dp/B0BYKFJJGJ/

![DC12v RS232 Relay Board](resources/device.webp?raw=true "DC12v RS232 Relay Board")

# Information from manufactor:

This is DC 12V 2 Channel Serial Port RS232 Relay Module Board

Features:

* Interface: DB9 Female
* Easy to operate
* It supports 5V or 9-12V input voltage
* Improved stability, with a capacitor filter circuit.
* Serial instructions are single-byte instructions

- 2 Channel Relay Module;
- 2 Power input: DC 12V(8.5-13.5V).
- PC:Serial ports RS232 Control Relay;
- Power indicator : LED lights;
- Output indication : relay output with LED indicators,easy to see working status of the relay;
- Communication protocol: UART protocol communication, baud rate 9600kpbs, 8 data bits, one stop bit, no parity. Each data frame contains eight bytes. Two-way data transmission.
- Baud rate 9600kbps, 8 data bits, one stop bit, no parity. Each data frame contains eight bytes.
- PCB Size : 71x47mm


# Control commands

## Reading status(reading the satus of the relay (on/off))

`0x55  0x56  0x00  0x00  0x00  0x00  0x00  0xAB`

## Relay open (issue this command,Relay open,COM connect to NO)

Channel 1 : `0x55  0x56  0x00  0x00  0x00  0x01  0x01  0xAD`

Channel 2 : `0x55  0x56  0x00  0x00  0x00  0x02  0x01  0xAE`

## Relay close (issue this command,Relay close,COM disconnect NO,and COM connect to NC)

Channel 1 : `0x55  0x56  0x00  0x00  0x00  0x01  0x02  0xAE`

Channel 2 : `0x55  0x56  0x00  0x00  0x00  0x02  0x02  0xAF`

## Relay toggle(Relay status reversal, if COM connect to NO,this commands will Disconnect COM to NO and Reverse COM connect to NC,and vice versa)

Channel 1 : `0x55  0x56  0x00  0x00  0x00  0x01  0x03  0xAF`

Channel 2 : `0x55  0x56  0x00  0x00  0x00  0x02  0x03  0xB0`

## Relay momentary(Relay COM connect to NO,disconnect after 200MS)

Channel 1 : `0x55  0x56  0x00  0x00  0x00  0x01  0x04  0xB0`
Channel 2 : `0x55  0x56  0x00  0x00  0x00  0x02  0x04  0xB1`

Once issue a command, will have return fame,7th byte of return fame mean the status of Relay.

# Return command

## Return relay open(return this command,mean COM connect to NO)

Channel 1 :  `0x33  0x3C  0x00  0x00  0x00  0x01  0x01  0x71`

Channel 2 :  `0x33  0x3C  0x00  0x00  0x00  0x02  0x01  0x72`

## Return relay close(return this command,mean COM disconnect NO , and COM connect to NC)

Channel 1 : `0x33  0x3C  0x00  0x00  0x00  0x01  0x02  0x72`

Channel 2 : `0x33  0x3C  0x00  0x00  0x00  0x02  0x02  0x73`
