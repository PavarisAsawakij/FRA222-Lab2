/*
 * QEI.c
 *
 *  Created on: Apr 1, 2024
 *      Author: acer
 */


#include "QEI.h"


void QEI_init ( QEI* qei, TIM_HandleTypeDef* htimx, int32_t ppr, float freq )
{
	qei-> htimx = htimx;
	qei-> ppr = ppr;
	qei-> freq = freq;
	qei-> c[NOW] = 0;
	qei-> c[PREV] = 0;
	qei-> pps = 0;
	qei-> rpm = 0;
	qei-> radps = 0;
	qei->enc_period = 65536-(65536%ppr);
	qei-> pulses = 0;
	qei-> revs = 0;
	qei->rads = 0;
	HAL_TIM_Encoder_Start(htimx,TIM_CHANNEL_ALL);
}





void QEI_get_diff_count(QEI* qei)
{

	qei->c[NOW]=__HAL_TIM_GET_COUNTER(qei->htimx);         // Update Pulse

	int32_t diff_counts = qei->c[NOW] - qei->c[PREV];   // Unwrap

	if (diff_counts > qei->enc_period / 2)
	{
		diff_counts -= qei->enc_period;
	}
	if (diff_counts < -(qei->enc_period)/2)
	{
		diff_counts += qei->enc_period;
	}

	qei->diff_counts = diff_counts;
	qei->c[PREV] = qei->c[NOW];

}





void QEI_compute_data(QEI* qei)
{

	qei->pps = qei -> diff_counts/(1/(qei->freq));
	qei->rpm = qei -> pps * 60.0 / (float)(qei->ppr);
	qei->radps = qei -> pps * 2 * M_PI / (float)(qei->ppr);


	qei -> pulses +=  qei -> pps*(1/(qei->freq));
	qei -> revs   += (qei -> rpm / 60.0)*(1/(qei->freq));
	qei -> rads = qei -> radps*(1/(qei->freq));


    qei->r[NOW] = qei->radps;
    float diff_velocity = (qei->r[NOW] - qei->r[PREV]);
    qei->radpss = diff_velocity/(1/(qei->freq));
    qei->r[PREV] = qei->r[NOW];  // Store the previous count


}




void QEI_reset(QEI* qei)
{
	qei->pulses = 0;
	qei->revs = 0;
	qei->rads = 0;
}
