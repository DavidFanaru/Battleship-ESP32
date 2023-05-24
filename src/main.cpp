#include <Arduino.h>
//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(13,14,26,1);



/* we always wait a bit between updates of the display */
unsigned long delaytime=500;
int pinStanga = 32;
int pinSus = 33;
int pinDreapta = 27;
int pinJos = 12;
int pinConfirm =  15;

void setup() {
  Serial.begin(115200);
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);

  pinMode(pinStanga, INPUT);
  pinMode(pinSus, INPUT);
  pinMode(pinDreapta, INPUT);
  pinMode(pinJos, INPUT);
}

int nava1_r = 1;
int nava1_c = 2;

void start(int r, int c){
  lc.setLed(0, r, c, true);
  delay(150);
  lc.setLed(0, r, c, false);
  delay(150);
}

int dr_sg = 0;
int sus_jos = 0;

void loop() { 
  // int nava1_r = 1;
  // int nava1_c = 2;
  int nava_r[6] = {1, 2, 3, 6, 6, 6};
  int nava_c[6] = {2, 2, 2, 5, 6, 7};
  int sg = digitalRead(pinStanga);
  int sus = digitalRead(pinSus);
  int dr = digitalRead(pinDreapta);
  int jos = digitalRead(pinJos);
  int confirm = digitalRead(pinConfirm);
  start(dr_sg, sus_jos);
  if(sg == HIGH){
    dr_sg--;
    if(dr_sg == -1){
      dr_sg = 7;
    }
  }
  if(sus == HIGH){
    sus_jos--;
    if(sus_jos == -1){
      sus_jos = 7;
    }
  }
  if(dr == HIGH){
    Serial.println("Dreapta");
    dr_sg++;
    if(dr_sg == 8){
      dr_sg = 0;
    }
  }
  if(jos == HIGH){
    sus_jos++;
    if(sus_jos == 8){
      sus_jos = 0;
    }
  }
  // if(confirm == HIGH){
  //   Serial.println("Confirm");
  //     if(nava1_c == sus_jos){
  //       if(nava1_r == dr_sg){
  //       lc.setLed(0, dr_sg, sus_jos, true);
  //       dr_sg = sus_jos = 0;
  //       }
  //     }
  // }
if(confirm == HIGH){
  Serial.println("Confirm");
    for(int i = 0; i < 6; i++){
      if(dr_sg == nava_r[i] && sus_jos == nava_c[i]){
        lc.setLed(0, dr_sg, sus_jos, true);
        dr_sg = sus_jos = 0;
      }
    }
}
  

}
