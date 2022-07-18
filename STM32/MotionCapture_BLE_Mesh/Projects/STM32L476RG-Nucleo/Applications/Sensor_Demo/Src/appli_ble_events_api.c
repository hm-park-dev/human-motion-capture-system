/**
******************************************************************************
* @file    appli_ble_events_api.c
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Bluetooth APIs events callback
******************************************************************************
* @attention
*
* Copyright (c) 2021 STMicroelectronics.
* All rights reserved.
*
* This software is licensed under terms that can be found in the LICENSE file
* in the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "bluenrg_mesh.h"
#include <stdio.h>

/** @addtogroup ST_BLE_Mesh
*  @{
*/

/** @addtogroup Application
*  @{
*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

#define BLE_MESH_MODE             0 
#define BLE_LEGACY_GATT_MODE      1

/* Private variables ---------------------------------------------------------*/
MOBLEUINT8 BLE_Mode=0;

/**
 * @brief This event is generated to the application by the GATT server when a
 *        client modifies any attribute on the server.
*/
void aci_gatt_attribute_modified_event(uint16_t  Connection_Handle,
                                       uint16_t  Attr_Handle,
                                       uint16_t  Offset,
                                       uint16_t Attr_Data_Length,
                                       uint8_t  Attr_Data[])
{
  if(BLE_Mode == BLE_MESH_MODE)
  {
    mesh_aci_gatt_attribute_modified_event(Connection_Handle, Attr_Handle,
                                  Offset, Attr_Data_Length, Attr_Data);
  }
  else
  { 
    /* User need to add the Legacy GATT API as per the requirement*/
  }

}


/**
 * @brief Each time BLE FW stack raises the error code @ref
 *        BLE_STATUS_INSUFFICIENT_RESOURCES, aci_gatt_tx_pool_available_event()
 *        is generated as soon as the available buffer size  is greater than
 *        maximum ATT MTU.
*/
void aci_gatt_tx_pool_available_event(uint16_t Connection_Handle,
                                      uint16_t Available_Buffers)
{
  
  if(BLE_Mode == BLE_MESH_MODE)
  {
    mesh_aci_gatt_tx_pool_available_event(Connection_Handle,
                                      Available_Buffers);
  }
  else
  { 
    /* User need to add the Legacy GATT API as per the requirement*/
  }  
  
}

/**
 * @brief This event is generated when the device completes a radio activity and
 *        provide information when a new radio activity will be performed.
*/
void aci_hal_end_of_radio_activity_event(uint8_t Last_State,
                                         uint8_t Next_State,
                                         uint32_t Next_State_SysTime)
{
	 printf(" test event  aci_hal_end_of_radio_activity_event \r\n");
  
  if(BLE_Mode == BLE_MESH_MODE)
  {
    mesh_aci_hal_end_of_radio_activity_event(Last_State, Next_State,
                                                Next_State_SysTime);
     printf("mesh_aci_hal_end_of_radio_activity_event \r\n");
  }
  else
  { 
    /* User need to add the Legacy GATT API as per the requirement*/
  }  
  
}  


/**
 * @brief This event is used to indicate that the
 *        Controller process to update the connection has completed. 
*/
void hci_le_connection_update_complete_event(uint8_t  Status,  
                                             uint16_t  Connection_Handle,  
                                             uint16_t  Conn_Interval,  
                                             uint16_t  Conn_Latency,  
                                             uint16_t  Supervision_Timeout  
                                             )
{
  printf(" test event 0 \r\n");
  if(BLE_Mode == BLE_MESH_MODE)
  {
    mesh_hci_le_connection_update_complete_event (Status, Connection_Handle,  
                                                  Conn_Interval, Conn_Latency,  
                                                  Supervision_Timeout);
    printf("mesh_hci_le_connection_update_complete_event \r\n");
  }
  else
  { 
		printf("no connection update event \r\n");
    /* User need to add the Legacy GATT API as per the requirement*/
  }    
  
}    

/**
 * @brief This event indicates to both of the Hosts
 *        forming the connection that a new connection has been created.
*/
void hci_le_connection_complete_event  (  uint8_t  Status,
                                          uint16_t  Connection_Handle,
                                          uint8_t  Role,
                                          uint8_t  Peer_Address_Type,
                                          uint8_t  Peer_Address[6],
                                          uint16_t  Conn_Interval,
                                          uint16_t  Conn_Latency,
                                          uint16_t  Supervision_Timeout,
                                          uint8_t  Master_Clock_Accuracy)
{
	printf(" test event 1 \r\n");
  
  if(BLE_Mode == BLE_MESH_MODE)
  {
     mesh_hci_le_connection_complete_event(Status, Connection_Handle,
                                          Role, Peer_Address_Type,
                                          Peer_Address, Conn_Interval,
                                          Conn_Latency, Supervision_Timeout,
                                          Master_Clock_Accuracy);
     
        printf("mesh_hci_le_connection_complete_event \r\n");
  }
  else
  { 
		printf("no connection_complete_event  event \r\n");
    /* User need to add the Legacy GATT API as per the requirement*/
  }    
  
}   

/**
 * @brief This event indicates that a Bluetooth device or
 *        multiple Bluetooth devices have responded to an active scan or
 *        received some information during a passive scan. 
*/
void hci_le_advertising_report_event(uint8_t Num_Reports,
                                     Advertising_Report_t Advertising_Report[])
{
  printf(" test event 2 \r\n");
  if(BLE_Mode == BLE_MESH_MODE)
  {
    mesh_hci_le_advertising_report_event(Num_Reports, Advertising_Report);
    printf("mesh_hci_le_advertising_report_event \r\n");
  }
  else
  { 
		printf("no advertising_report_event  event \r\n");
    /* User need to add the Legacy GATT API as per the requirement*/
  }    
    
}
                                          
/**
 * @brief The Disconnection Complete event occurs when a connection is
 *        terminated. 
*/                                     
void hci_disconnection_complete_event(uint8_t Status,
                                          uint16_t Connection_Handle,
                                          uint8_t Reason)
{
  printf(" test event 3 \r\n");
  if(BLE_Mode == BLE_MESH_MODE)
  {
    mesh_hci_disconnection_complete_event(Status, Connection_Handle, Reason);
    printf("mesh_hci_disconnection_complete_event \r\n");
  }
  else
  { 
    /* User need to add the Legacy GATT API as per the requirement*/
  }    
    
}


