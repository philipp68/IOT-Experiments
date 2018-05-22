# IOT-Experiments
To keep track of all my experiments with different hardware and software, I created this repository that contains a couple of "how-to" guides.

## Raspberry Pi
### Raspberry Pi Zero W 1.1
These are the steps to set up headless Pi (setting it up without attaching a keyboard or a HDMI screen to it).
#### Setting up SD Card
* Download Raspian Strech Lite https://www.raspberrypi.org/downloads/raspbian/
* User Etcher (https://etcher.io/) to burn image to SD card
#### Enabling Wi-Fi and SSH on your SD card
* Open your favorite terminal and navigate to your SD card (it should contain a single partition called boot)
* Create a new text file and call it wpa_supplicant.conf
* Copy this text into the file and replace ssid and psk with your own Wi-Fi ssid and psk
```
country=GB
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1

network={
    ssid="MyWiFiNetwork"
    psk="password123"
}
```
* If you have more than one Wi-Fi network that you want to add, for instance home and work, then you can simply duplicate that whole block of text, change the SSID and PSK, and add it to the bottom of that file. Save the file.
* To enable ssh create a completely blank file with the filename ssh, ensuring that there's no extension. Save it in that same boot partition.
* Eject the SD card from your computer, pop it into your Pi, and plug in the power.
#### Connect to your Pi
* Your Pi will get an IP address and have a hostname assigned to it
* You can use an IP scanner like Angry IP or Fing to find out your Pi's address, or you can use the hostname instead
* Connect to your Pi using ssh (raspberry is the default password in Raspbian)
```
ssh pi@raspberrypi.local
```
* To shutdown your Pi, simply type sudo shutdown -h now, or press control and d if you want to disconnect but leave your Pi running.
* Note that if you have a program running over SSH and you disconnect, then the program will likely stop as soon as you disconnect. The best way round this is to use screen, but we'll save that for another tutorial!
