//
// Height sensor
//

#include <Wire.h>

// Gyro address: switch off: 0x69, switch on: 0x68
#define GYRO_ADDR ((uint8_t)0x69)

// Accelerometer address: switch off: 0x1D, switch on: 0x53
#define ACCEL_ADDR ((uint8_t)0x1D)

#define REG_BW_RATE_ADDR      ((uint8_t)0x2c)
#define REG_PWR_CTL_ADDR      ((uint8_t)0x2d)
#define REG_INT_ENABLE_ADDR   ((uint8_t)0x2e)
#define REG_DATA_FORMAT_ADDR  ((uint8_t)0x31)
#define REG_DATAX0_ADDR       ((uint8_t)0x32)
#define REG_DATAX1_ADDR       ((uint8_t)0x33)
#define REG_DATAY0_ADDR       ((uint8_t)0x34)
#define REG_DATAY1_ADDR       ((uint8_t)0x35)
#define REG_DATAZ0_ADDR       ((uint8_t)0x36)
#define REG_DATAZ1_ADDR       ((uint8_t)0x37)
#define REG_FIFO_CTL_ADDR     ((uint8_t)0x38)

void Sensor::setup()
{
   // Join the I2C bus as master
   Wire.begin();

   // AUX_IF_RST, to pass through to the accelerometer
   WriteByte(GYRO_ADDR, (uint8_t)0x3D, (uint8_t)0x08);
   // Set up the Accelerometer
      // Set 25 Hz output data rate and 25 Hz bandwidth and disable low power mode
   WriteByte(ACCEL_ADDR, REG_BW_RATE_ADDR, 0x08);

   // Disable auto sleep
   WriteByte(ACCEL_ADDR, REG_PWR_CTL_ADDR, 0x08);

   // Disable interrupts (the pins are not brought out anyway)
   WriteByte(ACCEL_ADDR, REG_INT_ENABLE_ADDR, 0x0);
   
   // Make the accelerometer a slave to the gyro
   WriteByte(GYRO_ADDR, (uint8_t)0x14, (uint8_t)(0x80|ACCEL_ADDR));
   // Burst mode read address
   WriteByte(GYRO_ADDR, (uint8_t)0x18, (uint8_t)0x32);
   WriteByte(GYRO_ADDR, (uint8_t)0x3D, (uint8_t)(0x20|0x08));
}

void Sensor::loop()
{
  uint8_t buffer[14];
//  Serial.println("A");
  if ( readBytes(0x1b, buffer, 14)==14) {
//    Serial.println("B");
    temp = ~((buffer[0]<<8 | buffer[1])-1);
    gyro_x = ~((buffer[2]<<8 | buffer[3])-1);
    gyro_y = ~((buffer[4]<<8 | buffer[5])-1);
    gyro_z = ~((buffer[6]<<8 | buffer[7])-1);
    acc_x = ~((buffer[8]<<8 | buffer[9])-1);
    acc_y = ~((buffer[10]<<8 | buffer[11])-1);
    acc_z = ~((buffer[12]<<8 | buffer[13])-1);
  } else {
    Serial.println(F("Failed to read from sensor"));
  }
}

void Sensor::print()
{
  char buf[70];
  sprintf(buf, "%7d, %7d, %7d, %7d, %7d, %7d, %7d", temp, gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z);
  Serial.println(buf);

}

int Sensor::readBytes(uint8_t reg, uint8_t *buf, int bytes)
{
//  Serial.println("RB1");
  Wire.beginTransmission((uint8_t)GYRO_ADDR);
  Wire.write(reg);
  Wire.endTransmission();  
  
  Wire.requestFrom((uint8_t)GYRO_ADDR, (uint8_t)bytes); 
//  Serial.println("RB2");

  int i;
  for ( i=0 ; i<bytes ; i++ ) {
    while(!Wire.available()); // wait until data available
    *buf++ = Wire.read();    // receive a byte as character
  }
//  Serial.println("RB3");
  return i;
}

