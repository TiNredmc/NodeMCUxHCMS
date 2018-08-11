#include <ESP8266WiFi.h>
#include <LedDisplay.h>
#include <Time.h>
#define dataPin 16              // connects to the display's data in
#define registerSelect 5       // the display's register select pin
#define clockPin 4             // the display's clock pin
#define enable 0               // the display's chip enable pin
#define reset 2               // the display's reset pin

#define displayLength 8        // number of characters in the display
LedDisplay myDisplay = LedDisplay(dataPin, registerSelect, clockPin,
                                  enable, reset, displayLength);

int brightness = 15;        // screen brightness

const char* ssid = "jiamjarapun";  //  your network SSID (name)
const char* password = "226142abcd";       // your network password
const String month_name[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
const String day_name[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int timezone = 7 * 3600;
int dst = 0;
void setup()

{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
  // initialize the display library:
  myDisplay.begin();
  // set the brightness of the display:
  myDisplay.setBrightness(brightness);
}
  void loop()

  {
    time_t now = time(nullptr);
    struct tm* p_tm = localtime(&now);
    //set the 0 infront of the hour less than 10 AM
    if ((p_tm->tm_hour < 10) && (p_tm->tm_hour >= 0))
    {
      myDisplay.setCursor(0);
      myDisplay.print('0');
      myDisplay.setCursor(1);
      myDisplay.print(p_tm->tm_hour);
    } else
    {
      myDisplay.setCursor(0);
      myDisplay.print(p_tm->tm_hour);
    }

    myDisplay.setCursor(2);
    myDisplay.print(':');

    //set the 0 infront of the minute less than 10 minutes
    if ((p_tm->tm_min < 10) && (p_tm->tm_min >= 0))
    {
      myDisplay.setCursor(3);
      myDisplay.print('0');
      myDisplay.setCursor(4);
      myDisplay.print(p_tm->tm_min);
    } else
    {
      myDisplay.setCursor(3);
      myDisplay.print(p_tm->tm_min);
    }

    myDisplay.setCursor(5);
    myDisplay.print(':');

    //set the 0 infront of the second less than 10 seconds
    if ((p_tm->tm_sec <= 9) && (p_tm->tm_sec >= 0))
    {
      myDisplay.setCursor(6);
      myDisplay.print('0');
      myDisplay.setCursor(7);
      myDisplay.print(p_tm->tm_sec);
    } else
    {
      myDisplay.setCursor(6);
      myDisplay.print(p_tm->tm_sec);
    }

    delay(1000);

  }
