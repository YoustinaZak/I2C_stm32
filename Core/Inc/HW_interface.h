/*
 * HW_interface.h
 *
 *  Created on: Sep 1, 2024
 *      Author: hp
 */

#ifndef INC_HW_INTERFACE_H_
#define INC_HW_INTERFACE_H_

#include "../../Drivers/DS1307/ds1307.h"

//static uint8_t I2c_read(uint8_t *Data, uint8_t Len);
uint8_t I2c_write(uint8_t dev_SLA,uint8_t *Data, uint8_t Len);
uint8_t I2c_read(uint8_t dev_SLA,uint8_t *Data, uint8_t Len) ;
#endif /* INC_HW_INTERFACE_H_ */
