# EP-Sleepy 

EPSleepy is the code made for a prototype for my FMP. Here a summary of the contents of this page. For more information please take a look at the wiki 

## Code in the repository
### The Testing code 
There are different arduino programs in this repository. EP-SLeepy is the main code with all the different components. 
When setting up the system, it is good to test each part seperately. For this purpose, there are a set of Testing codes for the buttons, lights audioplayer and SD drive. Use these to test the parts of the system seperately and get a feel for the different parts of the full code. 

### Main code 
EP-Sleepy_arduino is the main code, it contains the code to control all the components. 

### h.files 
The .h files are the setup files, showing the steps the code takes. Think of it as a rough sketch of the final arduino code. 


## Hardware 
The hardware this code was made for: 

- 1x ESP32 WiFi en Bluetooth Board - CP2102
- 1x Mini MP3 Module YX5300 met Audio Jack
- 1x SN 74HC595N shiftregister 
- 6x Tactile Pushbutton Switch 4 Pin - Met [colour] LED Verlichting
- 6x 120 ohm resistor (LED) 
- 6x 10k ohm resistor (buttons pulldown)

### Schematics
![EPsleepy shiftregister without sd_bb](https://user-images.githubusercontent.com/46523801/168841017-b4ac8ba5-cf0c-44ba-aacb-1b34505a8684.png)

