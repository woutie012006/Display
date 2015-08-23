# CNC

Project for the interfacing of a CNC milling machine.

#Software

##Embedded software
Project will be based on the Arduino Uno hardware, especially in the prototype fase(s), but the software will be created by me as much as possible.
The embedded software will be built mainly in AtmelStudio and uploaded directly to the uC without a bootloader.
I don't want to rely on standard libraries from for example Adafruit.

Will include:
* PC <-> uC communication, probably over WiFi through the ESP8266
* Resistive touch input
* Display of standard figures (buttons/text etc.)
* Display image file

Would like to include:
* The ability to create new standard figures (with layer system as in Photoshop for example)
* Capacitive touch input

##PC software

Will be built in Qt Designer for multi-platform support.

Will include:
* PC <-> uC communication over the internet
* Cutting project uploading
* Manual controls

Would like to include
* Live simulation of the cut

#Hardware

The hardware side still has to be figured out, I am planning on building everything myself. From the stepper drivers to the uC motherboard.

Parts would include:
* Nema17 stepper motors for X,Y and Z positioning
* Brushless motor as the spindle
* Aluminium extrusion as the frame
