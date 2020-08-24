A small circuit made with a [Digispark](http://digistump.com/products/1) to remote control a LED floor lamp via infrared remote control.  

### Prerequisites ###

* Digispark USB
* LED floor lamp with DC 12V
* 2 x IRLZ 34N
* TSOP31238
* RC5 remote control
* Arduino IDE 
* Driver(Digispark Driver)(https://github.com/digistump/DigistumpArduino/releases/download/1.6.7/Digistump.Drivers.zip)

### Circuit ###
Circuit diagrams created with: [Fritzing](https://fritzing.org/)

![schematics](/circuit/CeilingSpotlightSketch_Schematics.png)
![wiring](/circuit/CeilingSpotlightSketch_wiring.png)

### Compile & Flash ###

Follow along this tutorial to compile the sources and flash the Digispark. 

[Tutorial](https://digistump.com/wiki/digispark?redirect=1)

### Control ###

The reading light and the large ceiling light can be dimmed and switched on/off separately via buttons for volume and channel change.

The numeric buttons on the remote control can be used to start a sleep timer. After the selected time period both lights will go off. 

* 1 = 10 min
* 2 = 20 min
* 3 = 30 min 
etc.

### View in Action ###

![LED floor lamp](/images/LEDFloorLamp.gif)

### Credits ###

* The Arduino RC5 remote control decoder library can be found at  [RC5](https://github.com/guyc/RC5)
