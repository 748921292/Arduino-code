

#include "config.h"
#include <Servo.h> //引入lib
Servo myservo;  // 创建一个伺服电机对象
#define LED1 D4
#define LED2 D5
#define LED3 D6
float lightval;

#define BUTTON_PIN D4

// LED Pin
#define LED_PIN LED_BUILTIN

// button state
bool btn_state = false;
bool prv_btn_state = false;

// set up the 'led' feed
AdafruitIO_Feed *led = io.feed("led");

// set up the 'button' feed
AdafruitIO_Feed *button = io.feed("button");
AdafruitIO_Feed *light = io.feed("light");
void setup() {
  myservo.attach(D3);  // 9号引脚输出电机控制信号
  myservo.write(0);
  delay(1000);
  myservo.write(90);    
  pinMode(LED1, OUTPUT);   //定义led引脚为输出模式
  pinMode(LED2, OUTPUT);   //定义led引脚为输出模式
  pinMode(LED3, OUTPUT);   //定义led引脚为输出模式
    digitalWrite(LED1, 0); //led引脚输出低电平，点亮led
    digitalWrite(LED2, 0); //led引脚输出低电平，点亮led
    digitalWrite(LED3, 0); //led引脚输出低电平，点亮led  
    delay(1000);
    digitalWrite(LED1, 1); //led引脚输出低电平，点亮led
    digitalWrite(LED2, 1); //led引脚输出低电平，点亮led
    digitalWrite(LED3, 1); //led引脚输出低电平，点亮led      
  // set button pin as an input
  pinMode(BUTTON_PIN, INPUT);

  // set LED pin as an output
  pinMode(LED_PIN, OUTPUT);

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while (! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  led->onMessage(handleMessage);

  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  led->get();

}
long timer1;
int val=0;

void loop() {


  io.run();

  if (millis() - timer1 > 10000)
  {
    timer1 = millis();
    lightval=analogRead(A0);
    val=map(lightval,0,4096,0,100);
    myservo.write(val); 
    if(val>80)
    {
    digitalWrite(LED1, 0); 
    digitalWrite(LED2, 0); 
    digitalWrite(LED3, 0);     
    }
    else if(val>50)
    {
    digitalWrite(LED1, 1);
    digitalWrite(LED2, 0);
    digitalWrite(LED3, 0);    
    }  
    else if(val>20)
    {
    digitalWrite(LED1, 1);
    digitalWrite(LED2, 1); 
    digitalWrite(LED3, 0);      
    }    
    else 
    {
    digitalWrite(LED1, 1); 
    digitalWrite(LED2, 1); 
    digitalWrite(LED3, 1);      
    }           
    light->save(lightval);
  }

}

// this function is called whenever a 'led' message
// is received from Adafruit IO. it was attached to
// the counter feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {
  Serial.print("received <- ");

  if (data->toPinLevel() == HIGH)
    Serial.println("HIGH");
  else
    Serial.println("LOW");

  digitalWrite(LED_PIN, data->toPinLevel());
}
