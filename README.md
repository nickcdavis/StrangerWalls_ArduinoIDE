# Stranger Wall (esp8266 receiver)

Receive messages from the Stranger Wall MeteorJS Sender! This project will:
* Run off most (any?) esp8266 microcontrollers that can execute ArduinoIDE code
* Connect to your wifi network 
* Receive data from your MeteorJS app
* Summon the Demogorgon (jk! Maybe v2)

Please note that this is just one part of the entire project. For more information on other steps, please view the project details at Hackster.io!

## Getting Started
This project is pretty straightforward. If you choose to use code as-is, all you will need to do is add your wifi info, and point the device to your MeteorJS app. If you run into any trouble however, please reach out!

## Materials Needed
* An esp8266 device (Such as an Adafruit Feather HUZZAH ESP8266)
* 2x 50pcs [WS2811 RGB Full Color 12mm Pixels digital Addressable LED String](https://www.amazon.com/Diffused-Digital-Pixels-Lights-Addressable/dp/B00B4UKG2W/ref=sr_1_4?ie=UTF8&qid=1508537139&sr=8-4&keywords=ws2811)
* 5v Power Supply
* [Cardstock, Black](https://www.amazon.com/gp/product/B008734L34/ref=oh_aui_detailpage_o02_s00?ie=UTF8&psc=1)

### Step One: Download Code
```
git clone https://github.com/nickcdavis/StrangerWalls_ArduinoIDE.git
```

### Step Two: Get your esp8266 Device Set Up
If you haven’t already, you will need to get your device set up to use Arduino IDE. Adafruit [has great instructions for this](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/overview), especially if you are using their Feather HUZZAH.

###	Step Three: Open Code and Modify Some Stuff
There are a few variables you have to set in order to get your device talking to the MeteorJS app. This includes some wifi parameters, as well as the website address in which your MeteorJS app is hosted:
```
const char* ssid     = “[YOUR_HOME_NETWORK]“;
const char* password = “[YOUR_HOME_NETWORK_PASSWORD“;
const char* host = “[YOUR_METEORJS_APP_URL]“;
```

Also, you will find a variable called “letterIndex’. This maps your letters to a light, hyphens represent empty lights. In my configuration I space mine out a couple letters apart, but you can really configure it however you like.

### Step Four: Upload Code to Device
Open the .ino file in ArduinoIDE, make sure your device is plugged in, and click “Upload”. Once uploaded, you will have a couple indications that it worked. First, the onboard light will flash, indicating that it is trying to connect to WiFi. When it connects, it should remain on.

If everything seems to check out using the serial window, unplug the device.

### Step Five: Hook up WS2811 Lights to Device
You only need to attach wires to two pins. Ground, and Data 2. Take a look at the image below:

![Pin it up](https://lh3.googleusercontent.com/sgbbXNOph_-dlSx7Bk37EDr_3ae9mueUQor2u12uWS6-4opbNLpc4PXA9a-pvkd8mcZ4eCpk_1PpP76vyhC2njlmRRr4J_hTDXofvwUErYDpTy6ScWeAZw3pcXxUxj82gBDIOV8nyY3Tn_IPMvyLSC7VREhU6wl4zHgTICBI56lbt7MbehqBpjnYxpC37QilPwzGPuoD2mknHc5XYL0DXRKdZRM11vt4aVT6dxchxOvLrzF2SFkM0Ml2QUR8-FUQGnSPael7wcv5548YUFHIkr5zgVu-VrPlLRQebaX27hD0O3Dtq2x7L4y6_zz3z38sECGO87O2-4pO4_a7RAFAjs-fEFU7ZzPSih1JCsvPdXoKfD83wEtdf3NmLn2qGGjFdrRFcz5A1e77P6iu2nGFhwvV5O3VaDwkPeSKqfPa7CSG6m1WHP2ne7HD8TX_PhWCcxsqwsedVVBWi8qenuGL1CQwirLA9FeIWPcQ_OhQzqQV3MempAls9-unqruPHf1oKfx0Jtt66umYJBNYE52ckPfTqBY-aU3yjj7SLJWnQ5gOcUPY1marPFyQgyKvml1ZTar3yhSwkfhSMXe2NaYxVxFUCJNx27p1tr6aXCgftfF4KschZKpfmUJSTS8TZqT7Zvp8diNx7xDxa8KQsQ2lVjx3dF-WzXF_vO-2=w832-h624-no?raw=true)

### Step Six: Test the Lights
From here, plug in the lights into a 5v power supply. The lights should turn on. Then, plug the device into your computer again. Wait a little bit and the lights should flicker eerily and then stay on.

Once the device connects to WiFi, open up your MeteorJS app and type in a test message. Keep your eyes on the lights and wait a little bit. You’ll know if its working as it will start flickering eerily once again and then flash LEDs corresponding to your message. Great job!

### Step Seven: Get Crafty, Cut Out Some Letters
For this step, I opted to use black card stock and printed letter outlines on them in black ink. It’s a little hard to see, but definitely enough to give you a point of reference for when you cut them out. 

Once all of your letters are cut, add them to a wall of your choice and hang your lights above the letters Stranger Things Style. Depending on the spacing of your letters, you may have to adjust your letter spacing using the “letterIndex” variable in the Arduino Code.

## Author
Nick Davis

Email: nick@nicholasdavis.info

Twitter: @armaexmachina

Instagram: armageddonmachine

## Acknowledgements
Shoutout to Leonardy Kristianto for his amazing [Heroku Instructions](https://medium.com/@leonardykris/how-to-run-a-meteor-js-application-on-heroku-in-10-steps-7aceb12de234)
