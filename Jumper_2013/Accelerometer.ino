//
// Accelerometer class //
//

#include "Accelerometer.h"

#include <Wire.h>

// Possible sensor addresses (suffix correspond to DIP switch positions)
#define SENSOR_ADDR_OFF  (0x1D)
#define SENSOR_ADDR_ON   (0x53)

#define SENSOR_ADDR SENSOR_ADDR_OFF

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
   // Join the I2C bus as master
   Wire.begin();

   // Set 25 Hz output data rate and 25 Hz bandwidth and disable low power mode
   WriteByte(SENSOR_ADDR, REG_BW_RATE_ADDR, 0x08);

   // Disable auto sleep
   WriteByte(SENSOR_ADDR, REG_PWR_CTL_ADDR, 0x08);

   // Disable interrupts (the pins are not brought out anyway)
   WriteByte(SENSOR_ADDR, REG_INT_ENABLE_ADDR, 0x0);
}

void Accelerometer::loop()
{
}

int Accelerometer::getValue()
{
   uint8_t devId;
   uint8_t x_msb;   // X-axis most significant byte
   uint8_t x_lsb;   // X-axis least significant byte
   uint16_t x;
   // Read the device ID just to make sure we are talking to the correct sensor
   if (ReadByte(SENSOR_ADDR, 0x0, &devId) != 0) {
      Serial.println(F("Cannot read device ID from sensor"));
   } else if (devId != 0xE5) {
      Serial.print(F("Wrong/invalid device ID "));
      Serial.print(devId);
      Serial.println(F(" (expected 0xE5)"));
   } else {
      // Read the output
      if ((ReadByte(SENSOR_ADDR, REG_DATAX1_ADDR, &x_msb) == 0) && (ReadByte(SENSOR_ADDR, REG_DATAX0_ADDR, &x_lsb) == 0) ) {
         x = (x_msb << 8) | x_lsb;

         // Perform 2's complement
         int16_t real_x = ~(x - 1);
         return real_x;
      }
      return -1;
   }
   return -1;
}


