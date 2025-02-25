#include "eeprom_processings.h"
#include "stm32f4xx_hal.h"
#include "main.h"


//AT24C16 EPPROM data
//capacity 16kbits(2048bytes)
//page size: 16 bytes
// Total pages: 128 pages
//Address Range: 0x0000 to 0x07ff

HAL_StatusTypeDef EEPROM_WriteBlock(uint8_t DevBlockAddress, uint16_t MemAddress, uint8_t* pBuffer, uint16_t NumByteToWrite)
{
	HAL_StatusTypeDef status = HAL_OK;
	/* Write EEPROM_PAGESIZE */
	status=HAL_I2C_Mem_Write(&hi2c1, DevBlockAddress, MemAddress, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(pBuffer), NumByteToWrite, 100);

	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
	{

	}

	/* Check if the EEPROM is ready for a new operation */
	while (HAL_I2C_IsDeviceReady(&hi2c1, DevBlockAddress, EEPROM_MAX_TRIALS, I2Cx_TIMEOUT_MAX) == HAL_TIMEOUT);

	/* Wait for the end of the transfer */
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
	{

	}
	return status;
}
HAL_StatusTypeDef EEPROM_ReadBlock(uint8_t DevBlockAddress, uint16_t MemAddress, uint8_t* pBuffer, uint16_t NumByteToWrite);
