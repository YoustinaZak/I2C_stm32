/*
 * ds1307.c
 *
 *  Created on: Jun 30, 2024
 *      Author: hp
 */
#include "ds1307.h"
#define dev_SLA       0b1101000
#define start_address 0x00

static uint8_t I2c_write(uint8_t *Data, uint8_t Len, ds1307_t *clock) { //address removed

	HAL_StatusTypeDef ok = HAL_I2C_Master_Transmit(clock->i2c_bus, dev_SLA << 1,
			Data, Len, 100); //sends write bit automatically
	return (ok == HAL_OK) ? 1 : 0;
	//return __HAL_I2C_GET_FLAG(clock->i2c_bus, HAL_I2C_ERROR_AF) ? 0 : 1;

}

static uint8_t I2c_read(uint8_t *Data, uint8_t Len, ds1307_t *clock) { //address removed

	HAL_StatusTypeDef ok = HAL_I2C_Master_Receive(clock->i2c_bus, dev_SLA << 1,
			Data, Len, 100);
	return (ok == HAL_OK) ? 1 : 0;
	//return __HAL_I2C_GET_FLAG(clock->i2c_bus, HAL_I2C_ERROR_AF) ? 0 : 1; // if ack fail it = true = return 0

}
static uint8_t BCD_to_dec(uint8_t num) {

	return (num >> 4) * 10 + (0xf & num);

}
static uint8_t dec_to_BCD(uint8_t num) {
	uint8_t div = num / 10;
	uint8_t rem = num % 10;

	return div << 4 | rem;
}

ds1307_stat_t DS1307_INIT(ds1307_t *clock, I2C_HandleTypeDef *i2c_bus) {
	uint8_t stat = 1;
	clock->i2c_bus = i2c_bus;

	//enable oscillator

	clock->Buffer[0] = 0x00;
	stat &= I2c_write(clock->Buffer, 1, clock);
	stat &= I2c_read(clock->Buffer, 1, clock);

	if ((clock->Buffer[0]) & (1 << 7) == 0) {	// 1 1010101
												// 1 0000000
												// 1

	} else {
		clock->Buffer[0] = 0x00;  //reg base address
		clock->Buffer[1] = 0;   //clock hold bit
		stat &= I2c_write(clock->Buffer, 2, clock);
	}

	if (stat == 1) {
		return DS1307_OK;
	} else {
		return DS1307_NOK;
	}

}
ds1307_stat_t DS1307_Set(ds1307_t *clock) {

	clock->Buffer[0] = start_address;
	clock->Buffer[1] = dec_to_BCD(clock->sec);
	clock->Buffer[2] = dec_to_BCD(clock->min);
	if (clock->format == 1) {
		clock->Buffer[3] = dec_to_BCD(clock->hour) | (clock->format << 6)
				| (clock->PM_AM << 5);
	} else {
		clock->Buffer[3] = dec_to_BCD(clock->hour) | (clock->format << 6);
	}
	//clock->Buffer[3] = dec_to_BCD(clock->hour) & 0x1f | (1 << 7); //5bits only
	clock->Buffer[4] = dec_to_BCD(clock->day) & 0x7;
	clock->Buffer[5] = dec_to_BCD(clock->date) & 0x3f;
	clock->Buffer[6] = dec_to_BCD(clock->month) & 0x1f;
	clock->Buffer[7] = dec_to_BCD(clock->year - 2000);

	if (I2c_write(clock->Buffer, 8, clock) == 1) {
		return DS1307_OK;
	} else {
		return DS1307_NOK;
	}
}
ds1307_stat_t DS1307_Read(ds1307_t *clock) {
	uint8_t stat = 1;
	clock->Buffer[0] = start_address;
	if (I2c_write(clock->Buffer, 1, clock) == 1) {

		if (I2c_read(clock->Buffer, 7, clock) == 1) {
			clock->sec = BCD_to_dec(clock->Buffer[0] & (0x7f));
			clock->min = BCD_to_dec(clock->Buffer[1]);
			clock->format = (clock->Buffer[2] & 0b01000000) >> 6;
			if (clock->format == 1) {  //12 h form
				clock->hour = BCD_to_dec(clock->Buffer[2] & 0b00011111);
				clock->PM_AM = (clock->Buffer[2] & 0b00100000) >> 5;
			} else {
				clock->hour = BCD_to_dec(clock->Buffer[2] & 0b00111111);
				if (clock->hour > 11) {
					clock->PM_AM = 1;
				} else {
					clock->PM_AM = 0;
				}
			}
			clock->day = BCD_to_dec(clock->Buffer[3] & 0x7);
			clock->date = BCD_to_dec(clock->Buffer[4] & 0x3f);
			clock->month = BCD_to_dec(clock->Buffer[5] & 0x1f);
			clock->year = BCD_to_dec(clock->Buffer[6]) + 2000;
			return DS1307_OK;
		} else {
			return DS1307_NOK;
		}

	} else {
		return DS1307_NOK;
	}

}

