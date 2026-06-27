#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
#include <ESP32Servo.h>

const int servoPin = 18;
const int ain1Pin = 27;
const int ain2Pin = 26;
const int bin1Pin = 25;
const int bin2Pin = 33;

Servo servo;

const int center = 90;
const int left = 55;
const int right = 125;

const int motorFullSpeed = 200;
const int motorTurnSpeed = 150;

void setup()
{
  Serial.begin(115200);
  Dabble.begin("Car");

  servo.attach(servoPin);
  servo.write(center);

  pinMode(ain1Pin, OUTPUT);
  pinMode(ain2Pin, OUTPUT);
  pinMode(bin1Pin, OUTPUT);
  pinMode(bin2Pin, OUTPUT);

  stop();
}

void loop()
{
  Dabble.processInput();

  bool up = Gamepad.isUpPressed();
  bool down = Gamepad.isDownPressed();
  bool left = Gamepad.isLeftPressed();
  bool right = Gamepad.isRightPressed();
  bool brakeButton = Gamepad.isCrossPressed();

  int angle = center;

  if (left && !right)
  {
    angle = left;
  }
  else if (right && !left)
  {
    angle = right;
  }

  servo.write(angle);

  int speed = (left || right) ? motorTurnSpeed : motorFullSpeed;

  if (up && !down)
  {
    forward(speed);
  }
  else if (down && !up)
  {
    backward(speed);
  }
  else
  {
    stop();
  }

  if (brakeButton)
  {
    brake();
  }

  delay(20);
}

void forward(int speed)
{
  digitalWrite(ain1Pin, LOW);
  analogWrite(ain2Pin, speed);
  digitalWrite(bin1Pin, LOW);
  analogWrite(bin2Pin, speed);
}

void backward(int speed)
{
  analogWrite(ain1Pin, speed);
  digitalWrite(ain2Pin, LOW);
  analogWrite(bin1Pin, speed);
  digitalWrite(bin2Pin, LOW);
}

void stop()
{
  digitalWrite(ain1Pin, LOW);
  digitalWrite(ain2Pin, LOW);
  digitalWrite(bin1Pin, LOW);
  digitalWrite(bin2Pin, LOW);
}

void brake()
{
  digitalWrite(ain1Pin, HIGH);
  digitalWrite(ain2Pin, HIGH);
  digitalWrite(bin1Pin, HIGH);
  digitalWrite(bin2Pin, HIGH);
}