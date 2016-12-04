// AmmoCounter V1 with Trigger Switch
// Updated 12/3/2016
// Created by: Nathaniel Deal
// More Info: www.ammocounter.com 

// Include Libraries
#include <Bounce2.h>
#include <AmmoCounter.h>

// Setup Toggle/Counter Variables
int toggleArray[] = {0,35,25,22,18,15,12,10,6}; // Setup array of magazine sizes
int toggleCount = (sizeof(toggleArray)/sizeof(int))-1; // Find size of array
int togglePosition = toggleCount; // Start at max capacity.
int count = toggleArray[toggleCount];  // Set intial count to highest capacity.
AmmoCounter counter = AmmoCounter(); // Setup AmmoCounter instance

// Setup Switches with Bounce2 Library
#define toggleBtnpin 4
//#define clipBtnpin 5
#define counterBtnpin 6
Bounce toggleBtn = Bounce(); 
//Bounce clipBtn = Bounce(); 
Bounce counterBtn = Bounce(); 

void setup() {

  // Toggle/Reset/Counter Setup
  pinMode(toggleBtnpin, INPUT); 
  // pinMode(clipBtnpin, INPUT); 
  pinMode(counterBtnpin, INPUT); 

  digitalWrite(toggleBtnpin, LOW);  // Activate internal pullup
  // digitalWrite(clipBtnpin, LOW);  // Activate internal pullup
  digitalWrite(counterBtnpin, LOW);  // Activate internal pullup

  toggleBtn.attach(toggleBtnpin);
  // clipBtn.attach(clipBtnpin);
  counterBtn.attach(counterBtnpin);

  toggleBtn.interval(5);
  // clipBtn.interval(5);
  counterBtn.interval(5); 

  // Show Initial Count
  counter.displayNumber(count);

  // Serial.begin(9600); // Uncomment for testing
  
}               

void loop(){

  // Monitor Counter Switch
  //----------------------------------------------------//

    // Check if the counter switch is pressed.    
    if (counterBtn.update() ) 
    {
      if (counterBtn.read() == HIGH)  
      {
        if (toggleArray[togglePosition] == 0) {
          
          // If OO has been selected, Count Up
          counter.displayNumber(++count);

          // Check if count has finished, Auto-Reset
          if (count == 99) {
            _autoReset(); // Reset Count
          }
          
        } else {
        
          // Count Down
          counter.displayNumber(--count); 
  
          // Check if count has finished, Auto-Reset
          if (count == 0) {
            _autoReset(); // Reset Count
          }
        }  
      }
    }  
  
  // Monitor Toggle Button
  //----------------------------------------------------//
  
    // Check if the togglebutton is pressed.
    if (toggleBtn.update() ) 
    {
      if (toggleBtn.read() == HIGH)  
      {
        if (togglePosition == 0) {
          togglePosition = toggleCount; //Reset to max.
        } else {
          togglePosition--; //Deincrement capacity one step 
        } 
  
        count = toggleArray[togglePosition];
        counter.displayNumber(count); //Send to display  
      }
    }
    
  // Monitor Clip Reset
  //----------------------------------------------------//
    
    // Check if clip is released
  
//    if (clipBtn.update() ) 
//    {
//      if (clipBtn.read() == HIGH)  
//      {
//        count = toggleArray[togglePosition]; // Reset count
//        counter.displayNumber(count); //Send to display  
//      }
//    }
}

// Blink display and then auto-reset     
//----------------------------------------------------//  
void _autoReset() {
  counter.blinkDisplay(3); // Blink display 3x    
  count = toggleArray[togglePosition]; // Reset count   
  counter.displayNumber(count); //Send to display   
}
