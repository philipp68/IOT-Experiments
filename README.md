# IOT-Experiments
To keep track of all my experiments with different hardware and software, I created this repository that contains a couple of "how-to" guides.

## Raspberry Pi
### Raspberry Pi Zero W 1.1
These are the steps to set up headless Pi (setting it up without attaching a keyboard or a HDMI screen to it).
#### Setting up SD Card
* Download Raspian Strech Lite https://www.raspberrypi.org/downloads/raspbian/
* User Etcher (https://etcher.io/) to burn image to SD card
##### Enabling Wi-Fi and SSH on your SD card
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
