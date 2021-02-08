/*
 * menu.c
 *
 *  Created on: Feb 2, 2021
 *      Author: niemc
 */


#include "menu.h"
#include "gps.h"
#include <stddef.h>
#include "usart.h"

menu_t menu_calendar = { "Calendar", &menu_position, &menu_speed, &menu_date, NULL, NULL };
	menu_t menu_date = { "Date", &menu_time, &menu_time, NULL, &menu_calendar, display_time };
	menu_t menu_time = { "Time", &menu_date, &menu_date, NULL, &menu_calendar, NULL };
menu_t menu_position = { "Position", &menu_speed, &menu_calendar, &menu_longitude, NULL, NULL };
	menu_t menu_latitude = { "Latitude", &menu_longitude, &menu_longitude, NULL, &menu_position, NULL };
	menu_t menu_longitude = { "Longitude", &menu_latitude, &menu_latitude, NULL, &menu_position, NULL };
menu_t menu_speed = { "Speed", &menu_calendar, &menu_position, NULL, NULL, NULL };

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
