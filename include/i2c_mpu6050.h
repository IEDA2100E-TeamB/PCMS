#ifndef MY_MPU6050_H
#define MY_MPU6050_H

bool mpu6050_setup();
// sensors_vec_t mpu6050_getAcceleration();
float mpu6050_getAcceleration_x();
float mpu6050_getAcceleration_y();
float mpu6050_getAcceleration_z();
// sensors_vec_t mpu6050_getGyro();
float mpu6050_getGyro_x();
float mpu6050_getGyro_y();
float mpu6050_getGyro_z();
float mpu6050_getTemperature();
bool mpu6050_getOrientation();
void mpu6050_print();

#endif
