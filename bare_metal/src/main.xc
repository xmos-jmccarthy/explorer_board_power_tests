// This Software is subject to the terms of the XMOS Public Licence: Version 1.
// XMOS Public License: Version 1

#include "platform.h"

extern "C" {
void main_tile0(void);
void main_tile1(void);
}

int main(void) {
  par {
      on tile[0] : main_tile0();
      on tile[1] : main_tile1();
  }
  return 0;
}
