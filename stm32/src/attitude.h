#ifndef __ATTITUDE_H
#define __ATTITUDE_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "stm32f10x.h"
#include "value_struct.h"
#include "math.h"
/*
 * kp,kiΪ���Ƽ��ٶȼ����������ǻ�����̬���ٶ�
 * halfT ��̬����ʱ���һ�룬��ʱ�Ľ����ٶ�Ϊ500Hz
*/
#define kp		1.5f
#define ki		0.001f
#define halfT	0.001
#define Gyro_G 	0.0610351f	

#define FILTER_NUM 	10

void data_filter(MPUData *data_in, MPUData *data_out);
void IMUupdate(MPUData *mpu_data, Angle *angle);

#ifdef __cplusplus
}
#endif

#endif /* __ATTITUDE_H */

