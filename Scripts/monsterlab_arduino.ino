#include <Stepper.h>
#include <IRremote.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Inititalise the colour sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_240MS, TCS34725_GAIN_1X);

// Internal LED
int led = 13;

// RGB LED
#define ledpin 4

// Parameters for the stepper motor
const int rolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int stepsPerRevolution = 2000;
const int no_bases = 8;
const int insert_distance = 2850;
const int step_distance = 254;
const int adjust = 73;
const int sequencing_delay = 350;

// Parameters for the remote
int receiver = 12; // Signal Pin of IR receiver to Arduino Digital Pin 6
IRrecv irrecv(receiver);    // create instance of 'irrecv'
decode_results results;     // create instance of 'decode_results'

int x;
uint16_t r, g, b, c, colorTemp, lux;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // LED off to prevent overheating
  digitalWrite(led, LOW);
  
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);

  Serial.begin(9600); //Open Serial connection for debugging

  // Verify the connection to the RGB sensor
    if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  irrecv.enableIRIn(); // Start the receiver
  // Turn off the internal LED on the board
  pinMode(led, OUTPUT);
 
  myStepper.setSpeed(rolePerMinute);
}

void do_sequencing() {
 for (x = 0; x < no_bases; x++) {
   tcs.getRawData(&r, &g, &b, &c);
   colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
   lux = tcs.calculateLux(r, g, b);
 
   Serial.print("Sequencing base number ");
   Serial.print(x);
//   Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
//   Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
   Serial.print(" - Readings: ");
   Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
   Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
   Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
   Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
   Serial.print("\t Called base: ");
   
   if(r > 10000 && g > 10000 && b > 10000){
     Serial.print("C / white");
   }
   else {
     if(r > b && g > b && b < 7000 && c > 20000){
        Serial.print("A / yellow");
     }
     else if(r > g && r > b){
        Serial.print("G / red");
     }
     else if(b > g && b > r){
        Serial.print("T / blue");
     }
     else{
        Serial.print("N");
    }
  }
   Serial.println(" ");

   myStepper.step(step_distance);
   delay(sequencing_delay); 
  }
}

void insert_flowcell() {
  Serial.println("###########################################################");
  Serial.println("##### START SEQUENCING RUN");
  Serial.println("###########################################################");
  Serial.println("Pulling in the flowcell");
  digitalWrite(4, HIGH);
  myStepper.step(insert_distance);
  delay(500);
}

void eject_flowcell() {
  Serial.println("Ejecting the flowcell");
  Serial.println("##### DONE!");
  Serial.println("###########################################################");
  Serial.println("");
  Serial.println("");
  digitalWrite(4, LOW);
  myStepper.step(-(insert_distance + (no_bases) * step_distance + adjust));
}


void loop() 
{  
  if (Serial.available()){
    
   // MAKING VARIABLE VISIBLE TO ONLY 1 FUNCTION
   // CALL AND PRESERVE THEIR VALUE
   
   static int t = 0;
   
   char rvalue = Serial.read();

   Serial.print("Received serial signal: ");
   Serial.println(rvalue);

   switch(rvalue){
   
    case 'S': // VOL+ button pressed
                    insert_flowcell();
                    do_sequencing();
                    eject_flowcell(); 
                    break;

   }
  }
  
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
   //  Serial.println(results.value, HEX);  // Enable this to see the reading from the IR remote to adjust your remote control code

    switch(results.value)
    {

      case 0xB54B73AD: // VOL+ button pressed
                      insert_flowcell();
                      do_sequencing();
                      eject_flowcell(); 
                      break;

      case 0xFF629D: // VOL- button pressed
                      insert_flowcell();
                      do_sequencing();
                      eject_flowcell(); 
                      break;
           
    }
    
      irrecv.resume(); // receive the next value
                 digitalWrite(8, LOW);
                 digitalWrite(9, LOW);
                 digitalWrite(10, LOW);
                 digitalWrite(11, LOW);       
  }
}
