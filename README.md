![Meow with the smart paw!](https://meow.build/assets/images/meow-poster.png "Meow with the smart paw!")


# Meow — the Slack Bot with the smart paw.
Meow is a little modified Maneki-neko. At first sight, she looks like any other happy lucky cat but once she’s connected to a WiFi network and integrated to your Slack environment, Meow starts to wave directly after you’ve received a Slack message.


### Setup:
This project was built with the PlatformIO IDE. So, I recommend you to install the PlatformIO extension for Visual Studio Code before you start.

#### Soft Access Point:
You can find the WiFi credentials for the initial soft access point in the /data folder. After a successful upload to your ESP32, 'Meow' will appear in your WiFI network list.

```json
{"wifi_ssid" : "Meow", "wifi_pass" : "smartpaw"}
```

#### Soft Access Point Network IP: 
Once connected with 'Meow', open up your browser and type

```
76.76.76.76
```
Now you'll be asked to enter your network credentials in order to connect Meow with the internet.
> Note: During the reboot process, Meow is going to redirect you to

#### Multicast DNS:
Since I'm using the ESP32 Multicast DNS library
```
meow.local/
```

-> After you've entered your credentials, the esp redirects / reboots -> meow.local (make sure you're now connected to your network)

#### Slack SSL fingerprint:
If you need to update the Slack SSL fingerprint run:
```
openssl s_client -connect slack.com:443 < /dev/null 2>/dev/null | openssl x509 -fingerprint -noout -in /dev/stdin | sed 's/:/ /g' | cut -d '=' -f 2
```
and update the fingerprint in the 'common.h'




![76.76.76.76 & meow.local/](https://meow.build/assets/images/meow-interface.png "76.76.76.76 & meow.local/")

#### API token:
https://yourworkspace.slack.com/apps/A0F7YS25R-bots
