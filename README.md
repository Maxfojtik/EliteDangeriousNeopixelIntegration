# EliteDangeriousNeopixelIntegration
Uses a combination of the Journal file and the Status.json file to determine what to display on the LEDs.
There are two projects within this repo, the Arduino project and the Java project, EliteComms is the java program and EliteArduino is the Arduino project. There is also a runnable jar file you can just download and run.

| Known Microcontrollers | Status |
| ------ | ------ |
| Arduino Nano | Works |
| Teensy LC | Works on pin 17 |
| Arduino Uno | No reason it shouldnt |  

Software Instructions:
1. Download the repo and put the files somewhere safe.
2. Get the arduino IDE from https://www.arduino.cc/en/Main/Software, install it and open it.
3. Click File->Open and open "EliteArduino.ino" from the repo you downloaded.
4. Change the config to match your hardware configuration and preferences.
5. Click Tools->Board and select your processor.
6. Click Tools->Port and select the COM port for the deivce you want to use. If you have multiple and dont know which one it is go to the device manager (search for it in the start menu) and find the device in the "Ports (COM & LPT)" tab.
7. Click the right arrow right underneath the edit button. This should upload the code to the arduino your viewing. If this fails check you changed the right variables in the config, if you didnt change anything or it isnt a complation issue then you will have to go to google to figure it out.
8. Open the folder you had and open "WindowsProgram.jar"
9. Hopefully the program will find the correct port and connect. The lights will flash green when a succesful connection was make.
10. Make sure to come back regularly to check if I've updated the program recetly!

Hardware Instructions:
1. Get an arduino
2. Get some WS2812B LEDs (Neopixels)
3. Get an external 5V power supply that can handle the amount of LEDs you want to have. (Every pixel uses .02A to .06A, your choice of how much saftey margin you need)
4. Wire LED+ to the 5V power supply +
5. Wire LED- to the 5V power supply - and arduino
6. Wire LED data to a resistor and the other side of that to the arduino pin 2.
7. The arduino should be on the left side of your monitor so that the effects will move the right way.

Uses these libarys  
jSerialComm https://fazecast.github.io/jSerialComm/  
JSON In Java http://www.json.org/  
