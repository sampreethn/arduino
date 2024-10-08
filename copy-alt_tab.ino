
#include <Wire.h>
#include<Keyboard.h>
#include "paj7620.h"

/* 
Notice: When you want to recognize the Forward/Backward gesture or other continuous gestures, your gestures' reaction time must less than GES_REACTION_TIME(0.8s). 
        You also can adjust the reaction time according to the actual circumstance.
*/
#define GES_REACTION_TIME    100
#define GES_QUIT_TIME     100

void setup()
{
  uint8_t error = 0;

  Serial.begin(9600);
  Keyboard.begin();
    Serial.println("\nPAJ7620U2 TEST DEMO: Recognize 15 gestures.");

  error = paj7620Init();      // initialize Paj7620 registers
  if (error) 
  {
    Serial.print("INIT ERROR,CODE:");
    Serial.println(error);
   }
  else
  {
    Serial.println("INIT OK");
  }
  Serial.println("Please input your gestures:");
}

void loop()
{
  uint8_t data = 0, data1 = 0, error; 

  error = paj7620ReadReg(0x43, 1, &data);       // Read Bank_0_Reg_0x43/0x44 for gesture result.
  if (!error) 
  {
    switch (data)                   // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).
    {
      case GES_RIGHT_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_LEFT_FLAG) 
        {
          Serial.println("Right-Left");
        }
        else if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Right");
          Keyboard.press(131);
          delay(100);
          Keyboard.press(215);
          delay(100);
          Keyboard.release(131);
          Keyboard.release(215);        
        }
                   
        break;
      case GES_LEFT_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_RIGHT_FLAG) 
        {
          Serial.println("Left-Right");
        }
        else if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Left");
          Keyboard.press(131);
          delay(100);
          Keyboard.press(216);
          delay(100);
          Keyboard.release(131);
          Keyboard.release(216);
        }          
        break;
        break;
      case GES_UP_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_DOWN_FLAG) 
        {
          Serial.println("Up-Down");
        }
        else if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
          Keyboard.press(224);
          delay(100);
          Keyboard.release(224);
        }
        else
        {
          Serial.println("Up");
          Keyboard.press(131);
          delay(100);
          Keyboard.press(218);
          delay(100);
          Keyboard.release(131);
          Keyboard.release(218);
          
        }
        break;
      case GES_DOWN_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_UP_FLAG) 
        {
          Serial.println("Down-Up");
        }
        else if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Down");

        }
        break;
      case GES_FORWARD_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Forward-Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
          Keyboard.press(32);
          delay(100);
          Keyboard.release(32);
        }
        break;
      case GES_BACKWARD_FLAG:     
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Backward-Forward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        break;
      case GES_CLOCKWISE_FLAG:
        Serial.println("Clockwise");
          Keyboard.press(130);
          delay(10);
          Keyboard.press(179);
          delay(100);
          Keyboard.release(130);
          Keyboard.release(179);
        break;
      case GES_COUNT_CLOCKWISE_FLAG:
        Serial.println("anti-clockwise");
          Keyboard.press(130);
          delay(10);
          Keyboard.press(179);
          delay(100);
          Keyboard.release(130);
          Keyboard.release(179);
        break;  
      default:
        paj7620ReadReg(0x44, 1, &data1);
        if (data1 == GES_WAVE_FLAG) 
        {
          Serial.println("wave");
        }
        break;
    }
  }
  delay(100);
}
