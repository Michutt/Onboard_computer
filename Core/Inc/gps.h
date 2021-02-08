/*
 * gps.h
 *
 *  Created on: Jan 22, 2021
 *      Author: niemc
 */

#ifndef INC_GPS_H_
#define INC_GPS_H_

#define	DEBUG_USART &huart2
#define	GPS_USART &huart3

#include <stdint.h>


typedef struct
{
	uint8_t UTC_Hour;
	uint8_t UTC_Min;
	uint8_t UTC_Sec;

	uint8_t latitude_min;
	float latitude_deg;
	char ns;

	uint8_t longitude_min;
	float longitude_deg;
	char ew;

	float speed;

	uint16_t UTC_Year;
	uint8_t UTC_Month;
	uint8_t UTC_Day;

}GPS_data_frame;


GPS_data_frame GPS_data;


void GPS_Init(void);
void GPS_CallBack(void);
void delete_commas(uint8_t *buff);
void parse(char *p);

#endif /* INC_GPS_H_ */
