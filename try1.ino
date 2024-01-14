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
}

void loop() {
  double temperature = thermocouple.readCelsius();
  Serial.print("Temperature: ");
  Serial.println(temperature);
  delay (1000);

  // step one revolution  in one direction:
  if (temperature < 40) {
    Serial.println("counterclockwise");
    myStepper.step(-stepsPerRevolution*10);
    delay(100);
    return;
  }

  // step one revolution in the other direction:
  if (temperature > 40) {
    Serial.println("clockwise");
    myStepper.step(stepsPerRevolution*10);
    delay(100);
    return;
  }
}
