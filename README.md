# Wifi-Mini-Doorbells

This is a project page to investige the very low cost chinese wifi camera doorbelbs that are available on the market.  With the long term goal to be able to reflash the hardware or reverse engineer them in someway to improve the software and make then usual for home automation and IOT.

## Example Device Links

https://www.amazon.co.uk/Smart-Wireless-Doorbell-Camera-Plug/dp/B074X5V743/ref=lp_7187472031_1_15?srs=7187472031&ie=UTF8&qid=1511989879&sr=8-15

https://www.amazon.co.uk/Vstarcam-Doorbell-Digital-Doorcam-Andorid/dp/B074TD9C63/ref=sr_1_10?ie=UTF8&qid=1511992073&sr=8-10&keywords=wifi+doorbell+camera

## Product Videos

https://www.youtube.com/watch?v=jitsaQnD0uc


## Initial Notes
These are initial thoughts based on available photos and videos online

### Door Press
Main doorpress button unit uses 2-4 AAA or AA batteries and houses the camera. 

Based on stated battery life assuming accurate this means the IC muct have a low power sleep in order uA 

From demos it is not believed that the Door press has any Wifi radio and instead is probably linked via some other 2.4Ghz radio module to the Reciver/Bell Unit.  Hopefully something like an nrf24l01 which is well known in the maker space.

Would expect 2 radio transmissions to take place.  An inital press signal then and second burst which will be the raw or processed data from the cmos sensor.  May be some form of handshakes and confirmation buit from review the image isn't always reliable so may just be a fire and forget system with no feedback.


### Reciever/Bell Unit.
This houses a speaker of some sort to make the ding dong sound.  Has a reciever for the signal from the door press.  And is beleived to house the actual Wifi Radio unit.  Hopefully an ESP but probably not that lucky.  

### Software and Backend

Android app sesms to be called "Mini Doorbells" https://play.google.com/store/apps/details?id=com.Millinkmini.ismartandroid2 

This is where the system gets worrying.  From info so far it appears that the images are sent to some cloud service where they are stored and retrived by the APP.  Location of these servers will need to be investigated and possibly the security of the images as well.  App is requested far more permission than needed to connect to a server and display an image.  This is a concern.  

## Ideal Version

In an ideal mod these devices would be flashed so that all traffic and image storage happens to a local FTP/NAS or other storage device.  From there a home automation system could pickup the image and notify.  Ultimately there should be no need for the image to go via a 3rd party or unknown service.  The use should be able to setup the server be it local or dropbox or other service of there choosing.  Some sort of MQTT pub/sub notification would also be ideal.  


## TODO
* Hands on Test in Safe Network
* Hardware Teardown and photos
* Circuit Traces
* IC identification
* Protocol Capture
* Protocal Analysys
* Current Draw
* Wifi Packet Traces
* Remote Server Investigation
* Mains unit safety



## Support

If anyone else has the skills and interest in these devices then please contribute I am by no means an expert but just have a n interest in IOT. These little doorbells just perked my interest as are only $30/£20 and having considered building a similar unit myself these seem far better if can be understood and implemented securely as come pre build with nice boxes and mains wireing etc handled.   
