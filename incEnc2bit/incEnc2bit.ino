/*

  Incremental( rotary ) encoder - 2 Bit
  developed by Klingl János

  If the counter moves in opposite way try to swap HIGH and LOW bits.
  If the counter doesn't work at all, check the connections.

*/

#include <chrono>

std::chrono::system_clock::time_point clockref;
std::chrono::system_clock::time_point nextPrint;

uint8_t HIGH_BIT = 6;
uint8_t LOW_BIT = 7;
int32_t c = 0;

void setup(void) {
  Serial.begin( 115200 );
  pinMode( HIGH_BIT, INPUT_PULLUP);
  pinMode( LOW_BIT, INPUT_PULLUP);
  clockref = std::chrono::system_clock::now();
  nextPrint = clockref + std::chrono::milliseconds( 500 ) ;
}

void loop(void) {
  int dh = digitalRead( HIGH_BIT );
  int dl = digitalRead( LOW_BIT );
  static int32_t ph = dh;
  static int32_t pl = dl;
  if( ph == dh && pl != dl ) {
    if( dh == dl )
        --c;
    else
        ++c;
  }
  if( pl == dl && ph != dh ) {
    if( dh == dl )
        ++c;
    else
        --c;
  }
  ph = dh;
  pl = dl;
  clockref = std::chrono::system_clock::now();
  if( clockref > nextPrint ) {
    Serial.printf( "%d\n", c );
    nextPrint = clockref + std::chrono::milliseconds( 200 ) ;
  }
}