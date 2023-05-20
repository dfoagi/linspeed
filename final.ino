#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);

int flamePin_start = 8; // задание порта для digital-выхода датчика на старте
int flamePin_stop = 9; // задание порта для digital-выхода датчика на финише
int but = 12;          // задание порта для присоединения кнопки

void setup() {
    // инициализация и очистка дисплея
    display.begin();
    display.clearDisplay();
    display.display();
    
    display.setContrast(30); // установка контраста
    delay(1000);
    display.setTextSize(1);  // установка размера шрифта
    display.setTextColor(BLACK); // установка цвета текста
    display.setCursor(0,0); // установка позиции курсора
  
    display.println("ready to start");
    display.display();

    Serial.begin(9600);
  
    pinMode( flamePin_start, INPUT );
    pinMode( flamePin_stop, INPUT );
    pinMode( but, INPUT_PULLUP );
    pinMode(13, 0);
    digitalWrite(but, HIGH);            // установка кнопки в нормально-поднятое состояние
}

      // задаем переменные 
double i = 0;
double a = millis();
double c ;
int z = 0;  // переменная-флажок для срабатывания первого датчика только один раз

void loop() {
  if(!digitalRead(flamePin_start) && z == 0)
  {
    display.clearDisplay();
    display.display();
    display.println("started");
    display.display();
    a = millis();
      while(digitalRead(flamePin_stop))
      {
        c = millis();
        i = (c-a)/1000;
        //Serial.println(i);
      }
  }

  //if(!digitalRead(flamePin_stop) && (flamePin_start)) {
  if(!digitalRead(flamePin_stop) && z ==0)
  {
    display.clearDisplay();
    display.display();
    display.print("time = ");
    display.print(i);
    display.println("s");
    Serial.println(i);
    display.print("speed = ");
    display.print(1.0 / i);
    display.println(" m/s");
    display.display();
    z = 1;
    delay(1000);
  }
   
     if(digitalRead(but) == LOW){
      z = 0;
      display.clearDisplay();
      display.println("ready to start");
      display.display();
      display.setCursor(0,0);
      delay(1000);            
     }

}
