#include <dht11.h>

dht11 DHT11;

const int pulseled = 13;
const int ledPin2 = 8;
const int pausezaehler = 10;

void setup()
{
  Serial.begin(9600);
  pinMode (pulseled, OUTPUT);      // sets the digital pin as output
  pinMode (ledPin2, OUTPUT);      // sets the digital pin as output
}

void getdata(int iPuerto)
{
  int chk = DHT11.read(iPuerto);
  switch (chk)
  {
    case 0:   
              break;
    case -1: Serial.println(" Checksum error"); break;
    case -2: Serial.println(" Time out error"); break;
    default: Serial.println(" Unknown error"); break;
  }
}


void loop()
{
  digitalWrite(pulseled, HIGH);   
  getdata(10);
      int feuchte_innen = (DHT11.humidity);
      int temp_innen = (DHT11.temperature);
  getdata(11);
      int feuchte_aussen = (DHT11.humidity);
    int temp_aussen = (DHT11.temperature);  
//  takepause;


  if (feuchte_innen > feuchte_aussen) {
    digitalWrite(ledPin2, LOW);
    Serial.println("###########################");
    Serial.print(" Feuchte innen = ");
    Serial.println(feuchte_innen);
    Serial.print(" Feuchte aussen = ");
    Serial.println(feuchte_aussen);
    Serial.println();
    Serial.println(" i groesser a ");
    Serial.println();
    Serial.println();
    Serial.print(" Temperatur innen = ");
    Serial.println(temp_innen);
    Serial.print(" Temperatur aussen = ");
    Serial.println(temp_aussen);
    Serial.println("###########################");
    }
  else {
    digitalWrite(ledPin2, HIGH);
    Serial.println("###########################");
    Serial.print(" Feuchte innen = ");
    Serial.println(feuchte_innen);
    Serial.print(" Feuchte aussen = ");
    Serial.println(feuchte_aussen);
    Serial.println();
    Serial.println(" a groesser i ");
    Serial.println();
    Serial.println();
    Serial.print(" Temperatur innen = ");
    Serial.println(temp_innen);
    Serial.print(" Temperatur aussen = ");
    Serial.println(temp_aussen);
    Serial.println("###########################");
  }

  delay(1000);
    digitalWrite(pulseled, LOW);
  delay(1000);
  for (int i=0; i <= pausezaehler; i++){
  Serial.println(i);
    delay(250);
      digitalWrite(pulseled, HIGH);
    delay(250);
      digitalWrite(pulseled, LOW);
    delay(250);
      digitalWrite(pulseled, HIGH);
    delay(250);
      digitalWrite(pulseled, LOW);
  }
}
// Alle Stunde eine Minute Lüfter an
//    digitalWrite(ledPin1, LOW);
//    digitalWrite(ledPin2, HIGH);   
//    delay(
