/*	fallDetector.ino
	Quran Karriem <quran.karriem@duke.edu>
	October 2017

  Requires https://github.com/sparkfun/SparkFun_MMA8452Q_Particle_Library

	Use a particle Photon and the MMA8452Q accelerometer to send text messages, flash lights and make noise
  when a child wearing it falls down.

*/
SYSTEM_MODE(AUTOMATIC);
#include "SparkFunMMA8452Q.h"

MMA8452Q accel; // Default constructor, SA0 pin is HIGH

int loPin = 3;
int midPin = 4;
int hiPin = 5;
int soundPin = 2;
int hiFreq = 1000;
int midFreq = 500;
int loFreq = 250;
int timer = 0;
float hiThreshold = 0.35; // define thresholds for g differentials to determine severity of a fall.
float midThreshold = 0.5;
float loThreshold = 0.65;
String hiFallMessage = "Your kid fell pretty hard. You should definitely check on him/her.";
String midFallMessage = "Your kid fell. He/she is probably OK, but consider checking on him/her.";
String loFallMessage = "Your kid took a light fall. He/she is probably OK.";
String noFallMessage1 = "It's been ";
String noFallMessage2 = " minutes since your kid fell. You're amazing.";
bool timeFlag = true;

void setup()
{
    pinMode(loPin, OUTPUT);
    pinMode(midPin, OUTPUT);
    pinMode(hiPin, OUTPUT);
    pinMode(soundPin, OUTPUT);
    Serial.begin(115200);
    accel.begin(SCALE_2G, ODR_6); // Set up accel with +/-2g range, and 6Hz ODR
    Particle.subscribe("buttonPressed", playArp);
}

void loop()
{
    if (accel.available())
    {
        accel.read();
        float x = accel.cx;
        float y = accel.cy;
        float z = accel.cz;
        Serial.println(x);
        Serial.println(y);
        Serial.println(z);
        Serial.println();

        if (x < 0){ x = -x;} //ignore rotation data in determining fall status
        if (y < 0){ y = -y;}
        if (z < 0){ z = -z;}

        if (x < hiThreshold && y < hiThreshold && z < hiThreshold) { //indicate fall if x, y & z all below threshold
          fallIndicator(hiPin, hiFreq, hiFallMessage);
        }
        else if (x < midThreshold && y < midThreshold && z < midThreshold) {
          fallIndicator(midPin, midFreq, midFallMessage);
        }
        else if (x < loThreshold && y < loThreshold && z < loThreshold) {
          fallIndicator(loPin, loFreq, loFallMessage);
        }
    }
    int timeSinceFall = (millis() - timer) / 1000;
    if (timeSinceFall > 1 && timeSinceFall % 60 == 0 && timeFlag == true){ //Send time since last fall to Becca once per minute
      Particle.publish("greatParent", noFallMessage1 + String(timeSinceFall/60) + noFallMessage2);
      timeFlag = false; // prevent duplicate events from triggering
    }
    if (timeSinceFall % 60 >= 2){ // reset time flag two seconds after each minute marker
      timeFlag = true;
    }
}

void fallIndicator(int pin, int freq, String message){ // make sounds, publish message, flash LEDs, and reset the fall timer
  timer = millis();
  digitalWrite(pin, HIGH);
  delay(150);
  digitalWrite(pin, LOW);
  tone(soundPin, freq, 500);
  Particle.publish("fallSeverity", message, 5);
  Serial.println(message);
}

void playArp(const char *event, const char *data){ //play an ominous minor arpeggio when the button on Becca's device is released.
  tone(soundPin, 261, 500);
  delay(250);
  tone(soundPin, 311, 500);
  delay(250);
  tone(soundPin, 392, 500);
}
