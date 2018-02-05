// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            2
#define COLORPIN       3
#define LOWPIN         0
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      6
#define MAXCOLORS	8  // Zero-based index: maximum - 1
int currColor = 0;

bool oldState = HIGH;
int showType = 0;

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 50; // delay for NeoPixels

// To add additional colors, add a unit32_t variable and add variable name to colors array below
// Also change MAXCOLORS to new maximum -1

uint32_t purple = pixels.Color(127,0,255); 
uint32_t red = pixels.Color(255,0,0);
uint32_t green = pixels.Color(0,255,0);
uint32_t blue = pixels.Color(0,0,255);
uint32_t yellow = pixels.Color(255,255,0);
uint32_t white = pixels.Color(255,255,255);
uint32_t pink = pixels.Color(255,0,100);
uint32_t cyan = pixels.Color(0,255,255);
uint32_t orange = pixels.Color(230,80,0);

uint32_t  colors[] = {purple, red, green, blue, yellow, white, pink, cyan, orange};

void setup() {
   // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

pinMode(COLORPIN, INPUT_PULLUP);
pinMode(LOWPIN, OUTPUT);    //  This pin will be LOW to COLORPIN
digitalWrite(LOWPIN, LOW);  //  Acts as GND - only one GND pin on Trinket



  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(40); // 1/3 Brightness
  pixels.show();
}
void loop() {
// Get current button state.

bool newState = digitalRead(COLORPIN);

// Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(COLORPIN);
    if (newState == LOW) {
      //Serial.print("Button Pushed!");
      currColor++;
      if (currColor > MAXCOLORS)
        currColor=0;
    }
  }

  // Set the last button state to the old state.
  oldState = newState;

  pixelSet();

}

void pixelSet()
{   for (int i=0; i<NUMPIXELS; i++)
    {
    pixels.setPixelColor(i, colors[currColor]);  
    delay(delayval); // Delay for a period of time (in milliseconds).
    }
    pixels.show(); // This sends the updated pixel color to the hardware.
    //delay(50);
  
}
