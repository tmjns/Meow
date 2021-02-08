![Meow with the smart paw!](https://meow.build/assets/images/meow-poster.png "Meow with the smart paw!")


# Meow — the Slack Bot with the smart paw.
Meow is a little modified Maneki-neko. At first sight, she looks like any other happy lucky cat but once she’s connected to a WiFi network and integrated to your Slack environment, Meow starts to wave directly after you’ve received a Slack message.


### How to setup: 
You can find the settings.json with the WiFi credentials for the inital soft access point in the /data folder.

```json
{"wifi_ssid" : "Meow", "wifi_pass" : "smartpaw"}
```

Soft AP network parameters 
```
76.76.76.76
```

If you need to update the Slack SSL fingerprint run:
```
openssl s_client -connect slack.com:443 < /dev/null 2>/dev/null | openssl x509 -fingerprint -noout -in /dev/stdin | sed 's/:/ /g' | cut -d '=' -f 2
```
Copy and paste:

```c++
#define SLACK_SSL_FINGERPRINT "C10D5349D23EE52BA261D59E6F990D3DFD8BB2B3"
```
