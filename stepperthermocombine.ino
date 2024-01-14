#include <max6675.h>
#include <Stepper.h>
#include <AccelStepper.h>

int preTemp, soakTemp, peakTemp;

// Define pin connections & motor's steps per revolution
const int dirPin = 2;
const int stepPin = 3;
const int stepsPerRevolution = 200;

//Define pins for MAX6675
int thermoSO = 4;
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoSO);

AccelStepper stepper(dirPin, stepPin, stepsPerRevolution);

void setup() 
{
  Serial.begin(9600);

  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);

  // Declare pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(1000);
  stepper.setSpeed(100);

  // Prompt the user to enter the desired temperature range
  Serial.println("Enter the Preheat temperature (in degrees Celsius):");
  while (!Serial.available()) {}
  int preTemp = Serial.parseInt();

  Serial.println("Enter the Soaking temperature (in degrees Celsius):");
  while (!Serial.available()) {}
  int soakTemp = Serial.parseInt();

  Serial.println("Enter the Peak temperature (in degrees Celsius):");
  while (!Serial.available()) {}
  int peakTemp = Serial.parseInt();
}

void loop() {
  // Read the temperature from the Max6675 sensor
  double temperature = thermocouple.readCelsius();
  Serial.println("C = ");
  Serial.print(temperature);

  if (temperature <= preTemp) {
    // Set the motor speed
    stepper.setSpeed(100);
    // Move the stepper motor
    stepper.runSpeedToPosition();
  }

  delay(1000); // Delay for preheating

  if (temperature >= preTemp && temperature <= soakTemp) {
    // Set the motor speed
    stepper.setSpeed(200);
    // Move the stepper motor
    stepper.runSpeedToPosition();
  }

  delay(1000); // Delay for soaking

  if (temperature >= soakTemp && temperature <= peakTemp) {
    // Set the motor speed
    stepper.setSpeed(300);
    // Move the stepper motor
    stepper.runSpeedToPosition();
  }  
}
