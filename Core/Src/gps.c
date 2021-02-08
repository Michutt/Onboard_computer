/*
 * gps.c
 *
 *  Created on: Jan 22, 2021
 *      Author: niemc
 */

#include "GPS.h"
#include "usart.h"
#include <string.h>

uint8_t ctr = 0;
uint8_t idx = 0;
uint8_t rx_data;
uint8_t buff[512];
char *p = buff;


void GPS_Init(void)
{
	HAL_UART_Receive_IT(GPS_USART, &rx_data, 1);
}


void GPS_CallBack(void)
{
	if (rx_data != '\n')
		buff[idx++] = rx_data;
	else
	{
		delete_commas(buff);
		parse(p);
		idx = 0;
		memset(buff, 0, sizeof(buff));
	}
//	HAL_UART_Transmit(DEBUG_USART, &rx_data, 1, 100); // print all frames
	HAL_UART_Receive_IT(GPS_USART, &rx_data, 1);
}


void delete_commas(uint8_t *buff)
{
    while ((buff = strchr(buff, ','))) {
        *buff++ = 0;
    }
}


void parse(char *p)
{
    uint32_t UTC_Time;
    uint32_t UTC_Date;
    double latitude; // longitude as well
    char *ptr;

    if (!strcmp(p, "$GPRMC"))
    {

        //frame name
        p += strlen(p) + 1;

        //time
        UTC_Time = atoi(p);
        GPS_data.UTC_Hour = UTC_Time / 10000;
        GPS_data.UTC_Min = UTC_Time % 10000 / 100;
        GPS_data.UTC_Sec = UTC_Time % 100;
        p += strlen(p) + 1;

        //receiver warning
        p += strlen(p) + 1;

        //latitude
        latitude = strtod(p, &ptr);
        GPS_data.latitude_min = latitude / 100;
        GPS_data.latitude_deg = latitude - GPS_data.latitude_min * 100;
        p += strlen(p) + 1;

        //latitude direction
        GPS_data.ns = *p;
        p += strlen(p) + 1;

        //longitude
        latitude = strtod(p, &ptr);
        GPS_data.longitude_min = latitude / 100;
        GPS_data.longitude_deg = latitude - GPS_data.longitude_min * 100;
        p += strlen(p) + 1;

        //longitude direction
        GPS_data.ew = *p;
        p += strlen(p) + 1;

        //speed in knots
        GPS_data.speed = atof(p) * 1.852; //conversion to km per hour
        if (GPS_data.speed == (float)1.852)
        {
        	GPS_data.speed = (float)0;
        }
        p += strlen(p) + 1;

        //course
        p += strlen(p) + 1;

        //date
        UTC_Date = 100000 + atoi(p);
        GPS_data.UTC_Day = (UTC_Date / 10000) - 10;
		GPS_data.UTC_Month = UTC_Date % 10000 / 100;
		GPS_data.UTC_Year = 2000 + (UTC_Date % 100);

    }
}
