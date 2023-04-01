# Home Automation System



Smart home automation systems are becoming increasingly popular as technology advances, allowing homeowners to operate their home equipment remotely via smartphones or computers. This project presents an Arduino-based system that provides a low-cost solution for automating and controlling various home appliances using sensors. The system features an LED control feature activated by a motion sensor and an IR remote to control three other lights, a sound and smoke detector that sets off an alarm, and an LCD display that shows notifications. An Android app is also being developed to remotely monitor smoke, gas, and temperature within the house.

The Arduino board is a fantastic platform for DIY enthusiasts and amateurs who want to automate and control various home appliances. The Arduino-based smart home automation system, which uses microcontrollers, provides homeowners with the flexibility and convenience of remotely controlling their home appliances, making it an interesting component of smart home automation.


# Code Explanation

The main control unit in the project is an Arduino Atmega2560, with IR and Bluetooth modules for wireless communication, an Android and LCD screen for displaying sensor data, and an IR for controlling the appliances. The libraries for the LCD screen, DHT11 sensor, and IR receiver are added to the IDE using #include in this first part.


The "unit8_t" and "struct" section of code defines the graphical user interface (GUI) required for app configuration on the phone. The void setup() function connects the RemoteXY interface to the Bluetooth module and configures communication with the Android device, whereas the remoteXY Handler() function updates the interface.


The void setup() function is used to initialise serial communication after defining the smoke sensor pin and setting a threshold value. The smoke level is detected using the analogRead() function in the void fire detector() function, and a notification is printed to the LCD screen and Android device, while also initialising the passive buzzer and the Red LED. The void loop() function serves as the starting point for the rest of the code. The sound sensor, like the smoke sensor, uses a threshold value to send a notification to the Android and LCD.


When the serial communication is initialised in the setup function, the DHT sensor begins to function. The void loop function reads temperature data in degrees Celsius and sends it to the display devices. The temperature values are converted to strings and stored in the RemoteXY.text 1 function by the 'dtostrf()' function.

The void motion detector() function is used to establish communication between the PIR and the first LED. Void room leds() connects LEDs to the IR Receiver. The receiver constantly reads the button's state and controls the LED accordingly.


Finally, after initialising and measuring the LDR values, both the void room leds() and void motion detector() functions work in the void loop() function.
