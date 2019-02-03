#include <LiquidCrystal.h> //includes the LiquidCrystal Library

LiquidCrystal lcd(1, 2, 4, 5, 6, 7); //Declare an LC object with parameters (rs, enable, d4, d5, d6, d7) -LCD screen

//VARIABLES
int potPin = 2; //set the input pin for the potentiometer
int buttonPin = 50;//set the input pin for the button
double val = 0; //store the value coming from the sensor
double conversion = 0; //Conversion factor (cm/voltage)
double yInt = 0; //y-intercept of linear equation modelling potentiometer to cm relatiosnhip
String lengthString = ""; //Output length
String units = " cm"; //units for length of displacement

//Initial Arduino Setup 
void setup() {
 lcd.begin(16,2); //Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display 
 lcd.print("Hello!");
 pinMode(8, INPUT); //initialies button as input
 delay(1000); //1 second delay

 calibrate();//calibrate the potentiometer
}

//Loop of measurement displayment
void loop() {

  //If the button is pressed, calibrate the system
 if(digitalRead(buttonPin) == 1) {
  delay(500); //delay to prevent overlap from button press
  calibrate();
 }


 val = analogRead(potPin) * conversion + yInt; //obtain length in cm from potentiometer

 //Display the measured value
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Length: ");
 lcd.setCursor(0,1);
 lengthString = String(val, 2);
 String output = lengthString + units;
 lcd.print(output);
 delay(50); //Small delay of 0.05 seconds between each loop
}

void calibrate() {
  //Display message on lcd screen
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set Bar to 3.18 cm");
  lcd.setCursor(0,1);
  lcd.print("Press the Button");
  
  while(digitalRead(buttonPin) == 0) {} //wait for button press
  double valueInitial = analogRead(potPin); //obtain initial raw value from arduino

  lcd.clear(); //Clears the display
  lcd.setCursor(0,0); //Sets the location at which subsequent text written to the LCD will be displayed 
  lcd.print("Set Bar to 6.36 cm");
  lcd.setCursor(0,1);
  lcd.print("Press the Button");
  delay(500);
  
  while(digitalRead(buttonPin) == 0) {} //wait for button press
  double valueFinal = analogRead(potPin); //obtain final raw value from arduino
  
  conversion = (6.36-3.18)/(valueFinal-valueInitial); //set slope value from potentiometer value to cm (measures 2 pot values (9.54-3.18)cm from each other)
  yInt = 6.36 - conversion * valueFinal; //calculate the y-intercept of the equation of the line
  delay(500);
}
