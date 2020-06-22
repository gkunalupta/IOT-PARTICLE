# IOT-PARTICLE
projects and firmware for argon development board using argon development board


# Reference for ble protocol
Beacon url

https://www.youtube.com/watch?v=4Q4UPWCpDg8

https://learn.adafruit.com/introduction-to-bluetooth-low-energy/gatt

https://www.argenox.com/library/bluetooth-low-energy/ble-advertising-primer/
https://devzone.nordicsemi.com/nordic/short-range-guides/b/bluetooth-low-energy/posts/ble-characteristics-a-beginners-tutorial



# Reference for GPS and GPS receivers

Navigation system

Constellations of satellites  forms the transmitter from which radio signals are captured by the navigation receiver  devices to get the location .
Global navigation satellite system(GNSS) is the global coverage by the satellites so that they can send signals to receiver devices so that they can get their location.
Types of GNSS- GPS(USA), Galileo(European), GLONASS( Russia), etc

https://en.wikipedia.org/wiki/Satellite_navigation


Navigation receivers-

These are hardware devices which collects the radio signals transmitted from GNSS and calculate the location.
A GPS receiver monitors multiple satellites and solves equations to determine the precise position of the receiver and its deviation from true time. At a minimum, four satellites must be in view of the receiver for it to compute four unknown quantities (three position coordinates and clock deviation from satellite time)


https://en.wikipedia.org/wiki/Assisted_GPS
https://en.wikipedia.org/wiki/Satellite_navigation_device#Consumer_applications


Gps signals 
https://en.wikipedia.org/wiki/GPS_signals#cite_note-FOOTNOTEGPS-IS-200%C2%A7&nbsp;20.3.4.1_(p.&nbsp;63%E2%80%93130)-7

https://learn.sparkfun.com/tutorials/gps-basics/all#gps-glossary



https://www.intechopen.com/books/multifunctional-operation-and-application-of-gps/gnsss-signals-and-receivers

https://www.gps.gov/technical/icwg/IS-GPS-200K.pdf

https://www.gps.gov/systems/gps/modernization/cnav/


The satellites continuously send data down to earth over dedicated RF frequencies. Our pocket-sized GPS receivers have tiny processors and antennas that directly receive the data sent by the satellites and compute your position,time ,etc. Simply amazing.


For NMEA MEDIATEk

https://cdn-shop.adafruit.com/datasheets/PMTK_A11.pdf

For nmea- it is the standard protocol defined by NMEa for communicating with GPS modules .GPS receiver communication is defined within this specification. Most computer programs that provide real time position information understand and expect data to be in NMEA format. This data includes the complete PVT (position, velocity, time) solution computed by the GPS receiver. The idea of NMEA is to send a line of data called a sentence that is totally self contained and independent from other sentences. There are standard sentences for each device category and there is also the ability to define proprietary sentences for use by the individual company. All of the standard sentences have a two letter prefix that defines the device that uses that sentence type. (For gps receivers the prefix is GP.) which is followed by a three letter sequence that defines the sentence contents. In addition NMEA permits hardware manufactures to define their own proprietary sentences for whatever purpose they see fit. All proprietary sentences begin with the letter P and are followed with 3 letters that identifies the manufacturer controlling that sentence. For example a Garmin sentence would start with PGRM and Magellan would begin with PMGN.

http://aprs.gids.nl/nmea/#allgp
https://www.gpsinformation.org/dale/nmea.htm

For NMEA MEDIATEk

Mt339 SOC datasheet-
https://s3-ap-southeast-1.amazonaws.com/mediatek-labs-imgs/downloads/51c3cf5aaee074767384ab70d4f7d602.pdf?response-content-disposition=inline%3B%20filename%3DMT3339_Datasheet.pdf&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEKT%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaDmFwLXNvdXRoZWFzdC0xIkgwRgIhAMfLeRq07J9tpf5F7yVvz%2Fww8DDOJlX%2BppeItVDc7HxWAiEAj73tsEX4RHoCIX8iq4IdpC1ps%2BaKFjYD233Y8Cu%2BJeAqvgMIHRABGgw0NDk2OTY5OTIwNjYiDKoqGBHgM%2BVWjpe%2BHCqbA0PpCe8idfWlcuIOCST2RLdD8X3x3HC6lET2g89HBw7tRTqP9F50WGC3IJmdKyCap6OpqFXEuQbX%2BmRiQ%2BeA5O2dpcbzsNr5Oa8qnPAwbVNJOil13NfZrJRxDoUL4CjT9CrX3FLLEehjg1Y53pik035pM6lKIz%2BJcbW0xlRhdnQXZmK3a5yzroVMaeBJdM8akODQQrlncEoI4A4p%2Bd8vUgkcgv6r6oyAUXWJTKGchr1XCVfUrYSYhD1HNuS9sLEsv4frrFsKQhLADJpAh1S8q5nayv03ZBDzswx40f8n9CqCSWEeI5Gm5hQZ2C%2FapDO7OKJ%2BvHiuYRarS6TGwOtRPAfBQGUSHLhtWPGNpscaPj0UwEDYSK%2BvV5sv81QSAaO6EtgJvIIDOswbYiXZEEZzukJCAo2uDY1duHpyn%2FImDtXDUlFo8up3v4RjX4kpBppf2pxeJ7fHgMjEOnSap4T9by1mVJNnmLQ6WlHW2k%2Bvwk7j3HMy5h6d98gMMHUP2z5PTKrHPobTk50JokFwlMJ8gtm7s6xq4oZ7f99rTjCz3v%2F2BTrqAfLdEcsfVNS4uoPy2nmDA6giPwUJEjRPeXmayVJ7pjaCqPDYrSGvcuMN5vXLSu%2BrBj%2Fv%2FYtrgD4AwPAeMuXbRqPc5n8L3S%2FO%2FTezDyv9Tc7AsaIMI5%2FAXAOBcr%2BZuXHGxeiauKzENTt%2F%2BFYt2mrD4rrpb%2BiGZnoRedfpbrJMsYZVUP7Y21nOFc%2FHPCz9am93HeI%2FoTeiyzOeLOaxMdlVbThMxJHe4a6u2dXJeo28WEuYuu%2ByvCwepCw0jvL0FzHOTolbXPda%2FAJkKw3kXTc0205ZZE6NxI3l4OxQacLQpZkjsINf1ra%2FodiVZw%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=ASIAWRNAHRNBM2VUMY7W%2F20200609%2Fap-southeast-1%2Fs3%2Faws4_request&X-Amz-Date=20200609T204826Z&X-Amz-SignedHeaders=host&X-Amz-Expires=600&X-Amz-Signature=56b12006e65d8b3eb2a82d794cacea24e3213db2438c9d17e47529e2c97006c6


 
https://s3-ap-southeast-1.amazonaws.com/mediatek-labs-imgs/downloads/6c524d3058a03e0371774c4c76f00813.pdf?response-content-disposition=inline%3B%20filename%3DMT3339_Product_Brief.pdf&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEKT%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaDmFwLXNvdXRoZWFzdC0xIkgwRgIhAMfLeRq07J9tpf5F7yVvz%2Fww8DDOJlX%2BppeItVDc7HxWAiEAj73tsEX4RHoCIX8iq4IdpC1ps%2BaKFjYD233Y8Cu%2BJeAqvgMIHRABGgw0NDk2OTY5OTIwNjYiDKoqGBHgM%2BVWjpe%2BHCqbA0PpCe8idfWlcuIOCST2RLdD8X3x3HC6lET2g89HBw7tRTqP9F50WGC3IJmdKyCap6OpqFXEuQbX%2BmRiQ%2BeA5O2dpcbzsNr5Oa8qnPAwbVNJOil13NfZrJRxDoUL4CjT9CrX3FLLEehjg1Y53pik035pM6lKIz%2BJcbW0xlRhdnQXZmK3a5yzroVMaeBJdM8akODQQrlncEoI4A4p%2Bd8vUgkcgv6r6oyAUXWJTKGchr1XCVfUrYSYhD1HNuS9sLEsv4frrFsKQhLADJpAh1S8q5nayv03ZBDzswx40f8n9CqCSWEeI5Gm5hQZ2C%2FapDO7OKJ%2BvHiuYRarS6TGwOtRPAfBQGUSHLhtWPGNpscaPj0UwEDYSK%2BvV5sv81QSAaO6EtgJvIIDOswbYiXZEEZzukJCAo2uDY1duHpyn%2FImDtXDUlFo8up3v4RjX4kpBppf2pxeJ7fHgMjEOnSap4T9by1mVJNnmLQ6WlHW2k%2Bvwk7j3HMy5h6d98gMMHUP2z5PTKrHPobTk50JokFwlMJ8gtm7s6xq4oZ7f99rTjCz3v%2F2BTrqAfLdEcsfVNS4uoPy2nmDA6giPwUJEjRPeXmayVJ7pjaCqPDYrSGvcuMN5vXLSu%2BrBj%2Fv%2FYtrgD4AwPAeMuXbRqPc5n8L3S%2FO%2FTezDyv9Tc7AsaIMI5%2FAXAOBcr%2BZuXHGxeiauKzENTt%2F%2BFYt2mrD4rrpb%2BiGZnoRedfpbrJMsYZVUP7Y21nOFc%2FHPCz9am93HeI%2FoTeiyzOeLOaxMdlVbThMxJHe4a6u2dXJeo28WEuYuu%2ByvCwepCw0jvL0FzHOTolbXPda%2FAJkKw3kXTc0205ZZE6NxI3l4OxQacLQpZkjsINf1ra%2FodiVZw%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=ASIAWRNAHRNBM2VUMY7W%2F20200609%2Fap-southeast-1%2Fs3%2Faws4_request&X-Amz-Date=20200609T204827Z&X-Amz-SignedHeaders=host&X-Amz-Expires=600&X-Amz-Signature=4b80a09624051762a111115ea29b6af9a547d61206c6fb78798988abac233732



Mediatek NMEA commands.

https://cdn-shop.adafruit.com/datasheets/PMTK_A11.pdf
https://whitebream.nl/files/product/Fastrax_NMEA-CommandManual.pdf


GPS module PA6H-
https://cdn-shop.adafruit.com/datasheets/GlobalTop-FGPMMOPA6H-Datasheet-V0A.pdf

Adafruit gps featherwing-
https://cdn-learn.adafruit.com/downloads/pdf/adafruit-ultimate-gps-featherwing.pdf
https://learn.adafruit.com/adafruit-ultimate-gps-featherwing/overview




