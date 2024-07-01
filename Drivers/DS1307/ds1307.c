/*
 * ds1307.c
 *
 *  Created on: Jun 30, 2024
 *      Author: hp
 */
#include "ds1307.h"
#define dev_SLA  0b1101000

static uint8_t I2c_write(uint8_t address, uint8_t *Data, uint8_t Len, ds1307_t *clock){

	HAL_I2C_Master_Transmit(clock->i2c_bus, dev_SLA, Data, Len, 100);

	return __HAL_I2C_GET_FLAG(clock->i2c_bus, HAL_I2C_ERROR_AF)? 0:1 ;

}

static uint8_t I2c_read(uint8_t address, uint8_t *Data, uint8_t Len, ds1307_t *clock){

	HAL_I2C_Master_Receive(clock->i2c_bus, dev_SLA, Data, Len, 100);
	return __HAL_I2C_GET_FLAG(clock->i2c_bus, HAL_I2C_ERROR_AF)? 0:1 ;
}
static uint8_t BCD_to_dec(uint8_t num){

	return (num>>4)*10 + (0xf & num);

}
static uint8_t dec_to_BCD(uint8_t num){
	uint8_t div =num/10;
	uint8_t rem = num%10;

	return div<<4 | rem ;
}

ds1307_stat_t DS1307_INIT(ds1307_t *clock, I2C_HandleTypeDef *i2c_bus){
	clock->i2c_bus = i2c_bus;

}
ds1307_stat_t DS1307_Set(ds1307_t *clock){

}
ds1307_stat_t DS1307_Read(ds1307_t *clock){

}

