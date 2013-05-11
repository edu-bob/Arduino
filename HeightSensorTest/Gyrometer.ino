//
// Gyrometer class
//

#include <Wire.h>
#include "Gyrometer.h"

#define GYRO_ADDR_OFF  (0x69)
#define GYRO_ADDR_ON   (0x68)

// Set the sensor address here
#define GYRO_ADDR GYRO_ADDR_OFF

void Gyrometer::setup()
{
}

void Gyrometer::loop()
{
   uint8_t x_msb;   // X-axis most significant byte
   uint8_t x_lsb;   // X-axis least significant byte
   uint8_t y_msb;   // Y-axis most significant byte
   uint8_t y_lsb;   // Y-axis least significant byte
   uint8_t z_msb;   // Z-axis most significant byte
   uint8_t z_lsb;   // Z-axis least significant byte

   uint16_t x;
   uint16_t y;
   uint16_t z;

   // Get the value from the sensor
   if ((ReadByte(GYRO_ADDR, 0x1d, &x_msb) == 0) &&
       (ReadByte(GYRO_ADDR, 0x1e, &x_lsb) == 0) &&
       (ReadByte(GYRO_ADDR, 0x1f, &y_msb) == 0) &&
       (ReadByte(GYRO_ADDR, 0x20, &y_lsb) == 0) &&
       (ReadByte(GYRO_ADDR, 0x21, &z_msb) == 0) &&
       (ReadByte(GYRO_ADDR, 0x22, &z_lsb) == 0))
   {
      x = (x_msb << 8) | x_lsb;
      y = (y_msb << 8) | y_lsb;
      z = (z_msb << 8) | z_lsb;

      // Perform 2's complement
//      real_x = ~(x - 1);
//      real_y = ~(y - 1);
//      real_z = ~(z - 1);
      real_x = x;
      real_y = y;
      real_z = z;

   } else {
      Serial.println("Failed to read from sensor");
   }
}

void Gyrometer::getValues(int *res)
{
  res[0] = real_x;
  res[1] = real_y;
  res[2] = real_z;
}

void Gyrometer::calibrate()
{
   uint8_t x_msb;   // X-axis most significant byte
   uint8_t x_lsb;   // X-axis least significant byte
   uint8_t y_msb;   // Y-axis most significant byte
   uint8_t y_lsb;   // Y-axis least significant byte
   uint8_t z_msb;   // Z-axis most significant byte
   uint8_t z_lsb;   // Z-axis least significant byte
  if ((ReadByte(GYRO_ADDR, 0x1d, &x_msb) == 0) &&
       (ReadByte(GYRO_ADDR, 0x1e, &x_lsb) == 0) &&
       (ReadByte(GYRO_ADDR, 0x1f, &y_msb) == 0) &&
       (ReadByte(GYRO_ADDR, 0x20, &y_lsb) == 0) &&
       (ReadByte(GYRO_ADDR, 0x21, &z_msb) == 0) &&
       (ReadByte(GYRO_ADDR, 0x22, &z_lsb) == 0))
  {
//     WriteByte( GYRO_ADDR, 0x0c, x_msb);
//     WriteByte( GYRO_ADDR, 0x0d, x_lsb);
//     WriteByte( GYRO_ADDR, 0x0e, y_msb);
//     WriteByte( GYRO_ADDR, 0x0f, y_lsb);
//     WriteByte( GYRO_ADDR, 0x10, z_msb);
//     WriteByte( GYRO_ADDR, 0x11, z_lsb);
     WriteByte( GYRO_ADDR, 0x0c, 0);
     WriteByte( GYRO_ADDR, 0x0d, 0);
     WriteByte( GYRO_ADDR, 0x0e, 0);
     WriteByte( GYRO_ADDR, 0x0f, 0);
     WriteByte( GYRO_ADDR, 0x10, 0);
     WriteByte( GYRO_ADDR, 0x11, 0);
  }
}

