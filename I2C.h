#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstdint>

class I2C {
public:
  I2C(){};
  int open(uint8_t);
  bool read(int, uint8_t*, int); //needs to be written
  bool write(int, uint8_t*, int);
  ~I2C(){};
};
