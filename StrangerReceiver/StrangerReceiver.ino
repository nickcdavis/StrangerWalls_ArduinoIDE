#include <b64.h>
#include <HttpClient.h>
#include <ESP8266WiFi.h>
#include "FastLED.h"

#define NUM_LEDS 100
#define DATA_PIN    2
#define BRIGHTNESS  255

CRGB leds[NUM_LEDS];

const String letterIndex = "A--B--C--D--E--F--G--H--I--J--K--L--M--N--O--P--Q--R--S--T--U--V--W--X--Y--Z----------------------";
const String colorLetterIndex = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char* ssid     = "";
const char* password = "";
const char* host = "";
const char* url = "/nextMessage";

// Number of milliseconds to wait without receiving any data before we give up
const int kNetworkTimeout = 30 * 1000;
// Number of milliseconds to wait if no data is available before trying again
const int kNetworkDelay = 1000;

// Warm White = 0xFFF0C4
// Blue = 0x0000FF
// Magenta = 0xFF00FF
// Cyan = 0x00FFB9
// Yellow = 0xFCEE21
// Red = 0xFF0000

uint32_t colorIndex[26] = {
  0xFFF0C4, // A
  0x0000FF, // B
  0xFF00FF, // C
  0x00FFB9, // D
  0x0000FF, // E
  0xFCEE21, // F
  0xFF0000, // G
  0x00FFB9, // H
  0x00FFB9, // I
  0xFF00FF, // J
  0x0000FF, // K
  0x00FFB9, // L
  0xFCEE21, // M
  0xFF0000, // N
  0xFF00FF, // O
  0x00FFB9, // P
  0xFF00FF, // Q
  0x00FFB9, // R
  0xFFF0C4, // S
  0xFCEE21, // T
  0x0000FF, // U
  0xFF0000, // V
  0x00FFB9, // W
  0xFCEE21, // X
  0xFF00FF, // Y
  0xFF0000, // Z
};

void setup() {
  Serial.begin(9600);
  delay(10000);
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  flickerLeds(25);
  turnOnAll();

  setupWifi();
}

void loop() {
  httpGet();
  delay(2000);
}

void httpGet()
{
  int err = 0;

  WiFiClient client;
  HttpClient http(client);

  err = http.get(host, url);
  if (err == 0)
  {
    err = http.responseStatusCode();
    if (err >= 0)
    {
      err = http.skipResponseHeaders();
      if (err >= 0)
      {
        blinkBoardLED();

        int bodyLen = http.contentLength();

        unsigned long timeoutStart = millis();
        char c;
        String compiledResult;
        bool isBody;
        isBody = false;

        while ( (http.connected() || http.available()) &&
                ((millis() - timeoutStart) < kNetworkTimeout) )
        {
          if (http.available())
          {
            c = http.read();
            if (c == '\r')
            {
              isBody = !isBody;
            }
            if (isBody)
            {
              compiledResult += c;
            }
            bodyLen--;
            timeoutStart = millis();
          }
          else
          {
            delay(kNetworkDelay);
          }
        }
        compiledResult.trim();
        compiledResult.toUpperCase();
        if (compiledResult != "")
        {
          flickerLeds(50);
          writeWord(compiledResult, 1300, 300);
          delay(2000);
          turnOnAll();
        }
      }
      else
      {
        Serial.println("Failed to skip response headers: " + err);
      }
    }
    else
    {
      Serial.println("Getting response failed: " + err);
    }
  }
  else
  {
    Serial.println("Connect failed: " + err);
  }
  http.stop();
}

void setupWifi() {
  delay(1000);
  Serial.println("Connecting to: " + String(ssid));

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    blinkBoardLED();
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Connected to " + String(ssid) + " | IP " + WiFi.localIP());
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
}

void blinkBoardLED()
{
    delay(250);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
}

void turnOnAll()
{
  int stringLen = letterIndex.length() + 1;
  char char_array[stringLen];
  letterIndex.toCharArray(char_array, stringLen);
  for (int i = 0; i < stringLen - 1; i++)
  {
    if ( String(char_array[i]) != "-" )
    {
      turnOnLetter(String(char_array[i]));
    }
  }
  FastLED.show();
}

void allToFullBright()
{
  int stringLen = letterIndex.length() + 1;
  char char_array[stringLen];
  letterIndex.toCharArray(char_array, stringLen);
  for (int i = 0; i < stringLen - 1; i++)
  {
    if ( String(char_array[i]) != "-" )
    {
      leds[i].maximizeBrightness();
    }
  }
  FastLED.show();
}

void turnOnLetter(String theLetter)
{
  int lightIndex = letterIndex.indexOf(theLetter);
  int colorIndexValue = colorLetterIndex.indexOf(theLetter);
  uint32_t colorValue = colorIndex[colorIndexValue];
  leds[lightIndex] = colorValue;
}

void writeWord(String theword, int letterDuration, int letterSpacing)
{
  Serial.println("writeWord: " + theword);
  int stringLen = theword.length() + 1;
  char char_array[stringLen];
  theword.toCharArray(char_array, stringLen);
  for (int i = 0; i < stringLen - 1; i++)
  {
    displayLetter(String(char_array[i]), letterDuration);
    delay(letterSpacing);
  }
}

void displayLetter(String theLetter, int letterDuration)
{
  int lightIndex = letterIndex.indexOf(theLetter);
  int colorIndexValue = colorLetterIndex.indexOf(theLetter);
  uint32_t colorValue = colorIndex[colorIndexValue];
  lightLED(lightIndex, colorValue, letterDuration);
}

void lightLED(int ledIndex, uint32_t colorValue, int duration)
{
  // Turn the LED on, then pause
  leds[ledIndex] = colorValue;
  FastLED.show();
  delay(duration);
  // Now turn the LED off, then pause
  leds[ledIndex] = CRGB::Black;
  FastLED.show();
}

void flickerLeds(int numTimes)
{
  turnOnAll();
  for ( int i = 0; i < numTimes; i++)
  {
    flicker();
  }
  allToFullBright();
  fill_solid( leds, NUM_LEDS, CRGB::Black);
  delay(2000);
}

void flicker() {
  int random_bright = random(0, 255);
  int random_delay = random(10, 100);
  int randomFullLight = random(0, 2);
  int stringLen = letterIndex.length() + 1;
  char char_array[stringLen];
  letterIndex.toCharArray(char_array, stringLen);
  for (int i = 0; i < stringLen - 1; i++)
  {
    if ( String(char_array[i]) != "-" )
    {
      if ( randomFullLight == 0 )
      {
        leds[i].maximizeBrightness();
      }
      leds[i].fadeLightBy(random_bright);
    }
  }
  FastLED.show();
  delay(random_delay);
}
