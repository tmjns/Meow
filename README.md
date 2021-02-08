![Meow with the smart paw!](https://meow.build/assets/images/meow-poster.png "Meow with the smart paw!")


# Meow — the Slack Bot with the smart paw.
Meow is a little modified Maneki-neko. At first sight, she looks like any other happy lucky cat but once she’s connected to a WiFi network and integrated to your Slack environment, Meow starts to wave directly after you’ve received a Slack message.


### Setup: 
You can find the WiFi credentials for the inital soft access point in the /data folder.

#### settings.json
```json
{"wifi_ssid" : "Meow", "wifi_pass" : "smartpaw"}
```

#### Soft AP network IP: 
```
76.76.76.76
```

#### Slack SSL fingerprint:
If you need to update the Slack SSL fingerprint run:
```
openssl s_client -connect slack.com:443 < /dev/null 2>/dev/null | openssl x509 -fingerprint -noout -in /dev/stdin | sed 's/:/ /g' | cut -d '=' -f 2
```
and update the fingerprint in the 'common.h'


#### Multicast DNS
Since I'm using the ESP32 Multicast DNS library
```
meow.local/
```

![76.76.76.76 & meow.local/](https://meow.build/assets/images/meow-interface.png "76.76.76.76 & meow.local/")
