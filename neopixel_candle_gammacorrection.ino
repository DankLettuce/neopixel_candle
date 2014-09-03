//Gavin McMahon 
//adafruit neopixel candle code
//5v trinket 

#include <Adafruit_NeoPixel.h>
#define PIN 2

//allow scalability of code -- needs to be a 'const int' in order to allow the color arrays to be scalable
const int number_of_pixels = 8;

// color variables: mix RGB (0-255) for desired yellow
int Red_neutral = 255;
int Green_neutral = 200;
int Blue_neutral = 200;

//declare arrays that holds the individual pixel color values
int Red[number_of_pixels];
int Green[number_of_pixels];
int Blue[number_of_pixels];

// animation variables -- these are just initialization values and change throughout the program
double burn_height_max = 8; //this is a weighted value that pulls the burn heigh back to a controlled value 
// burn_height_neutral will decrease over time like a real flame
double burn_height = 6; //the candle flame height
double burn_height_min = burn_height_max - burn_height; //

int delay_min = 5; //cycle delay minimum
int delay_max = 100; // cycle delay maximum

//adafruit supplied gamma correction table
const uint8_t PROGMEM gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

Adafruit_NeoPixel strip = Adafruit_NeoPixel(number_of_pixels, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
strip.begin();
strip.show();
}

void loop() {
 RGB_values();
 
 flame_normal();
 delay(random(delay_min, delay_max));
}

void RGB_values(){
  for(int pixel = number_of_pixels - 1; pixel>=0; pixel--){
    int gradient = pixel-(burn_height_min-1);
    int redtemp = Red[pixel];
    int greentemp = Green[pixel];
    int bluetemp = Blue[pixel];
    if(pixel > burn_height_max)
    {
      Red[pixel] = pgm_read_byte(&gamma[0]);
      Green[pixel] = pgm_read_byte(&gamma[0]);
      Blue[pixel] = pgm_read_byte(&gamma[0]);
    }
    else if(pixel <= burn_height_max && pixel > burn_height_min)
    {
     Red[pixel] = pgm_read_byte(&gamma[(redtemp + random (200, 255))/gradient]);
     Green[pixel] = pgm_read_byte(&gamma[(greentemp + random(150, 200)/gradient)]); 
     Blue[pixel] = pgm_read_byte(&gamma[(bluetemp + random(80, 120))/gradient]);
    }
//    else if(pixel <= burn_height_max && pixel >= burn_height_max-2)
//    {
//     Red[pixel] = (redtemp + random(50, 120))/4; 
//    }
    else
    {     
      Red[pixel] = pgm_read_byte(&gamma[255]);
      Green[pixel] = pgm_read_byte(&gamma[175]);
      Blue[pixel] = pgm_read_byte(&gamma[100]);
    }
  }
}

void flame_normal() {
 for(int pixel = number_of_pixels - 1; pixel>=0; pixel--){
    strip.setPixelColor(pixel, Red[pixel], Green[pixel], Blue[pixel]);
  strip.show();
  delay(random(delay_min, delay_max));
 }
}

