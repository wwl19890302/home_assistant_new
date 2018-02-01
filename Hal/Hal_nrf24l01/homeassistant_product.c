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
#include "hal_key.h"
#include "homeassistant_product.h"
#include "common.h"
#include "hal_led.h"
#include "hal_relay.h"
#include "Hal_nrf24l01.h"

static uint32_t HA_timerMsCount;
uint8_t HA_aRxBuffer;


/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void HA_Handle(void)
{
 /*
    currentDataPoint.valuedoor_onoff = ;//Add Sensor Data Collection
    currentDataPoint.valuewindow1_onoff = ;//Add Sensor Data Collection
    currentDataPoint.valuewindow2_onoff = ;//Add Sensor Data Collection
    currentDataPoint.valuewindow3_onoff = ;//Add Sensor Data Collection
    currentDataPoint.valuewindow4_onoff = ;//Add Sensor Data Collection

    */
    
}


void HA_read_status(void)
{
    uint8_t i;
    ha_datapoint_t.cmd = READ_DEV_STATUS;
    for(i = 0;i<SUB_MAX;i++)
    {
        ha_datapoint_t.sub_num = i+1;
        NRF24L01_tx_cmd(ha_datapoint_t);
    }
}


