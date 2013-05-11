//
// Accelerometer class
//

#include "Accelerometer.h"

#include <Wire.h>

// Possible sensor addresses (suffix correspond to DIP switch positions)
#define ACCEL_ADDR_OFF  (0x1D)
#define ACCEL_ADDR_ON   (0x53)

#define ACCEL_ADDR ACCEL_ADDR_OFF

// Sensor register addresses (gotten from datasheet)
#define REG_DEVID_ADDR        (0x00)
#define REG_THRESH_TAP_ADDR   (0x1d)
#define REG_TAP_DUR_ADDR      (0x21)
#define REG_TAP_LATENCY_ADDR  (0x22)
#define REG_TAP_WINDOW_ADDR   (0x23)      
#define REG_BW_RATE_ADDR      (0x2c)
#define REG_PWR_CTL_ADDR      (0x2d)
#define REG_INT_ENABLE_ADDR   (0x2e)
#define REG_DATA_FORMAT_ADDR  (0x31)
#define REG_DATAX0_ADDR       (0x32)
#define REG_DATAX1_ADDR       (0x33)
#define REG_DATAY0_ADDR       (0x34)
#define REG_DATAY1_ADDR       (0x35)
#define REG_DATAZ0_ADDR       (0x36)
#define REG_DATAZ1_ADDR       (0x37)
#define REG_FIFO_CTL_ADDR     (0x38)

void Accelerometer::setup()
{

   // Set 25 Hz output data rate and 25 Hz bandwidth and disable low power mode
   WriteByte(ACCEL_ADDR, REG_BW_RATE_ADDR, 0x08);

   // Disable auto sleep
   WriteByte(ACCEL_ADDR, REG_PWR_CTL_ADDR, 0x08);

   // Disable interrupts (the pins are not brought out anyway)
   WriteByte(ACCEL_ADDR, REG_INT_ENABLE_ADDR, 0x0);
}

void Accelerometer::loop()
{
   uint8_t devId;
   uint8_t x_msb;   // X-axis most significant byte
   uint8_t x_lsb;   // X-axis least significant byte
   uint8_t y_msb;   // Y-axis most significant byte
   uint8_t y_lsb;   // Y-axis least significant byte
   uint8_t z_msb;   // Z-axis most significant byte
   uint8_t z_lsb;   // Z-axis least significant byte
   uint16_t x;
   uint16_t y;
   uint16_t z;

   // Read the device ID just to make sure we are talking to the correct sensor
   if (ReadByte(ACCEL_ADDR, 0x0, &devId) != 0) {
      Serial.println(F("Cannot read device ID from sensor"));
   } else if (devId != 0xE5) {
      Serial.print(F("Wrong/invalid device ID "));
      Serial.print(devId);
      Serial.println(F(" (expected 0xE5)"));
   } else {
      // Read the output
      if ((ReadByte(ACCEL_ADDR, REG_DATAX1_ADDR, &x_msb) == 0) &&
          (ReadByte(ACCEL_ADDR, REG_DATAX0_ADDR, &x_lsb) == 0) &&
          (ReadByte(ACCEL_ADDR, REG_DATAY1_ADDR, &y_msb) == 0) &&
          (ReadByte(ACCEL_ADDR, REG_DATAY0_ADDR, &y_lsb) == 0) &&
          (ReadByte(ACCEL_ADDR, REG_DATAZ1_ADDR, &z_msb) == 0) &&
          (ReadByte(ACCEL_ADDR, REG_DATAZ0_ADDR, &z_lsb) == 0))
      {
         x = (x_msb << 8) | x_lsb;
         y = (y_msb << 8) | y_lsb;
         z = (z_msb << 8) | z_lsb;

         // Perform 2's complement
//         real_x = ~(x - 1);
//         real_y = ~(y - 1);
//         real_z = ~(z - 1);
         real_x = x;
         real_y = y;
         real_z = z;
      }
   }
}

void Accelerometer::getValues(int *res)
{
  res[0] = real_x;
  res[1] = real_y;
  res[2] = real_z;
}


