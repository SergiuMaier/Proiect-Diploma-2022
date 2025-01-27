##  SARS-Cov-2 virus infection assessment system using the body temperature

### Short Description

The system detects body temperature by positioning the hand within a predefined scanning range.  
The values acquired from the sensors are transmitted in real time via Bluetooth to a mobile phone and displayed in an [application](http://ai2.appinventor.mit.edu/#4972066926624768) developed using the MIT App Inventor online development platform.  
Additionally, the default system settings can be modified through the application.  

At the user's choice, the values displayed in the application can be stored in a Google Spreadsheet for further analysis.  
For this functionality, a [script](https://script.google.com/d/1ZvxSbKQELXQpO4ODZA-MBYUkUSaNE9s10FG8xVb0a-EfYcUUJ65DivRc/edit) was created on the Google Apps Script platform.  

---

### Components

The system is based on an Arduino Nano module and includes the following components:

- **MLX90614** non-contact IR temperature sensor  
- **HC-SR04** ultrasonic sensor  
- **HC-05** Bluetooth module  
- Buzzer  
- Momentary button  
- 2 x PCBs  
- 5 resistors (**1kΩ**)  
- 5 resistors (**220Ω**)  
- 4 red LEDs  
- 3 green LEDs  

