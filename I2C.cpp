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
#include <iostream>
#include "I2C.h"


int I2C::open(uint8_t addr)
{
  int file;
  int adapter_nr = 1; /* our OBC should only have one I2C adapter */
  char filename[20];
 
  snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
  file = ::open(filename, O_RDWR);
  if (file < 0) { 
    /* ERROR HANDLING; you can check errno to see what went wrong */
    exit(1);
  }

/*When you have opened the device, you must specify with what device
address you want to communicate:*/

  if (ioctl(file, I2C_SLAVE, addr) < 0) {
    /* ERROR HANDLING; you can check errno to see what went wrong */
    exit(1);
  }
  return file;
}

bool I2C::write (int file, uint8_t packet[], int length)
{
	int x;
    if (x = ::write(file,packet,length) != length) 
    {
      /* ERROR HANDLING: i2c transaction failed */
      printf("Failed to write to the i2c bus.\n");
      //buffer = g_strerror(errno);
     // printf(buffer);
     // printf("\n\n");
		return 0;
    }
	return 1;
}


bool I2C::read (int file, uint8_t packet[], int length)
{
	
	// Using I2C Read
    if (::read(file,packet,length) != length) 
	{
        /*ERROR HANDLING: i2c transaction failed */
        printf("Failed to read from the i2c bus. %d != %d\n", length);
        packet = (uint8_t*)strerror(errno);
		printf("%s", packet);
        printf("\n\n");
		return 0;
    }
	else
	{
		printf("Data read: %s\n", packet);
		return 1;
	}
}