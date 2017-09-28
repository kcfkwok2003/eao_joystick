/*
  eao_js
  
*/

#include "Mouse.h"

// PINS define
#define Y0 A0
#define YP1 A1
#define YM1 A2
#define XM1 A3
#define XP1 A4
#define X0 A5

#define XP3 2
#define XM3 3
#define XP2 4
#define XM2 5
#define YP2 6
#define YM2 7

#define YP3 8
#define YM3 9

#define BTN 10

#define LED 13

#define SCALE 1
#define RESPONSE_DELAY 5

int px;
int py;
unsigned long tm;

int x_axis[]= { XM3,XM2,XM1,X0,XP1,XP2,XP3 };
//int y_axis[] = { YM3,YM2,YM1,Y0,YP1,YP2,YP3};
int y_axis[] = { YP3,YP2,YP1,Y0,YM1,YM2,YM3};

void init_x_axis() {
     int i;
     for (i=0; i<7; i=i+1) {
     	 pinMode(x_axis[i],INPUT);
	 digitalWrite(x_axis[i],HIGH);
     }
     px=0;
}

int read_x_axis() {
    int x,i;
    for (i=0; i<7; i=i+1) {
    	if (digitalRead(x_axis[i])==0) {
	   x=i-3;
	   return x;
	}
    }
    return px;
}

void init_y_axis() {
     int i;
     for (i=0; i<7; i=i+1) {
     	 pinMode(y_axis[i],INPUT);
	    digitalWrite(y_axis[i],HIGH);
     }
     py=0;
}

int read_y_axis() {
    int i,y;
    for (i=0; i<7; i=i+1) {
    	if (digitalRead(y_axis[i])==0) {
	      y=i-3;
	      return y;
	    }
    }
    return px;
}


void init_btn() {
     pinMode(BTN,INPUT);
     digitalWrite(BTN, HIGH);
}

void setup() {
    tm=0;
     init_x_axis();
     init_y_axis();
     init_btn();
     pinMode(LED,OUTPUT);
     Mouse.begin();
}

void loop() {
     int x,y;
     int kpressed=0;
     x = read_x_axis() * SCALE;
     y = read_y_axis() * SCALE;
     Mouse.move(x,y,0);

     if (digitalRead(BTN)==LOW) {
         digitalWrite(LED, HIGH);
     	if (!Mouse.isPressed(MOUSE_LEFT)) {
	        Mouse.press(MOUSE_LEFT);
          kpressed=1;
	      } 
     } else {
        digitalWrite(LED,  LOW);
       if (Mouse.isPressed(MOUSE_LEFT)) {
       	  Mouse.release(MOUSE_LEFT);
       }
     }
     if (kpressed) {
        tm= millis() + 100;
        //digitalWrite(LED, HIGH);
     } else {
        if (millis() > tm) {
          //digitalWrite(LED,LOW);
        }
     }
     
     delay(RESPONSE_DELAY);
}
