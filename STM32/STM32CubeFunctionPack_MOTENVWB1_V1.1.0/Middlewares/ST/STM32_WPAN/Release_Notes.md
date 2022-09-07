---
pagetitle: Release Notes for STM32 Middleware WPAN
lang: en
header-includes: <link rel="icon" type="image/x-icon" href="./_htmresc/favicon.png" />
---

::: {.row}
::: {.col-sm-12 .col-lg-4}

<center>
# Release Notes for
# <mark>STM32 Middleware WPAN</mark>
Copyright &copy; 2020 STMicroelectronics\
    
[![ST logo](_htmresc/st_logo_2020.png)](https://www.st.com){.logo}
</center>


License
=======

This software component is licensed by ST under Ultimate Liberty license
SLA0044, the "License";

You may not use this file except in compliance with the License.

You may obtain a copy of the License at:
[SLA0044](http://www.st.com/SLA0044)

Purpose
=======

STM32 Wireless Personal Area Network Middleware developed within the
STM32WB framework is used to support:

-   Bluetooth Low Energy 5 Certified Applications

-   802.15.4 Thread Certified Applications (based on
    [OpenThread](thread\openthread\Release_Notes.html) stack)

-   802.15.4 MAC layer

-   Zigbee Applications

**NOTE** : Depending on the kind of Application targeted, the appropriate
Wireless Coprocessor Firmware needs to be loaded.

- **Zigbee** clusters are provided as a library. 
  - Available on **IAR/SW4STM32**(**stm32wb_zigbee_wb_lib.a**) and **Keil**(**stm32wb_zigbee_wb_lib_keil.lib**) under Middlewares/ST/STM32_WPAN/zigbee/lib.
  - To get access to Zigbee clusters source code, please contact ST local office.

- All available binaries are located under/Projects/STM32\_Copro\_Wireless\_Binaries directory.

- Refer to UM2237 to learn how to use/install STM32CubeProgrammer.

- Refer to /Projects/STM32\_Copro\_Wireless\_Binaries/ReleaseNote.html for the detailed procedure to change the Coprocessor binary.
:::

::: {.col-sm-12 .col-lg-8}
Update History
==============

::: {.collapse}
<input type="checkbox" id="collapse-section14" checked aria-hidden="true">
<label for="collapse-section14" aria-hidden="false">V1.12.0 / 17-June-2021</label>
<div>

## Main Changes

- Zigbee:
  - ZCL Reporting improvement in order to eliminate an unused 1 second timer handler processing
  - Comments improvements in the API descriptions associated to the clusters  (header files)
  - Code cleanup (MISRA rules compliancy)
  - Adding of a function requested by the Scene Cluster which was missing on the previous stm32wb_zigbee_wb_lib library
  - Security API cleanup + install code management
  
- BLE updates:
  - Remove completely ACI_HAL_SET_SMP_ENG_CONFIG command
  - GATT_Check_For_Service_Change: add check of GATT database minimum length    
  -	ID 104796 : HIDS_Handle_Mouse_Input_Write/HIDS_Handle_Keyboard_Output_Write : Null pointer used             

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section13" aria-hidden="true">
<label for="collapse-section13" aria-hidden="false">V1.11.0 / 5-February-2021</label>
<div>

## Main Changes


- BLE-Mesh library version 1.13.002
  - Updated max number of element to 5 and max number of Model per element to 11:
      To support lighting control system with occupancy sensing.  
  - Bug fix: Client API, Light LC model and sensor status, modify Light LC FSM default Lightness values
  - Sensor & Light LC Server Models updated
  - Client Models updated
  - Config Model APIs callbacks added over application layer
  - Save & Restore APIs for Models parameters in Flash updated
  - Publication enabled for multiple elements
  - Remove double disconnection to accelerate provisioning with IOS ST BLE Mesh App version 1.08.001
  - Bug correction during unprovisioning with ST BLE Mesh App of non GATT connected Nodes. 
  - Bug correction for loss of Vendor model publication: fix on dynamic memory allocation leak when publishing vendor command into group      

- BLE is Compliant BT5.2:
  - HID: added: Battery Service and Device Information Service, connection and disconnection events
  - ID 97936 :  L2CAP update to support IP over BLE (M.6874), SHCI_C2_BLE_init() updated parameters to be provided to CPU2 with new BLE stack Options flags to be configured as:
    - SHCI_C2_BLE_INIT_OPTIONS_LL_ONLY
    - SHCI_C2_BLE_INIT_OPTIONS_LL_HOST
    - SHCI_C2_BLE_INIT_OPTIONS_NO_SVC_CHANGE_DESC
    - SHCI_C2_BLE_INIT_OPTIONS_WITH_SVC_CHANGE_DESC
    - SHCI_C2_BLE_INIT_OPTIONS_DEVICE_NAME_RO
    - SHCI_C2_BLE_INIT_OPTIONS_DEVICE_NAME_RW
    - SHCI_C2_BLE_INIT_OPTIONS_POWER_CLASS_1
    - SHCI_C2_BLE_INIT_OPTIONS_POWER_CLASS_2_3
  - ID 95186 :  SHCI_C2_FUS_GetState fixed to identify when wireless stack running (with correct error code)
  - ID 94042, ID 97931 : STM32WB to handle certification BT5.2 (tcrl 2019-2)

- THREAD:
  - Update OpenThread stack to **SHA-1: 3dbd91aa2b70c7d5cc71b2c465ce3583a13dea79** (thread-reference-20191113)
  - ID 91270: CoapSecure support added
  - ID 96955: Fix for entering standby mode while Thread stop procedure is called. New system command SHCI_C2_802_15_4_DeInit added

- Zigbee:
  - Clarification of PICS information inside the Clusters API interface include files 
  - New directory structure used to store Clusters API interfaces include files
  - Range input parameter checks added when managing Clusters
  - ZCL Commissioning Cluster improvement to allow joining commissioning network and sending unicast frames (as well as Inter-PAN)
  - Support of a Custom Cluster (Refer to the appropriate applications to see how to use it : Zigbee_custom_ls_Server_Coord, and Zigbee_custom_ls_Client_Router)
  - Support of new APIs to control  TouchLink features (Refer to  zcl.touchlink.h file for more details). Adding of TouchLink utility commands
  - Minor fixes in DRLC, Voice over Zigbee & RSSI location Clusters

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section12" aria-hidden="true">
<label for="collapse-section12" aria-hidden="false">V1.10.0 / 26-October-2020</label>
<div>

## Main Changes

- General:
    - tl_dbg_conf.h file removed from STM32WPAN Middleware and moved to application side.

- BLE-Mesh library version 1.13.001
    - Improvements:
      - Updated number of element to 8 and number of Model per element to 7
	- Bug fix:
      - Bug correction on Vendor Model: set correct peer address for Vendor Model command
	  
- BLE updates :
    - **ID 91486** - Trace support on all BLE / SYSTEM packets exchanged over the MailBox
    - **ID 92539** - Calibration for RFWUCK - code comment improvement
    - **ID 93153** - Wrong comment on CFG_RTC_WUCKSEL_DIVIDER in app_conf.h
    - **ID 93790** - Clear FLASH_FLAG_OPTVERR at the begin of main.c 
    - **ID 95187** - BLE_OTA : infinite loop when trying to update the wireless stack with a wrong binary file
    
- ZIGBEE :
    - Zigbee interface clarification by adding comments inside the ZCL header files
    - Minor Poll control, IAS and Window covering cluster improvements (For ex : return status and parameter range checking)
    
</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section11" aria-hidden="true">
<label for="collapse-section11" aria-hidden="false">V1.9.0 / 21-September-2020</label>
<div>

## Main Changes

- BLE-Mesh library version 1.13.000
    - New Development:
      - Light LC Server model
      - New state transition functions and structures in common, new TID check & update functions in common
      - Disable No OOB authentication
      - Multi-element support in Friendship
      - Use of hardware cryptogrphic functions instead of ST Cryptographic Library
      - Remove hci_reset() function calls during provisionning
    - Improvements:
      - Logs optimization and clean up of Server models
      - ATLLC & ATSNR modified to ATUT
      - Server model publication modifications
      - Serial_ut moved to middleware
      - Fixed firmware for crash issue with the publish message
      - Model flash data saving for multi-element
      - APIs update, naming convention updated in light.c
      - Unused code commented in model_generic.c
      - NULL checks added in remaining exposed functions to avoid hardfault in case sensor server is not initialized or failed to initialize
    - Bug fix:
      - Generic OnOff bug when Generic Default Transition Time is enabled
      - Element index update for Generic OnOff
      - Generic OnOff Transition bug, LED not turning off
      - Ongoing Transition should be turned off if any other on/off command received in between
      - The Light Lightness model appears to behave in a non compliant way in the case a new Light_Lightness_Set command is received during an ongoing transition of the Light Level. This causes also the ‘Light Lightness Last’ value to get a wrong value.
      - API MobleConfigModel_SendAppKeyList updated in model_config.c & pal_crypto.c to get the list of all appKeys bounded with a netKey if number of appKeys is>1
      - Bug related to AppKey Delete resolved
      - Bug related to Memory Leak resolved
      - Checkpoint has been added in API ApplicationGetVendorModelList if someone commented ENABLE_VENDOR_MODEL_SERVER in mesh_cfg_usr.h
      
- BLE WPAN updates
    - **ID 88523** - SHCI_C2_BLE_Init() return value type wrong
    - **ID 91533** - Improve the SHCI_GetWirelessFwInfo() to decode the Device Information Table when FUS is running on CPU2

- Thread
  - **ID 91267** - Fix CoAP OpenThread API exposed on application side
    - The CoAP API is now compliant with OpenThread definition and mContext parameter is then correctly returned to the application.

- Zigbee
  - Update on PICS for following clusters : Power Configuration, Diagnostics, Scenes
  - APIs renaming on the Door Lock cluster
  - Parameter range checking updates on several clusters (Power config, Door lock, Commissioning, Color)
    
</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section10" aria-hidden="true">
<label for="collapse-section10" aria-hidden="false">V1.8.0 / 22-June-2020</label>
<div>

## Main Changes

- BLE-Mesh library version 1.12.008
    - Mesh Model Client & Server Certification Passed – TCRL 2019-2
    - Management of Client Models in PRF Node project
    - Correction on Vendor message commands
    - Changes Models enabling in mesh_cfg_usr.h
      with the definition of a bitmap of 3 bits: 
      -	bit 2 element 3 
      -	 bit 1 element 2
      -	 bit 0 element 1
      
- BLE WPAN updates
    - **ID 83714** - Support of four new events to notify the CPU1 about flash operation (after aci_gap_clear_security_db())
    - **ID 83750** - PREPARE_WRITE_LIST_SIZE and MBLOCKS_COUNT in app_conf.f defined with macro
                 The macro definition is required to keep these parameters consistent with other parameters.
    - **ID 85448** - Bonding (CFG_BONDING_MODE=1) in BLE_HeartRate application
    - **ID 85782** - Option to move NVM to unsecure SRAM2
    - **ID 86573** - BLE_Ota updated to pad with 0xFF the uncomplete data to be written in flash
    - **ID 86711** - New command SHCI_C2_Config() available to configure system parameter on the CPU2
                 This command can be used to configure the NVM in either SRAM2 or Flash and
                 to mask asynchronous system events reported by the CPU2. More details in ./interface/patterns/ble_thread/shci/shci.h

- ZigBee
    - FFD Zigbee 3.0 certification compliant.
    - Support of OTA.
    - Support of persistent data management (NVM).
    - Exposure of APIs allowing access to APS layer.
    
</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section9" aria-hidden="true">
<label for="collapse-section9" aria-hidden="false">V1.7.0 / 11-May-2020</label>
<div>

## Main Changes

BLE-Mesh:

- BLE Mesh Models Fixe/Update

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section8" aria-hidden="true">
<label for="collapse-section8" aria-hidden="false">V1.6.0 / 27-March-2020</label>
<div>

## Main Changes

BLE-Mesh:

- BLE-Mesh library version 1.12.007
    - Updated for Delta level set binding to Light lightness
    - Multi Key updates.
    - Correction of FSM issues in the LC Model: no way to consume a packet internally.
    - Correction of Sensor_LC_Light_Publish sending wrong property (and LC Model handling wrong property).
    - Updates on Generic Models for Certification tests: Generic OnOff, Level, Power OnOff, Transition Time    
    - Update Multi elements support
    - Changes for DYNAMIC_PROVISIONER in Provisioner project
- New Cryptographic library v3.1.3

    
Zigbee:

- Libarry available on IAR/SW4STM32(stm32wb_zigbee_wb_lib.a) and Keil(stm32wb_zigbee_wb_lib_keil.lib)
- Support following list (47 clusters):

Cluster Number      Cluster ID      Cluster Name
------              ----------      ----------------------------------------
1	                0x0000	        Basic
2	                0x0001	        Power Configuration
3	                0x0003	        Identify6
4	                0x0004	        Groups
5	                0x0005	        Scenes
6	                0x0006	        On/Off
7	                0x0008	        Level Control
8	                0x000a	        Time
9	                0x0019	        OTA Upgrade
10	                0x0020	        Poll Control
11	                0x0021	        Green Power Proxy
12	                0x0102	        Window Covering
13	                0x0202	        Fan Control
14	                0x0204	        Thermostat User Interface Configuration
15	                0x0300	        Color control
16	                0x0301	        Ballast Configuration
17	                0x0400	        Illuminance Measurement
18	                0x0402	        Temperature Measurement
19	                0x0406	        Occupancy Sensing
20	                0x0502	        IAS Warning Device (WD)
21	                0x0b05	        Diagnostics
22	                0x1000	        Touchlink
23	                0x0002	        Device Temperature Configuration
24	                0x0007	        On/Off Switch Configuration
25	                0x0009	        Alarms
26	                0x000b	        RSSI Location
27	                0x0015	        Commissioning
28	                0x001a	        Power Profile Cluster
29	                0x0024	        Nearest Gateway Cluster
30	                0x0101	        Door Lock
31	                0x0200	        Pump Configuration and Control
32	                0x0201	        Thermostat
33	                0x0203	        Dehumidification Control
34	                0x0401	        Illuminance Level Sensing
35	                0x0403	        Pressure Measurement
36	                0x0405	        Relative Humidity Measurement
37	                0x0500	        IAS Zone
38	                0x0501	        IAS Ancillary Control Equipment (ACE)
39	                0x0700	        Price
40	                0x0701	        Demand Response and Load Control
41	                0x0702	        Metering
42	                0x0703	        Messaging
43	                0x0704	        Smart Energy Tunneling (Complex Metering)
44	                0x0800	        Key Establishment
45	                0x0904	        Voice Over ZigBee
46	                0x0b01	        Meter Identification
47	                0x0b04	        Electrical Measurement


</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section7" aria-hidden="true">
<label for="collapse-section7" aria-hidden="false">V1.5.0 / 22-January-2020</label>
<div>

## Main Changes

Interface:

-	Added new commmand SHCI_C2_SetFlashActivityControl() to configure BLE timing protection

Zigbee:

- Support of the following Zigbee clusters:
    - Basic
    - On/Off
    - Device Temperature Configuration
    - Identify
    - Power Profile
    - Thermostat-UI-Config
    - Ballast-Configuration
    - Illuminance-Measurement
    - Temperature Measurement
    - Pressure Measurement
    - Occupancy-Sensing
    - Messaging
    - Meter Identification

BLE-Mesh:

- BLE-Mesh library version 1.12.000
    - Embedded Provisioner example added including config-client
    - Multi Net Key support has been added(limited to 2 Net Keys)
    - Key Refresh updated for Multiple Keys
    - Vendor Model updated to add Read and Write messages
    - TID check added in the firmware
    - Light_LC sensor property updated
    - Generic Power OnOff Message updated
    - Multi elements support limited to 3


</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section6" aria-hidden="true">
<label for="collapse-section6" aria-hidden="true">V1.4.0 / 22-November-2019</label>
<div>

## Main Changes

Interface:

-	Added new commmand SHCI_C2_ExtpaConfig() to support external PA
-	Update System and BLE transport layer so that a user event packet is released by default

BLE:

-	Added support to ACI_GATT_READ_EX_EVENT
-	Added macro HCI_LE_ADVERTISING_REPORT_RSSI_0(p) to extract properly RSSI from the event packet


</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section5" aria-hidden="true">
<label for="collapse-section5" aria-hidden="true">V1.3.0 / 4-September-2019</label>
<div>

## Main Changes

General:

-   Introducing support of Zigbee 

Interface:

-	Cleanup inclusion file dependencies
-	Fix local buffer size used in command SHCI_C2_FUS_StoreUsrKey()
-	ble user events are now reported one by one (hci_notify_asynch_evt is called for each packet reported)
-	system users event are now reported one by one (shci_notify_asynch_evt is called for each packet reported)

Zigbee:

- 	First release supporting Zigbee (FFD :Full Function Device)
-	Supporting only On/Off Cluster

BLE-Mesh:

-	BLE-Mesh library version 1.10.004
	-	Light LC Controller state machine for Occupancy detection is implemented
	-	Light LC Controller state machine for Ambient Lux Level is implemented 
	-	Light LC Server Mode messages added
	-	Light LC Server Occupancy Mode messages added
	-	Light LC Server Property messages added
	-	Save State in NVM controlled by Macro ENABLE_SAVE_MODEL_STATE_NVM
	-	Mode of Save State in NVM selected by Macro SAVE_MODEL_STATE_FOR_ALL_MESSAGES and SAVE_MODEL_STATE_POWER_FAILURE_DETECTION
	-	Generic Power OnOff message added
	-	Generic Power OnOff Setup message added
	-	Generic Default Transition Time message added

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section4" aria-hidden="true">
<label for="collapse-section4" aria-hidden="true">V1.2.0 / 27-June-2019</label>
<div>

## Main Changes

General:

-   Following utilities : Scheduler and Low Power Manager reworked and moved to "Utilities" directory
-	Split tl_if.c into hci_tl_if.c (BLE) and shci_tl_if.c (System) to remove dependencies to the BLE library when the application is built on top of HCI.

BLE:

- 	Add 2 new GATT events: aci_gatt_indication_event_rp0 and aci_gatt_notification_event_rp0
-	Rework BLE folder architecture to separate the Core from the Services implementation
-	Mesh library V1.10.000:
	- 	Sensors Model example updated 
	-	Sensor data publishing updated 
	-	PB-ADV implementation added 
	-	APIs to control frequency of unprovisioned device beacon, secure network beacon, provisioning service advertisement and proxy service advertisement 
	-	Node unprovision on 5 consecutive Power Replug or Reset cycle with duration of each cycle(ON) less than 2 seconds 
	-	SIG Models handling optimized 
	-	printf statement is replaced with TRACE_M(Function name print) and TRACE_I in application code 

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section3" aria-hidden="true">
<label for="collapse-section3" aria-hidden="true">V1.1.1 / 10-May-2019</label>
<div>

## Main Changes

BLE:

-	Fix race condition in transport layer when an operating system is used.
-   Mesh Library V1.09.000:
	-	Fix of the BD Address issue.
	-	Light HSL Model implementation.
	-	Sensor Server Model Example.
	-	CID, PID Configuration.
-	STM32 Cryptographic Library V3.1.1/ 20 April 2018:
	-	Two new STM32 Cryptographic Libraries provided for IAR Embedded Workbench for ARM (EWARM) Toolchain v8.22:
		-	**STM32CryptographicV3.1.1_CM4_IARv8.a**: First official release of optimized STM32 Cryptographic Library for ***Cortex M4*** with ***High size*** optimization.
		-	**STM32CryptographicV3.1.1_CM4_IARv8_otnsc.a**: First official release of optimized STM32 Cryptographic Library for ***Cortex M4*** with ***High speed*** optimization and the option ***No Size constraints*** is enabled.
-	STM32 Cryptographic Library V3.0.0/ 05 June 2015:
	-	Two STM32 Cryptographic Libraries provided for each Development Toolchain:
		-	IAR Embedded Workbench for ARM (EWARM) toolchain v7.40:
			-	**STM32CryptographicV3.0.0_CM4_IAR.a**: New official release of optimized STM32 Cryptographic Library for ***Cortex M4*** with ***High size*** optimization.
			-	**STM32CryptographicV3.0.0_CM4_IAR_otnsc.a**: First official release of optimized STM32 Cryptographic Library for ***Cortex M4*** with ***High speed*** optimization and the option ***No Size constraints*** is enabled.
		-	RealView Microcontroller Development Kit (MDK-ARM) toolchain v5.14:
			-	**STM32CryptographicV3.0.0_CM4_KEIL_slsm1elfspf.lib**: New official release of optimized STM32 Cryptographic Library for ***Cortex M4*** with ***High size*** optimization.
			-	**STM32CryptographicV3.0.0_CM4_KEIL_otslsm1elfspf.lib**: First official release of optimized STM32 Cryptographic Library for ***Cortex M4*** with ***High speed*** optimization and the option ***Split Load and Store Multiple*** and ***One elf Section per Function*** are enabled.
		-	Atollic TrueSTUDIO STM32 (TrueSTUDIO) toolchain v5.3.0:
			-	**STM32CryptographicV3.0.0_CM4_GCC.a**: First official release of optimized STM32 Cryptographic Library for ***Cortex M4*** with ***High size*** optimization.
			-	**STM32CryptographicV3.0.0_CM4_GCC_ot.a**: First official release of optimized STM32 Cryptographic Library for ***Cortex M4*** with ***High speed*** optimization.

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section2" aria-hidden="true">
<label for="collapse-section2" aria-hidden="true">V1.1.0 / 29-March-2019</label>
<div>

## Main Changes

General:

-   Licenses in utilities and patterns moved from sla0044 to 3-clauses  BSD
-   Customer Key Storage APIs
-   Get Wireless Coprocessor Firmware information using following API : SHCI\_GetWirelessFwInfo()

BLE:

-   New BLE Mesh lib to fix provisioning issue

Thread:

-	802.15.4 radio driver robustness improvement with additional error checks; the application is now notified in case of radio error
    detected inside the wireless binary
-	TxPower management improvement:
	-   New APIs provided to control the Tx power: otPlatRadioGetTransmitPower() and otPlatRadioSetTransmitPower()
	-	The default Tx power is now set to 0dBm\

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section1" aria-hidden="true">
<label for="collapse-section1" aria-hidden="true">V1.0.0 / 31-January-2019</label>
<div>			

## Main Changes

First release

</div>
:::


For complete documentation on STM32WBxx, visit:
\[[www.st.com/stm32wb](http://www.st.com/stm32wb)\]
:::
:::
