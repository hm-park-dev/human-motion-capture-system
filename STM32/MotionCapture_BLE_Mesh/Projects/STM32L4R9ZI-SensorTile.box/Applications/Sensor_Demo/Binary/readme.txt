In these folders, compiled images of the firmware are provided, in order to allow the user to test the application in a quick and easy way.

- Install ST-LINK drivers: http://www.st.com/web/en/catalog/tools/FM146/CL1984/SC720/SS1450/PF251168   
- On the Nucleo board put JP5 jumper in U5V position 

The binaries are provided in .bin format and can be flashed into the micro-controller flash memory using one of the procedures described below. 


- Procedure 1 (.hex and .bin) -

 1 - Install ST-LINK Utility: http://www.st.com/web/en/catalog/tools/FM146/CL1984/SC720/SS1450/PF251168.
 2 - Plug the Sensortile.box with ST-Link/v2 to the host PC.
 3 - Open the ST-LINK utility.
 4 - Set the "Connect Under Reset" Mode selecting "Target -> Settings" from the menu.
 5 - Connect to the board selecting "Target -> Connect" from the menu or pressing the corresponding button.
 6 - Open the binary file selecting "File -> Open File..." and choose the one you want to flash.
 7 - From the menu choose: "Target -> Program"
 8 - Check the Start address, it must be equal to 0x08000000.
 9 - Check the box "Reset after programming"
10 - Click Start.
11 - Wait until flashing is complete.

Description of Binary files
---------------------------
1. Sensor-STBOX : This binary uses static random address of the controller to generate MAC address for Sensortile.box.
                        

Note: a. Uncomment EXTERNAL_MAC_ADDR_MGMT in mesh_usr_cfg.h file for external MAC address.
         Some examples of MAC address are available from Utilities\STM32L4_MAC 
      b. When using external MAC address, it is recommended to firstly program the generated binary after uncommenting EXTERNAL_MAC_ADDR_MGMT and then 
	 program the MAC address Utilities\STM32L4_MAC
      b. Uncomment INTERNAL_UNIQUE_NUMBER_MAC in mesh_cfg.h file for Internal Unique Number. 



 