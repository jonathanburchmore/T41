
#ifndef BEENHERE
#include "SDT.h"
#endif

/*****
  Purpose: Determine which UI button was pressed

  Parameter list:
    int valPin            the ADC value from analogRead()

  Return value;
    int                   -1 if not valid push button, index of push button if valid
*****/
int ProcessButtonPress(int valPin)
{
  int switchIndex;

  if (valPin == BOGUS_PIN_READ) {                  // Not valid press
    return -1;
  }
  if (valPin == MENU_OPTION_SELECT && menuStatus == NO_MENUS_ACTIVE) {
    NoActiveMenu();
    return -1;
  }
  for (switchIndex = 0; switchIndex < NUMBER_OF_SWITCHES; switchIndex++)
  {
    if (abs(valPin - EEPROMData.switchValues[switchIndex]) < WIGGLE_ROOM)    // ...because ADC does return exact values every time
    {     
      return switchIndex;
    }
  }
  return -1;                                              // Really should never do this
}

/*****
  Purpose: Check for UI button press. If pressed, return the ADC value

  Parameter list:
    int vsl               the value from analogRead in loop()\

  Return value;
    int                   -1 if not valid push button, ADC value if valid
*****/
int ReadSelectedPushButton()
{
  minPinRead        = 0;
  int buttonReadOld = 1023;
  
  while (abs(minPinRead - buttonReadOld) > 3) {                   // do averaging to smooth out the button response
    minPinRead = analogRead(BUSY_ANALOG_PIN);
    buttonRead = .1 * minPinRead + (1 - .1) * buttonReadOld;      // See expected values in next function.
    buttonReadOld = buttonRead;
  }
  if (buttonRead > 1023 - WIGGLE_ROOM) {
    return -1;
  }
  minPinRead = buttonRead;
  MyDelay(100L);
  return minPinRead;  
}

/*****
  Purpose: Function is designed to route program control to the proper execution point in response to
           a button press.

  Parameter list:
    int vsl               the value from analogRead in loop()

  Return value;
    void
*****/
void ExecuteButtonPress(int val)
{
  if (val == MENU_OPTION_SELECT && menuStatus == NO_MENUS_ACTIVE) {          // Pressed Select with no primary/secondary menu selected  
    NoActiveMenu();
    return;
  } else {
    menuStatus = PRIMARY_MENU_ACTIVE;
  }

  switch (val) {
    case MENU_OPTION_SELECT:                                     // 0
      /*                                    Useful comment in understanding how menues align:
const char *topMenus[]      = {"CW Options", "Spectrum Set", "AGC",      "NR Set",   "IQ Manual",
                               "EQ Rec Set", "EQ Xmt Set",   "Mic Comp", "Calibrate Freq", "Noise Floor",
                               "RF Set",     "VFO Select",   "EEPROM",
                              };

int (*functionPtr[])()      = {&CWOptions, &SpectrumOptions, &AGCOptions, &NROptions, &IQOptions,
                               &EqualizerRecOptions, &EqualizerXmtOptions, &MicOptions, &CalibrateFrequency, &ButtonSetNoiseFloor,
                               &RFOptions, &VFOSelect, &EEPROMOptions
                              };      */

      if (menuStatus == PRIMARY_MENU_ACTIVE) {                             // Doing primary menu
        ErasePrimaryMenu();
        secondaryMenuChoiceMade = functionPtr[mainMenuIndex]();            // These are processed in MenuProcessing.cpp
        menuStatus = SECONDARY_MENU_ACTIVE;
        secondaryMenuIndex = -1;                                  // Reset secondary menu
      } else {
        if (menuStatus == SECONDARY_MENU_ACTIVE) {                         // Doing primary menu
          menuStatus = PRIMARY_MENU_ACTIVE;
          mainMenuIndex = 0;
        }
      }
      EraseMenus();
      break;

    case MAIN_MENU_UP:                                            // 1
      ButtonMenuIncrease();                                       // This makes sure the increment does go outta range
      if (menuStatus != NO_MENUS_ACTIVE) {                        // Doing primary menu
        ShowMenu(&topMenus[mainMenuIndex], PRIMARY_MENU);
      }
      break;

    case BAND_UP:                                                 // 2 Now calls ProcessIQData and Encoders calls
      EraseMenus();
      digitalWrite(bandswitchPins[currentBand], LOW);
      ButtonBandIncrease();
      digitalWrite(bandswitchPins[currentBand], HIGH);
      BandInformation();
      NCO_Freq = 0L;
      CenterFilterOverlay();
      SetFreq(); 
      ShowSpectrum(); 
      break;

    case ZOOM:                                                    // 3
      menuStatus = PRIMARY_MENU_ACTIVE;
      EraseMenus();
      ButtonZoom();
      break;

    case MAIN_MENU_DN:                                            // 4
      ButtonMenuDecrease();
      if (menuStatus != NO_MENUS_ACTIVE) {                        // Doing primary menu
        ShowMenu(&topMenus[mainMenuIndex], PRIMARY_MENU);
      }
      break;

    case BAND_DN:                                                 // 5
      EraseMenus();
      ShowSpectrum();                                           //Now calls ProcessIQData and Encoders calls
      digitalWrite(bandswitchPins[currentBand], LOW);
      ButtonBandDecrease();
      digitalWrite(bandswitchPins[currentBand], HIGH);
      BandInformation();
      NCO_Freq = 0L;
      CenterFilterOverlay();  
      break;

    case FILTER:                                                  // 6
      EraseMenus();
      ButtonFilter();
      break;

    case DEMODULATION:                                            // 7
      EraseMenus();
      ButtonDemodMode();
      break;

    case SET_MODE:                                                // 8
      ButtonMode();
      ShowSpectrumdBScale();
      break;
      
    case NOISE_REDUCTION:                                         // 9
      ButtonNR();
      break;

    case NOTCH_FILTER:                                            // 10
      ButtonNotchFilter();
      UpdateNotchField();
      break;

    case NOISE_FLOOR:                                             // 11
      ButtonSetNoiseFloor();
      break;

    case FINE_TUNE_INCREMENT:                                     // 12
      if (stepFT == 50) {                                          
        stepFT = 500;
      } else {
        stepFT = 50;
      }
      UpdateIncrementField();
      break;    

    case DECODER_TOGGLE:                                          // 13
      if (decoderFlag == DECODE_OFF) {
        decoderFlag = DECODE_ON; 
               
      } else {
        decoderFlag = DECODE_OFF;
      }
      UpdateDecoderField();
      break;

    case MAIN_TUNE_INCREMENT:                                     // 14
      ButtonFreqIncrement();
      break;

    case UNUSED_1:                                                // 15
      break;

    case UNUSED_2:                                                // 16
      break;

    case CALIBRATE_FREQUENCY:                                                // 17
      Xmit_IQ_Cal();  //AFP 09-21-22
      break;

    default:
      break;
  }
}


/*****
  Purpose: To process a band decrease button push

  Parameter list:
    void

  Return value:
    void
*****/
void ButtonFreqIncrement()
{
  tuneIndex--;
  if (tuneIndex < 0)
    tuneIndex = 5;
  freqIncrement = incrementValues[tuneIndex];
  UpdateIncrementField();
}


/*****
  Purpose: Error message if Select button pressed with no Menu active

  Parameter list:
    void

  Return value;
    void
*****/
void NoActiveMenu()
{
  tft.setFontScale( (enum RA8875tsize) 1);
  tft.setTextColor(RA8875_RED);
  tft.setCursor(10, 0);
  tft.print("No menu selected");
  
  menuStatus         = NO_MENUS_ACTIVE;
  mainMenuIndex      = 0;
  secondaryMenuIndex = 0;
}
