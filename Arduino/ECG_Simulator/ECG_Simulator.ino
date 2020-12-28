/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

---------------------------------------------------------------------------------
|                                                                                 |
| Copyright Johan Smets 2020.                                                     |
|                                                                                 |
| This source is part of the ECG Patient Simulator project and is licensed under  | 
| a Creative Commons Attribution-ShareAlike 4.0 International License.            |
|                                                                                 |
 ---------------------------------------------------------------------------------
 
 ---------------------------------------------------------------------------------
| Copyright Johan Smets 2020.                                                     |
|                                                                                 |
| This program is free software: you can redistribute it and/or modify            |
| it under the terms of the GNU General Public License as published by            |
| the Free Software Foundation, either version 3 of the License, or               |
| any later version.                                                              |
|                                                                                 |
| This program is distributed in the hope that it will be useful,                 |
| but WITHOUT ANY WARRANTY; without even the implied warranty of                  |
| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                   |
| GNU General Public License for more details.                                    |
|                                                                                 |
| You should have received a copy of the GNU General Public License               |
| along with this program.  If not, see <https://www.gnu.org/licenses/>.          |
|                                                                                 |
 --------------------------------------------------------------------------------

 --------------------------------------------------------------------------------------------------------------------------------------
| Copyright Johan Smets 2020.                                                                                                          |
|                                                                                                                                      |
| The, in this source described hardware, if applicable, is Open Hardware and is licensed under the CERN-OHL-S v2 or any later version.|
|                                                                                                                                      |
| You may redistribute and modify the hardware in this source and make products using it under                                         |
| the terms of the CERN-OHL-S v2 or any later version (https://ohwr.org/cern_ohl_s_v2.txt).                                            |
|                                                                                                                                      |
| This source is distributed WITHOUT ANY EXPRESS OR IMPLIED WARRANTY,                                                                  |
| INCLUDING OF MERCHANTABILITY, SATISFACTORY QUALITY AND FITNESS FOR A                                                                 |
| PARTICULAR PURPOSE. Please see the CERN-OHL-S v2 or any later version for applicable conditions.                                     |
|                                                                                                                                      |
| Source location: https://www.steamreactor.be/projecten/ecg-patient-simulator-en/ecg-patient-simulator-one-file-download-en .         |                                  |
|                                                                                                                                      |
| As per CERN-OHL-S v2 section 4, should You produce hardware based on this                                                            |
| source, You must where practicable maintain the Source Location visible                                                              |
| on the external case of the Gizmo or other products you make using this                                                              |
| source.                                                                                                                              |
 --------------------------------------------------------------------------------------------------------------------------------------

 --------------------------------------------------------------------------------------------------------------------------------------
|
| Arduino credentials
|
| This software is developed Using Arduino UNO Hardware and Software.  
| This software is available at the official Arduino website https://www.arduino.cc/ and can be downmloaded and used under the  
| conditions of Arduino company.
|
 --------------------------------------------------------------------------------------------------------------------------------------


Project: ECG Patient Simulator.

Code Version: 1.0
Code Revision: 0
Date (yyyy-mm-dd): 2020-11-12
Related Hardware in development state: Arduino UNO R3
Related Hardware in final version: Self developed PCB (EuroCirquits ref: E1242373) for Atmega328 with Arduino UNO Bootloader.
Related electronics schematic: ECG Patient Simulator for diagnostic use. Rev: 1.0 Date 2020-09-03

Attribution: Designed by: Johan Smets, johan.smets2@gmail.com
Complete project and all related files can be found and downloaded at https://www.steamreactor.be/projecten/ecg-patient-simulator-en

By downloading this(these) file(s) and / or making this project or a derivative of this project, you agree and accept that the designer of this project 
is not responsible for any damage, problems or consequences of any kind that may directly or indirectly be associated with this hardware, 
software and/or intellectual and written content.

FULLY COMMENTED CODE VERSION.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ECG Patient Simulator.
//
// Introduction:
// 
// The main intention of this project is to make a cheap, easy to build and easy to use design of an ECG Patient Simulator.
// It provides anesthesia doctors, nursing and tecnical staff with the ability to quickly test the ECG connections of a 3- or 5-Lead ECG-Monitor
// or anesthesia-device.
// This ECG Patient Simulator has initially been build with an Arduino UNO.  At the end an escape version of the Arduino UNO microcontroller,
// the Atmega328 with Arduino UNO bootloader, is integrated on a specially designed PCB to keep the overall dimensions as small as possible.
//
// Controls and Functions:
//  
// The ECG Patient Simulator only has two pushbuttons, a Power/UP and a DOWN pushbutton.
// The ECG Patient Simulator can be powerd ON by pressing the Power/UP Pushbutton. (SW1A connected to Digital I/O 3 of the Arduino UNO / Pin 5 of the Atmega328).
// A Startup sound will be played through a speaker. (Speaker connected to Digital I/O 6 of the Arduino UNO / Pin 12 of the Atmega328 via a Mosfet).
// At startup, the default heartrate is set to 60BPM and the ECG Wave is produced in PWM format at Digital I/O 9 of the Arduino UNO / Pin 15 of the Atmega328.
// By operating the Power/UP or DOWN pushbutton (Digital I/O 3 of the Arduino UNO / Pin 5 of the Atmega328 and Digital I/O 2 of the Arduino UNO / Pin 4 of the Atmega328) 
// respectively steps up or steps down the heartrate to 30, 60, 90, 120, 150, 180, 210 or 240 BPM.
//
// Because of the build-in power saving, the ECG Patient Simulator switches itself off after 5 minutes of operation, controlled by 
// Digital I/O 5 of the Arduino UNO / Pin 11 of the Atmega328.  
// The ECG Patient Simulator can manually be switched of by keeping the Power/UP pusbutton pressed for about 3 seconds.  A shutdown sound will also
// be played. 
// A longer operation time before the ECG Patient Simulator switches itself off can be selected by pressing and holding the DOWN pushbutton while
// pressing the Power/UP pushbutton.  The device will stay on for about 30 Minutes before auto power off is activated.  Depending on the state of
// Dip switch 2 the normal startup sound or a longer startup sound will be played.  Dip switch 2 is connected to Digital I/O 13 of the Arduino UNO / 
// Pin 19 of the Atmega328.
//
// An LED (Digital I/O 17 of the Arduino UNO / Pin 11 of the Atmega328) will blink at the rate of the heartbeat and a beep tone at the same ritme will  
// sound through the speaker, depending on the state of Dip switch 1 (Digital I/O 18 of the Arduino UNO / Pin 12 of the Atmega328).  If DIP switch 1 is 
// off, no beep tone at the same ritme of the heartbeat will sound, but instead a high (4KHz) attention tone will draw the attention of the 
// operator every 15 seconds.     
// The battery of the ECG Patient Simulator is continuously monitored by the microcontroller (Analog I/O A0 of the Arduino UNO / Pin 23 of the Atmega328) and  
// the frequency of the heartbeat beep tone will indicate in three steps the state of the battery.  Battery Voltage > 7,2 Vdc then the Beeptone frequency is 900Hz, 
// Battery Voltage between 7,2 Vdc and 6,7 Vdc then the Beeptone frequency is 200Hz, Battery Voltage between 6,7 Vdc and 6,3 Vdc then the Beeptone 
// frequency is 80Hz.
// At Power ON the startuptone sounds normal as long as the battery voltage is higher than 6,7 Vdc.  If the battery voltage is between 6,7 Vdc and
// 6,3 Vdc, a warning sound (4 short and low frequency beeps) instead of the normal startup sound.   
// If at Power ON the battery voltage is beneith 6,3 Vdc a warning beep will sound immediatly followed by the shutdown sound and the device will
// auto power off to indicate that the battery capacity is to low for reliable operation.  If, in this case and in case of emergency, you keep
// the Power/UP switch pressed for about 5 seconds, the ECG Patient Simulator will sound warning beeps consecutively.  When releasing the
// Power/UP switch the ECG Heartbeat Simulator will continue operating for 5 more minutes and will then power off.
//
// Adjusting the amplitude of the ECG wave.
//
// It is advisable to perform a calibration before first use of the ECG Patient Simulator.
// Because the Arduino UNO has no analog output the ECG Waveform is delivered via a PWM signal that passes through two consecutive LOW-Pass filters
// (RC Integrators) to become an analog waveform again.  These LOW-Pass filters produce a lower amplitude at a higher frequency.  Also, a deviation
// in the resitor and capacitor values of the filters and the output resistor network due to tollerances may result in a to low or to high output
// waveform amplitude. In order to become an equal amplitude at all frequencies (at all Beats Per Minute / BPM) a calibration can be performed.  
// This calibration should actually be called an adjustment because an exact output voltage level can not be set due to the 256 bit resolution 
// of the PWM signal.  An amplutude of 0 mV to approximatly 3 mV at ECG lead II can be set.  Commercial ECG Patient Simulator produce an output 
// of 1 mV to 2 mV which is a realistic value.
// To perform the calibration (adjustement) connect the ECG Patient Simulator to an ECG Monitor and press and hold the Power/UP pushbutton.  
// Keep this buton pressed even when the startupsound has played.  By holding the Power/UP pushbutton for 15 seconds a continuous beeptone is 
// generated and releasing the Power/UP button thereafter, the ECG Patient Simulator will generate its highest beatrate.  By momentary pressing
// the Power/UP or DOWN pushbuttons you can adjust the amplitude of the ECG Waveform to a level that suits you most.  This WantedAmplitude
// will be used to automatically calibrate the amplitude at the other BPM rates.  When the upper or lower limit is reached during the adjustement
// a high tone will be produced to indicate this.
// Not pressing any button for a period of 30 seconds will start the calibration at all consecutive, lower, BPM rates.  This can rather take a
// while because the amplitude of the ECG wave is measured only once per heartbeat at the output of the low pass filters and at the highest level of the wave via 
// Analog I/O A1 of the Arduino UNO / Pin 24 of the Atmega328.  The measured value will than be compared to the WantedAmplitude and will increase or decrease
// an AttenuationXXXBpm value that holds the atenuation factor to eventially become an output amplitude that approaches the WantedAmplitude.  This adustment
// will be repeated at a every next ECG Waveform until the WantedAmpitude is reached.  
// This means that at a lower BPM it wil take a lot longer to reach the WantedAmplitude than at a higher BPM rate.  
// After a completed calibraton the ECG Patient Simulator will save the WantedAmplitude and all attenuation values to EEPROM an will then automatically shutdown.
// When the Power/UP pusbutton is hold for 3 seconds during the calibration process the ECG Patient Simulator will shut down and no values will
// be stored in EEPROM.  In this case all previous values will remain in EEPROM.
//
// Have great fun with this design.
//
// Johan Smets
// November 2020 
// (In the middle of the second wave of a COVID-19 Pandemic.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Libraries used ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <EEPROM.h>                                           // Use the EEPROM library to store the calibration values.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of used Libraries section /////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Global constants and Variables ////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const byte EcgSignalPin = 9;                                  // PWM Output pin 5 => Outputs the ECG signal in PWM format.
const byte MonitorLedPin = 11;                                // LedPin for blinking an LED at HeartRate.
//const int EcgWaveForm[] = {48,48,48,48,48,48,48,48,48,48,50,50,50,50,50,50,51,51,51,51,51,53,53,53,55,55,55,55,57,57,59,61,61,61,63,63,65,65,65,67,67,67,69,69,69,69,69,69,67,67,67,65,65,65,63,61,61,61,59,57,55,55,55,55,53,53,53,53,53,53,53,53,53,53,53,53,51,51,51,51,51,51,51,51,51,51,51,48,48,48,48,44,44,42,42,40,38,36,34,30,28,26,24,22,20,22,24,26,30,36,42,51,61,71,83,99,114,130,148,165,185,201,216,230,240,248,250,255,252,246,238,226,210,195,177,157,138,120,102,85,69,53,40,30,20,14,8,4,2,0,2,4,6,10,12,14,18,22,24,28,32,34,38,40,42,42,44,44,44,46,46,46,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,51,51,51,51,53,53,53,53,55,57,57,57,59,59,61,61,63,65,65,67,67,67,69,69,69,71,69,71,69,71,69,69,69,67,67,65,65,63,63,61,61,61,59,57,57,55,53,53,53,51,51,51,51,51,51,51,51,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48};
const int EcgWaveForm[] = {48,48,48,48,48,48,48,48,48,48,50,50,50,50,50,50,51,51,51,51,51,53,53,53,55,55,55,55,57,57,59,61,61,61,63,63,65,65,65,67,67,67,69,69,69,69,69,69,67,67,67,65,65,65,63,61,61,61,59,57,55,55,55,55,53,53,53,53,53,53,53,53,53,53,53,53,51,51,51,51,51,51,51,51,51,51,51,48,48,48,48,44,44,42,42,40,38,36,34,30,28,26,24,22,22,22,24,26,30,36,42,51,61,71,83,99,114,130,148,165,185,201,216,230,240,248,250,255,252,246,238,226,210,195,177,157,138,120,102,85,69,53,40,30,20,14,8,4,2,2,2,4,6,10,12,14,18,22,24,28,32,34,38,40,42,42,44,44,44,46,46,46,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,50,50,50,50,50,50,51,51,51,51,52,52,54,54,55,56,57,58,59,61,63,63,64,66,66,68,69,69,71,71,73,73,75,75,77,77,78,78,79,79,80,80,80,80,80,80,79,79,78,78,77,76,75,75,74,73,72,71,70,67,67,66,65,63,62,60,59,57,56,55,54,52,52,52,51,51,51,50,50,50,49,49,49,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48};

// StartUp sound: A HipHop alike sound // This is the startup sound when 30 minutes auto power off is selected and dip switch two is on.
const int StartupSound1[] = {329,493,783,329,493,783,329,493,739,324,493,739,329,493,587,261,392,587,261,392,587,261,392,659,293,440,659,277,293,440,493,293,783,329,493,783,329,493,783,329,493,739,329,329,329,329};//,493,739,329,493,587,32,32,32,32,34,34,34,34};
const int StartupSoundLength1[] = {100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,255,255,255,255};//,100,100,100,100,50,255,255,255,255};

// StartUp sound 2: Four Increasing tones. // This is the startup sound when 5 minutes auto power off is selected no matter the state of dip switch two.
const int StartupSound2[] = {200,300,400,500};
const int StartupSoundLength2[] = {255,255,255,255};

// ShutDown sound: Four Decreasing tones.  
const int ShutdownSound[] = {500,400,300,200,200,200,200,200};
const int ShutdownSoundLength[] = {255,255,255,255,255,255,255,255};

int SelectStartupSound = 2;                                   // Set StartupSound2 as default startup sound.

const int BlankEcgValue = 48;                                 // Value of the flat line before and after the actual ECG wave.
const byte ButtonUpPin = 3;                                   // Button pin to increase the HeartBeat rate to the next/higher value And ON-OFF switch of the ECG Simulator.
const byte ButtonDownPin = 2;                                 // Button pin to decrease the HeartBeat rate to the previous/lower value.
const byte SpeakerPin = 6;                                    // Uotput pin to control the speaker.
const byte DipSwitchPin1 = 12;                                // Switch one of Dip switch.  Switch to set ON or OFF the heartbeat BEEPtone.  Switch ON = Pin LOW = BEEP ON.
const byte DipSwitchPin2 = 13;                                // Switch two of Dip switch.  Switch to set ON or OFF the StartupSound2.  Switch ON = Pin LOW = StartupSound2 ON.
const byte AutoPowerOffPin = 5;                               // Power of the ECG Simulator is kept ON as long ast this pin is HIGH.
int EcgWaveSample = 0;                                        // Actual sample number of the ECG Wave.
int HeartBeat = 60;                                           // Current HeartRate value (Default = 60 BPM).
unsigned long EcgPeriod = 1000;                               // In Miliseconds.  Trigger interval for new ECG wave. 
unsigned long CurrentEcgPeriod;                               // Variable to keep track of the trigger interval.
byte BeatRunning=1;                                           // Variable to indicate if an ECG wave is currently running.

unsigned long SampleWriteInterval = 1666;                     // In Microseconds.  Time to write out the next samplevalue of the ECG waveform to EcgSignalPin.  For HeartRate 60bpm the interval between samples to write is 1666 microseconds.
unsigned long CurrentMicros;                                  // Variable to keep track of the SampleWriteInterval.
unsigned long CheckButtonInterval = 100;                      // In Miliseconds.  Check for a button pressed every 100 ms.
unsigned long CurrentMillis;                                  // Variable to keep track of the CheckButtoInterval.
bool ButtonUpPressed = false;                                 // This Variable is true when the button UP is pressed.
bool ButtonUpReleased = false;                                // This Variable is true when the button UP is released.
bool ButtonDownPressed = false;                               // This Variable is true when the button DOWN is pressed.
bool ButtonDownReleased = false;                              // This Variable is true when the button DOWN is released.
int PreviousButtonUpPin = 1;                                  // Variable to figure ou if there was a change in the state of the UP button.
int PreviousButtonDownPin = 1;                                // Variable to figure ou if there was a change in the state of the DOWN button.
int ButtonUnderTest = 1;                                      // Shows the state of the button that is being tested. 
unsigned long AutoPowerOffTime = 300000;                      // In Miliseconds.  By default the device will automatically shut down after 5 Minutes UNLESS altered by the ButtonDown and ButtonUP at startup
unsigned long AttentionBeepTime = 30000;                      // In Miliseconds.  Interval to sound a short attention beep to show that the ECG Simulator is still ON.  If beep at HeartRate is disabled (Dip Switch 1) the Attention Beep will sound every "AttentionBeepTime" miliseconds
unsigned long CurrentAttentionBeepTime;                       // Variable to keep track of the AttentionBeepTime.
unsigned long CurrentOnTime;                                  // Total time the device is swiched on.
unsigned long PowerSwitchPressed;                             // Registers (milis value) the moment that the power switch (= UP switch) is pressed.
unsigned long PowerSwitchPressedTime = 0;                     // Keeps track of the total time that the power switch (= UP switch) is pressed.
unsigned long TimePowerSwitchPressedToSwitchOff = 2500;       // In miliseconds.  Time the power switch has to be pressed until the device switches itself off.
int BeepFrequency = 900;                                      // Frequency of the heartrate beep tone.
int BatteryVoltagePin=A0;                                     // Analog input pint for measuring the battery voltage.
unsigned long CheckBatteryInterval=15000;                     // In Miliseconds.  Time interval to check battery voltage (set at 15 seconds).
unsigned long CurrentBatteryIntervalTime;                     // Variable to keep track of the CheckBatteryInterval.
const int VoltageLevelHigh = 420;                             // Approximatly 7,2 Vdc measured at the 9 Vdc bus (measured behind MOSFET Q1 at input of Voltage regulator.
const int VoltageLevelMedium = 390;                           // Approximatly 6,7 Vdc measured at the 9 Vdc bus (measured behind MOSFET Q1 at input of Voltage regulator.
const int VoltageLevelLow = 370;                              // Approximatly 6,3 Vdc measured at the 9 Vdc bus (measured behind MOSFET Q1 at input of Voltage regulator.
const int BeepFrequencyHigh = 900;                            // Beepfrequency high level = 900 Hz
const int BeepFrequencyMedium = 200;                          // Beepfrequency high level = 200 Hz
const int BeepFrequencyLow = 80;                              // Beepfrequency high level = 80 Hz
byte Attenuation30bpm = 141;                                  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
byte Attenuation60bpm = 144;                                  //
byte Attenuation90bpm = 149;                                  //
byte Attenuation120bpm = 154;                                 // ATTENUATION VALUE FOR EVERY HEARTRATE TO BECOME AN EQUAL AMPLITUDE FOR THE ECG WAVE BEHIND THE LOW-PASS FILTERS.
byte Attenuation150bpm = 160;                                 // These default values will be used if there are no calibration values in the EEPROM yet.
byte Attenuation180bpm = 169;                                 //
byte Attenuation210bpm = 186;                                 //
byte Attenuation240bpm = 200;                                 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int EEAddrAttenuation30bpm=2;                           ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int EEAddrAttenuation60bpm=3;                           //
const int EEAddrAttenuation90bpm=4;                           //
const int EEAddrAttenuation120bpm=5;                          // ADDRESS DEFINITION IN THE EEPROM TO HOLD THE CALIBRATION VALUES TO BE WRITTEN FOR EVERY HEARTRATE.
const int EEAddrAttenuation150bpm=6;                          //
const int EEAddrAttenuation180bpm=7;                          //
const int EEAddrAttenuation210bpm=8;                          //
const int EEAddrAttenuation240bpm=9;                          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SampleAttenuation = Attenuation60bpm;                     // Set the current attenuation value to the attenuation value for the default heartrate of 60 BPM.
int WaveSamplePin = A1;                                       // Pin to measure the amplitude of the ECG Waveform behind the LOW-Pass filters.
int Amplitude;                                                // Variable to hold the measured amplitude.
int AmplitudeTop;                                             // Variable to hold the maximum measured amplitude.
int WantedAmplitude = 440;                                    // Variable to hold the target amplitude.
const int WantedAmplitudeStep=5;
const int EEAddrWantedAmplitudeLowByte = 0;                   // Address definition in the EEPROM to hold the low byte of the target amplitude after calibration. 
const int EEAddrWantedAmplitudeHighByte = 1;                  // Address definition in the EEPROM to hold the high byte of the target amplitude after calibration.
bool Calibrating = false;                                     // Defines if an overall calibration is going on.
bool BpmCalibrated = true;                                    // Defines the completion of calibration for a certain heartrate.
unsigned long CalibrationTriggerTime = 15000;                 // In Miliseconds.  Time the power switch has to be kept pressed at power on to trigger the calibration procedure.
unsigned long CurrentCalibrationTriggerTime;                  // Variable to keep track of the CalibrationTriggerTime.
bool SettingAmplitude = false;                                // Defines if an amplitude setting is going on.
unsigned long SettingAmplitudeTimeout=30000;                  // In Miliseconds.  Time that NEITHER up or down button may have been pressed to proceed to auto-calibration at the subsequent haertrates.
unsigned long CurrentSettingAmplitudeTime;                    // Variable to keep track of the SettingAmplitudeTimeout.


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End Of Global constants and Variables section //////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Beginning of the setup section ******************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  TCCR1B = TCCR1B & 0b11111001;                               // Modify timer 1 to change the PWM base frequency at pin 9 (and pin10) to 31372.55 Hz (The DEFAULT is 490.20 Hz).
  //Serial.begin (9600);                                      // Un-Comment for diagnostics via RS232.
  pinMode (EcgSignalPin, OUTPUT);                             
  pinMode (ButtonUpPin, INPUT_PULLUP);
  pinMode (ButtonDownPin, INPUT_PULLUP);
  pinMode (MonitorLedPin, OUTPUT);
  pinMode (SpeakerPin, OUTPUT);
  pinMode (DipSwitchPin1, INPUT_PULLUP);
  pinMode (DipSwitchPin2, INPUT_PULLUP);
  pinMode (AutoPowerOffPin, OUTPUT);
  pinMode (BatteryVoltagePin,INPUT); 
  CurrentMicros = micros();                                   // Initialize the microsseconds timer (for multi tasking).
  CurrentMillis = millis();                                   // Initialize the miliseconds timer (for multi tasking).
  CurrentOnTime = millis();                                   // Register the switch on time in order to auto power off.
  CurrentAttentionBeepTime = millis();                        // Initialize the start of the AttentionBeep interval.
  CurrentBatteryIntervalTime = millis();                      // Initialize the start of the battery voltage measuring interval.
  CurrentEcgPeriod = millis();                                // Initialize the start of the new ECG Wave trigger.
  CurrentCalibrationTriggerTime=millis();                     // Initialize the start of the calibration trigger time.
  CurrentSettingAmplitudeTime=millis();                       // Initialize the start of the calibration trigger time.  Will be re-initialized at the need of calibration.
    
  digitalWrite (MonitorLedPin, HIGH);                         // Switch the LED OFF.
  digitalWrite(SpeakerPin, LOW);                              // Set the speaker output to OFF
  digitalWrite(AutoPowerOffPin, HIGH);                        // Keep the power ON

  if (digitalRead(ButtonDownPin)==LOW){                       // If the DOWN button is pressed while switching on, then the auto power off time is set to 30 Minutes. And select the long startup sound.
    AutoPowerOffTime = 1800000;                               //
    SelectStartupSound = 1;                                   //
  }

  // Check the battery Voltage at Startup and shut back off when voltage lower than 6,3Vdc
  if (analogRead(BatteryVoltagePin)>= VoltageLevelHigh){          // Check if battery voltage is higher than approx. 7,2Vdc.
    BeepFrequency = BeepFrequencyHigh;                            // Set Beeptone to High.
    PlayStartupSound();                                           // Do normal startup.

  }
  else if (analogRead(BatteryVoltagePin)>= VoltageLevelMedium){   // Check if battery voltage is higher than approx. 6,7Vdc.
    BeepFrequency = BeepFrequencyMedium;                          // Set Beeptone to Medium to mention a degrading battery.
    PlayStartupSound();                                           // Do normal startup.
  }
  else if (analogRead(BatteryVoltagePin)>= VoltageLevelLow){      // Check if battery voltage is higher than approx. 6,3Vdc
    BeepFrequency = BeepFrequencyLow;                             // Set Beeptone to Low to mention a highly degraded battery.
    SoundWarningBeep();                                           // Sound Warning Beep and Proceed without startup sound to draw attention to a highly degraded battery.
  }
  else {                                                          // If battery voltage is lower than approx. 6,3Vdc
    SoundWarningBeep();                                           // Sound Warning Beep;
    PlayShutdownSound();                                          // Play shutdown sound
    digitalWrite(AutoPowerOffPin, LOW);                           // Shutdown the power
    delay (5000);                                                 // Emergency startup: If the power switch is kept pressed for 5 seconds then te device will continue working even with low battery.
    digitalWrite(AutoPowerOffPin, HIGH);                          // Engage power again.
    BeepFrequency = BeepFrequencyLow;                             // Set Beeptone to Low to mention a highly degraded battery.
    do {                                                          // Do not continue until both the Button UP (Power On Pin in this case) and the Button Down is released.
    SoundWarningBeep();                                           // Sound the warning beep as long as one or both buttons is pressed to indicate that emergency startup is initialized.
    delay(1000);                                                  // This delay is to prevent that the switches would be read as Up or Down command. 
    } while(digitalRead(ButtonUpPin)==LOW || digitalRead(ButtonDownPin)==LOW);
  }

    ReadSettingsFromEeprom();                                     // Get the calibration values out of the EEPROM and put them in the corresponding AttenuationXXBpm variables.
    HeartBeat=60;                                                 // Set default Heartbeat (60 Bpm).
    DefineSampleWriteInterval();                                  // Define the write interval between samples according to this 60 Bpm Heartrate.

  do {                                                            // Check if a calibration is requested and if so then initialize calibration.
    delay(100);                                                   // This is to prevent that the switches would be read as Up or Down command.
    if ((millis()-CurrentCalibrationTriggerTime)>=CalibrationTriggerTime){       
      SettingAmplitude=true;
      BpmCalibrated=true;
      Calibrating=false;
      ReadSettingsFromEeprom();
      HeartBeat=240;
      DefineSampleWriteInterval();
      tone (SpeakerPin,2000);
    }
  } while(digitalRead(ButtonUpPin)==LOW || digitalRead(ButtonDownPin)==LOW);     // Do not continue until both the Button Up (Power On Pin in this case) and the Button Down is released.
  noTone(SpeakerPin);
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the setup section ******************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Beginning of the loop section ******************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {

// Trigger a new Heart Beat according to the period of the selected HeartBeat, pulse the monitor LED and sound a beeptone if selected by dip switch 1.
  if ((millis()- CurrentEcgPeriod) >= EcgPeriod){
    CurrentEcgPeriod = millis();
    BeatRunning = 1;
      if (digitalRead(DipSwitchPin1)==LOW){
        tone (SpeakerPin, BeepFrequency, 40);
      }
  }

// Trigger and write the next ECG sample at the specified Sample Write Interval while a beat is in progress.
// When in calibration mode adjust the wave amplitude and define the attenuation value for every heartrate.
  if ((micros() - CurrentMicros) >= SampleWriteInterval && BeatRunning == 1){
    CurrentMicros=micros();                                           // Update the interval Timer.
    WriteEcg();                                                       // Write the ECG samples to the PWM output or perform calibration.
  }
  
// Read Button condition and Check if Auto Power Off time has been reached.
// Check XX times per second the button status according to the value in CheckButtonInterval (Interval is in miliseconds so 100 = 10 Times per second)
  if ((millis() - CurrentMillis) >= CheckButtonInterval) {
    CurrentMillis = millis();
    ReadButtons();
    CheckPowerOff();
  }

// Pulse the led at the ritme of the heartbeat.  
  if(EcgWaveSample==1){                                               // Put LED ON at the beginning of the Wave cycle.
    digitalWrite(MonitorLedPin, LOW);
  }
  if(EcgWaveSample==50){
    digitalWrite(MonitorLedPin, HIGH);                                // Put LED OFF after 50 samples written.
  }

// Increase or decrease the TARGET amplitude of the ECG wave if a calibration is going on.
// These adjustments run multitasked with the WriteEcg() function where the actual wave amplitude progresses to this target amplitude. 
// Increasing TARGET amplitude can be done by intermediate pressing the UP button.
// Decreasing TARGET amplitude can be done by intermediate pressing the DOWN button.
// A contnuous pressing of the UP button for 3 seconds, during Setting Amplitude or Auto Calibration will shut down the ECG Simulator.  The current adjustments will not be saved in EEPROM.
if (SettingAmplitude==true){                                          // Check if the TARGET amplitude adjustment of the calibration is going on.  (Initalized by the calibration request in the setup section.)
  if (ButtonUpPressed==true){                                         // If Button UP is pressed increase the TARGET amplitude bij a WantedAmplitudeStep value.
    WantedAmplitude += WantedAmplitudeStep;
    CurrentSettingAmplitudeTime=millis();                             // Reset the timeout preventing to continue with amplitude adjustment at all subsequent BPM rates.
    ButtonUpPressed=false;                                            // Reset the button UP pressed flag. (Set by the ReadButtons() function).
  }
  if (ButtonDownPressed==true){                                       // If Button DOWN is pressed decrease the TARGET amplitude bij a WantedAmplitudeStep value.
    WantedAmplitude -= WantedAmplitudeStep;
    CurrentSettingAmplitudeTime=millis();                             // Reset the timeout preventing to continue with amplitude adjustment at all subsequent BPM rates.
    ButtonDownPressed=false;                                          // Reset the button DOWN pressed flag. (Set by the ReadButtons() function).
  }
  if ((millis()-CurrentSettingAmplitudeTime)>=SettingAmplitudeTimeout){             // If the SettingAmplitudeTimeout is triggered while in the SettingAmplitude condition. (No button pressed for 30 seconds)
    SettingAmplitude=false;                                                         // Leave the SettingAmplitude condition.
    BpmCalibrated=false;                                                            // Initiate a non finished amplitude adjustment at the current BPM setting.
    Calibrating=true;                                                               // Initiate the amplitude adjustment (Calibrating) at all subsequent BPM rates.
    tone(SpeakerPin,2000,1000);                                                     // Mention the start of the amplitude adjustment (Calibrating) at all subsequent BPM rates with a 2 KHz beep of 1 second.
  }
}
else {                                                                              // If the amplitude adjustment of the calibration is finished.  (Initalized by the calibration request in the setup section.)
  if (Calibrating==true){                                                           // but the amplitude adjustment (Calibrating) at all subsequent BPM rates is initiated bij the SettinAmplitude.
   if (BpmCalibrated==true && HeartBeat != 30){                                     // Then adjust all amplitudes of the subsequent BPM rates one by one downwards until the BPM of 30 has been finished.
      DecreaseHeartBeat();
      tone(SpeakerPin,2000,100);                                                    // Mention every decrease of BPM with a 2 KHz beep of 1 second.
      DefineSampleWriteInterval();
      BpmCalibrated=false;
    }
    else if (BpmCalibrated==true){
      Calibrating=false;
      WriteSettingsToEeprom();                                                      // After completion of all BPM rates auto shutdown the ECG Simulator.
      PlayShutdownSound();
      digitalWrite(AutoPowerOffPin, LOW);
      delay (10000);
    }
  }
  else {                                                                            // Normal operation.  NO Target amplitude adjustment or calibration going on.
                                                                                    // If the Up or Down Button is pressed and released (Falling edge)then change the Heartbeat and set the interval between
                                                                                    // the samples to be written to the output to match the correct Heartbeat period.
    if (ButtonUpReleased == true || ButtonDownReleased == true){
      SwitchHeartBeat();
      DefineSampleWriteInterval();
      ButtonUpReleased = false;                                                     // Reset the state of the UP button. (Set by the ReadButtons() function).
      ButtonDownReleased = false;                                                   // Reset the state of the DOWN button. (Set by the ReadButtons() function).
    }
                                                                                    
    if (((millis()- CurrentAttentionBeepTime) >= AttentionBeepTime) && (digitalRead(DipSwitchPin1) == HIGH)){
      CurrentAttentionBeepTime = millis();                                          //Give an Attention Beep every AttentionBeepTime when dip switch 1 is OFF (Beep tone at heart rate disabled by dip switch 1)
      tone (SpeakerPin, 4000, 50);
    }

    if ((millis()- CurrentBatteryIntervalTime) >= CheckBatteryInterval){            // Check the battery voltage every CheckBatteryInterval.
      CurrentBatteryIntervalTime = millis();
      CheckBatteryVoltage();    
    }

    if ((millis()- CurrentOnTime) >= AutoPowerOffTime){                             // When the AutoPowerOffTime has been reached than play the shutdownsound and automatically switch off the device 
      PlayShutdownSound();                                                          
      digitalWrite(AutoPowerOffPin, LOW);
    }
  }
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the loop section ******************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Write the ECG Samples to the output.  The write of each sample is initiated by the SampleWriteInterval in combination with the BeatRunning flag as defined in the Loop section.
void WriteEcg (void){
  if (EcgWaveSample <= 299){                                      // Write all the samples to the PWM output when teh BeatRunning flag is true.
    if (EcgWaveSample == 129){                                    // Sample 129 is the highest amplitude value of the EcgWaveForm[] array.  Do not alter the EcgWaveForm[] array without considering this sample position.
      AmplitudeTop=analogRead(WaveSamplePin);                     // Read the highest amplitude value of the ECG Wave behind the LOW Pass filters just before the next sample is written.  This value will be used to adjust the Amplitude.
    }
    analogWrite(EcgSignalPin, map(EcgWaveForm[EcgWaveSample],0,255,0,SampleAttenuation));     // Write the Attenuated EcgWaveForm sample to the ECG output signal pin in PWM format .
    EcgWaveSample += 1;                                           // Set the next sample position.
  }
  else {
    BeatRunning=0;                                                // If all samples are written then reset ECG Wave in progress flag (BeatRunning flag set to 0 false).
    EcgWaveSample = 0;                                            // And Reset the position of the ECG samples in the EcgWaveForm table.
    if ((BpmCalibrated==false)||(SettingAmplitude==true)){        // Depending of the BpmCalibrated flag or the SettingAmplitude flag, now there is time for Calibrating the amplitude of the current BPM rate or for adjusting the amplitude towards the target amplitude.
      Amplitude=AmplitudeTop;
      if (Amplitude > WantedAmplitude +1){                        // If the current amplitude of the ECG wave is greather than the target amplitude then decrease the attenuation value.
        SampleAttenuation--;
        if (SampleAttenuation <= 0){                              // If the attenuation factor reached 0 (Minimum).
          SampleAttenuation=0;
          BpmCalibrated=true;                                     // Then declare this BPM rate to be calibrated (When in calibrating mode).
          tone(SpeakerPin,2000,100);                              // Sound a beep tone to mention that limit has been reached.
          if (SettingAmplitude==true){                            // Unless the adjustment of the target amplitude is still in progress.
            WantedAmplitude += WantedAmplitudeStep;               // Then increase the target amplitude with the WantedAmplitudeStep value.
            BpmCalibrated=false;                                  // and declare this BPM rate not to be finished (When not in calibrating mode in other words When in SettingAmplitude mode).
          }
          UpdateNewAttenuationValue();                            // Update the attenuation value for the running BPM rate with the current Attenuation value.
        }
      }
      else if (Amplitude < WantedAmplitude -2){                   // If the current amplitude of the ECG wave is lower than the target amplitude then increase the attenuation value.
        SampleAttenuation++;
        if (SampleAttenuation >= 255){                            // If the attenuation factor reached 255 (Maximum).
         SampleAttenuation=255;
         BpmCalibrated=true;                                      // Then declare this BPM rate to be calibrated (When in calibrating mode).
         tone(SpeakerPin,2000,100);                               // Sound a beep tone to mention that limit has been reached.
          if (SettingAmplitude==true){                            // Unless the adjustment of the target amplitude is still in progress.
            WantedAmplitude -= WantedAmplitudeStep;               // Then decrease the target amplitude with the WantedAmplitudeStep value.
            BpmCalibrated=false;                                  // and declare this BPM rate not to be finished (When not in calibrating mode in other words When in SettingAmplitude mode).
          }
         UpdateNewAttenuationValue();                             // Update the attenuation value for the running BPM rate with the current Attenuation value.
        }
      }
      else {
        BpmCalibrated=true;                                       // If the current Amplitude is not higher or lower than the WantedAmplitude then declare this BPM as calibrated. 
        UpdateNewAttenuationValue();                              // Update the attenuation value for the running BPM rate with the current Attenuation value.
      }
     }
   
  }
   
}

// Change the heartbeat beep frequency according to the battery voltage.
void CheckBatteryVoltage(void){
  if (analogRead(BatteryVoltagePin)>=VoltageLevelHigh){           // Test for higher then 7,2 Vdc.
    BeepFrequency = BeepFrequencyHigh;                            // Change beeptone frequency to High.
  }
  else if (analogRead(BatteryVoltagePin)>=VoltageLevelMedium){    // Test for higher then 6,7 Vdc.
    BeepFrequency = BeepFrequencyMedium;                          // Change beeptone frequency to Medium.
  }
  else {                                                          // If battery voltage is too low (Lower than 6,7 Vdc)
    BeepFrequency = BeepFrequencyLow;                             // Then change beeptone frequency to the lowest beeptone.
  }
}



// Check if the UP or DOWN buttons are pressed or released.  Button Pins are active LOW.  This function is executed every "CheckButtonInterval" time and the buttons are debounced.
// A "Button pressed" state is set true as soon as a button is pressed (Low voltage at button pin) and will not be set true again until the corresponding button has been released first.
// If, at the next check, the UP button pin is in the same state as in the previous check then the down button pin will be checked.
// If, at the next check, the DOWN button pin is in the same state as in the previous check then the routine is left.
// The state of the buttons should be reset (Set to false) by a button servicing function in the main program in the loop section. 
// The UP button also functions as the power button.  Keeping this button pressed for the "TimePowerSwitchPressedToSwitchOff" value will trigger the powering off the ECG simulator.
void ReadButtons(void){
  ButtonUnderTest = digitalRead(ButtonUpPin);                     // Select the UP button to be tested.
  if (ButtonUnderTest != PreviousButtonUpPin){                    // If change is detected then.... 
    PreviousButtonUpPin = ButtonUnderTest;
    if (ButtonUnderTest == LOW){                                  // ....check if button is pressed.
      ButtonUpPressed = true;                                     // If pressed set ButtonUpPressed true......
      ButtonUpReleased = false;                                   // ....and set ButtonUpReleased false.     
      PowerSwitchPressed = millis();                              // UP Button is also Power Switch.  Set the start time the switch is pressed and....
      PowerSwitchPressedTime = 0;                                 // ....reset the total time this switch is pressed.
    }
    else{
      ButtonUpPressed = false;                                    // If the UP button is not pressed then it should have been released.  So set ButtonUpPressed false.... 
      ButtonUpReleased = true;                                    // ....and set ButtonUpReleased true.
      PowerSwitchPressedTime = 0;                                 // Reset the total time this switch is pressed.
    }
  } 
  else if (ButtonUnderTest == LOW){                               // If the UP button state is not changed but the UP button is still pressed......
    PowerSwitchPressedTime = millis() - PowerSwitchPressed;       // .....then update the time that this UP button has been pressed.
  }
  //else{
    //Do Nothing (Future use?)
  //}

 ButtonUnderTest = digitalRead(ButtonDownPin);                    // Select the DOWN button to be tested.
  if (ButtonUnderTest != PreviousButtonDownPin){                  // If change is detected then.... 
    PreviousButtonDownPin = ButtonUnderTest;
    if (ButtonUnderTest == LOW){                                  // ....check if button is pressed.
      ButtonDownPressed = true;                                   // If pressed set ButtonDownPressed true......
      ButtonDownReleased = false;                                 // ....and set ButtonDownReleased false. 
    }
    else{
      ButtonDownPressed = false;                                  // If the DOWN button is not pressed then it should have been released.  So set ButtonDOWNPressed false....
      ButtonDownReleased = true;                                  // ....and set ButtonDownReleased true.
    }
  } 
  
}

void UpdateNewAttenuationValue(void){                             // Write the newly adjusted Attenuation values per beatrate into the corresponding AttenuationXXXbpm registers.
  switch(HeartBeat){
  case 240:
  Attenuation240bpm = SampleAttenuation;
  break;
  case 210:
  Attenuation210bpm = SampleAttenuation;
  break;
  case 180:
  Attenuation180bpm = SampleAttenuation;
  break;
  case 150:
  Attenuation150bpm = SampleAttenuation;
  break;
  case 120:
  Attenuation120bpm = SampleAttenuation;
  break;
  case 90:
  Attenuation90bpm = SampleAttenuation;
  break;
  case 60:
  Attenuation60bpm = SampleAttenuation;
  break;
  default:
  Attenuation30bpm = SampleAttenuation;
  break;
  }
}

void DefineSampleWriteInterval (void){                             // Get the period, the time between sample writes and the attenuation value to be used at the selected BPM rate.
  switch (HeartBeat){
    case 240:
    SampleWriteInterval=750;
    EcgPeriod=250;
    SampleAttenuation=Attenuation240bpm;
    break;
    case 210:
    SampleWriteInterval=870;
    EcgPeriod=285;
    SampleAttenuation=Attenuation210bpm;
    break;
    case 180:
    SampleWriteInterval=1081;
    EcgPeriod=333;
    SampleAttenuation=Attenuation180bpm;
    break;
    case 150:
    SampleWriteInterval=1234;
    EcgPeriod=400;
    SampleAttenuation=Attenuation150bpm;
    break;
    case 120:
    SampleWriteInterval=1388;
    EcgPeriod=500;
    SampleAttenuation=Attenuation120bpm;
    break;
    case 90:
    SampleWriteInterval=1527;
    EcgPeriod=666;
    SampleAttenuation=Attenuation90bpm;
    break;
    case 60:
    SampleWriteInterval=1666;
    EcgPeriod=1000;
    SampleAttenuation=Attenuation60bpm;
    break;
    default:                                                        //HeartBeat = 30.
    SampleWriteInterval=1817;
    EcgPeriod=2000;
    SampleAttenuation=Attenuation30bpm;
    break;
  }
}

void SwitchHeartBeat(void){                                         // Increase or decrease the heartrate corresponding to the UP or DOWN button that has been released.
  if (ButtonUpReleased == true){
    IncreaseHeartBeat();
  }
  if (ButtonDownReleased == true){
    DecreaseHeartBeat();
  }
}

void IncreaseHeartBeat(void){                                       // Increase heartbeat by 30 Bpm and limit to 240 Bpm.
    HeartBeat += 30;
    if (HeartBeat == 270){
      HeartBeat = 240;
    }
}

void DecreaseHeartBeat(void){                                       // Decrease heartbeat by 30 Bpm and limit to 30 Bpm.
  HeartBeat -= 30;
    if (HeartBeat == 0){
      HeartBeat = 30;
    }
}


void PlayStartupSound (void){                                       // Play StartupSound 1 (Long Startup sound)or StartupSound 2 (Short StartupSound) depending on the state of Dip Switch 2 and the AutoPowerOffTime selected.
  if (digitalRead(DipSwitchPin2) == LOW && SelectStartupSound == 1){                // Play Long Startupsound when DIP Switch 2 is ON and long AutoPowerOffTime (30 Minutes) is selected.
    for (int i=0; i < sizeof(StartupSound1)/2; i++){
      tone (SpeakerPin, StartupSound1[i], StartupSoundLength1[i]);
      delay (160);
    }
  noTone (SpeakerPin);
  }
  else {                                                                            // If DIP switch 2 is OFF or normal AutoPowerOffTime (5 minutes) is selected.
    for (int i=0; i < sizeof(StartupSound2)/2; i++){
      tone (SpeakerPin, StartupSound2[i], StartupSoundLength2[i]);
      delay (100);
    }
  noTone (SpeakerPin);
  }
}

void PlayShutdownSound (void){                                     // Play ShutdownSound
  for (int i=0; i < sizeof(ShutdownSound)/2; i++){
    tone (SpeakerPin, ShutdownSound[i],ShutdownSoundLength[i]);
    delay (100);
  }
  noTone (SpeakerPin);
}

void CheckPowerOff(){                                              // If the PowerSwitch is pressed uninterrupted for TimePowerSwitchPressedToSwitchOff time then play ShutdownSound and switch power off.
      if(PowerSwitchPressedTime >= TimePowerSwitchPressedToSwitchOff){
        PlayShutdownSound();
        digitalWrite(AutoPowerOffPin, LOW);
        delay (50000);
      }
}

void SoundWarningBeep(void){
  tone(SpeakerPin,50,60);                                         // Generate low frequency beep sound (3 beeps of 0,5 seconds)to draw attention at for example low battery state.
  delay(100);
  tone(SpeakerPin,50,60);                                         
  delay(100);
  tone(SpeakerPin,50,60);
  delay(100);
  tone(SpeakerPin,50,60);
  delay(500);                                         
}

void WriteSettingsToEeprom(void){                                 // Write the adjusted Amplitude and attenuation values to EEPROM.
  EEPROM.write(EEAddrWantedAmplitudeLowByte,lowByte(WantedAmplitude));
  EEPROM.write(EEAddrWantedAmplitudeHighByte,highByte(WantedAmplitude));
  EEPROM.write(EEAddrAttenuation30bpm,Attenuation30bpm);
  EEPROM.write(EEAddrAttenuation60bpm,Attenuation60bpm);
  EEPROM.write(EEAddrAttenuation90bpm,Attenuation90bpm);
  EEPROM.write(EEAddrAttenuation120bpm,Attenuation120bpm);
  EEPROM.write(EEAddrAttenuation150bpm,Attenuation150bpm);
  EEPROM.write(EEAddrAttenuation180bpm,Attenuation180bpm);
  EEPROM.write(EEAddrAttenuation210bpm,Attenuation210bpm);
  EEPROM.write(EEAddrAttenuation240bpm,Attenuation240bpm);
}

void ReadSettingsFromEeprom(void){                                // Read the adjusted Amplitude and attenuation values fro EEPROM.
  WantedAmplitude=(EEPROM.read(EEAddrWantedAmplitudeLowByte) + EEPROM.read(EEAddrWantedAmplitudeHighByte)*256);
  Attenuation30bpm=EEPROM.read(EEAddrAttenuation30bpm);
  Attenuation60bpm=EEPROM.read(EEAddrAttenuation60bpm);
  Attenuation90bpm=EEPROM.read(EEAddrAttenuation90bpm);
  Attenuation120bpm=EEPROM.read(EEAddrAttenuation120bpm);
  Attenuation150bpm=EEPROM.read(EEAddrAttenuation150bpm);
  Attenuation180bpm=EEPROM.read(EEAddrAttenuation180bpm);
  Attenuation210bpm=EEPROM.read(EEAddrAttenuation210bpm);
  Attenuation240bpm=EEPROM.read(EEAddrAttenuation240bpm);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// END OF CODE //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
