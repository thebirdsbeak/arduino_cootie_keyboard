# arduino_cootie_keyboard
A cootie keyboard using the Keyboard.h library

Circuit diagram will follow shortly, but the set up is quite straightforward.

Using an Arduino Micro:

 - Connect a Pot to +ve and -ve, with wiper to A0
 - Connect 8ohm speaker to -ve and pin 10 on the Arduino
 - Connect Cootie key to 2 and 3 (dit and dah) on the Arduino, with the centre contact to -ve
 - Remember to debounce the cootie inputs via a resistor to +ve rail
 - Optionally, connects leds to pins 8 and 9 for a visual aid on timing
 
 Numbers,letters, and some punctuation is supported. Adding new punctuation or even prosigns should be self explanatory for the code.
 
 Currently, the speed is mapped to the full range of the potentiometer, however switch or if statements could easily replace the map function at the beginning of each loop if you wish to use discrete, known speeds.
