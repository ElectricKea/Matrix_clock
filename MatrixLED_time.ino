#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

int now_hour, now_min, now_date;
//int now_sec;

const char *dayName[7] = {
 "Fr", "Sa", "Su", "Mo", "Tu", "We", "Th"
};

void Thu (){
  matrix.drawRect(15, 9, 2, 2, matrix.Color333(1,0,0));   //DrawRect (xpoint, ypoint, points from xpoint, points from ypoint)
  matrix.drawRect(15, 8, 2, 2, matrix.Color333(1,0,0));
}

void setup() {
  matrix.begin();
}

void time_print() {
  matrix.setTextSize(1);
  tmElements_t tm;
  if (RTC.read(tm)) {       //If it can read the RTC then do this part
    matrix.setCursor(18,0);
    print2digits(tm.Minute);
      if (now_min != tm.Minute) {
        for (int x=17; x<32; x++){
            for (int y=0;y<8; y++){
              matrix.drawPixel(x,y, matrix.Color333(0,0,0));
          }
      }  
    }
  now_min = tm.Minute;

//seperator
  matrix.drawRect(15, 1, 2, 2, matrix.Color333(1,0,0));   //DrawRect (xpoint, ypoint, points from xpoint, points from ypoint)
  matrix.drawRect(15, 4, 2, 2, matrix.Color333(1,0,0));


  matrix.setCursor(3,0);
  print2digits(tm.Hour);
  if (now_hour != tm.Hour) {
    for (int x=0; x<14; x++){
      for (int y=0;y<8; y++){
            matrix.drawPixel(x,y, matrix.Color333(0,0,0));
      }
    }  
  }
  now_hour = tm.Hour;
    
  matrix.setCursor(0,9);
  matrix.print(tm.Day);
  matrix.print('/');
  matrix.print(tm.Month);
  matrix.print(tm.Wday);
  if (now_date != tm.Day){
    for (int x=0; x<12; x++){
      for (int y=9; y<16; y++){
        matrix.drawPixel(x,y, matrix.Color333(0,0,0)); 
      }
    }    
  }
  now_date = tm.Day;
     
  }else {          //If it can't read the RTC, then do this part
    if (RTC.chipPresent()) {
      matrix.print("RTC stopped");
   } else {
      matrix.print("DS1307 read error!");
   }
    delay(9000);
  }
  //delay(1000);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    matrix.print('0');
  }
  matrix.print(number);
}


void loop(){
  time_print();
  matrix.setTextColor(matrix.Color333(0,0,1));

  
}
