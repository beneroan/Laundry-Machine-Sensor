

#include "Wire.h" 

const int MPU_ADDR = 0x68;
//initializes variables to determine variance of accelerometer
int xMax = -100000;
int xMin = 100000;
int yMax = -100000;
int yMin = 1000000;
int zMax = -10000000;
int zMin = 10000000;
//used for recording time passed
long previousMillis = 0;
//initializes variables for accelerometer data
int16_t acc_x, acc_y, acc_z; 

char tmp_str[7]; 
char* convert_int16_to_str(int16_t i) { 
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
void setup() {
  //sets up the virtual ports for the accelerometer
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); 
  Wire.write(0x6B);
  Wire.write(0); 
  Wire.endTransmission(true);
  //sets up the two color LED
  pinMode(2,OUTPUT);//red
  pinMode(3,OUTPUT);//green
}
void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 7*2, true);
  //reads data from the accelerometer
  acc_x = Wire.read()<<8 | Wire.read(); 
  acc_y = Wire.read()<<8 | Wire.read();
  acc_z = Wire.read()<<8 | Wire.read();
  // print out data
  Serial.print("aX = "); Serial.print(convert_int16_to_str(acc_x));
  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(acc_y));
  Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(acc_z));
  Serial.println();
if (xMin == -31072){
  xMin = 0;
}
  //updates maximum and minimum recorded value
  if (acc_x > xMax) {xMax = acc_x;}
  Serial.println(acc_x);
  Serial.println(xMin);
  if (-10000 < acc_x < xMin) {xMin = acc_x;}
  if (acc_y > yMax) {yMax = acc_y;}
  if (acc_y < yMin) {yMin = acc_y;}
  if (acc_z > zMax) {zMax = acc_z;}
  if (acc_z < zMin) {zMin = acc_z;}
  //runs after 15 seconds has passed
  //&& yMax-yMin <= 10000 && zMax-zMin <= 1000
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > 5000) {
    previousMillis = currentMillis;
    //checks if there was substantial variance in the accelerometer data
    if (xMax-xMin <= 10000){
    Serial.println("Washing is Done!");
    //sets the LED to green
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);
    }else{
    Serial.println("Still Washing");
    //sets the LED to red
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    Serial.println(xMax-xMin);
    xMin = 0;
    }
  }
  
  // delay
 delay(1000);
}
