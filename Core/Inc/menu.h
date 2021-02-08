/*
 * menu.h
 *
 *  Created on: Feb 2, 2021
 *      Author: niemc
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_

typedef struct menu_struct menu_t;

struct menu_struct
{
	const char *name;
	menu_t *next;
	menu_t *previous;
	menu_t *child;
	menu_t *parent;
	const char *(*menu_f)(void);

};

menu_t menu_calendar;
menu_t menu_date;
menu_t menu_time;
menu_t menu_position;
menu_t menu_latitude;
menu_t menu_longitude;
menu_t menu_speed;

menu_t *current_menu;

void menu_sw_next(void);
void menu_sw_previous(void);
void menu_sw_child(void);
void menu_sw_parent(void);

const char *display_time(void);
const char *display_date(void);
const char *display_latitude(void);
const char *display_longitude(void);
const char *display_speed(void);

#endif /* INC_MENU_H_ */
