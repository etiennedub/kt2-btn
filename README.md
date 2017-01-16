## Description 
Add physical buttons to a Kindle (KT2) to change pages. A ATtiny10 is connected to two push buttons (previous and next page) and to the Kindle Rx pin. 

**This project is still in development. It is not completed (see Development Status section).**

## Requirements
### Hardware
The following pieces are required:

* ATtiny10
* Capacitors
* Two push buttons
* 1.8v regulator (probably useless)
* Tools
### Software
The Kindle need root access without password.

## Documentation
The principle is really simple, every time someone presses the next page button, the ATtiny10 will send *sudo\nF\n* at 115200 bps on the Kindle Rx pin. The previous command will connect as *root* and execute the ***F*** program which will simulate a touch press on the right side of the screen. The same thing is produced with the previous page button but the message will be *sudo\nB\n* which will execute the ***B*** program.

### Diagram

				 ATiny10
				+-------+
		BTN1 +--+PB0 PB3+--+
				|       |
		 GND +--+GND VCC+--+ 1.8V
				|       |
		  Rx +--+PB1 PB2+--+ BTN2
				+-------+

## Installation 
### Kindle
**You need to have root access to your Kindle.**

Binary files, **bw** and **fw**,  can be found in *kindle/bin* folder of the repository or you can compile from source. Copy binary files as **B** and **F** in */usr/bin/* of the Kindle. The simplest way is to use SCP (SSH connection is required).

### ATtiny10
Flash *main.hex* on the ATtiny10, you can also compile from source. I use a Arduino and follow this [tutorial](http://junkplusarduino.blogspot.ca/p/attiny10-resources.html) to flash it. 

## Development Status
At this moment, the pages can change but the ATtiny10 still need external source. I didn't find a good pin on the Kindle where I can connect the ATtiny10 VCC pin. I'm looking to add a 1.8v regulator directly to the Kindle battery. Also, I didn't add the buttons to the Kindle case yet.

The project is still in development and I will update this repository with any further update.
