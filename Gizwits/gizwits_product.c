/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits control protocol processing, and platform-related       hardware initialization 
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/

#include <stdio.h>
#include <string.h>
#include "Hal_key/hal_key.h"
#include "gizwits_product.h"
#include "common.h"
#include "Hal_led/hal_led.h"
#include "Hal_relay/hal_relay.h"
#include "Hal_nrf24l01/Hal_nrf24l01.h"

static uint32_t timerMsCount;
uint8_t aRxBuffer;

/** User area the current device state structure*/
dataPoint_t currentDataPoint;
extern keysTypedef_t keys;

extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

/**@} */
/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *gizdata, uint32_t len)
{
  uint8_t i = 0;
	extern uint8_t tx_tmp_buf[32];
  dataPoint_t *dataPointPtr = (dataPoint_t *)gizdata;
  moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)gizdata;
  protocolTime_t *ptime = (protocolTime_t *)gizdata;
  
#if MODULE_TYPE
  gprsInfo_t *gprsInfoData = (gprsInfo_t *)gizdata;
#else
  moduleInfo_t *ptModuleInfo = (moduleInfo_t *)gizdata;
#endif

  if((NULL == info) || (NULL == gizdata))
  {
    return -1;
  }

  for(i=0; i<info->num; i++)
  {
    switch(info->event[i])
    {
      case EVENT_light1:
        currentDataPoint.valuelight1 = dataPointPtr->valuelight1;
        GIZWITS_LOG("Evt: EVENT_light1 %d \n", currentDataPoint.valuelight1);
        if(0x01 == currentDataPoint.valuelight1)
        {
          //user handle
			relay_on(0);//ledon(1);
        }
        else
        {
          //user handle    
			relay_off(0);//ledoff(1);
        }
        break;
      case EVENT_light2:
//        currentDataPoint.valuelight2 = dataPointPtr->valuelight2;
        GIZWITS_LOG("Evt: EVENT_light2 %d \n", currentDataPoint.valuelight2);
        if(0x01 == dataPointPtr->valuelight2)
        {
          //user handle
			tx_tmp_buf[5] = 1;
        }
        else
        {
          //user handle   
			tx_tmp_buf[5] = 0;			
        }
		NRF24L01_tx_cmd(tx_tmp_buf);

		GIZWITS_LOG("Evt: EVENT_light2 \n");
        break;
      case EVENT_light3:
//        currentDataPoint.valuelight3 = dataPointPtr->valuelight3;
        GIZWITS_LOG("Evt: EVENT_light3 %d \n", currentDataPoint.valuelight3);
        if(0x01 == dataPointPtr->valuelight3)
        {
          //user handle
			tx_tmp_buf[6] = 1;
        }
        else
        {
          //user handle    
			tx_tmp_buf[6] = 0;
        }
		NRF24L01_tx_cmd(tx_tmp_buf);
        break;
      case EVENT_light4:
        currentDataPoint.valuelight4 = dataPointPtr->valuelight4;
        GIZWITS_LOG("Evt: EVENT_light4 %d \n", currentDataPoint.valuelight4);
        if(0x01 == currentDataPoint.valuelight4)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_light5:
        currentDataPoint.valuelight5 = dataPointPtr->valuelight5;
        GIZWITS_LOG("Evt: EVENT_light5 %d \n", currentDataPoint.valuelight5);
        if(0x01 == currentDataPoint.valuelight5)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_light6:
        currentDataPoint.valuelight6 = dataPointPtr->valuelight6;
        GIZWITS_LOG("Evt: EVENT_light6 %d \n", currentDataPoint.valuelight6);
        if(0x01 == currentDataPoint.valuelight6)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_light7:
        currentDataPoint.valuelight7 = dataPointPtr->valuelight7;
        GIZWITS_LOG("Evt: EVENT_light7 %d \n", currentDataPoint.valuelight7);
        if(0x01 == currentDataPoint.valuelight7)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_light8:
        currentDataPoint.valuelight8 = dataPointPtr->valuelight8;
        GIZWITS_LOG("Evt: EVENT_light8 %d \n", currentDataPoint.valuelight8);
        if(0x01 == currentDataPoint.valuelight8)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_light9:
        currentDataPoint.valuelight9 = dataPointPtr->valuelight9;
        GIZWITS_LOG("Evt: EVENT_light9 %d \n", currentDataPoint.valuelight9);
        if(0x01 == currentDataPoint.valuelight9)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_water_heater:
        currentDataPoint.valuewater_heater = dataPointPtr->valuewater_heater;
        GIZWITS_LOG("Evt: EVENT_water_heater %d \n", currentDataPoint.valuewater_heater);
        if(0x01 == currentDataPoint.valuewater_heater)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_TV:
        currentDataPoint.valueTV = dataPointPtr->valueTV;
        GIZWITS_LOG("Evt: EVENT_TV %d \n", currentDataPoint.valueTV);
        if(0x01 == currentDataPoint.valueTV)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_curtain:
        currentDataPoint.valuecurtain = dataPointPtr->valuecurtain;
        GIZWITS_LOG("Evt: EVENT_curtain %d \n", currentDataPoint.valuecurtain);
        if(0x01 == currentDataPoint.valuecurtain)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_air_condition_onoff:
        currentDataPoint.valueair_condition_onoff = dataPointPtr->valueair_condition_onoff;
        GIZWITS_LOG("Evt: EVENT_air_condition_onoff %d \n", currentDataPoint.valueair_condition_onoff);
        if(0x01 == currentDataPoint.valueair_condition_onoff)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_music_onoff:
        currentDataPoint.valuemusic_onoff = dataPointPtr->valuemusic_onoff;
        GIZWITS_LOG("Evt: EVENT_music_onoff %d \n", currentDataPoint.valuemusic_onoff);
        if(0x01 == currentDataPoint.valuemusic_onoff)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_music_prevnext:
        currentDataPoint.valuemusic_prevnext = dataPointPtr->valuemusic_prevnext;
        GIZWITS_LOG("Evt: EVENT_music_prevnext %d \n", currentDataPoint.valuemusic_prevnext);
        if(0x01 == currentDataPoint.valuemusic_prevnext)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_music_voice_updown:
        currentDataPoint.valuemusic_voice_updown = dataPointPtr->valuemusic_voice_updown;
        GIZWITS_LOG("Evt: EVENT_music_voice_updown %d \n", currentDataPoint.valuemusic_voice_updown);
        if(0x01 == currentDataPoint.valuemusic_voice_updown)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_switch1_onoff:
        currentDataPoint.valueswitch1_onoff = dataPointPtr->valueswitch1_onoff;
        GIZWITS_LOG("Evt: EVENT_switch1_onoff %d \n", currentDataPoint.valueswitch1_onoff);
        if(0x01 == currentDataPoint.valueswitch1_onoff)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_switch2_onoff:
        currentDataPoint.valueswitch2_onoff = dataPointPtr->valueswitch2_onoff;
        GIZWITS_LOG("Evt: EVENT_switch2_onoff %d \n", currentDataPoint.valueswitch2_onoff);
        if(0x01 == currentDataPoint.valueswitch2_onoff)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_switch3_onoff:
        currentDataPoint.valueswitch3_onoff = dataPointPtr->valueswitch3_onoff;
        GIZWITS_LOG("Evt: EVENT_switch3_onoff %d \n", currentDataPoint.valueswitch3_onoff);
        if(0x01 == currentDataPoint.valueswitch3_onoff)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;

      case EVENT_air_condition_mode:
        currentDataPoint.valueair_condition_mode = dataPointPtr->valueair_condition_mode;
        GIZWITS_LOG("Evt: EVENT_air_condition_mode %d\n", currentDataPoint.valueair_condition_mode);
        switch(currentDataPoint.valueair_condition_mode)
        {
          case air_condition_mode_VALUE0:
            //user handle
            break;
          case air_condition_mode_VALUE1:
            //user handle
            break;
          default:
            break;
        }
        break;

      case EVENT_air_condition_temperature:
        currentDataPoint.valueair_condition_temperature = dataPointPtr->valueair_condition_temperature;
        GIZWITS_LOG("Evt:EVENT_air_condition_temperature %d\n",currentDataPoint.valueair_condition_temperature);
        //user handle
        break;


      case WIFI_SOFTAP:
        break;
      case WIFI_AIRLINK:
        break;
      case WIFI_STATION:
        break;
      case WIFI_CON_ROUTER:
 
        break;
      case WIFI_DISCON_ROUTER:
 
        break;
      case WIFI_CON_M2M:
 
        break;
      case WIFI_DISCON_M2M:
        break;
      case WIFI_RSSI:
        GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
        break;
      case TRANSPARENT_DATA:
        GIZWITS_LOG("TRANSPARENT_DATA \n");
        //user handle , Fetch data from [data] , size is [len]
        break;
      case WIFI_NTP:
        GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
        break;
      case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
      #if MODULE_TYPE
            GIZWITS_LOG("GPRS MODULE ...\n");
            //Format By gprsInfo_t
      #else
            GIZWITS_LOG("WIF MODULE ...\n");
            //Format By moduleInfo_t
            GIZWITS_LOG("moduleType : [%d] \n",ptModuleInfo->moduleType);
      #endif
    break;
      default:
        break;
    }
  }

  return 0;
}

/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void userHandle(void)
{
 /*
    currentDataPoint.valuedoor_onoff = ;//Add Sensor Data Collection
    currentDataPoint.valuewindow1_onoff = ;//Add Sensor Data Collection
    currentDataPoint.valuewindow2_onoff = ;//Add Sensor Data Collection
    currentDataPoint.valuewindow3_onoff = ;//Add Sensor Data Collection
    currentDataPoint.valuewindow4_onoff = ;//Add Sensor Data Collection

    */
    
}

/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    
    /** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 
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


/**
* @brief Millisecond timing maintenance function, milliseconds increment, overflow to zero

* @param none
* @return none
*/
void gizTimerMs(void)
{
    timerMsCount++;
}

/**
* @brief Read millisecond count

* @param none
* @return millisecond count
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}

/**
* @brief MCU reset function

* @param none
* @return none
*/
void mcuRestart(void)
{
    __set_FAULTMASK(1);
    HAL_NVIC_SystemReset();
}

/**@} */

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
 
  return ch;
}

/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim==&htim2)
	{
			keyHandle((keysTypedef_t *)&keys);
			gizTimerMs();
	}
}

/**
* @brief Timer TIM3 init function

* @param none
* @return none
*/
void timerInit(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
}

/**
  * @brief  This function handles USART IDLE interrupt.
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef*UartHandle)  
{  
    if(UartHandle->Instance == USART2)  
    {  
				gizPutData((uint8_t *)&aRxBuffer, 1);

        HAL_UART_Receive_IT(&huart2, (uint8_t *)&aRxBuffer, 1);//开启下一次接收中断  
    }  
}  

/**
* @brief USART init function

* Serial communication between WiFi modules and device MCU
* @param none
* @return none
*/
void uartInit(void)
{
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&aRxBuffer, 1);//开启下一次接收中断  
}

/**
* @brief Serial port write operation, send data to WiFi module
*
* @param buf      : buf address
* @param len      : buf length
*
* @return : Return effective data length;-1，return failure
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
		uint8_t crc[1] = {0x55};
    uint32_t i = 0;
	
    if(NULL == buf)
    {
        return -1;
    }

    for(i=0; i<len; i++)
    {
        HAL_UART_Transmit_IT(&huart2, (uint8_t *)&buf[i], 1);
				while (huart2.gState != HAL_UART_STATE_READY);//Loop until the end of transmission

        if(i >=2 && buf[i] == 0xFF)
        {
						HAL_UART_Transmit_IT(&huart2, (uint8_t *)&crc, 1);
						while (huart2.gState != HAL_UART_STATE_READY);//Loop until the end of transmission
        }
    }

#ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("MCU2WiFi[%4d:%4d]: ", gizGetTimerCount(), len);
    for(i=0; i<len; i++)
    {
        GIZWITS_LOG("%02x ", buf[i]);

        if(i >=2 && buf[i] == 0xFF)
        {
            GIZWITS_LOG("%02x ", 0x55);
        }
    }
    GIZWITS_LOG("\n");
#endif
		
		return len;
}  
