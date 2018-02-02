/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits control protocol processing, and platform-related       hardware initialization 
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
* 
* @note         ???.????????
*               Gizwits Smart Cloud  for Smart Products
*               ??|???|??|??|??|??|??|??
*               www.gizwits.com
*
***********************************************************/

#include <stdio.h>
#include <string.h>
#include "Hal_key/hal_key.h"
#include "homeassistant_product.h"
#include "common.h"
#include "Hal_led/hal_led.h"
#include "Hal_relay/hal_relay.h"
#include "Hal_nrf24l01.h"


ha_datapoint_t ha_datapoint_tx,ha_datapoint_rx;
control_flag_t control_flag;
sub1_data_t sub1_data;
sub2_data_t sub2_data;
sub3_data_t sub3_data;
sub4_data_t sub4_data;


/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void HA_Handle(void)
{
 /*
      currentDataPoint.valuelight1 = ;
      currentDataPoint.valuelight2 = ;
      currentDataPoint.valuelight3 = ;
      currentDataPoint.valuelight4 = ;
      currentDataPoint.valuelight5 = ;
      currentDataPoint.valuelight6 = ;
      currentDataPoint.valuelight7 = ;
      currentDataPoint.valuelight8 = ;
      currentDataPoint.valuelight9 = ;
      currentDataPoint.valuewater_heater = ;
      currentDataPoint.valueTV = ;
      currentDataPoint.valuecurtain = ;
      currentDataPoint.valueair_condition_onoff = ;
      currentDataPoint.valuemusic_onoff = ;
      currentDataPoint.valuemusic_prevnext = ;
      currentDataPoint.valuemusic_voice_updown = ;
      currentDataPoint.valueswitch1_onoff = ;
      currentDataPoint.valueswitch2_onoff = ;
      currentDataPoint.valueswitch3_onoff = ;
      currentDataPoint.valueair_condition_mode = ;
      currentDataPoint.valueair_condition_temperature = ;
      currentDataPoint.valuedoor_onoff = ;
      currentDataPoint.valuewindow1_onoff = ;
      currentDataPoint.valuewindow2_onoff = ;
      currentDataPoint.valuewindow3_onoff = ;
      currentDataPoint.valuewindow4_onoff = ;

    */
    
}


void HA_read_status(void)
{
    uint8_t i;
    uint32_t delay_time;

    if(READ_DEV_STATUS == ha_datapoint_tx.cmd)
    {
        control_flag.sub_flag[0].sub_control_flag = 1;
        control_flag.sub_flag[1].sub_control_flag = 1;
        control_flag.sub_flag[2].sub_control_flag = 1;
        control_flag.sub_flag[3].sub_control_flag =1;
    }
    for(i = 0;i<SUB_MAX;i++)
    {
        if(1 == control_flag.sub_flag[i].sub_control_flag)
        {
            delay_time = gizGetTimerCount();
            ha_datapoint_tx.sub_num = i;
            NRF24L01_tx_cmd((uint8_t *)&ha_datapoint_tx);
            while(((gizGetTimerCount() - delay_time) < 200) && (NRF24L01_RxPacket((uint8_t *)&ha_datapoint_rx) == 0))
            {
                HA_subset_status_2_currentdatapoint();
            }

            control_flag.sub_flag[i].tx_times++;
            if(3 == control_flag.sub_flag[i].tx_times)
            {
                control_flag.sub_flag[i].tx_times = 0;
                control_flag.sub_flag[i].sub_control_flag = 0;
            }
            memset((uint8_t *)&ha_datapoint_tx,0x0,sizeof(ha_datapoint_t));
        }
    }
}

#include "gizwits_protocol.h"
/* copy subset data to currentdatapoint */
void HA_subset_status_2_currentdatapoint(void)
{
    sub1_data_t* sub1_data_rx;
    sub2_data_t* sub2_data_rx;
    sub3_data_t* sub3_data_rx;
    sub4_data_t* sub4_data_rx;
    extern dataPoint_t currentDataPoint;

    switch(ha_datapoint_rx.sub_num){
    case SUB1:
        sub1_data_rx = (sub1_data_t*)ha_datapoint_rx.data;
        currentDataPoint.valuelight2 = sub1_data_rx->valuelight2;
        currentDataPoint.valuelight3 = sub1_data_rx->valuelight3;
        break;
    case SUB2:
        sub2_data_rx = (sub2_data_t *)ha_datapoint_rx.data;
        currentDataPoint.valuelight4 = sub2_data_rx->valuelight4;
        currentDataPoint.valuelight5 = sub2_data_rx->valuelight5;
        currentDataPoint.valuelight6 = sub2_data_rx->valuelight6;
        break;
    case SUB3:
        sub3_data_rx = (sub3_data_t *)ha_datapoint_rx.data;
        currentDataPoint.valuelight7 = sub3_data_rx->valuelight7;
        currentDataPoint.valuelight8 = sub3_data_rx->valuelight8;
        currentDataPoint.valuelight9 = sub3_data_rx->valuelight9;
        break;
    case SUB4:
        sub4_data_rx = (sub4_data_t *)ha_datapoint_rx.data;
        currentDataPoint.valueair_condition_onoff = sub4_data_rx->valueair_condition_onoff;
        currentDataPoint.valueair_condition_mode = sub4_data_rx->valueair_condition_mode;
        currentDataPoint.valueair_condition_temperature = sub4_data_rx->valueair_condition_temperature;
        break;
    default:
        break;
    }

    control_flag.sub_flag[ha_datapoint_rx.sub_num].tx_times = 0;
    control_flag.sub_flag[ha_datapoint_rx.sub_num].sub_control_flag = 0;
}

