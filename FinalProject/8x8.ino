

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

int car_pos = 0;

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

int score = 0;

int command = 0;
int inc = 0;
int NewMap = 0;
int timer[] = {85, 75, 65, 50 , 45, 40, 35, 30, 25, 20};

void setup() {
  Serial.begin(9600);
  
  matrix.begin(0x70);  // pass in the address
  matrix.setRotation(3);
}

static const uint8_t PROGMEM
  two_long[] =
  { B10000000,
    B10000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000},
  car_init[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B10000000,
    B10000000};





int xpos[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int ypos[] = {-2,-4,-6, -8, -10,-12,-14,-16,-18,-20,-22,-24,-26,-28,-30,-32};

int xbuff[] = {3, 4, 1, 6};
int ybuff[] = {-34, -36, -38, -40};

int count = 0;
int roundcount = 0;


void genlevel(){
  for(int j = 0; j < 15; j++){
      int x = random(0,8);
      xpos[j] = x;
  }
}

void minusy(){
  if(count == timer[inc]){
    for(int i = 0; i < 15; i++){
      if(ypos[i] >= 28){
        ypos[i] -= 38;
      }
      ypos[i]++;
    }
    count = 0;
  }
  score++;
  count++;
  roundcount++;
}


void playerMove(){
    if (Serial.available() > 0) {
    command = Serial.read();
    Serial.print("I received: ");
    Serial.println(command, DEC);
    
    switch(command) { 
      case 0:
        break;
      case 1: //left
          while(car_pos > 0){
            car_pos--;
            break;
          }
        break;
      case 2: //right
          while(car_pos < 7){
            car_pos++;
            break;
          }  
        break;
      case 3:
            break;
      default:
        break;
    }
    
  }
}

void IncLevel(){
    if(NewMap == 0){
      genlevel();
      NewMap = 1;
    }
    if(roundcount == (38 * timer[inc]) + 1){
      roundcount = 0;
      if(inc < 9){
        inc++;
      }
      NewMap = 0;
    }
}
void checkLose(){
  for(int i = 0; i < 15; i++){
    if((xpos[i] == car_pos) & ((ypos[i] == 5) | (ypos[i] == 6))){
      matrix.drawBitmap(car_pos, 0, car_init, 8, 8, LED_YELLOW);
      matrix.writeDisplay();
      lose();
    }
  }
}


void lose(){
  playerMove();
  if(command == 0x03){  
    reset();
  }
  else{
    sendScore();
    lose();
  }
}

void reset(){
    for(int i = 0; i < 15; i++){
      xpos[i] = 0;
      ypos[i] = -2*(i+1);
    }
    NewMap = 0;
    inc = 0;
    count=0;
    car_pos = 0;
    roundcount=0;
    score=0;
}

int switchOn = 0;
void InitialOn(){
  matrix.clear();
  matrix.writeDisplay();
  playerMove();
  if(command == 0x03){
    reset();
  }
  else{
    InitialOn();
  }
}

void sendScore(){
  int time = score/325;
  //Serial.print("I sent: ");
  //Serial.println(time);
  Serial.write(time);
}

void loop() {

  if(switchOn==0){
    InitialOn();
    switchOn=1;
  }
  
 IncLevel();
 playerMove();
 minusy();

 sendScore();
  
  matrix.clear();
  matrix.drawBitmap(car_pos, 0, car_init, 8, 8, LED_RED); 
  matrix.drawBitmap(xpos[0], ypos[0], two_long, 8,8,LED_GREEN);
  matrix.drawBitmap(xpos[1], ypos[1], two_long, 8,8,LED_GREEN);
  matrix.drawBitmap(xpos[2], ypos[2], two_long, 8,8,LED_GREEN);
  matrix.drawBitmap(xpos[3], ypos[3], two_long, 8,8,LED_GREEN);
  matrix.drawBitmap(xpos[4], ypos[4], two_long, 8,8,LED_GREEN);
  matrix.drawBitmap(xpos[5], ypos[5], two_long, 8,8,LED_GREEN);
  matrix.drawBitmap(xpos[6], ypos[6], two_long, 8,8,LED_GREEN);
  matrix.drawBitmap(xpos[7], ypos[7], two_long, 8,8,LED_GREEN);
  matrix.drawBitmap(xpos[8], ypos[8], two_long, 8,8,LED_GREEN);
  matrix.drawBitmap(xpos[9], ypos[9], two_long, 8,8,LED_GREEN);
  matrix.drawBitmap(xpos[10], ypos[10], two_long, 8,8,LED_GREEN);
  matrix.drawBitmap(xpos[11], ypos[11], two_long, 8,8,LED_GREEN);
  matrix.drawBitmap(xpos[12], ypos[12], two_long, 8,8,LED_GREEN);
  matrix.drawBitmap(xpos[13], ypos[13], two_long, 8,8,LED_GREEN);
  matrix.drawBitmap(xpos[14], ypos[14], two_long, 8,8,LED_GREEN);
  matrix.drawBitmap(xpos[15], ypos[15], two_long, 8,8,LED_GREEN);

  
  
  matrix.writeDisplay();

  checkLose();


}
