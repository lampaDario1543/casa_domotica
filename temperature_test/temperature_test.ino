#include <SoftwareSerial.h>
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11
int led= 10;

float finalTemperature=0;
float finalHumidity=0;

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );
SoftwareSerial BTSerial(0, 1); // RX, TX del modulo HC-05
String message = "";
static bool measure_environment( float *temperature, float *humidity )
{
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      return( true );
    }

  return( false );
}
void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  BTSerial.begin(115200);
}

void loop() {
  measure_environment( &finalTemperature, &finalHumidity );
  while (BTSerial.available()) {
    char c = BTSerial.read();
    if(c==' ') {
      if (message == "Accendi"){
          digitalWrite(led, HIGH);
      }else if(message == "Spegni"){
        digitalWrite(led, LOW);
      }else if("getTemp"){
          String temperatureMsg = String(finalTemperature) + "," + String(finalHumidity);
          //Serial.println(temperatureMsg);
          Serial.println(temperatureMsg);
      }
      message = "";
    }else{
      message += c;
      //Serial.println(message);
    }
  }
}
