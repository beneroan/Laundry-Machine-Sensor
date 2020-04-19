#include "Wire.h" 

//SENSITIVITY
int sensitivity = 120;

//WAIT TIME
int Time = 15000;

//sets the address of the accelerometer sensor
const int MPU_ADDR = 0x68;
//initializes the record previous output of accelerometer
int xP = 0;
int yP = 0;
int zP = 0;
//used for recording time passed
long previousMillis = 0;
int counter = 0;
//initializes variables for accelerometer data
int16_t acc_x, acc_y, acc_z; 
//sets up the serial interface to recieve data from the accelerometer
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
  //Serial.print("aX = "); Serial.print(convert_int16_to_str(acc_x));
  //Serial.print(" | aY = "); Serial.print(convert_int16_to_str(acc_y));
  //Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(acc_z));
  if(abs(acc_x-xP) > 400 || abs(acc_y-yP) > 400 || abs(acc_z-zP) > 400){
    counter++;
  }
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > Time) {
    previousMillis = currentMillis;
    //checks if there was substantial variance in the accelerometer data
    if (counter < sensitivity){
    Serial.println("Washing is Done!");
    //sets the LED to green
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);
    }else{
    Serial.println("Still Washing");
    //sets the LED to red
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    }
    counter = 0;
  }
  //sets existing value to the previous value
  xP = acc_x;
  yP = acc_y;
  zP = acc_z;
  Serial.println(counter);
  Serial.println();
}
