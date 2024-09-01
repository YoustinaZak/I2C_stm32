/*
 * HW_interface.c
 *
 *  Created on: Sep 1, 2024
 *      Author: hp
 */

#include "../Inc/HW_interface.h"
#include "stm32f1xx.h"
//ds1307_t Clock1;
//Clock1.HW_Interface.write = I2c_write;
//Clock1.HW_Interface.read = I2c_read;
extern I2C_HandleTypeDef hi2c1;

uint8_t I2c_write(uint8_t dev_SLA, uint8_t *Data, uint8_t Len) { //address removed

			HAL_StatusTypeDef ok = HAL_I2C_Master_Transmit(&hi2c1, dev_SLA << 1,
					Data, Len, 100); //sends write bit automatically
			return (ok == HAL_OK) ? 1 : 0;
			//return __HAL_I2C_GET_FLAG(clock->i2c_bus, HAL_I2C_ERROR_AF) ? 0 : 1;

		}

uint8_t I2c_read(uint8_t dev_SLA, uint8_t *Data, uint8_t Len) { //address removed

			HAL_StatusTypeDef ok = HAL_I2C_Master_Receive(&hi2c1, dev_SLA << 1,
					Data, Len, 100);
			return (ok == HAL_OK) ? 1 : 0;
			//return __HAL_I2C_GET_FLAG(clock->i2c_bus, HAL_I2C_ERROR_AF) ? 0 : 1; // if ack fail it = true = return 0

}
