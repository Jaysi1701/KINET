#define BLYNK_TEMPLATE_ID "TMPL3pc1GEVZB"
#define BLYNK_TEMPLATE_NAME "gasleak"
#define BLYNK_AUTH_TOKEN "r2n4sGKDANgyUT5tpu0JQQtA7LzzZbWd"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
#define BLYNK_PRINT Serial    
char auth[] = "r2n4sGKDANgyUT5tpu0JQQtA7LzzZbWd"; 
char ssid[] = "Airtel_3036";
char pass[] = "Airtel@123"; 
 
#define buzzer_alarm D3
const int buzzer = D3;

int alarm_status;
int mq2 = A0; // smoke sensor is connected with the analog pin A0 
int data = 0; 

int PIR = D1; // PIR sensor is connected with the digital pin D1 
int datap = 0; 

#define relay_fan D5 //relay at D5

const int ldr = D2; //ldr at D2
const int led = D0; //led at D0

BLYNK_WRITE(V0) 
{
  digitalWrite(D0, param.asInt());
}

void setup() 
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, getSendData);

  digitalWrite(buzzer_alarm, LOW);
  pinMode(buzzer, OUTPUT);

  pinMode(relay_fan, OUTPUT);
  digitalWrite(relay_fan, HIGH);

  pinMode(ldr, INPUT);

  pinMode(led, OUTPUT);
  //Set the LED pin as an output pin
  pinMode(D0, OUTPUT);
}
 
void loop() 
{
  timer.run(); // Initiates SimpleTimer
  Blynk.run();

  if (data >140)
  {
  digitalWrite(relay_fan, LOW);

  Serial.println("Exhaust Fan: ON");
  Serial.println("Buzzer Status: ON");

  digitalWrite(buzzer, HIGH); //buzzer on
  delay(200);
  digitalWrite(buzzer, LOW); 
  delay(200); 

  Blynk.virtualWrite(V4, relay_fan);
  Blynk.virtualWrite(V3, buzzer);
  }
}

void getSendData()
{
  data = analogRead(mq2); 
  Blynk.virtualWrite(V2, data);
  Serial.println(data);

  datap = digitalRead(PIR); 
  Blynk.virtualWrite(V1, datap);
  Serial.println(datap);

  if (datap==1)
  {
    int value = digitalRead(ldr);
  if(value == 1)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
  Serial.println(value);
  }
}

