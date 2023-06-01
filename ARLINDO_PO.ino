//This is simple project that works in two modes: OFFLINE and ONLINE, in offline we will control the charges using LoRa module
//In Online mode will use Blynk Server, to control the charges by a website or app in great distances and any SmartPhone or computer
//There are 4 charges to control, we have an app created in C# to control in its Two modes, we are using the API of Blynk to communicate to
//its Server
#include <DHT.h>

#include <Thread.h>
#include <TimerOne.h>
#include <SoftwareSerial.h>
#include <ThreadController.h>
#include <BlynkSimpleStream.h>
#include <StaticThreadController.h>

/* Fill-in information from Blynk Device Info here  */
#define BLYNK_TEMPLATE_NAME "NEXUS" // Put here your template name
#define BLYNK_TEMPLATE_ID "TMPL2SGR_OP1H" //Put her your template ID
#define BLYNK_AUTH_TOKEN "93NWr4sYeSdsPOFbc4IBeBLZPBszDS7t" //put here your token

//Pins to connect the buttons
#define BTN_1 4
#define BTN_2 5
#define BTN_3 6
#define BTN_4 7
//Pins to connect the charges(We are using LEDs)
#define LED_1 8
#define LED_2 9
#define LED_3 10
#define LED_4 11

#define sensor_1 A4 //Humidity
#define sensor_2 A5 //Temperature
#define DHT_PIN 12

//CONST VARIABLES
const unsigned long delayTime = 2000; // delay in milissecunds
unsigned long previousMillis = 0; // Variable to store the initial moment of delay


//BOOL VARIABLES
bool led1Status = LOW;
bool led2Status = LOW;
bool led3Status = LOW;
bool led4Status = LOW;

bool btn1Flag = LOW;
bool btn2Flag = LOW;
bool btn3Flag = LOW;
bool btn4Flag = LOW;

//Objects instancies
BlynkTimer Timer;
SoftwareSerial lora(2,3);//Rx e TX
Thread LoraThread =  Thread();
DHT dht;


//LoraRuning
void LoraRunningBack()
{
  checkButtons();
  UpdateData();
  LoRaRun();
}

void timerLoraRun()
{
  LoraThread.run();
}

BLYNK_CONNECTED() 
{
  Blynk.syncVirtual(V0); //LED 1
  Blynk.syncVirtual(V1); //LED 2
  Blynk.syncVirtual(V2); //LED 3
  Blynk.syncVirtual(V3); //LED 4
}

// This function will be called whenever Virtual pin 1 value changes.
BLYNK_WRITE(V0)
{
  led1Status = param.asInt();
  digitalWrite(LED_1, led1Status); // Writes the value of virtualPin 1 to the LED_1.

  if(led1Status){lora.print("a");}
  else{lora.print("b");}

}

// This function will be called whenever Virtual pin 2 value changes.
BLYNK_WRITE(V1)
{
  led2Status = param.asInt();
  digitalWrite(LED_2, led2Status); // Writes the value of virtualPin 1 to the LED_1.

  if(led2Status){lora.print("c");}
  else{lora.print("d");}
}

// This function will be called whenever Virtual pin 3 value changes.
BLYNK_WRITE(V2)
{
  led3Status = param.asInt();
  digitalWrite(LED_3, led3Status); // Writes the value of virtualPin 1 to the LED_1.

  if(led3Status){lora.print("e");}
  else{lora.print("f");}
}

BLYNK_WRITE(V3)
{
  led4Status = param.asInt();
  digitalWrite(LED_4, led4Status); // Writes the value of virtualPin 1 to the LED_1.

  if(led4Status){lora.print("g");}
  else{lora.print("h");}
}

void setup()
{
  // Debug console
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BTN_3, INPUT_PULLUP);
  pinMode(BTN_4, INPUT_PULLUP);

  dht.setup(DHT_PIN); // data pin 12

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);

  LoraThread.onRun(LoraRunningBack);
  LoraThread.setInterval(500);

  Timer1.initialize(20000);
  Timer1.attachInterrupt(timerLoraRun); // blinkLED to run every 0.15 seconds
  Timer1.start();

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Serial.flush();
  lora.begin(9600);
  lora.flush();
  Blynk.begin(Serial, BLYNK_AUTH_TOKEN);
  Timer.setInterval(500L,sensores);
  // Setup a function to be called every second
}

void loop()
{
  //if(Blynk.connected()==false){LoraRun();}//Other way to use Offline and online mode descarting the threads and interrupts usedin this project
  Blynk.run();
  Timer.run();
}
  
void checkButtons()
{
  if(!digitalRead(BTN_1) && btn1Flag) // Check if BTN_1 was pressed.
  {
    led1Status = !led1Status; // Toggle the state of the LED_1.
      digitalWrite(LED_1, led1Status);

      // Update Button Widget
      Blynk.virtualWrite(V0, led1Status);

      if(led1Status){lora.print("a");}
      else{lora.print("b");}
  }

  btn1Flag = digitalRead(BTN_1);

  if(!digitalRead(BTN_2) && btn2Flag ) // Check if BTN_2 was pressed.
  {
    led2Status = !led2Status; // Toggle the state of the LED_1.
      digitalWrite(LED_2, led2Status);

      // Update Button Widget
      Blynk.virtualWrite(V1, led2Status);
      if(led2Status){lora.print("c");}
      else{lora.print("d");}
  }

  btn2Flag = digitalRead(BTN_2);

  if(!digitalRead(BTN_3) && btn3Flag) // Check if BTN_3 was pressed.
  {
    led3Status = !led3Status; // Toggle the state of the LED_1.
      digitalWrite(LED_3, led3Status);

      // Update Button Widget
      Blynk.virtualWrite(V2, led3Status);
      if(led3Status){lora.print("e");}
      else{lora.print("f");}
  }

  btn3Flag = digitalRead(BTN_3);

  if(!digitalRead(BTN_4) && btn4Flag) // Check if BTN_3 was pressed.
  {
    led4Status = !led4Status; // Toggle the state of the LED_1.
      digitalWrite(LED_4, led4Status);

      // Update Button Widget
      Blynk.virtualWrite(V3, led4Status);
      if(led4Status){lora.print("g");}
      else{lora.print("h");}
  }

  btn4Flag = digitalRead(BTN_4);
}

void LoRaRun()
{
  if(lora.available()>0)
  {
    char dados = lora.read();
        if(dados == 'a'){
          led1Status = 1;
          digitalWrite(LED_1,1);  //Ligar LED_1

          Blynk.virtualWrite(V0, led1Status);
          lora.print('a');
        }
        if(dados == 'b'){
          digitalWrite(LED_1,0); //DesLigar LED_1

          led1Status = 0;
          Blynk.virtualWrite(V0, led1Status);
          lora.print('b');

        }
        if(dados == 'c'){
          digitalWrite(LED_2,1); //Ligar LED_2

          led2Status = 1;
          Blynk.virtualWrite(V1, led2Status);
          lora.print('c');
        }
        if(dados == 'd'){
          digitalWrite(LED_2,0); //DesLigar LED_2
          led2Status = 0;
          Blynk.virtualWrite(V1, led2Status);
          lora.print('d');
        }
        if(dados == 'e'){
          digitalWrite(LED_3,1); //Ligar LED_3
          led3Status = 1;
          Blynk.virtualWrite(V2, led3Status);
          lora.print('e');
        }
        if(dados == 'f')
        {
          digitalWrite(LED_3,0); //DesLigar LED_3  

          led3Status = 0;
          Blynk.virtualWrite(V2, led3Status);
          lora.print('f');     
        }
        if(dados == 'g'){
          digitalWrite(LED_4,1); //Ligar LED_4

          led4Status = 1;
          Blynk.virtualWrite(V2, led3Status);
          lora.print('g');
        }
        if(dados == 'h')
        {
          digitalWrite(LED_4,0); //DesLigar LED_4  

          led4Status = 0;
          Blynk.virtualWrite(V2, led3Status);
          lora.print('h');     
        }   

        if(dados == 'x')  //Ligar Todas As cargas Excepto a abertura/Fechadura do portao
        {
          digitalWrite(LED_1,1);
          digitalWrite(LED_2,1);
          digitalWrite(LED_3,1);
          digitalWrite(LED_4,1);         
        }
        if(dados == 'y') //DesLigar Todas As cargas Excepto a abertura/Fechadura do portao
        {
          digitalWrite(LED_1,0);
          digitalWrite(LED_2,0);
          digitalWrite(LED_3,0);
          digitalWrite(LED_4,0);                  
        } 
  }

}

void sensores()
{

  //delay(dht.getMinimumSamplingPeriod());
  //float humidity = dht.getHumidity();
  //float temperature = dht.getTemperature();

  //Blynk.virtualWrite(V4, temperature); //Temperature
  //Blynk.virtualWrite(V5, humidity); //Humidaty
} 

void UpdateData()
{
    unsigned long currentMillis = millis(); // Obtém o valor atual de millis()
    //Actualizacao dos LEDS na aplicacao via LORA
    // Verifica se o tempo de atraso decorreu
    if(currentMillis - previousMillis >= delayTime)
    {
      led1Status = digitalRead(LED_1);
      led2Status = digitalRead(LED_2);
      led3Status = digitalRead(LED_3);
      led4Status = digitalRead(LED_4);

      //  float sensor1Leitura;
      //float sensor2Leitura;
      //delay(dht.getMinimumSamplingPeriod());

      //float humidity = (float)dht.getHumidity();
      //float temperature = (float)dht.getTemperature();
      int sensor1Leitura = map(analogRead(sensor_1),0, 1023, 0, 100);
      int sensor2Leitura = map(analogRead(sensor_2),0, 1023, 0, 100);

      //Blynk.virtualWrite(V5, sensor1Leitura); //Temperature
      //Blynk.virtualWrite(V4, sensor2Leitura); //Humidaty

      lora.print(led1Status);
      lora.print(",");
      lora.print(led2Status);
      lora.print(",");
      lora.print(led3Status);
      lora.print(",");
      lora.print(led4Status);
      lora.print(",");
      
    //Dados dos SENSORES
      lora.print(sensor1Leitura);
      lora.print(",");
      lora.print(sensor2Leitura);
      lora.print(",");
      //Atualiza o momento inicial do atraso
      previousMillis = currentMillis;
    }
}
