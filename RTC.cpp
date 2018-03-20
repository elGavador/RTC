#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdint>
#include "I2C.cpp"


class RTC {
public:
  RTC(){};
  void cmd(uint8_t, int, uint8_t);  //command, data[0], data[1]
  ~RTC(){};
};

void RTC::cmd(uint8_t cmd, int data0, uint8_t data1)
{
  uint8_t addr = 0x00;//RTC ADDRESS
  uint8_t packet[60] = {0};
  int file;
  int length;
  bool TRcomplete;
  
  I2C i2c;
  
  file = i2c.open(addr);
  
  packet[0] = cmd;
  int * data0location = (int*)(&packet[1]);
  *data0location = data0;
  packet[5] = data1;
  
  length = 6;	//length of command frame
  
  //if TRcomplete = 1, the command was sent successfully and data can then be read from the EPS
  TRcomplete = i2c.write(file, packet, length);  //address of EPS should be a global variable in fact all of the I2C 
												//addresses should be global or at least known by the I2C class 
  if (TRcomplete)
  {
	length = 2; //how many data bytes to be read
	i2c.read(file, packet, length);
  }
}