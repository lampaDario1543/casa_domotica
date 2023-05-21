#include <SoftwareSerial.h>
#include <dht_nonblocking.h>
#include <Stepper.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

class Room{ //classe per le stanze
  protected:
    int ledPin;
    boolean ledStatus;
  public:
    Room(int ledPin){
        this->ledPin=ledPin;
        ledStatus=false;
    }
    Room(){
        this->ledPin=2;
        ledStatus=false;
      
    }
    boolean getStatus(){
      return ledStatus;
    }
    void setStatus(boolean s){
      ledStatus=s;
    }
    int getPin(){
      return ledPin;
    }
};
class Garage:public Room{ //classe per il garage
  private:
    int stepsPerRevolution = 2048;
    int rolePerMinute = 17;
    Stepper basculante;
  public:
    Garage(int ledPin):Room(ledPin),basculante(stepsPerRevolution, 8, 10, 9, 11){
      basculante.setSpeed(rolePerMinute);
    }
    Garage():Room(),basculante(stepsPerRevolution, 8, 10, 9, 11){
      basculante.setSpeed(rolePerMinute);
    }
};

//Bluetooth
String message = "";
//STANZE
Room cucina(3); //digital pin 3
Room bagno(4); //digital pin 4
Room camera(5); //digital pin 5
Garage garage(6); //digital pin 4
//temperatura casa
float finalTemperature=0;
float finalHumidity=0;

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );
SoftwareSerial BTSerial(0, 1); // RX, TX del modulo HC-05
static bool measure_environment( float *temperature, float *humidity )
{
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      return( true );
    }

  return( false );
}
//inizializzazione
void initialize(){
}
//setup
void setup() {
  //inizializzo i pin
  pinMode(cucina.getPin(), OUTPUT);
  pinMode(bagno.getPin(), OUTPUT);
  pinMode(camera.getPin(), OUTPUT);
  pinMode(garage.getPin(), OUTPUT);
  //imposto la velocità di trasmissione
  Serial.begin(115200);
  BTSerial.begin(115200);
  //inizializzo
  initialize();
}
//loop
void loop() {
  measure_environment( &finalTemperature, &finalHumidity );
  while (BTSerial.available()) {
    char c = BTSerial.read();
    if(c==' ') {
      if (message == "cucina"){
          setCucina();
      }else if(message == "garage"){
          setGarage();
      }else if(message=="bagno"){
        setBagno();
      }else if(message=="getTemp"){
          String temperatureMsg = String(finalTemperature) + "," + String(finalHumidity);
          Serial.println(temperatureMsg);
      }else if(message=="getAllStates"){
          getAllStates();
      }
      message = "";
    }else{
      message += c;
    }
  }
}
//imposta lo stato della cucina
void setCucina(){
  if(cucina.getStatus())
    digitalWrite(cucina.getPin(), LOW);
  else
    digitalWrite(cucina.getPin(), HIGH);
  cucina.setStatus(!cucina.getStatus());
}
void setBagno(){
  if(bagno.getStatus())
    digitalWrite(bagno.getPin(), LOW);
  else
    digitalWrite(bagno.getPin(), HIGH);
  bagno.setStatus(!bagno.getStatus());
}
//imposta lo stato del garage
void setGarage(){
  if(garage.getStatus())
    digitalWrite(garage.getPin(), LOW);
  else
    digitalWrite(garage.getPin(), HIGH);
  garage.setStatus(!garage.getStatus());
}
void getAllStates(){
  String state = String(cucina.getStatus())+","+String(bagno.getStatus())+","+String(camera.getStatus())+","+String(garage.getStatus());
  Serial.println(state);
}
