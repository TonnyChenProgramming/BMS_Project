#ifndef __EEPROM_PROCESSINGS_H
#define __EEPROM_PROCESSINGS_H

#include <stdint.h>
#include "stm32f4xx_hal.h"

#define EEPROM_PAGESIZE 8
#define I2Cx_TIMEOUT_MAX                50      // Max 50ms per I2C operation
#define EEPROM_MAX_TRIALS               100     // Retry 100 times, total ~5s

// Function prototypes
HAL_StatusTypeDef EEPROM_WritePage(uint8_t DevBlockAddress, uint16_t MemAddress, uint8_t* pBuffer, uint16_t NumByteToWrite);
HAL_StatusTypeDef EEPROM_ReadPage(uint8_t DevBlockAddress, uint16_t MemAddress, uint8_t* pBuffer, uint16_t NumByteToRead);




#endif
