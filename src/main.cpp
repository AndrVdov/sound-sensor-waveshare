#include <Arduino.h>
const unsigned int ledPinRed = 8;
const unsigned int ledPinYellow = 7;
const unsigned int soundAin = A0;
unsigned int adValue = 0;
unsigned int cottonCount = 0;

boolean swich = false;

const unsigned int rattling = 200; // ms
const unsigned int cotton = 1000;  // ms
unsigned long rattlingMillis = 0;
unsigned long cottonMillis = 0;

void setup()
{
  pinMode(soundAin, INPUT);
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinYellow, OUTPUT);
}

void loop()
{
  adValue = analogRead(soundAin);

  if (adValue > 720 || adValue < 320)
  {
    if (millis() - rattlingMillis > rattling)
    {
      rattlingMillis = millis();
      cottonCount++;
      digitalWrite(ledPinYellow, 1);

      // если хлопок первый, создаем временную точку
      if (cottonCount == 1)
      {
        cottonMillis = millis();
      }
    }
  }

  // выключаем жолтый лед через rattling милисекунд
  if (millis() - rattlingMillis > rattling)
  {
    digitalWrite(ledPinYellow, 0);
  }

  // если с момента первого хлопка прошло больше cotton милисекунд, сбрасываем сщетчик хлопков
  if (millis() - cottonMillis > cotton)
  {
    cottonCount = 0;
  }

  // зафиксировали два хлопка в пределах cotton милисекунд
  if (cottonCount >= 2)
  {
    cottonCount = 0;
    swich = !swich;
    digitalWrite(ledPinRed, swich);
  }
}
