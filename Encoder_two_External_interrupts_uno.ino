/*
Developer: KaiChun, Wu 
Email: kai.wu013@gmail.com

Read two encoder use uno(or other 329P Arduino bord) 
with two External interrupts pin.

connect
encoder 1 phase A digital pin2
encoder 1 phase B digital pin4
encoder 2 phase A digital pin3
encoder 2 phase B digital pin5
*/

#include "Timer.h" 
/* https://github.com/JChristensen/Timer */
#include "arduino2.h"
/* https://github.com/jdolinay/Arduino_DIO2  
remember two copy out the folder in "board" according to your board
*/

#define ENCL_a 2
#define ENCR_a 3
GPIO_pin_t ENCL_b = PD4 ;
GPIO_pin_t ENCR_b = PD5 ;
int  L_step=0;
int  R_step=0;
int  L_state=0;
int  R_state=0;
Timer t;
volatile uint8_t *ENCL_b_port;
volatile uint8_t *ENCR_b_port;
uint8_t ENCL_b_mask;
uint8_t ENCR_b_mask;

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
  pinMode(ENCL_a, INPUT);
  pinMode(ENCL_b, INPUT);
  pinMode(ENCR_a, INPUT);
  pinMode(ENCR_b, INPUT);
  pinMode(13, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ENCL_a), ENCL, FALLING );
  attachInterrupt(digitalPinToInterrupt(ENCR_a), ENCR, FALLING );
  t.every(100, sandprint);
    ENCL_b_mask = digitalPinToBitMask(ENCL_b);
    ENCL_b_port = portInputRegister(digitalPinToPort(ENCL_b));
    ENCR_b_mask = digitalPinToBitMask(ENCR_b);
    ENCR_b_port = portInputRegister(digitalPinToPort(ENCR_b));
}

void loop() {
  t.update();

}


void ENCL() {
  L_state = ( *ENCL_b_port & ENCL_b_mask) != 0; //read the pin state
  if (L_state){L_step++;}
  else {
  L_step--;}
}

void ENCR() {
  R_state = ( *ENCR_b_port & ENCR_b_mask) != 0;  //read the pin state
  if (R_state){R_step++;}
  else{R_step--;}
}

void sandprint(void *context)
{
   Serial.print("L:");
  Serial.print(L_step);
  L_step=0;
  Serial.print("____R:");
  Serial.println(R_step);
  R_step=0;
}
