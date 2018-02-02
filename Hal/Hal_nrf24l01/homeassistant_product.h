/**
************************************************************
* @file         gizwits_product.h
* @brief        Corresponding gizwits_product.c header file (including product hardware and software version definition)
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
#ifndef _HOMEASSISTANT_PRODUCT_H
#define _HOMEASSISTANT_PRODUCT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stm32f1xx.h>
#include <stdbool.h>
// #include "homeassistant_protocol.h"

/* which subset controled will change statue */
#define SUB_MAX 4

typedef struct {
   bool valuelight2;
   bool valuelight3;
} sub1_data_t;

typedef struct {
   bool valuelight4;
   bool valuelight5;
   bool valuelight6;
} sub2_data_t;

typedef struct {
   bool valuelight7;
   bool valuelight8;
   bool valuelight9;
} sub3_data_t;

typedef struct {
   bool valueair_condition_onoff;
   uint32_t valueair_condition_mode;
   uint32_t valueair_condition_temperature;
} sub4_data_t;

/** command mode **/
typedef enum
{
    READ_DEV_STATUS              = 0X01,
    HA2S_TRANSPORT_CONTROL_DATA  = 0X02,
    S2HA_TRANSPORT_STATUS_DATA   = 0X03,
}command_mode_t;

typedef enum
{
    SUB1 = 0X00,
    SUB2 = 0X01,
    SUB3 = 0X02,
    SUB4 = 0X03,
} sub_num_t;

typedef struct
{
    uint8_t sub_control_flag;
    uint8_t tx_times;
} sub_flag_t;

typedef struct {
    sub_flag_t sub_flag[4];
} control_flag_t;

typedef struct {
    uint32_t id;
    command_mode_t cmd;
    sub_num_t sub_num;
    uint8_t data[20];
} ha_datapoint_t;

extern ha_datapoint_t ha_datapoint_tx,ha_datapoint_rx;
extern control_flag_t control_flag;
extern sub1_data_t sub1_data;
extern sub2_data_t sub2_data;
extern sub3_data_t sub3_data;
extern sub4_data_t sub4_data;

extern uint32_t gizGetTimerCount(void);

void HA_read_status(void);
void HA_subset_status_2_currentdatapoint(void);

#ifdef __cplusplus
}
#endif

#endif
