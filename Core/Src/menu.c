/*
 * menu.c
 *
 *  Created on: Feb 2, 2021
 *      Author: niemc
 */


#include "menu.h"
#include "gps.h"
#include <stddef.h>

menu_t menu_calendar = { "Calendar", &menu_position, &menu_speed, &menu_date, NULL, NULL };
	menu_t menu_date = { "Date", &menu_time, &menu_time, NULL, &menu_calendar, display_date };
	menu_t menu_time = { "Time", &menu_date, &menu_date, NULL, &menu_calendar, display_time };
menu_t menu_position = { "Position", &menu_speed, &menu_calendar, &menu_longitude, NULL, NULL };
	menu_t menu_latitude = { "Latitude", &menu_longitude, &menu_longitude, NULL, &menu_position, display_latitude };
	menu_t menu_longitude = { "Longitude", &menu_latitude, &menu_latitude, NULL, &menu_position, display_longitude };
menu_t menu_speed = { "Speed", &menu_calendar, &menu_position, NULL, NULL, display_speed };

menu_t *current_menu = &menu_calendar;

void menu_sw_next(void)
{
	current_menu = current_menu->next;
}

void menu_sw_previous(void)
{
	current_menu = current_menu->previous;
}

void menu_sw_child(void)
{
	if (current_menu->child)
	current_menu = current_menu->child;
}

void menu_sw_parent(void)
{
	if (current_menu->parent)
		current_menu = current_menu->parent;
}

const char *display_time(void)
{
	static char data[10];
	sprintf((char *)data, "%i:%i:%i", GPS_data.UTC_Hour, GPS_data.UTC_Min, GPS_data.UTC_Sec);
	return &data[0];
}

const char *display_date(void)
{
	static char data[10];
	sprintf((char *)data, "%i.%i.%i", GPS_data.UTC_Year, GPS_data.UTC_Month, GPS_data.UTC_Day);
	return &data[0];
}

const char *display_latitude(void)
{
	static char data[15];
	sprintf((char *)data, "%i %f %c", GPS_data.latitude_min, GPS_data.latitude_deg, GPS_data.ns);
	return &data[0];
}

const char *display_longitude(void)
{
	static char data[15];
	sprintf((char *)data, "%i'%f\"%c", GPS_data.longitude_min, GPS_data.longitude_deg, GPS_data.ew);
	return &data[0];
}

const char *display_speed(void)
{
	static char data[10];
	sprintf((char *)data, "%f", GPS_data.speed);
	return &data[0];
}
