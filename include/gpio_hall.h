#ifndef MY_HALL_SENSOR_H
#define MY_HALL_SENSOR_H

void my_hall_init();
bool my_hall_getData();
void my_hall_interrupt_init();
void my_hall_isr();

#endif