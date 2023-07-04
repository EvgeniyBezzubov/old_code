/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 2.4.3 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.7.12 or later version;
     - for iOS 1.4.7 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// определение режима соединения и подключение библиотеки RemoteXY 
#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD
#include <ESP8266WiFi.h>

#include <RemoteXY.h>

// настройки соединения 
#define REMOTEXY_WIFI_SSID "SNR-CPE-60F4"
#define REMOTEXY_WIFI_PASSWORD "19720708"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "cc2b460777235c3ab60df995ad2be4e3"

// конфигурация интерфейса  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,1,0,2,0,19,0,11,13,0,
  1,0,5,10,12,12,2,31,88,0,
  65,6,47,12,9,9 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // input variables
  uint8_t button_1; // =1 если кнопка нажата, иначе =0 

    // output variables
  uint8_t led_1_r; // =0..255 яркость красного цвета индикатора 
  uint8_t led_1_g; // =0..255 яркость зеленого цвета индикатора 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_BUTTON_1 D8
#define PIN_BUTTON_2 D7


void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_BUTTON_1, OUTPUT);
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  if (RemoteXY.button_1 == 0)
  {
    Serial.print("YYYY");
    digitalWrite(PIN_BUTTON_1, LOW);
  }
  else
  {
    digitalWrite(PIN_BUTTON_1, HIGH);
  }
//  digitalWrite(PIN_BUTTON_1, (RemoteXY.button_1==0)?LOW:HIGH);

  // TODO you loop code
  // используйте структуру RemoteXY для передачи данных
  // не используйте функцию delay() 


}
