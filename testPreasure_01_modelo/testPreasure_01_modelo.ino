#include <SPI.h>
#include <MPL115A1.h>
#include <dht11.h>
#include <Wire.h> //I2C library

#define __DEBUG__ //note: I used for debug a ht1632c led display
                  //If you can't/don't use it, undef this macro! :-)
#ifdef __DEBUG__
#include <ht1632c.h>

//debug display
ht1632c dotmatrix = ht1632c(&PORTD, 7, 6, 4, 5, GEOM_32x16, 2);
#endif

//i2c settings
#define SLAVE_ADDRESS 0x04
int number_command = 0;
float value_to_send=0.0;

//I2C commands
#define TEMP 1
#define HUMI 2
#define PRES 3
#define DEW 4

//out pint for DHT11 sensor
#define DHT11PIN 2

//sensors
MPL115A1 Pressure_sensor;
dht11 DHT11_sensor;

//current atmo values
float current_pressure=0.0;
float current_humidity=0.0;
float current_temperature=0.0;
double current_dewpoint=0.0;

void setup() {
  //serial setup
  Serial.begin(115200);
  //initialize pressure sensor
  Pressure_sensor.begin();

  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);

  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
//#ifdef __DEBUG__
//  dotmatrix.clear();
//  dotmatrix.setfont(FONT_5x8);
//#endif
}

void loop() {
  //take & save pressure values
  current_pressure = GetPressure();
  GetTemp_Humidity_DewPoint();

  //print current valueson serial ...debug (remove it if you want)!
  Serial.print(current_pressure);
  Serial.print(" hPa\n");

  Serial.print (current_humidity);
  Serial.print(" % Humidity\n");

  Serial.print (current_temperature);
  Serial.print(" °C\n");

  Serial.print (current_dewpoint);
  Serial.print(" Dew point (°C)\n");
#ifdef __DEBUG__
  dotmatrix.clear();
  char tmp[20] = "";
  //pressure
  sprintf(tmp, "P=%dhPa", (int)current_pressure);
  byte len = strlen(tmp);
  for (int i = 0; i < len; i++)
    dotmatrix.putchar(5*i, 0, tmp[i], ORANGE);

  //temperaure
  sprintf(tmp, "T=%dC", (int)current_temperature);
  len = strlen(tmp);
  for (int i = 0; i < len; i++)
  dotmatrix.putchar(5*i, 8, tmp[i], RED);
  //humidity
  sprintf(tmp, "H=%d%%", (int)current_humidity);
  len = strlen(tmp);
  for (int i = 0; i < len; i++)
     dotmatrix.putchar(32+5*i, 8, tmp[i], GREEN);
  dotmatrix.sendframe();

#endif
  //delay
  delay(5000);
}

//Acquisition functions
//from sensors
float GetPressure()
{
  float hPa = Pressure_sensor.pressure();
  return hPa;
}

void GetTemp_Humidity_DewPoint()
{
  //take & save DHT11 values (temp + rel. humidity)
  int chk = DHT11_sensor.read(DHT11PIN);
  switch (chk) //check errors
  {
    case DHTLIB_OK:
      Serial.println("read OK");

      //read values
      current_humidity=(float)(DHT11_sensor.humidity);
      current_temperature=(float)(DHT11_sensor.temperature);

      //dew point
      current_dewpoint=dewPoint(DHT11_sensor.temperature, DHT11_sensor.humidity);
    break;

    case DHTLIB_ERROR_CHECKSUM:
      Serial.println("Checksum error");
    break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.println("Time out error");
    break;

   default:
     Serial.println("Unknown error");
   break;
  }
}

//dewpoint function (taken from http://playground.arduino.cc/main/DHT11Lib)
// dewPoint function NOAA
// reference (1) : http://wahiduddin.net/calc/density_algorithms.htm
// reference (2) : http://www.colorado.edu/geography/weather_station/Geog_site/about.htm
//
double dewPoint(double celsius, double humidity)
{
  // (1) Saturation Vapor Pressure = ESGG(T)
  double RATIO = 373.15 / (273.15 + celsius);
  double RHS = -7.90298 * (RATIO - 1);
  RHS += 5.02808 * log10(RATIO);
  RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1/RATIO ))) - 1) ;
  RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1) ;
  RHS += log10(1013.246);
  // factor -3 is to adjust units - Vapor Pressure SVP * humidity
  double VP = pow(10, RHS - 3) * humidity;
  // (2) DEWPOINT = F(Vapor Pressure)
  double T = log(VP/0.61078); // temp var
  return (241.88 * T) / (17.558 - T);
}

//I2C callbacks

// callback for received command
void receiveData(int byteCount)
{
  while(Wire.available()) {
    number_command = Wire.read();

    if(number_command==TEMP) { //request temperature
      value_to_send = current_temperature;
    }
    if(number_command==HUMI) { //request humidity
      value_to_send = current_humidity;
    }

    if(number_command==PRES) { //request humidity
      value_to_send = current_pressure;
    }

    if(number_command==DEW) { //request dewpoint
     value_to_send = current_dewpoint;
    }
  }
}

// callback for sending data via I2C
void sendData()
{
  //convert the float values in a vector of 4 bytes to send via i2c bus
  char vector_to_send[4];
  memcpy(vector_to_send,(char*)&(value_to_send),4);
  Wire.write(vector_to_send,4);
}
