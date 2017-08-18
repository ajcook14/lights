#include <SPI.h>
#define STR 1
#define DELAY 20
#define CHIPS 6

void setup() {
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  pinMode(STR, OUTPUT);
}

// shift in arr of 8 bit ints, larger index translates 
// to further down the wire.
void shift(int *arr) {
  for(int i = CHIPS - 1; i >= 0; i--) {
    SPI.transfer(*(arr+i)); // SPI.transfer(arr[i]);
    //SPI.transfer((data>>(8*i)) & 255);
  }
  
  digitalWrite(STR, HIGH);
  delay(DELAY);
  digitalWrite(STR, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  int a[CHIPS], i, j, k;
  
  for(i = 0; i < CHIPS; i++) {
    a[i] = 0;
  }
  
  for(i = 0; i < CHIPS; i++) {
    for(j = 0; j < ((i < CHIPS - 1) ? 8 : 7); j++) {
      a[i] = 1<<j;
      shift(a);
    }
    a[i] = 0;
  }
  
  for(i = CHIPS-1; i >= 0; i--) {
    for(j = 7; j >= (i > 0 ? 0 : 1); j--) {
      a[i] = 1<<j;
      shift(a);
    }
    a[i] = 0;
  }
  /*
  for(unsigned long i = 1; i<(1<<10); i = i<<1) {
    shift(i);
  }
  */
  
  /*
  int limit = 1<<((CHIPS*8)-1);
  for(int i = 1; i < limit; i = i << 1) {
    shift(i);
  }
  */
}
