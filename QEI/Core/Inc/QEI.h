/*
 * QEI.h
 *
 *  Created on: Mar 31, 2024
 *      Author: acer
 */

#ifndef INC_QEI_H_
#define INC_QEI_H_

#include "main.h"
#include "math.h"

typedef struct
{
	uint32_t c[2];               // NOW Counter & PREVIOUS Counter
	float r[2];					 // NOW Radius/Second & PREVIOUS Radius/Second

	TIM_HandleTypeDef* htimx;    // QEI Pointer
	int32_t enc_period;          // Period QEI (Max)
	int32_t ppr;				 // Pulse/Revolution
	int32_t diff_counts;          // Pulse ที่นับได้

	float freq;				     // Frequency
	float pps;					 // Pulse/Second     (W)
	float rpm;					 // Revolution/Minute(W)
	float radps;                 // Radius/Second    (W)
	float pulses;                // Distance Pulse
	float revs;                   // Distance Revolution
	float rads;                   // Distance Radius
	float radpss;                // Acceleration Radius
} QEI;

enum
{
	NOW,PREV
};


void QEI_init(QEI* qei, TIM_HandleTypeDef* htimx, int32_t ppr, float freq);
void QEI_get_diff_count(QEI* qei);
void QEI_compute_data(QEI* qei);
void QEI_reset(QEI* qei);



#endif /* INC_QEI_H_ */
