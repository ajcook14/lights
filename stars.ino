#include <SPI.h>
#define STR 1
#define DELAY 200
#define CHIPS 3

int a[CHIPS];
int pause;

void setup() {
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  pinMode(STR, OUTPUT);
  randomSeed(1);
  
  for(int i = 0; i < CHIPS; i++) {
    a[i] = 0;
  }
}

// shift in arr of 8 bit ints, larger index translates 
// to further down the wire.
void shift(int *arr) {
  for(int i = CHIPS - 1; i >= 0; i--) {
    SPI.transfer(*(arr+i));
    //SPI.transfer((data>>(8*i)) & 255);
  }
  
  digitalWrite(STR, HIGH);
  delay(pause);
  digitalWrite(STR, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  int chip = random(0, CHIPS);
  int light = random(0, 8);
  int i, j;
  int steps = 8;
  
  // toggle the random light with pwm
  for(i = 0; i < steps; i++) {
    for(j = 0; j < 1; j++) {
      a[chip] = a[chip] ^ (1<<light);
      pause = i;
      shift(a);
      
      a[chip] = a[chip] ^ (1<<light);
      pause = steps-1-i;
      shift(a);
    }
  }
  
  a[chip] = a[chip] ^ (1<<light);
  shift(a);
}


