# !! PLEASE AVOID USING 5V ON THE MODULE!!

You shouldn't use USB-UART module as a 5v pin header power supply. It does not output enough current sometimes. Do so could fry your computer's motherboard or USB port!! 

# YOU DON'T NEED DRIVER for the most time

Windows should install module through windows update. And if you had working on some arduino before (for example ELEC299 robot), your computer could already had the driver. However if windows update fuck you up, feel free to use the driver includes.
 
For Linux, it should show on /dev as TTYUSB somehow. 

# Dip switch for USB to UART dongle

TTL mode should be used when trying to connect Dev board to computer or upper computer. (In most case this is the use case)

![](https://github.com/sikaxn/QRMWiki/blob/master/IMG/usb-uart%20dongle%20mode.jpg)
