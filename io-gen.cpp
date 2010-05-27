#include <stdio.h>
#include <stdint.h>

#define LETTER_COUNT 8  // A to H
#define PIN_COUNT 8     // 0 to 7
int main(void){
  for(uint8_t letter = 'A'; letter < 'A' + LETTER_COUNT; letter++){
    printf("\n/* PORT %1c */\n", letter);
    for(uint8_t pin = 0; pin < PIN_COUNT; pin++){
      printf("#ifdef P%1c%1d\n", letter, pin);
      printf("AVRPin_F(%1c, %1d);\n", letter, pin);
      printf("#endif\n");
    }
  }
  return 0;
}

