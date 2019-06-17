# Wifi-Mini-Doorbells

This is a project page to investige the very low cost chinese wifi camera doorbells that are available on the market.  With the long term goal to be able to reflash the hardware or reverse engineer them in someway to improve the software and make then usual for home automation and IOT.

## Example Device Links

https://www.amazon.co.uk/Smart-Wireless-Doorbell-Camera-Plug/dp/B074X5V743/ref=lp_7187472031_1_15?srs=7187472031&ie=UTF8&qid=1511989879&sr=8-15

https://www.amazon.co.uk/Vstarcam-Doorbell-Digital-Doorcam-Andorid/dp/B074TD9C63/ref=sr_1_10?ie=UTF8&qid=1511992073&sr=8-10&keywords=wifi+doorbell+camera

## Product Videos

https://www.youtube.com/watch?v=jitsaQnD0uc


### Door Press
Main doorpress button unit uses 2-4 AAA or AA batteries and houses the camera.

Standby ~58uA

Transmit ~70mA ~5sec

Voltage cutoff seems to be ~2.4V so 0.6V per cell.  Although LED's cease to flash at this level as below forward voltage of blue/white leds. But image is still sent over 2.4Ghz radio without fault in tests.

Based on the above numbers Door press could easily last over 1 year depending on number of visitors and batteries used.

Door press to base unit comms is via a deadicated 2.4Ghz  (non wifi) radio.

More investigation is needed but seems comms is 2 way as door press beeps an error if base unit is offline.


### Reciever/Bell/Base Unit.

Base unit uses a 2.4GHz radio and an ESP8285 unit.  The power supply comms from a seperate board which is then joined over to the main unit.

Board Markings: GWIFI-RF-V1.1 

2.4Ghz Reciever BK2425 http://www.bekencorp.com/en/Botong.Asp?Parent_id=2&Class_id=8&Id=87



### Software and Backend

Android app sesms to be called "Mini Doorbells" https://play.google.com/store/apps/details?id=com.Millinkmini.ismartandroid2

This is where the system gets worrying.  From info so far it appears that the images are sent to some cloud service where they are stored and retrived by the APP.  Location of these servers will need to be investigated and possibly the security of the images as well.  App is requested far more permission than needed to connect to a server and display an image.  This is a concern.  

## Ideal Version

In an ideal mod these devices would be flashed so that all traffic and image storage happens to a local FTP/NAS or other storage device.  From there a home automation system could pickup the image and notify.  Ultimately there should be no need for the image to go via a 3rd party or unknown service.  The use should be able to setup the server be it local or dropbox or other service of there choosing.  Some sort of MQTT pub/sub notification would also be ideal.  


## door_bell_server

The attached c program is build to spoof the remote server.  It listens on TCP/39090 and needs DNS spoofing to redirect the domain name minidoorbell.guogee.com to the servers ip address.  Once running it will create a image for each visitor in /tmp/vistor_%Y%m%dT%H%M%S.jpg

It is very much a POC but does capture images although they are currently upside down.

Your doorbell may resolve a different address.







## TODO
* Hands on Test in Safe Network - COMPLETED
* Hardware Teardown and photos - TO UPLOAD
* Circuit Traces  
* IC identification
* Protocol Capture - DONE
* Protocal Analysys - PART DONE
* Current Draw  - COMPLETED
* Wifi Packet Traces - DONE
* Remote Server Investigation  
* Mains unit safety



## Support

If anyone else has the skills and interest in these devices then please contribute I am by no means an expert but just have a n interest in IOT. These little doorbells just perked my interest as are only $30/£20 and having considered building a similar unit myself these seem far better if can be understood and implemented securely as come pre build with nice boxes and mains wireing etc handled.   
