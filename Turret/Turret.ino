#include <Wire.h>
#include <Servo.h>
const int MPU = 0x68; //I2C address for MPU 6050
Servo ServX;          //Servo for x-axis
Servo ServY;          //Servo for y-axis

int SX_pin = 2; //pin output for x-axis Servo motor
int SY_pin = 4; //pin output for y-axis Servo motor

int16_t Ax, Ay, Az, Gx, Gy, Gz, SAx, SAy; //Int variables for Accelerometer and Gyroscope Values
//float AngleX, Angle Y
void setup() {
  ServX.attach(SX_pin); //Connects the output pin with the Servo motor for the x-axis
  ServY.attach(SY_pin); //Connects the output pin with the Servo motor for the y-axis

  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.begin(115200); //Baud rate 
}


void loop() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);

  Wire.requestFrom(MPU, 9, true); //Request of registers

  //Ax=Wire.read()<<8|Wire.read(); //Reads the X values of the Accelorometer
  //Ay=Wire.read()<<8|Wire.read(); //Reads the Y values of the Accelorometer
  //Az=Wire.read()<<8|Wire.read(); //Reads the Z values of the Accelorometer

  Gx=Wire.read()<<8|Wire.read(); //Reads the X values of the Gyroscope
  Gy=Wire.read()<<8|Wire.read(); //Reads the Y values of the Gyroscope
  Gz=Wire.read()<<8|Wire.read(); //Reads the Z values of the Gyroscope

  SAx = map(Gx, -17000, 17000, 0, 180);
  SAy = map(Gy, -17000, 17000, 0, 180);

  ServX.write(SAx); //Communicates the x-axis position of the MPU6050 with the Servo motor X
  ServY.write(SAy); //Communicates the y-axis position of the MPU6050 with the Servo motor Y 
  Serial.print("Ax = "); Serial.print(Ax);
  Serial.print(", Ay = "); Serial.println(Ay);
  delay(200);
}
