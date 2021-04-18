![Meow with the smart paw!](https://miro.medium.com/max/1400/1*yKEke4YjMCd7ZJ4FutNlcQ.gif "Meow with the smart paw!")

Meow — the Slack Bot with the smart paw.
----------------------------------------
Meow is a little modified Maneki-neko. At first sight, she looks like any other happy lucky cat but once she’s connected to a WiFi network and integrated to your Slack environment, Meow starts to wave directly after you’ve received a Slack message.

Setup
-----
This project was built with the PlatformIO IDE. I recommend you to install the PlatformIO extension for Visual Studio Code before you start. Clone this repo and open the ```src``` folder.

SPIFFS
------
Upload all files from the ```data``` folder running this command via PlatformIO Core CLI:
```
pio run -t uploadfs
```

Soft Access Point
-----------------
You'll find the WiFi settings for the initial soft access point in the ```data``` folder. After a successful build and upload, 'Meow' will appear in your WiFi network list.

```json
{"wifi_ssid" : "Meow", "wifi_pass" : "smartpaw"}
```

Network IP
----------
Once connected with 'Meow', open up your browser and type:

```
76.76.76.76
```
You'll be asked to enter your network credentials to connect Meow with your network.
> Note: During the save and reboot process, the browser performs a redirect to 'meow.local/'. In some cases, if there is no WiFi connection, your browser will display an error screen... Double-check your WiFi connection and reload the page.

Multicast DNS
-------------
Open the URL:
```
meow.local/
```
Now you need to enter your API token to create a connection to your Slack environment. Choose a specific User-ID you want to listen for.
> Note: Since I'm using the ESP32 Multicast DNS library, you might get some trouble using this website on mobile devices.

API token
---------
You need to create a custom Slack app integration to generate the necessary API token. For help check out the link below:
[https://yourworkspace.slack.com/apps/A0F7YS25R-bots](https://yourworkspace.slack.com/apps/A0F7YS25R-bots)

Slack User-ID
-------------
The simplest way to find your specific User-ID is to follow these steps:
[https://moshfeu.medium.com/how-to-find-my-member-id-in-slack-workspace-d4bba942e38c](https://moshfeu.medium.com/how-to-find-my-member-id-in-slack-workspace-d4bba942e38c)

Usage
-----
![Meow with the smart paw!](https://miro.medium.com/max/1080/1*Ce81ZzjCN6fMHqInYjiUMA.gif "Meow with the smart paw!")

Every time you receive a message in a Slack channel, Meow is listening to your predefined User-ID. Teammate mention (Meow starts waving): 
```"Hi @Tom how are you doing?"``` Reaction to the message (Meow stops waving): ```:+1:```

Troubleshooting
---------------
<details>
<summary>Espressif 32 (1.11.2)</summary>
<p>Make sure you're using the 1.11.2. version of the Espressif 32 platform in your environment. Other versions could cause some errors.</p>  
</details>

<details>
<summary>Slack SSL Fingerprint</summary>
<p>If you need to update the Slack SSL fingerprint run (MacOS terminal):</p>

openssl s_client -connect slack.com:443 < /dev/null 2>/dev/null | openssl x509 -fingerprint -noout -in /dev/stdin | sed 's/:/ /g' | cut -d '=' -f 2

</details>
  
<details>
<summary>meow.local/ not working</summary>
<p>Check the list of your connected devices in your router settings and connect via the IP address. 
</p>  
</details>
