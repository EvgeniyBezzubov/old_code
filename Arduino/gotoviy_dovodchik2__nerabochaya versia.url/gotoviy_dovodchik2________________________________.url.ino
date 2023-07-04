#define REMOTEXY_MODE__ESP8266WIFI_LIB_POINT
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
#include <ESP8266WebServer.h>
#include <RemoteXY.h>

// настройки соединения 
#define REMOTEXY_WIFI_SSID "Car-kit-wifi"
#define REMOTEXY_WIFI_PASSWORD "19720708"
#define REMOTEXY_SERVER_PORT 6377





extern "C" {
#include "user_interface.h"
uint8 wifi_softap_get_station_num(void);
}

const IPAddress remote_ip(192, 168, 4, 2);







// легенда 
// //d10 переднее водительское окно
//d2  переднее левое окно

//d3 заднее левое
//d4  заднее правое

// d5 вблокировка дверей.

// d6 закрытие зеркал.

// d7 разблокировка двери












// конфигурация интерфейса  
#pragma pack(push, 1)

uint32_t myTimer1;
uint32_t starttrigger;
uint32_t myTimer2;
uint32_t triger;
uint32_t sterttrigger;
uint32_t schetchik_vklucheniy;
uint32_t wifitrigger;
bool flag;


uint8_t RemoteXY_CONF[] =
  { 255,5,0,0,0,60,0,13,13,1,
  2,0,19,5,22,11,2,26,31,31,
  79,78,0,79,70,70,0,1,0,7,
  24,12,12,2,31,88,0,1,0,39,
  24,12,12,2,31,88,0,1,0,7,
  47,12,12,2,31,88,0,1,0,39,
  47,12,12,2,31,88,0 };
  
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // input variables
  uint8_t switch_1; // =1 если переключатель включен и =0 если отключен 
  uint8_t button_1; // =1 если кнопка нажата, иначе =0 
  uint8_t button_2; // =1 если кнопка нажата, иначе =0 
  uint8_t button_3; // =1 если кнопка нажата, иначе =0 
  uint8_t button_4; // =1 если кнопка нажата, иначе =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 
 // uint8_t RemoteXY_isConnected ()
} RemoteXY;
#pragma pack(pop)
//int state = RemoteXY_isConnected();
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_BUTTON_1 LED_BUILTIN
#define PIN_BUTTON_2 D10
#define PIN_BUTTON_3 D2  
#define PIN_BUTTON_4 D3
#define PIN_BUTTON_5 D4
#define PIN_BUTTON_6 D5
#define PIN_BUTTON_7 D6
#define PIN_BUTTON_8 D7  //

#define PIN_BUTTON_10 D9


void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_BUTTON_1, OUTPUT);
  pinMode (PIN_BUTTON_2, OUTPUT);
  pinMode (PIN_BUTTON_3, OUTPUT);
  pinMode (PIN_BUTTON_4, OUTPUT);
  pinMode (PIN_BUTTON_5, OUTPUT);
  pinMode (PIN_BUTTON_6, OUTPUT);
  pinMode (PIN_BUTTON_7, OUTPUT);
  pinMode (PIN_BUTTON_8, OUTPUT);
  
  pinMode (PIN_BUTTON_10, INPUT); // пин для датчика включения двигателя
  digitalWrite(PIN_BUTTON_1, HIGH); //устанавливаем в higt т.к. модули релле ардуно работаю на вуключения от притягивания к нулю
  digitalWrite(PIN_BUTTON_2, HIGH);
  digitalWrite(PIN_BUTTON_3, HIGH);
  digitalWrite(PIN_BUTTON_4, HIGH);
  digitalWrite(PIN_BUTTON_5, HIGH);
  digitalWrite(PIN_BUTTON_6, HIGH);
  digitalWrite(PIN_BUTTON_7, HIGH);
  digitalWrite(PIN_BUTTON_8, HIGH);

  // TODO you setup code
  myTimer1 = 0;
  myTimer2 = 0;
  schetchik_vklucheniy = 0;
  starttrigger = 0;
  //digitalWrite (PIN_BUTTON_1, LOW);
  Serial.begin(9600);
}











// переменная хранения времени (unsigned long)

void loop() {
//Serial.println(millis());
  //Serial.println(wifi_softap_get_station_num());количество подключённых клиентов в вифи
  //Serial.println(triger);
  RemoteXY_Handler ();
  if (RemoteXY.switch_1!=0) {     // главный рычаГ РУЧНОГО/АВТО РЕЖИМА
    triger = 0;   
    //myTimer2 = millis();
  } else {
    triger = 2;
    
  }



    

  if(Ping.ping(remote_ip)) {      //задание триггера, который отслеживает пинг до цели, 
    Serial.println("Success!!");
    wifitrigger = 1;
    sterttrigger = 1;
  } else {
    Serial.println("пинга нет, только что запустилась программа");
      if (sterttrigger == 1){

        Serial.println("пинга нет, программа была запущена давно, запускаю доводчик");
        sterttrigger = 2; //
        
         
      }
    wifitrigger = 0;
  }


  Serial.println(triger);

  
  if (wifi_softap_get_station_num() == 1){        // если кто то подключён, то выводим на печать в монитор количество подключений, и выводи на плату синий огонёк, с учётом того, что low на плате это high в коде 
    digitalWrite (PIN_BUTTON_1, HIGH);  
    //Serial.println(wifi_softap_get_station_num());
    myTimer1 = millis();
   // schetchik_vklucheniy = 0;
  }
  else {
    digitalWrite (PIN_BUTTON_1, LOW);
    myTimer2 = millis();
          

  }


  if (triger == 0){
    if (RemoteXY.button_1!=0){
      digitalWrite (PIN_BUTTON_2, HIGH); //d10 переднее водительское окно
      Serial.println("переднее водительское окно");
    }else{
      digitalWrite (PIN_BUTTON_2, LOW);
    }
    
  }
  if (triger == 0){
    if (RemoteXY.button_2!=0){
      digitalWrite (PIN_BUTTON_3, HIGH); //d2  переднее левое окно
      Serial.println("переднее левое окно");
    }else{
      digitalWrite (PIN_BUTTON_3, LOW);
    }
    
  }
  if (triger == 0){
    if (RemoteXY.button_3!=0){
      digitalWrite (PIN_BUTTON_8, HIGH); //d7 разблокировка машины 
      Serial.println("разблокировка машины ");
    }else{
      digitalWrite (PIN_BUTTON_8, LOW);
    }
    
  }
  if (triger == 0){
    if (RemoteXY.button_4!=0){
      digitalWrite (PIN_BUTTON_7, HIGH); //d6 закрытие зеркал
      Serial.println("закрытие зеркал ");
    }else{
      digitalWrite (PIN_BUTTON_7, LOW);
    }
    
  }
  if (triger == 2 && wifitrigger == 0 && 0>myTimer2 - myTimer1 > 10000 && sterttrigger == 2){ //проверика по главному выелючателю на интерфейсе, включен ли он, проверка по триггеру пинга, проверка сколько прошло времени
      //digitalWrite (PIN_BUTTON_1, HIGH);
      Serial.println("прошло 10 секудн с тех пор как ты отключился даун"); //d10 переднее водительское окно
      Serial.println(myTimer2 ,myTimer1);
      //Сдесь нужно написать что начинать делать
      digitalWrite (PIN_BUTTON_2, LOW);  //d10 переднее водительское окно 
      sterttrigger = 3;
  }
  if (triger == 2 && wifitrigger == 0 && 10000>myTimer2 - myTimer1 > 15000 && sterttrigger == 3){ //проверика по главному выелючателю на интерфейсе, включен ли он, проверка по триггеру пинга, проверка сколько прошло времени
      //digitalWrite (PIN_BUTTON_1, HIGH);
      Serial.println("прошло 15 секудн с тех пор как ты отключился даун");
      Serial.println(myTimer2 ,myTimer1);
      //Сдесь нужно написать что начинать делать
      digitalWrite (PIN_BUTTON_3, LOW);  //d2 довод окон вверх 
      digitalWrite (PIN_BUTTON_2, HIGH); //d10 завершаем довод окпереднее водительское окно
      sterttrigger = 4;
  }
  if (triger == 2 && wifitrigger == 0 && 15000>myTimer2 - myTimer1 > 20000 && sterttrigger == 4){ //проверика по главному выелючателю на интерфейсе, включен ли он, проверка по триггеру пинга, проверка сколько прошло времени
      //digitalWrite (PIN_BUTTON_1, HIGH);
      Serial.println("прошло 20 секудн с тех пор как ты отключился даун");
      Serial.println(myTimer2);
      Serial.println(myTimer1);
      //Сдесь нужно написать что начинать делать
      digitalWrite (PIN_BUTTON_4, LOW);   //d3 довод окон вверх 
      digitalWrite (PIN_BUTTON_3, HIGH); // d2завершаем довод окна
      sterttrigger = 5;
  }
  if (triger == 2 && wifitrigger == 0 && 20000>myTimer2 - myTimer1 > 25000 && sterttrigger == 5){ //проверика по главному выелючателю на интерфейсе, включен ли он, проверка по триггеру пинга, проверка сколько прошло времени
      //digitalWrite (PIN_BUTTON_1, HIGH);
      Serial.println("прошло 25 секудн с тех пор как ты отключился даун");
      Serial.println(myTimer2 ,myTimer1);
      //Сдесь нужно написать что начинать делать
      digitalWrite (PIN_BUTTON_5, LOW);    //d4 довод окон вверх 
      digitalWrite (PIN_BUTTON_4, HIGH); // d3 завершаем довод окна
      sterttrigger = 6;
  }

  if (triger == 2 && wifitrigger == 0 && 25000>myTimer2 - myTimer1 > 30000 && sterttrigger == 6){ //проверика по главному выелючателю на интерфейсе, включен ли он, проверка по триггеру пинга, проверка сколько прошло времени
      //digitalWrite (PIN_BUTTON_1, HIGH);
      Serial.println("прошло 30 секудн с тех пор как ты отключился даун");
      Serial.println(myTimer2 ,myTimer1);
      //Сдесь нужно написать что начинать делать
      digitalWrite (PIN_BUTTON_6, LOW);    //d5 блокировка дверей.
      sterttrigger = 7;
      digitalWrite (PIN_BUTTON_5, HIGH);  //d4 довод окон вверх 
  }
   if (triger == 2 && wifitrigger == 0 && 30000>myTimer2 - myTimer1 > 35000 && sterttrigger == 7){ //проверика по главному выелючателю на интерфейсе, включен ли он, проверка по триггеру пинга, проверка сколько прошло времени
      //digitalWrite (PIN_BUTTON_1, HIGH);
      Serial.println("прошло 35 секудн с тех пор как ты отключился даун");
      Serial.println(myTimer2 ,myTimer1);
      //Сдесь нужно написать что начинать делать
      digitalWrite (PIN_BUTTON_6, HIGH);    //d5 отжимаем кнопку блокировки двери
      digitalWrite (PIN_BUTTON_7, LOW);   //d6 кнопка закрытия зеркал
      
  }
   if (triger == 2 && wifitrigger == 0 && 35000>myTimer2 - myTimer1 > 40000 && sterttrigger == 7){ //проверика по главному выелючателю на интерфейсе, включен ли он, проверка по триггеру пинга, проверка сколько прошло времени
      //digitalWrite (PIN_BUTTON_1, HIGH);
      Serial.println("прошло 40 секудн с тех пор как ты отключился даун");
      Serial.println(myTimer2 ,myTimer1);
      //Сдесь нужно написать что начинать делать

      digitalWrite (PIN_BUTTON_7, HIGH); //d6 кнопка закрытия зерка
      sterttrigger = 0;     
  }
}
