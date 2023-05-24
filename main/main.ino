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
    void toggleSwitch(){
      if(ledStatus)
        digitalWrite(ledPin, LOW);
      else
        digitalWrite(ledPin, HIGH);
      ledStatus=(!ledStatus);
    }
};
class Garage:public Room{
  private:
    int stepsPerRevolution = 2048;
    int rolePerMinute = 11;
    const int MAX=stepsPerRevolution+650;
    int currentOpen;
    int apertura; //apertura in % della basculante
    Stepper basculante;
  public:
    Garage(int ledPin):Room(ledPin),basculante(stepsPerRevolution, 10, 12, 11, 13){
      basculante.setSpeed(rolePerMinute);
      apertura=0;
      currentOpen=0;
    }
    Garage():Room(),basculante(stepsPerRevolution, 10, 12, 11, 13){
      basculante.setSpeed(rolePerMinute);
      apertura=0;
      currentOpen=0;
    }
    void setBasculante(int n){
      int passiPer;
      if(n!=0)
        passiPer= (int)((n / 100.0) * MAX); // Calcolo aggiornato con divisione decimale
      else
        passiPer=0;
      int passi=abs(currentOpen-passiPer);
      if (n > apertura){
        basculante.step(-passi); // Apre la basculante
        currentOpen+=passi;
      }
      else if (n < apertura){
        basculante.step(passi); // Chiude la basculante
        currentOpen-=passi;
      }
      
      apertura = n; // Aggiorna il valore di apertura
    }
    int getApertura(){
      return apertura;
    }
};
//Bluetooth
String message = "";
//STANZE
Room cucina(3); //digital pin 3
Room bagno(4);
Room camera(5);
Garage garage(6); //digital pin 6

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
          cucina.toggleSwitch();
      }else if(message=="bagno"){
        bagno.toggleSwitch();
      }else if(message == "garage"){
        garage.toggleSwitch();
      }else if(message=="camera"){
        camera.toggleSwitch();
      }else if(message=="getTemp"){ 
          String temperatureMsg = String(finalTemperature) + "," + String(finalHumidity);
          Serial.println(temperatureMsg);
      }else if(message=="getAllStates"){
        getAllStates();
      }else if(message.startsWith("setBasculante-")){
        String numeroString = message.substring(14); // Estrapola la parte della stringa dopo il trattino
        int n= numeroString.toInt();
        n*=20; //numero in percentuale
        garage.setBasculante(n);
      }
      message = "";
    }else{
      message += c;
    }
  }
}

void getAllStates(){
  String state = String(cucina.getStatus())+","+String(bagno.getStatus())+","+String(camera.getStatus())+","+String(garage.getStatus());
  Serial.println(state);
}
