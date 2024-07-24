/*
 * ds1307.h
 *
 *  Created on: Jun 30, 2024
 *      Author: hp
 */

#ifndef DS1307_DS1307_H_
#define DS1307_DS1307_H_
#include <stdint.h>
#include "stm32f1xx_hal.h"

typedef struct {
	uint8_t Buffer[8];                                    //slave address + data
	uint8_t sec, min, hour;
	uint8_t day, date, month;
	uint16_t year;
	uint8_t CH;//clock hold
	uint8_t format:1;
	uint8_t PM_AM:1;

	I2C_HandleTypeDef *i2c_bus;
} ds1307_t;

typedef enum {
	 DS1307_NOK,
	 DS1307_OK
} ds1307_stat_t;

ds1307_stat_t DS1307_INIT(ds1307_t *clock, I2C_HandleTypeDef *i2c_bus);
ds1307_stat_t DS1307_Set(ds1307_t *clock);
ds1307_stat_t DS1307_Read(ds1307_t *clock);

#endif /* DS1307_DS1307_H_ */
