#include <Stepper.h>
#include <max6675.h>

// Define pin connections & motor's steps per revolution
const int dirPin = 2;
const int stepPin = 3;
const int stepsPerRevolution = 200;

// Define pins for MAX6675
int thermoSO = 4;
int thermoCS = 5;
int thermoCLK = 6;

float preTemp = 0;
float soakTemp = 0;
float peakTemp = 0;

// initialize the stepper library:
Stepper myStepper(stepsPerRevolution, dirPin, stepPin, 4, 5, 6);

//intialize max6675 library:
MAX6675 thermocouple(thermoCLK, thermoCS, thermoSO);

void setup() {
  // set the speed at 1000 rpm:
  myStepper.setSpeed(1000);
  // initialize the serial port:
  Serial.begin(9600);
  Serial.println("MAX6675 test");

  // Prompt the user to enter the desired temperature range
  Serial.println("Enter Preheat Temperature: ");
  while (Serial.available()) {
    Serial.read();
  }
  while(Serial.available() == 0){}
  preTemp = Serial.parseInt();
    
  Serial.println("Enter Soak Temperature: ");
  while (Serial.available()) {
    Serial.read();
  }
  while(Serial.available() == 0){}
  soakTemp = Serial.parseInt();
    
  Serial.println("Enter Peak Temperature: ");
  while (Serial.available()) {
    Serial.read();
  }
  while(Serial.available() == 0){
  peakTemp = Serial.parseInt();
  }
}

void loop () {
  double temperature = thermocouple.readCelsius();
  Serial.print("Temperature: ");
  Serial.println(temperature);
  delay (1000);
}
