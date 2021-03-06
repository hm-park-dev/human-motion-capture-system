/**
******************************************************************************
* @file    common.h
* @author  BLE Mesh Team
* @version V1.14.000
* @date    19-11-2021
* @brief   Model middleware file
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of STMicroelectronics nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Initial BlueNRG-Mesh is built over Motorola?s Mesh over Bluetooth Low Energy 
* (MoBLE) technology. The present solution is developed and maintained for both 
* Mesh library and Applications solely by STMicroelectronics.
*
******************************************************************************
*/
#ifndef __COMMON_H
#define __COMMON_H

/* Includes ------------------------------------------------------------------*/
#include "types.h"
#include "bluenrg_mesh.h"
#include "mesh_cfg_usr.h"
#include "light_lc.h"

/* Exported macro ------------------------------------------------------------*/
/* Macros defined for the number of bytes saved, number of bytes dedicated 
   for ganeric model and light model */
#define APP_NVM_GENERIC_MODEL_SIZE                                          16U
#define APP_NVM_LIGHT_MODEL_SIZE                                            48U
#define APP_NVM_LIGHT_LC_MODEL_SIZE                                         80U
#define APP_NVM_MODELDATA_PER_ELEMENT_SIZE  (APP_NVM_GENERIC_MODEL_SIZE + \
                                             APP_NVM_LIGHT_MODEL_SIZE) 
#define APP_NVM_MODEL_SIZE   (APP_NVM_MODELDATA_PER_ELEMENT_SIZE * APPLICATION_NUMBER_OF_ELEMENTS +\
                              APP_NVM_LIGHT_LC_MODEL_SIZE)
                               
                                 

#define GENERIC_VALID_FLAG                                                 0xAA

#define TESTING_BYTE                                                        240

#define No_NVM_FLAG                                                        0XFE
#define GENERIC_ON_OFF_NVM_FLAG                                            0X01
#define GENERIC_LEVEL_NVM_FLAG                                             0X02
#define GENERIC_DEFAULT_TRANSITION_NVM_FLAG                                       0X03
#define LIGHT_LIGHTNESS_NVM_FLAG                                           0X04
#define LIGHT_CTL_NVM_FLAG                                                 0X05
#define LIGHT_HSL_NVM_FLAG                                                 0X06
#define LIGHT_LC_NVM_FLAG                                                  0X07

#define GENERIC_POWER_OFF_STATE                                            0X00
#define GENERIC_POWER_ON_STATE                                             0X01
#define GENERIC_POWER_RESTORE_STATE                                        0X02

#define FLAG_SET                                                              1
#define FLAG_RESET                                                            0
                                               
#define VALUE_UPDATE_SET                                                   0X01
#define VALUE_UPDATE_RESET                                                 0X00
                                               
#define CLK_FLAG_ENABLE                                                       1
#define CLK_FLAG_DISABLE                                                      0
                                               
#define PWM_ZERO_VALUE                                                        1
#define INTENSITY_LEVEL_ZERO                                               0X00
#define INTENSITY_LEVEL_FULL                                             31990U
                                               
#define MAX_TID_VALUE                                                      0XFF

#define STEP_HEX_VALUE_0                                                   0X00
#define STEP_HEX_VALUE_1                                                   0X01
#define STEP_HEX_VALUE_2                                                   0X02
#define STEP_HEX_VALUE_3                                                   0X03

#define STEP_RESOLUTION_100MS                                               100
#define STEP_RESOLUTION_1S                                                 1000
#define STEP_RESOLUTION_10S                                               10000
#define STEP_RESOLUTION_10M                                              600000

#define MODEL_TRANSITION_STOP                                              0X00

#define DEFAULT_RANDOM_DELAY_VALUE                                          300
#define PUBLISH_1SEC_TIME                                                  1000

typedef MOBLE_RESULT (*APPLI_SAVE_MODEL_STATE_CB)(MOBLEUINT8* stateBuff, MOBLEUINT16 size);
typedef MOBLE_RESULT (*APPLI_SAVE_MODEL_TEST_STATE_CB)(MOBLEUINT8* stateBuff, MOBLEUINT16 size);
typedef MOBLE_RESULT (*APPLI_RETRIEVE_MODEL_TEST_STATE_CB)(MOBLEUINT8* stateBuff, MOBLEUINT16 size);

/******************************************************************************/
/********** Following Section defines the SIG MODEL IDs            ************/
/******************************************************************************/
#define GENERIC_MODEL_SERVER_ONOFF_MODEL_ID                              0x1000
#define GENERIC_MODEL_SERVER_LEVEL_MODEL_ID                              0x1002
#define GENERIC_MODEL_SERVER_DEFAULT_TRANSITION_TIME_MODEL_ID            0x1004
#define GENERIC_MODEL_SERVER_POWER_ONOFF_MODEL_ID                        0x1006
#define GENERIC_MODEL_SERVER_POWER_ONOFF_SETUP_MODEL_ID                  0x1007
#define GENERIC_MODEL_SERVER_POWER_LEVEL_MODEL_ID                        0x1009
#define GENERIC_MODEL_SERVER_POWER_LEVEL_SETUP_MODEL_ID                  0x100A
#define GENERIC_MODEL_SERVER_BATTERY_MODEL_ID                            0x100C
#define GENERIC_MODEL_SERVER_LOCATION_MODEL_ID                           0x100E
#define GENERIC_MODEL_SERVER_LOCATION_SETUP_MODEL_ID                     0x100F
#define GENERIC_MODEL_SERVER_ADMIN_PROPERTY_MODEL_ID                     0x1011
#define GENERIC_MODEL_SERVER_MANUFACTURER_PROPERTY_MODEL_ID              0x1012
#define GENERIC_MODEL_SERVER_USER_PROPERTY_MODEL_ID                      0x1013
#define GENERIC_MODEL_SERVER_CLIENT_PROPERTY_MODEL_ID                    0x1014
#define SENSOR_SERVER_MODEL_ID                                          0x1100U  
#define SENSOR_SETUP_SERVER_MODEL_ID                                    0x1101U
#define SENSOR_CLIENT_MODEL_ID                                          0x1102U 
#define LIGHT_MODEL_SERVER_LIGHTNESS_MODEL_ID                            0x1300
#define LIGHT_MODEL_SERVER_LIGHTNESS_SETUP_MODEL_ID                      0x1301
#define LIGHT_MODEL_SERVER_CTL_MODEL_ID                                  0x1303
#define LIGHT_MODEL_SERVER_CTL_SETUP_MODEL_ID                            0x1304
#define LIGHT_MODEL_SERVER_CTL_TEMPERATURE_MODEL_ID                      0x1306
#define LIGHT_MODEL_SERVER_HSL_MODEL_ID                                  0x1307
#define LIGHT_MODEL_SERVER_HSL_SETUP_MODEL_ID                            0x1308
#define LIGHT_MODEL_SERVER_HSL_HUE_MODEL_ID                              0x130A
#define LIGHT_MODEL_SERVER_HSL_SATURATION_MODEL_ID                       0x130B
#define LIGHT_MODEL_SERVER_XYL_MODEL_ID                                  0x130C
#define LIGHT_MODEL_SERVER_XYL_SETUP_MODEL_ID                            0x130D
#define LIGHT_LC_SERVER_MODEL_ID                                         0x130F
#define LIGHT_LC_SETUP_SERVER_MODEL_ID                                   0x1310
#define LIGHT_LC_CLIENT_MODEL_ID                                         0x1311

#define GENERIC_ONOFF_CLIENT_MODEL_ID                                    0x1001
#define GENERIC_LEVEL_CLIENT_MODEL_ID                                    0x1003
#define GENERIC_DEFAULT_TRANSITION_TIME_CLIENT_MODEL_ID                  0x1005
#define GENERIC_POWER_ONOFF_CLIENT_MODEL_ID                              0x1008

#define LIGHT_LIGHTNESS_SERVER_MODEL_ID                                  0x1300
#define LIGHT_LIGHTNESS_SETUP_SERVER_MODEL_ID                            0x1301
#define LIGHT_LIGHTNESS_CLIENT_MODEL_ID                                  0x1302
#define LIGHT_CTL_SERVER_MODEL_ID                                        0x1303
#define LIGHT_CTL_SETUP_SERVER_MODEL_ID                                  0x1304
#define LIGHT_CTL_CLIENT_MODEL_ID                                        0x1305
#define LIGHT_CTL_TEMPERATURE_SERVER_MODEL_ID                            0x1306
#define LIGHT_HSL_SERVER_MODEL_ID                                        0x1307
#define LIGHT_HSL_SETUP_SERVER_MODEL_ID                                  0x1308
#define LIGHT_HSL_CLIENT_MODEL_ID                                        0x1309
#define LIGHT_HSL_HUE_SERVER_MODEL_ID                                    0x130A
#define LIGHT_HSL_SATURATION_SERVER_MODEL_ID                             0x130B
#define LIGHT_MODEL_SERVER_XYL_MODEL_ID                                  0x130C
#define LIGHT_MODEL_SERVER_XYL_SETUP_MODEL_ID                            0x130D
/* Sensor Server model opcode */                                      
#define SENSOR_DESCRIPTOR_GET                                           0x8230U      
#define SENSOR_DESCRIPTOR_STATUS                                          0X51U
#define SENSOR_GET                                                      0X8231U
#define SENSOR_STATUS                                                     0X52U
#define SENSOR_COLUMN_GET                                               0X8232U
#define SENSOR_COLUMN_STATUS                                              0X53U
#define SENSOR_SERIES_GET                                               0X8233U
#define SENSOR_SERIES_STATUS                                              0X54U
/* Sensor Setup Server model opcode */                                        
#define SENSOR_CADENCE_GET                                              0X8234U
#define SENSOR_CADENCE_SET                                                0X55U
#define SENSOR_CADENCE_SET_UNACK                                          0X56U
#define SENSOR_CADENCE_STATUS                                             0X57U
#define SENSOR_SETTINGS_GET                                             0X8235U
#define SENSOR_SETTINGS_STATUS                                            0X58U
#define SENSOR_SETTING_GET                                              0X8236U
#define SENSOR_SETTING_SET                                                0X59U
#define SENSOR_SETTING_SET_UNACK                                          0X5AU
#define SENSOR_SETTING_STATUS                                             0X5BU
/* Light LC Server model opcode */                                    
#define LIGHT_LC_MODE_GET                                                0X8291
#define LIGHT_LC_MODE_SET                                                0X8292
#define LIGHT_LC_MODE_SET_UNACK                                          0X8293
#define LIGHT_LC_MODE_STATUS                                             0X8294
#define LIGHT_LC_OM_GET                                                  0X8295
#define LIGHT_LC_OM_SET                                                  0X8296
#define LIGHT_LC_OM_SET_UNACK                                            0X8297
#define LIGHT_LC_OM_STATUS                                               0X8298
#define LIGHT_LC_ON_OFF_GET                                              0X8299
#define LIGHT_LC_ON_OFF_SET                                              0X829A
#define LIGHT_LC_ON_OFF_SET_UNACK                                        0X829B
#define LIGHT_LC_ON_OFF_STATUS                                           0X829C
/* Light LC Setup server model opcode */
#define LIGHT_LC_PROPERTY_GET                                            0X829D
#define LIGHT_LC_PROPERTY_SET                                              0X62
#define LIGHT_LC_PROPERTY_SET_UNACK                                        0X63
#define LIGHT_LC_PROPERTY_STATUS                                           0X64


#define GENERIC_SERVER_MAIN_ELEMENT_INDEX                                     0
/* Element index of main element which supports Light Lightness Server
   and Light Lightness Linear is binded with Light LC Linear Out */
#define LIGHT_LIGHTNESS_SERVER_MAIN_ELEMENT_INDEX                             0

              /* Mesh Device Properties and Property IDs  */
/* Temperature 8 In A Period Of Day */
#define AVERAGE_AMBIENT_TEMPERATURE_IN_A_PERIOD_OF_DAY_PID               0x0001
/* Average Current */                                              
#define AVERAGE_INPUT_CURRENT_PID                                        0x0002
/* Average_Voltage */                                              
#define AVERAGE_INPUT_VOLTAGE_PID                                        0x0003
/* Average Current */                                              
#define AVERAGE_OUTPUT_CURRENT_PID                                       0x0004
/* Average_Voltage */                                              
#define AVERAGE_OUTPUT_VOLTAGE_PID                                       0x0005
/* Luminous Intensity */                                           
#define CENTER_BEAM_INTENSITY_AT_FULL_POWER _PID                         0x0006
/* Chromaticity Tolerance */                                        
#define CHROMATICITY_TOLERANCE_PID                                       0x0007
/* Cie 13.3-1995 Color Rendering Index */                           
#define COLOR_RENDERING_INDEX_R9_PID                                     0x0008
/* Cie 13.3-1995 Color Rendering Index */                                
#define COLOR_RENDERING_INDEX_RA_PID                                     0x0009
/* Gap.Appearance */                                                     
#define DEVICE_APPEARANCE_PID                                            0x000A
/* Country Code */                                                       
#define DEVICE_COUNTRY_OF_ORIGIN_PID                                     0x000B
/* Date Utc */                                                           
#define DEVICE_DATE_OF_MANUFACTURE_PID                                   0x000C
/* Energy */                                                             
#define DEVICE_ENERGY_USE_SINCE_TURN_ON_PID                              0x000D
/* Fixed_String 8 */                                                     
#define DEVICE_FIRMWARE_REVISION_PID                                     0x000E
/* Global Trade Item_Number */                                           
#define DEVICE_GLOBAL_TRADE_ITEM_NUMBER_PID                              0x000F
/* Fixed_String 16 */                                                    
#define DEVICE_HARDWARE_REVISION _PID                                    0x0010
/* Fixed_String 36 */                                                    
#define DEVICE_MANUFACTURER_NAME_PID                                     0x0011
/* Fixed_String 24 */                                                    
#define DEVICE_MODEL_NUMBER_PID                                          0x0012
/* Temperature Range */                                                  
#define DEVICE_OPERATING_TEMPERATURE_RANGE_SPECIFICATION_PID             0x0013
/* Temperature_Statistics */                                             
#define DEVICE_OPERATING_TEMPERATURE_STATISTICAL_VALUES_PID              0x0014
/* Event_Statistics */                                                 
#define DEVICE_OVER_TEMPERATURE_EVENT_STATISTICS_PID                     0x0015
/* Power_Specification */                                                
#define DEVICE_POWER_RANGE_SPECIFICATION_PID                             0x0016
/* Time_Hour 24 */
#define DEVICE_RUNTIME_SINCE_TURN_ON_PID                                 0x0017
/* Time_Hour 24 */
#define DEVICE_RUNTIME_WARRANTY_PID                                      0x0018
/* Fixed_String 16 */
#define DEVICE_SERIAL_NUMBER_PID                                         0x0019
/* Fixed_String 8 */
#define DEVICE_SOFTWARE_REVISION_PID                                     0x001A
/* Event_Statistics */
#define DEVICE_UNDER_TEMPERATURE_EVENT_STATISTICS_PID                    0x001B
/* Temperature 8_Statistics */
#define INDOOR_AMBIENT_TEMPERATURE_STATISTICAL_VALUES_PID                0x001C
/* Chromaticity Coordinates */                                   
#define INITIAL_CIE_1931_CHROMATICITY_COORDINATES_PID 	                 0x001D
/* Correlated Color Temperature */                               
#define INITIAL_CORRELATED_COLOR_TEMPERATURE_PID                         0x001E
/* Luminous_Flux */                                              
#define INITIAL_LUMINOUS_FLUX_PID                                        0x001F
/* Chromatic Distance_From_Planckian */                          
#define INITIAL_PLANCKIAN_DISTANCE_PID                                   0x0020
/* Electric Current_Specification */                             
#define INPUT_CURRENT_RANGE_SPECIFICATION_PID                            0x0021
/* Electric Current_Statistics */                                
#define INPUT_CURRENT_STATISTICS_PID                                     0x0022
/* Event_Statistics */                                           
#define INPUT_OVER_CURRENT_EVENT_STATISTICS_PID                          0x0023
/* Event_Statistics */                                           
#define INPUT_OVER_RIPPLE_VOLTAGE_EVENT_STATISTICS_PID	                 0x0024
/* Event_Statistics */                                           
#define INPUT_OVER_VOLTAGE_EVENT_STATISTICS_PID                          0x0025
/* Event_Statistics */                                           
#define INPUT_UNDER_CURRENT_EVENT_STATISTICS_PID                         0x0026
/* Event_Statistics */                                           
#define INPUT_UNDER_VOLTAGE_EVENT_STATISTICS_PID                         0x0027
/* Voltage_Specification */                                      
#define INPUT_VOLTAGE_RANGE_SPECIFICATION_PID 	                         0x0028
/* Percentage 8 */                                               
#define INPUT_VOLTAGE_RIPPLE_SPECIFICATION_PID                           0x0029
/* Voltage Statistics */                                         
#define INPUT_VOLTAGE_STATISTICS_PID                                     0x002A
/* Illuminance */                                                
#define LIGHT_CONTROL_AMBIENT_LUXLEVEL_ON_PID                            0x002B
/* Illuminance */
#define LIGHT_CONTROL_AMBIENT_LUXLEVEL_PROLONG_PID                       0x002C
/* Illuminance */
#define LIGHT_CONTROL_AMBIENT_LUXLEVEL_STANDBY_PID                       0x002D
/* Perceived_Lightness */
#define LIGHT_CONTROL_LIGHTNESS_ON_PID                                   0x002E
/* Perceived_Lightness */
#define LIGHT_CONTROL_LIGHTNESS_PROLONG_PID                              0x002F
/* Perceived_Lightness */                                                
#define LIGHT_CONTROL_LIGHTNESS_STANDBY_PID                              0x0030
/* Percentage 8 */                                                       
#define LIGHT_CONTROL_REGULATOR_ACCURACY_PID                             0x0031
/* Coefficient */
#define LIGHT_CONTROL_REGULATOR_KID_PID                                  0x0032
/* Coefficient */                                                        
#define LIGHT_CONTROL_REGULATOR_KIU_PID                                  0x0033
/* Coefficient */                                                        
#define LIGHT_CONTROL_REGULATOR_KPD_PID                                  0x0034
/* Coefficient */                                                        
#define LIGHT_CONTROL_REGULATOR_KPU_PID                                  0x0035
/* Time Millisecond 24 */
#define LIGHT_CONTROL_TIME_FADE_PID                                      0x0036
/* Time Millisecond 24 */
#define LIGHT_CONTROL_TIME_FADE_ON_PID 	                                 0x0037
/* Time Millisecond 24 */                                               
#define LIGHT_CONTROL_TIME_FADE_STANDBY_AUTO_PID                         0x0038
/* Time Millisecond 24 */                                               
#define LIGHT_CONTROL_TIME_FADE_STANDBY_MANUAL_PID                       0x0039
/* Time Millisecond 24 */
#define LIGHT_CONTROL_TIME_OCCUPANCY_DELAY_PID                           0x003A
/* Time Millisecond 24 */                                             
#define LIGHT_CONTROL_TIME_PROLONG_PID                                   0x003B
/* Time Millisecond 24 */
#define LIGHT_CONTROL_TIME_RUN_ON_PID                                    0x003C
/* Percentage 8 */
#define LUMEN_MAINTENANCE_FACTOR_PID                                     0x003D
/* Luminous_Efficacy */
#define LUMINOUS_EFFICACY_PID                                            0x003E
/* Luminous_Energy */
#define LUMINOUS_ENERGY_SINCE_TURN_ON_PID                                0x003F
/* Luminous_Exposure */
#define LUMINOUS_EXPOSURE_PID                                            0x0040
/* Luminous_Flux Range */
#define LUMINOUS_FLUX_RANGE_PID                                          0x0041
/* Percentage 8 */
#define MOTION_SENSED_PID                                                0x0042
/* Percentage 8 */
#define MOTION_THRESHOLD_PID                                             0x0043
/* Event_Statistics */
#define OPEN_CIRCUIT_EVENT_STATISTICS_PID                                0x0044
/* Temperature 8_Statistics */
#define OUTDOOR_STATISTICAL_VALUES_PID 	                                 0x0045
/* Electric Current Range */
#define OUTPUT_CURRENT_RANGE_PID                                         0x0046
/* Electric Current_Statistics */
#define OUTPUT_CURRENT_STATISTICS_PID                                    0x0047
/* Percentage 8 */
#define OUTPUT_RIPPLE_VOLTAGE_SPECIFICATION_PID                          0x0048
/* Voltage_Specification */
#define OUTPUT_VOLTAGE_RANGE_PID                                         0x0049
/* Voltage_Statistics */
#define OUTPUT_VOLTAGE_STATISTICS_PID                                    0x004A
/* Event_Statistics */
#define OVER_OUTPUT_RIPPLE_VOLTAGE_EVENT_STATISTICS_PID	                 0x004B
/* Count 16 */
#define PEOPLE_COUNT_PID                                                 0x004C
/* Boolean */
#define PRESENCE_DETECTED_PID 	                              	         0x004D
/* Illuminance */
#define PRESENT_AMBIENT_LIGHT_LEVEL_PID                                  0x004E
/* Temperature 8 */                                                 
#define PRESENT_AMBIENT_TEMPERATURE_PID                                  0x004F
/* Chromaticity Coordinates */                                      
#define PRESENT_CIE_1931_CHROMATICITY_COORDINATES_PID 	                 0x0050
/* Correlated Color Temperature */
#define PRESENT_CORRELATED_COLOR_TEMPERATURE_PID                         0x0051
/* Power */
#define PRESENT_DEVICE_INPUT_POWER_PID                                   0x0052
/* Percentage 8 */
#define PRESENT_DEVICE_OPERATING_EFFICIENCY_PID                          0x0053
/* Temperature */
#define PRESENT_DEVICE_OPERATING_TEMPERATURE_PID                         0x0054
/* Illuminance */
#define PRESENT_ILLUMINANCE_PID                                          0x0055
/* Temperature 8 */                                                      
#define PRESENT_INDOOR_AMBIENT_TEMPERATURE_PID	              	         0x0056
/* Electric Current */                                                   
#define PRESENT_INPUT_CURRENT_PID                                        0x0057
/* Percentage 8 */                                                       
#define PRESENT_INPUT_RIPPLE_VOLTAGE_PID                                 0x0058
/* Voltage */                                                            
#define PRESENT_INPUT_VOLTAGE_PID                                        0x0059
/* Luminous_Flux */                                                      
#define PRESENT_LUMINOUS_FLUX_PID                                        0x005A
/* Temperature 8 */
#define PRESENT_OUTDOOR_AMBIENT_TEMPERATURE_PID                          0x005B
/* Electric Current */
#define PRESENT_OUTPUT_CURRENT_PID                                       0x005C
/* Voltage */                                                            
#define PRESENT_OUTPUT_VOLTAGE_PID                                       0x005D
/* Chromatic Distance_From_Planckian */
#define PRESENT_PLANCKIAN_DISTANCE_PID                                   0x005E
/* Percentage 8 */
#define PRESENT_RELATIVE_OUTPUT_RIPPLE_VOLTAGE_PID                       0x005F
/* Energy In_A_Period Of Day */
#define RELATIVE_DEVICE_ENERGY_USE_IN_A_PERIOD_OF_DAY_PID                0x0060
/* Relative Runtime In_A_Generic_Level Range */
#define RELATIVE_DEVICE_RUNTIME_IN_A_GENERIC_LEVEL_RANGE_PID             0x0061
/* Relative_Value In_An Illuminance Range */
#define RELATIVE_EXPOSURE_TIME_IN_AN_ILLUMINANCE_RANGE_PID               0x0062
/* Luminous_Energy */
#define RELATIVE_RUNTIME_IN_A_CORRELATED_COLOR_TEMPERATURE_RANGE_PID     0x0063
/* Relative_Value In_A Temperature Range */
#define RELATIVE_RUNTIME_IN_A_DEVICE_OPERATING_TEMPERATURE_RANGE_PID     0x0064
/* Relative Runtime In_A Current Range */
#define RELATIVE_RUNTIME_IN_AN_INPUT_CURRENT_RANGE_PID                   0x0065
/* Relative_Value In_A_Voltage Range */                                  
#define RELATIVE_RUNTIME_IN_AN_INPUT_VOLTAGE_RANGE_PID 	                 0x0066
/* Event_Statistics */                                                   
#define SHORT_CIRCUIT_EVENT_STATISTICS_PID                               0x0067
/* Time_Second 16 */
#define TIME_SINCE_MOTION_SENSED_PID                                     0x0068
/* Time Second 16 */                                                     
#define TIME_SINCE_PRESENCE_DETECTED_PID                                 0x0069
/* Energy */                                                             
#define TOTAL_DEVICE_ENERGY_USE_PID                                      0x006A
/* Count 24 */
#define TOTAL_DEVICE_OFF_ON_CYCLES_PID                                   0x006B
/* Count 24 */
#define TOTAL_DEVICE_POWER_ON_CYCLES_PID                                 0x006C
/* Time_Hour 24 */
#define TOTAL_DEVICE_POWER_ON_TIME_PID                                   0x006D
/* Time_Hour 24 */
#define TOTAL_DEVICE_RUNTIME_PID                                         0x006E
/* Time_Hour 24 */
#define TOTAL_LIGHT_EXPOSURE_TIME_PID                                    0x006F
/* Luminous_Energy */
#define TOTAL_LUMINOUS_ENERGY_PID                                        0x0070
/* Temperature 8 */                                                      
#define DESIRED_AMBIENT_TEMPERATURE_PID                                  0x0071
#define PRECISE_TOTAL_DEVICE_ENERGY_USE_PID                              0x0072
#define POWER_FACTOR_PID                                                 0x0073
#define SENSOR_GAIN_PID                                                  0x0074
#define PRECISE_PRESENT_AMBIENT_TEMPERATURE_PID                          0x0075
#define PRESENT_AMBIENT_RELATIVE_HUMIDITY_PID                            0x0076
#define PRESENT_AMBIENT_CARBON_DIOXIDE_CONCENTRATION_PID                 0x0077
#define PRESENT_AMBIENT_VOLATILE_ORGANIC_COMPOUNDS_CONCENTRATION_PID     0x0078
#define PRESENT_AMBIENT_NOISE_PID                                        0x0079
#define ACTIVE_ENERGY_LOADSIDE_PID                                       0x0080
#define ACTIVE_POWER_LOADSIDE_PID                                        0x0081
#define AIR_PRESSURE_PID                                                 0x0082
#define APPARENT_ENERGY_PID                                              0x0083
#define APPARENT_POWER_PID                                               0x0084
#define APPARENT_WIND_DIRECTION_PID                                      0x0085
#define APPARENT_WIND_SPEED_PID                                          0x0086
#define DEW_POINT_PID                                                    0x0087
#define EXTERNAL_SUPPLY_VOLTAGE_PID                                      0x0088
#define EXTERNAL_SUPPLY_VOLTAGE_FREQUENCY_PID                            0x0089
#define GUST_FACTOR_PID                                                  0x008A
#define HEAT_INDEX_PID                                                   0x008B
#define LIGHT_DISTRIBUTION_PID                                           0x008C
#define LIGHT_SOURCE_CURRENT_PID                                         0x008D
#define LIGHT_SOURCE_ON_TIME_NOT_RESETTABLE_PID                          0x008E
#define LIGHT_SOURCE_ON_TIME_RESETTABLE_PID                              0x008F
#define LIGHT_SOURCE_OPEN_CIRCUIT_STATISTICS_PID                         0x0090
#define LIGHT_SOURCE_OVERALL_FAILURES_STATISTICS_PID                     0x0091
#define LIGHT_SOURCE_SHORT_CIRCUIT_STATISTICS_PID                        0x0092
#define LIGHT_SOURCE_START_COUNTER_RESETTABLE_PID                        0x0093
#define LIGHT_SOURCE_TEMPERATURE_PID                                     0x0094
#define LIGHT_SOURCE_THERMAL_DERATING_STATISTICS_PID                     0x0095
#define LIGHT_SOURCE_THERMAL_SHUTDOWN_STATISTICS_PID                     0x0096
#define LIGHT_SOURCE_TOTAL_POWER_ON_CYCLES_PID                           0x0097
#define LIGHT_SOURCE_VOLTAGE_PID                                         0x0098
#define LUMINAIRE_COLOR_PID                                              0x0099
#define LUMINAIRE_IDENTIFICATION_NUMBER_PID                              0x009A
#define LUMINAIRE_MANUFACTURER_GTIN_PID                                  0x009B
#define LUMINAIRE_NOMINAL_INPUT_POWER_PID                                0x009C
#define LUMINAIRE_NOMINAL_MAXIMUM_AC_MAINS_VOLTAGE_PID                   0x009D
#define LUMINAIRE_NOMINAL_MINIMUM_AC_MAINS_VOLTAGE_PID                   0x009E
#define LUMINAIRE_POWER_AT_MINIMUM_DIM_LEVEL_PID                         0x009F
#define LUMINAIRE_TIME_OF_MANUFACTURE_PID                                0x00A0
#define MAGNETIC_DECLINATION_PID                                         0x00A1
#define MAGNETIC_FLUX_DENSITY_2D_PID                                     0x00A2
#define MAGNETIC_FLUX_DENSITY_3D_PID                                     0x00A3
#define NOMINAL_LIGHT_OUTPUT_PID                                         0x00A4
#define OVERALL_FAILURE_CONDITION_PID                                    0x00A5
#define POLLEN_CONCENTRATION_PID                                         0x00A6
#define PRESENT_INDOOR_RELATIVE_HUMIDITY_PID                             0x00A7
#define PRESENT_OUTDOOR_RELATIVE_HUMIDITY_PID                            0x00A8
#define PRESSURE_PID                                                     0x00A9
#define RAINFALL_PID                                                     0x00AA
#define RATED_MEDIAN_USEFUL_LIFE_OF_LUMINAIRE_PID                        0x00AB
#define RATED_MEDIAN_USEFUL_LIGHT_SOURCE_STARTS_PID                      0x00AC
#define REFERENCE_TEMPERATURE_PID                                        0x00AD
#define TOTAL_DEVICE_STARTS_PID                                          0x00AE
#define TRUE_WIND_DIRECTION_PID                                          0x00AF
#define TRUE_WIND_SPEED_PID                                              0x00B0
#define UV_INDEX_PID                                                     0x00B1
#define WIND_CHILL_PID                                                   0x00B2
#define LIGHT_SOURCE_TYPE_PID                                            0x00B3
#define LUMINAIRE_IDENTIFICATION_STRING_PID                              0x00B4
#define OUTPUT_POWER_LIMITATION_PID                                      0x00B5
#define THERMAL_DERATING_PID                                             0x00B6
#define OUTPUT_CURRENT_PERCENT_PID                                       0x00B7

#define PRESSURE_CUSTOM_PID                                              0x2A6D
#define HUMIDITY_PID                                                     0x2A6F
#define TIME_OF_FLIGHT_PID                                               0X2A7F
#define MAGNETO_METER_PID                                                0x2AA1
#define ACCELERO_METER_PID                                               0x2BA1
#define GYROSCOPE_PID                                                    0x2BA2
#define VOLTAGE_PID                                                      0x0005
#define CURRENT_PID                                                      0x0004
#define POWER_FACTOR_CUSTOM_PID                                          0x0072
#define ACTIVE_POWER_PID                                                 0x0073
#define REACTIVE_POWER_PID                                               0x0074
#define APPARENT_POWER_CUSTOM_PID                                        0x0075
#define ACTIVE_ENERGY_PID                                                0x0083
#define REACTIVE_ENERGY_PID                                              0x0084
#define APPARENT_ENERGY_CUSTOM_PID                                       0x0085

#define PROPERTY_ID_LENGTH                                                    2

#define ONE_BYTE_VALUE                                                        1
#define TWO_BYTE_VALUE                                                        2
#define THREE_BYTE_VALUE                                                      3
#define FOUR_BYTE_VALUE                                                       4

#define PROPERTY_ID_PROHIBITED                                           0x0000


/** @addtogroup MODEL_GENERIC
*  @{
*/

/** @addtogroup Generic_Model_Callbacks
*  @{
*/

/* Exported types ------------------------------------------------------------*/


/**
  * transition status enum
 */
typedef enum
{
  TRANSITION_STATUS_STOP = 0,
  TRANSITION_STATUS_DELAY,
  TRANSITION_STATUS_RUNNING
}transition_status_e;


/**
  * transition parameters struct
 */
typedef struct
{
  MOBLEUINT32 stepResolutionMs;
  MOBLEUINT32 trTimeMs;
  MOBLEUINT32 trBeginTick;
  MOBLEUINT32 trEndTick;
  MOBLEUINT32 trNextActionTick;
  transition_status_e trStatus;
  MOBLEUINT8 publishEventTrig;
  MOBLEUINT8 res[2];
} transition_params_t;


/**
  * status send (in reply to get, set & setunack messages) enum
 */
typedef enum
{
  STATUS_SEND_REPLY = 0,
  STATUS_SEND_PUBLISH,
  STATUS_SEND_REPLY_PUBLISH
} status_send_e;


/**
  * transition event enum
 */
typedef enum
{
  TRANSITION_EVENT_NO = 0,
  TRANSITION_EVENT_ABORT,
  TRANSITION_EVENT_DELAY,
  TRANSITION_EVENT_TIMER_START,
  TRANSITION_EVENT_TIMER_TRIG,
  TRANSITION_EVENT_PUBLISH,
  TRANSITION_EVENT_TIMER_STOP
}transition_event_e;


/**
  * Model tid value structure
 */
typedef struct
{
  MOBLEUINT8 Tid_Value;
  MOBLEUINT8 TidSend;
  MOBLE_ADDRESS Peer_Addrs;
  MOBLE_ADDRESS Dst_Addrs;
}Model_Tid_t;


/**
  * TID params struct
 */
typedef struct
{
  MOBLEUINT32 tidTick;
  MOBLE_ADDRESS src;
  MOBLE_ADDRESS dst;
  MOBLEUINT8 tid;
  MOBLEUINT8 res[3];
}tid_param_t;


/**
  * variable used for binding status
 */
typedef struct
{
  MOBLEUINT16 Model_Rx_Opcode;  
  MOBLEUINT16 Model_ID;
  MOBLE_ADDRESS Dst_Peer;
}Model_Binding_Var_t;

typedef struct
{
  MOBLEUINT8 Restore_Flag;
  MOBLEUINT8 LightTransitionStatus;
  MOBLEUINT8 GenericTransitionStatus;
  MOBLEUINT8 PowerOnOff;
#ifdef ENABLE_GENERIC_MODEL_SERVER_ONOFF  
  MOBLEUINT8 Generic_OnOff; 
  MOBLEUINT8 GenericTarget;
#endif

#ifdef ENABLE_GENERIC_MODEL_SERVER_LEVEL  
  MOBLEUINT16 Generic_Level;
#endif
  
#ifdef ENABLE_GENERIC_MODEL_SERVER_DEFAULT_TRANSITION_TIME  
  MOBLEUINT8 Generic_Default_Transition;
#endif  
  
#ifdef ENABLE_LIGHT_MODEL_SERVER_LIGHTNESS
  MOBLEUINT16 LightLightness;
  MOBLEUINT16 LightTarget;
  MOBLEUINT16 LightDefault;
  MOBLEUINT16 LightLast;
#endif

#ifdef ENABLE_LIGHT_MODEL_SERVER_CTL
  MOBLEUINT16 CtlLightness;
  MOBLEUINT16 CtlTemperature;
  MOBLEUINT16 CtlDelta;
  MOBLEUINT16 CtlDefaultLightness;
  MOBLEUINT16 CtlDefaultTemperature;
  MOBLEUINT16 CtlDefaultDelta;
  MOBLEUINT16 CtlLightTarget;
  MOBLEUINT16 CtlTempTarget;
  MOBLEUINT16 CtlDeltaTarget; 
#endif  

#ifdef ENABLE_LIGHT_MODEL_SERVER_HSL
  MOBLEUINT16 HslLightness;
  MOBLEUINT16 HslHue;
  MOBLEUINT16 HslSaturation; 
  MOBLEUINT16 HslLightnessDefault;
  MOBLEUINT16 HslHueDefault;
  MOBLEUINT16 HslSaturationDefault;
  MOBLEUINT16 HslLightTarget;
  MOBLEUINT16 HslHueTarget;
  MOBLEUINT16 HslSatTarget;
#endif  
 
}Model_DataNvm_t;

typedef struct
{
  Model_DataNvm_t Model_DataNvm[APPLICATION_NUMBER_OF_ELEMENTS];
  
#ifdef ENABLE_LIGHT_MODEL_SERVER_LC 
  MOBLEUINT8 LightLCBuff[4];
  MOBLEUINT32 LightLCPropIdBuff[LC_PROPERTY_TABLE_COUNT]; 
#endif
  
}Models_ParamNvm_t;

/* Exported functions ------------------------------------------------------- */
MOBLE_RESULT Chk_OptionalParamValidity(MOBLEUINT8 param_length, MOBLEUINT8
                                        mandatory_length, MOBLEUINT8 param,
                                                  MOBLEUINT8 max_param_value  );
MOBLE_RESULT Chk_ParamMinMaxValidity(MOBLEUINT16 min_param_value, 
                                                 const MOBLEUINT8* param,
                                                 MOBLEUINT16 max_param_value );

MOBLE_RESULT Chk_ParamValidity(MOBLEUINT8 param, MOBLEUINT8 max_param_val );
 
MOBLE_RESULT Chk_RangeValidity(MOBLEUINT16 min_param_value, const MOBLEUINT8* param, 
                                                     MOBLEUINT16 max_param_value );
MOBLE_RESULT  Chk_HslRangeValidity(const MOBLEUINT8* param,MOBLEUINT16 min_param_value_1, 
                                   MOBLEUINT16 max_param_value_1,MOBLEUINT16 min_param_value_2,
                                     MOBLEUINT16 max_param_value_2);
MOBLE_RESULT  Chk_TwoParamValidity(MOBLEUINT16 min_param_range1, MOBLEUINT16 max_param_range1,                                        
                                      MOBLEUINT16 min_param_range2, MOBLEUINT16 max_param_range2,
                                        const MOBLEUINT8* param);
MOBLE_RESULT  Chk_MultiParamValidity(MOBLEUINT16 min_param_range1, MOBLEUINT16 max_param_range1,                                        
                                      MOBLEUINT16 min_param_range2, MOBLEUINT16 max_param_range2,
                                      MOBLEINT16 min_param_range3, MOBLEUINT16 max_param_range3,
                                        const MOBLEUINT8* param);
MOBLE_RESULT  Chk_MultiParamValidityAllUnsigned(MOBLEUINT16 min_param_range1, MOBLEUINT16 max_param_range1,                                        
                                      MOBLEUINT16 min_param_range2, MOBLEUINT16 max_param_range2,
                                      MOBLEINT16 min_param_range3, MOBLEUINT16 max_param_range3,
                                        const MOBLEUINT8* param);
MOBLE_RESULT Chk_ParamMinMaxIntValidity(MOBLEINT16 min_param_value, const MOBLEUINT8* param, 
                                                     MOBLEINT16 max_param_value );
MOBLEUINT8 Tid_CheckAndUpdate(MOBLEUINT8 currentMsgTid,
                             MOBLE_ADDRESS currentMsgSrc,
                             MOBLE_ADDRESS currentMsgDst,
                             tid_param_t* pLastMsgTidParams);
MOBLE_RESULT TimeDttFGet(MOBLEUINT32 timeMs, MOBLEUINT8* timeDttF);
MOBLEUINT32 Get_StepResolutionValue(MOBLEUINT8 time_param);

float Ratio_CalculateValue(MOBLEUINT16 setValue , MOBLEUINT16 maxRange , MOBLEINT16 minRange);
void TraceHeader(const char* func_name, int mode);
MOBLE_RESULT SaveModelsStateNvm(MOBLEUINT8* flag);
MOBLEUINT8 Bluenrg_GetElementNumber(void);
void Test_Process(void);
void ModelSave_Process(void);
void BluenrgMesh_PacketResponseTime(MOBLEUINT8 *testFunctionParm);
MOBLEUINT8 Time_Conversion(MOBLEUINT32 lc_Time);
void Model_RestoreStates(MOBLEUINT8 const *pModelState_Load, MOBLEUINT16 size);   

void Generic_OnOffPowerOnValue(Model_DataNvm_t *state_Value, MODEL_MessageHeader_t *pmsgParam);
MOBLEUINT16 Light_lightnessPowerOnValue(Model_DataNvm_t *state_Value, MODEL_MessageHeader_t *pmsgParam);                                       
void Light_CtlPowerOnValue(Model_DataNvm_t *state_Value, MODEL_MessageHeader_t *pmsgParam);
void Light_HslPowerOnValue(Model_DataNvm_t *state_Value, MODEL_MessageHeader_t *pmsgParam);

void MemoryDumpHex(const MOBLEUINT8* memory_addr, int size);
void PutLittleEndian(MOBLEUINT8* stream, MOBLEUINT32 value, MOBLEUINT8 octets);
void GetLittleEndian(MOBLEUINT8 const *stream, MOBLEUINT8 octets, MOBLEUINT32* result);

void CopyU8LittleEndienArray_fromU16word (MOBLEUINT8* pArray, MOBLEUINT16 inputWord);
void CopyU8LittleEndienArray_fromU32word (MOBLEUINT8* pArray, MOBLEUINT32 inputWord);
void CopyU8LittleEndienArray_2B_fromU32word (MOBLEUINT8* pArray, MOBLEUINT32 inputWord);
MOBLEUINT16 CopyU8LittleEndienArrayToU16word (MOBLEUINT8* pArray);
MOBLEUINT32 CopyU8LittleEndienArrayToU32word (MOBLEUINT8* pArray);
void NvmStatePowerFlag_Set(MOBLEUINT8 nvmModelFlag, MOBLEUINT8 elementIndex);
void Device_FlashTesting(void);

transition_event_e Transition_Stop(transition_status_e* status);
transition_event_e Transition_Sm(transition_params_t* transitionParams,
                                 MOBLEUINT32 delayMs);
MOBLEUINT32 Transition_RemainingTimeGet(transition_params_t* transitionParams);
MOBLEUINT32 Transition_TimerGet(transition_params_t* pTrParams);
MOBLEUINT32 Transition_TimeToNextActionGet(transition_params_t* pTrParams);
MOBLEUINT32 Transition_StateValueGet(MOBLEUINT32 finalState, 
                                     MOBLEUINT32 initialState, 
                                     MOBLEUINT32 timer, 
                                     MOBLEUINT32 transitionTime);
MOBLE_RESULT ExtractPropertyId(const MOBLEUINT8* data,
                                      MOBLEUINT16* pPropertyId);
MOBLE_RESULT ExtractMarshalledSensorData(const MOBLEUINT8* pData,
                                         MOBLEUINT32 dataLength,
                                         MOBLEUINT16 offset,
                                         MOBLEUINT16 maxPropertyId,
                                         MOBLEUINT16* pPropertyId,
                                         MOBLEUINT8* pPropertyDataLength,
                                         MOBLEUINT16* pOffsetPropertyData);
MOBLE_RESULT Binding_GenericOnOff_LightLcLightOnOff(MOBLEUINT8 genericElementIndex, 
                                                    MOBLEUINT8 genericOnOff,
                                                    MOBLEUINT8 optionalParams,
                                                    MOBLEUINT32 delayMs,
                                                    MOBLEUINT8 transitionParam);
MOBLE_RESULT Binding_LightLcLightOnOff_GenericOnOff(MOBLEUINT8 lcElementIndex, MOBLEUINT8 lcOnOff);
MOBLE_RESULT Binding_LcLinearOut_LightLightnessLinear(MOBLEUINT8 lcElementIndex, MOBLEUINT16 lcLinearOut);
void BindingDisable_LcLinearOut_LightLightnessLinear(MOBLEUINT8 lightnessLinearElementIndex);
void BluenrgMesh_ModelsDefaultValueInit(void);

#endif /* __COMMON_H */

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/

