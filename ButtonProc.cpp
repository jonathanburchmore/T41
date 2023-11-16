#ifndef BEENHERE
#include "SDT.h"
#endif

/*****
  Purpose: To process a menu increase button push

  Parameter list:
    void

  Return value:
    void
*****/
void ButtonMenuIncrease()
{
  if (menuStatus == PRIMARY_MENU_ACTIVE) {
    mainMenuIndex++;
    if (mainMenuIndex == TOP_MENU_COUNT) {            // At last menu option, so...
      mainMenuIndex = 0;                              // ...wrap around to first menu option
    }
  } else {
    if (menuStatus == SECONDARY_MENU_ACTIVE) {
      secondaryMenuIndex++;
      if (secondaryMenuIndex == subMenuMaxOptions) {  // Same here...
        secondaryMenuIndex = 0;
      }
    }
  }
}

/*****
  Purpose: To process a menu decrease button push

  Parameter list:
    void

  Return value:
    void
*****/
void ButtonMenuDecrease()
{
  if (menuStatus == PRIMARY_MENU_ACTIVE) {
    mainMenuIndex--;
    if (mainMenuIndex < 0) {                        // At last menu option, so...
      mainMenuIndex = TOP_MENU_COUNT - 1;           // ...wrap around to first menu option
    }
  } else {
    if (menuStatus == SECONDARY_MENU_ACTIVE) {
      secondaryMenuIndex--;
      if (secondaryMenuIndex < 0) {                   // Same here...
        secondaryMenuIndex = subMenuMaxOptions - 1;
      }
    }
  }
}
//==================  AFP 09-27-22

/*****
  Purpose: To process a band increase button push

  Parameter list:
    void

  Return value:
    void
*****/
void ButtonBandIncrease()
{
  int tempIndex;
  
  tempIndex = currentBand;                                      // Save the current index
  currentBand++;
  
  if (currentBand == NUMBER_OF_BANDS) {                         // Incremented too far?
    currentBand = 0;                                            // Yep. Roll to list front.
  }

  switch (activeVFO) {
    case VFO_A:
      lastFrequencies[tempIndex][VFO_A] = currentFreqA;         // Save pre-increment frequency for VFO A
      centerFreq = TxRxFreq = currentFreqA = lastFrequencies[currentBand][VFO_A];
      break;
      
    case VFO_B:
      lastFrequencies[tempIndex][VFO_B] = currentFreqB;         // Same for VFO B
      centerFreq = TxRxFreq = currentFreqB = lastFrequencies[currentBand][VFO_B];   
      break;
      
    case VFO_SPLIT:
      DoSplitVFO();
      break;
  }

  EraseSpectrumDisplayContainer();
  DrawSpectrumDisplayContainer();
  DrawFrequencyBarValue();
  SetBand();
  SetFreq();
  ShowFrequency();
  MyDelay(1L);
  AudioInterrupts();
}

/*****
  Purpose: To process a band decrease button push

  Parameter list:
    void

  Return value:
    void
*****/
void ButtonBandDecrease()
{
  int tempIndex;
  //AudioNoInterrupts();

  tempIndex = currentBand;                                      // Save the current index
  currentBand--;                                                // decrement band index

  if (currentBand < 0) {                                        // decremented too far?
    currentBand = NUMBER_OF_BANDS - 1;                          // Yep. Roll to list end.
  }

  switch (activeVFO) {
    case VFO_A:                                                 // 0
      lastFrequencies[tempIndex][VFO_A] = currentFreqA;         // Save pre-increment frequency for VFO A
      centerFreq = TxRxFreq = currentFreqA = lastFrequencies[currentBand][VFO_A];
      break;
      
    case VFO_B:                                                 // 1
      lastFrequencies[tempIndex][VFO_B] = currentFreqB;         // Same for VFO B
      centerFreq = TxRxFreq = currentFreqB = lastFrequencies[currentBand][VFO_B];   
      break;
      
    case VFO_SPLIT:                                             // 3
      DoSplitVFO();
      break;
  }
  EraseSpectrumDisplayContainer();
  DrawSpectrumDisplayContainer();
  DrawFrequencyBarValue();
  SetBand();
  SetFreq();
  ShowFrequency();
  MyDelay(1L);
  AudioInterrupts();
}



//================ AFP 09-27-22
/*****
  Purpose: Chnage the horizontal scale of the frequency display

  Parameter list:
    void

  Return value:
    int             index of the option selected
*****/
void ButtonZoom()
{
  zoomIndex++;

  if (zoomIndex == MAX_ZOOM_ENTRIES) {
    zoomIndex = 0;
  }
  if (zoomIndex <= 0)
    spectrum_zoom = 0;
  else
    spectrum_zoom = zoomIndex;

  ZoomFFTPrep();
  UpdateZoomField();
  DrawBandWidthIndicatorBar();
  DrawFrequencyBarValue();
  ShowBandwidth();
}

/*****
  Purpose: To process a filter button push

  Parameter list:
    void

  Return value:
    void
*****/
void ButtonFilter()
{
  switchFilterSideband = !switchFilterSideband;
  ControlFilterF();
  FilterBandwidth();
  SetFreq();
  ShowFrequency();
}

/*****
  Purpose: Process demodulation mode

  Parameter list:
    void

  Return value:
    void
*****/
void ButtonDemodMode()
{
  bands[currentBand].mode++;
  if (bands[currentBand].mode > DEMOD_MAX) {
    bands[currentBand].mode = DEMOD_MIN;            // cycle thru demod modes
  }
  //AudioNoInterrupts();
  SetupMode(bands[currentBand].mode);
  ShowFrequency();
  ControlFilterF();
  FilterBandwidth();
  DrawSMeterContainer();
  ShowAnalogGain();
  AudioInterrupts();
}


/*****
  Purpose: Set transmission mode for SSB or CW

  Parameter list:
    void

  Return value:
    void
*****/
void ButtonMode()        //====== CW Receive code AFP 08-04-22   Most of function is new=================
{
  if (xmtMode == CW_MODE) {                     // Toggle the current mode
    xmtMode = SSB_MODE;
  } else {
    xmtMode = CW_MODE;
  }
//  RedrawDisplayScreen();

  if (xmtMode == CW_MODE) {
    modeSelectOutL.gain(0, 5);
    modeSelectOutR.gain(0, 5);
    FLoCutOld = bands[currentBand].FLoCut;
    FHiCutOld = bands[currentBand].FHiCut;
    currentFreqA = centerFreq + NCO_Freq;             // Yep, prepare lower sideband
    if (currentBand < 2) {                            // 80 or 40M?
      bands[currentBand].FLoCut = -3000;
      bands[currentBand].FHiCut = -200;
      TxRxFreq = centerFreq +NCO_Freq;                // AFP 09-27-22
    } else {
      bands[currentBand].FLoCut = 200;
      bands[currentBand].FHiCut = 3000;
      TxRxFreq = centerFreq + NCO_Freq;              // AFP 09-27-22
    }
  } else {
    modeSelectOutL.gain(0, 1.0);
    modeSelectOutR.gain(0, 1.0);
    if (currentBand < 2) {
      bands[currentBand].FLoCut = FLoCutOld;
      bands[currentBand].FHiCut = FHiCutOld;
    } else {
      bands[currentBand].FLoCut = FLoCutOld;
      bands[currentBand].FHiCut = FHiCutOld;
    }
    TxRxFreq = centerFreq +NCO_Freq;
    currentFreqA = TxRxFreq;
  }
  
  RedrawDisplayScreen();  
  EraseSpectrumDisplayContainer();
  DrawSpectrumDisplayContainer();
  ControlFilterF();
  FilterBandwidth();
  UpdateDecoderField();
  SetFreq();
  ShowFrequency();
}

/*****
  Purpose: To process select noise reduction

  Parameter list:
    void

  Return value:
    void
*****/
void ButtonNR()  //AFP 09-19-22 update
{
  nrOptionSelect++;
  if (nrOptionSelect > 3) {
    nrOptionSelect = 0;  
  }
  NROptions();   //AFP 09-19-22
  UpdateNoiseField();
}

/*****
  Purpose: To set the notch filter

  Parameter list:
    void

  Return value:
    void
*****/
void ButtonNotchFilter()
{
  ANR_notchOn = !ANR_notchOn;
  MyDelay(100L);
}


/*****
  Purpose: Allows quick setting of noise floor in spectrum display

  Parameter list:
    void

  Return value;
    int           the current noise floor value
*****/
int ButtonSetNoiseFloor()
{
  int currentNoiseFloor = SPECTRUM_BOTTOM - spectrumNoiseFloor;
  int val;

  tft.setFontScale( (enum RA8875tsize) 1);
  ErasePrimaryMenu();
  tft.fillRect(SECONDARY_MENU_X - 100, MENUS_Y, EACH_MENU_WIDTH + 120, CHAR_HEIGHT, RA8875_MAGENTA);
  tft.setTextColor(RA8875_WHITE);
  tft.setCursor(SECONDARY_MENU_X - 98, MENUS_Y + 1);
  tft.print("Pixels above axis:");
  tft.setCursor(SECONDARY_MENU_X + 200, MENUS_Y + 1);
  tft.print(currentNoiseFloor);
  MyDelay(150L);

  while (true) {
    if (filterEncoderMove != 0) {
      currentNoiseFloor += filterEncoderMove;                 // It moves the display
      if (currentNoiseFloor < -15) {    //AFP 09-22-22                        // Don't exceed limits
        currentNoiseFloor = -15;        //AFP 09-22-22
      } else {
        if (currentNoiseFloor > SPECTRUM_HEIGHT) {
          currentNoiseFloor = SPECTRUM_HEIGHT;
        }
      }
      tft.fillRect(SECONDARY_MENU_X + 190, MENUS_Y, 80, CHAR_HEIGHT, RA8875_MAGENTA);
      tft.setCursor(SECONDARY_MENU_X + 200, MENUS_Y + 1);
      tft.print(currentNoiseFloor);
      filterEncoderMove = 0;
    }

    val = ReadSelectedPushButton();              // Get ADC value
    MyDelay(100L);
    val = ProcessButtonPress(val);
    if (val == MENU_OPTION_SELECT)               // If they made a choice...
    {
      spectrumNoiseFloor = SPECTRUM_BOTTOM - currentNoiseFloor;
      if (spectrumNoiseFloor > SPECTRUM_BOTTOM+15) { //AFP 09-22-22
        spectrumNoiseFloor = SPECTRUM_BOTTOM+15; //AFP 09-22-22
      } else {
        if (spectrumNoiseFloor < SPECTRUM_BOTTOM - 50)
          spectrumNoiseFloor = SPECTRUM_BOTTOM - 50;
      }
      EEPROMData.spectrumNoiseFloor = spectrumNoiseFloor;
      EEPROMWrite();
      break;
    }
  }
  EraseMenus();
  EraseSpectrumDisplayContainer();  DrawSpectrumDisplayContainer();
  tft.setTextColor(RA8875_WHITE);
  DrawSpectrumDisplayContainer();
  ShowSpectrumdBScale();
  ShowSpectrum();
  return spectrumNoiseFloor;
}

/*****
  Purpose: The next 3 functions are "empty" user-defined function stubs that can be filled in by the user with
           "real" code.

  Parameter list:
    void

  Return value;
    int           the current noise floor value
*****/
int Unused1()
{
  return -1;
}
int Unused2()
{
  return -1;
}
int Unused3()
{
  return -1;
}
