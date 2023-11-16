#ifndef BEENHERE
#include "SDT.h"
#endif

/*****
  Purpose: void EEPROMRead()

  Parameter list:
    struct config_t e[]       pointer to the EEPROM structure

  Return value;
    void
*****/
void EEPROMRead()
{
  EEPROM.get(EEPROM_BASE_ADDRESS, EEPROMData);                    // Read as one large chunk

  AGCMode                               = EEPROMData.AGCMode;     // 1 byte
  CWFilterIndex                         = EEPROMData.CWFilterIndex;  // Off
  nrOptionSelect                        = EEPROMData.nrInUse;     // 1 byte

  activeVFO                             = EEPROMData.currentVFO;  // 2 bytes

  audioVolume                           = EEPROMData.audioVolume; // 4 bytes
  currentBand                           = EEPROMData.currentBand; // 4 bytes
  currentBandA                          = EEPROMData.currentBandA;// 4 bytes
  currentBandB                          = EEPROMData.currentBandB;// 4 bytes
  decoderFlag                           = EEPROMData.decoderFlag;



  for (int i = 0; i < EQUALIZER_CELL_COUNT; i++) {
    recEQ_Level[i] =  EEPROMData.equalizerRec[i];// 4 bytes each
    xmtEQ_Level[i] =  EEPROMData.equalizerXmt[i];
  }

  freqIncrement                         = EEPROMData.freqIncrement;  // 4 bytes
  keyType                               = EEPROMData.keyType;  // straight key = 0, keyer = 1
  currentMicThreshold                   = EEPROMData.currentMicThreshold;// 4 bytes      // AFP 09-22-22
  currentMicCompRatio                   = EEPROMData.currentMicCompRatio;
  currentMicAttack                      = EEPROMData.currentMicAttack;
  currentMicRelease                     = EEPROMData.currentMicRelease;
  currentMicGain                        = EEPROMData.currentMicGain;

  paddleDit                             = EEPROMData.paddleDit;
  paddleDah                             = EEPROMData.paddleDah;
  rfGainAllBands                        = EEPROMData.rfGainAllBands;
  spectrumNoiseFloor                    = EEPROMData.spectrumNoiseFloor;    // AFP 09-26-22

  //  Note: switch values are read and written to EEPROM only

  tuneIndex                             = EEPROMData.tuneIndex;
  transmitPowerLevel                    = EEPROMData.powerLevel;
  currentWPM                            = EEPROMData.wordsPerMinute; // 4 bytes
  xmtMode                               = EEPROMData.xmtMode;                    // AFP 09-26-22

  currentScale                          = EEPROMData.currentScale;
  spectrum_zoom                         = EEPROMData.spectrum_zoom;
  spectrum_display_scale                = EEPROMData.spectrum_display_scale;// 4 bytes
  sidetoneVolume                        = EEPROMData.sidetoneVolume;// 4 bytes
  cwTransmitDelay                       = EEPROMData.cwTransmitDelay;   // 4 bytes

  freqCorrectionFactor                  = EEPROMData.freqCorrectionFactor;

  LPFcoeff                              = EEPROMData.LPFcoeff;// 4 bytes
  NR_PSI                                = EEPROMData.NR_PSI;// 4 bytes
  NR_alpha                              = EEPROMData.NR_alpha;// 4 bytes
  NR_beta                               = EEPROMData.NR_beta;// 4 bytes
  omegaN                                = EEPROMData.omegaN;// 4 bytes
  pll_fmax                              = EEPROMData.pll_fmax;// 4 bytes

  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    CWPowerCalibrationFactor[i]           = EEPROMData.CWPowerCalibrationFactor[i];  // 0.019;   //AFP 10-29-22
    SSBPowerCalibrationFactor[i]          = EEPROMData.SSBPowerCalibrationFactor[i]; // 0.008;   //AFP 10-29-22
    powerOutCW[i]                         = EEPROMData.powerOutCW[i];// 4 bytes  //AFP 10-28-22
    powerOutSSB[i]                        = EEPROMData.powerOutSSB[i];     // 4 bytes AFP 10-28-22
    IQAmpCorrectionFactor[i]              = EEPROMData.IQAmpCorrectionFactor[i];
    IQPhaseCorrectionFactor[i]            = EEPROMData.IQPhaseCorrectionFactor[i];
    IQXAmpCorrectionFactor[i]             = EEPROMData.IQXAmpCorrectionFactor[i];
    IQXPhaseCorrectionFactor[i]           = EEPROMData.IQXPhaseCorrectionFactor[i];
  }

  if (EEPROMData.lastFrequencies[0][1] < 3560000L || EEPROMData.lastFrequencies[0][0] > 3985000L) {  // Already set?
    EEPROMData.lastFrequencies[0][0] =  3985000L;  // 80 Phone
    EEPROMData.lastFrequencies[1][0] =  7200000L;  // 40
    EEPROMData.lastFrequencies[2][0] = 14285000L;  // 50
    EEPROMData.lastFrequencies[3][0] = 18130000L;  // 17
    EEPROMData.lastFrequencies[4][0] = 21385000L;  // 15
    EEPROMData.lastFrequencies[5][0] = 24950000L;  // 12
    EEPROMData.lastFrequencies[6][0] = 28385800L;  // 10

    EEPROMData.lastFrequencies[0][1] =  3560000L;  // 80 CW
    EEPROMData.lastFrequencies[1][1] =  7030000L;  // 40
    EEPROMData.lastFrequencies[2][1] = 14060000L;  // 20
    EEPROMData.lastFrequencies[3][1] = 18096000L;  // 17
    EEPROMData.lastFrequencies[4][1] = 21060000L;  // 15
    EEPROMData.lastFrequencies[5][1] = 24906000L;  // 12
    EEPROMData.lastFrequencies[6][1] = 28060000L;  // 10
 } else {
    for (int i = 0; i < NUMBER_OF_BANDS; i++) {
      lastFrequencies[i][0] = EEPROMData.lastFrequencies[i][0];
      lastFrequencies[i][1] = EEPROMData.lastFrequencies[i][1];
    }
  }

  //  long favoriteFreqs[MAX_FAVORITES];               // 40 bytes
  centerFreq                            = EEPROMData.lastFrequencies[currentBandA][activeVFO]; // 4 bytes
  currentFreqA                          = EEPROMData.lastFrequencies[currentBandA][VFO_A];     // 4 bytes
  currentFreqB                          = EEPROMData.lastFrequencies[currentBandB][VFO_B];     // 4 bytes
}


/*****
  Purpose: To save the configuration data to EEPROM

  Parameter list:
    struct config_t e[]       pointer to the EEPROM structure

  Return value;
    void
*****/
void EEPROMWrite()
{
    Serial.println("EEPROMWrite ");
  strcpy(EEPROMData.versionSettings, VERSION);        // Save version number

  EEPROMData.AGCMode                    = AGCMode;     // 1 byte
  EEPROMData.CWFilterIndex              = CWFilterIndex;
  EEPROMData.nrInUse                    = nrOptionSelect;     // 1 byte

  EEPROMData.currentVFO                 = activeVFO;  // 2 bytes

  EEPROMData.audioVolume                = audioVolume; // 4 bytes
  EEPROMData.currentBand                = currentBand; // 4 bytes
  EEPROMData.currentBandA               = currentBandA;
  EEPROMData.currentBandB               = currentBandB;
  EEPROMData.decoderFlag                = decoderFlag;

  for (int i = 0; i < EQUALIZER_CELL_COUNT; i++) {
    EEPROMData.equalizerRec[i] = recEQ_Level[i];// 4 bytes each
    EEPROMData.equalizerXmt[i] = xmtEQ_Level[i];
  }

  EEPROMData.freqIncrement              = freqIncrement;  // 4 bytes
  EEPROMData.keyType                    = keyType;  // straight key = 0, keyer = 1
  EEPROMData.currentMicThreshold        = currentMicThreshold;// 4 bytes      // AFP 09-22-22
  EEPROMData.currentMicCompRatio        = currentMicCompRatio;
  EEPROMData.currentMicAttack           = currentMicAttack;
  EEPROMData.currentMicRelease          = currentMicRelease;
  EEPROMData.currentMicGain             = currentMicGain;

  EEPROMData.paddleDit                  = paddleDit;
  EEPROMData.paddleDah                  = paddleDah;
  EEPROMData.rfGainAllBands             = rfGainAllBands;
  EEPROMData.spectrumNoiseFloor         = spectrumNoiseFloor;    // AFP 09-26-22

  EEPROMData.tuneIndex                  = tuneIndex;
  EEPROMData.powerLevel                 = transmitPowerLevel;
  EEPROMData.wordsPerMinute             = currentWPM; // 4 bytes
  EEPROMData.xmtMode                    = xmtMode;                    // AFP 09-26-22

  EEPROMData.currentScale               = currentScale;
  EEPROMData.spectrum_zoom              = spectrum_zoom;
  EEPROMData.spectrum_display_scale     = spectrum_display_scale;// 4 bytes
  EEPROMData.sidetoneVolume             = sidetoneVolume;// 4 bytes
  EEPROMData.cwTransmitDelay            = cwTransmitDelay;   // 4 bytes

  // === ?? centerfreq...

  EEPROMData.freqCorrectionFactor          = freqCorrectionFactor;
  EEPROMData.currentFreqA               = currentFreqA / NEW_SI5351_FREQ_MULT;
  EEPROMData.currentFreqB               = currentFreqB / NEW_SI5351_FREQ_MULT;

  EEPROMData.LPFcoeff                   = LPFcoeff;// 4 bytes
  EEPROMData.NR_PSI                     = NR_PSI;// 4 bytes
  EEPROMData.NR_alpha                   = NR_alpha;// 4 bytes
  EEPROMData.NR_beta                    = NR_beta;// 4 bytes
  EEPROMData.omegaN                     = omegaN;// 4 bytes
  EEPROMData.pll_fmax                   = pll_fmax;// 4 bytes

  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    EEPROMData.CWPowerCalibrationFactor[i]          = CWPowerCalibrationFactor[i];  // 0.019;   //AFP 10-29-22
    EEPROMData.SSBPowerCalibrationFactor[i]         = SSBPowerCalibrationFactor[i]; // 0.008;   //AFP 10-29-22
    EEPROMData.powerOutCW[i]                        = powerOutCW[i];// 4 bytes //AFP 10-21-22
    EEPROMData.powerOutSSB[i]                       = powerOutSSB[i];     // 4 bytes AFP 10-21-22
    EEPROMData.IQAmpCorrectionFactor[i]             = IQAmpCorrectionFactor[i] ;
    EEPROMData.IQPhaseCorrectionFactor[i]           = IQPhaseCorrectionFactor[i] ;
    EEPROMData.IQXAmpCorrectionFactor[i]            = IQXAmpCorrectionFactor[i];
    EEPROMData.IQXPhaseCorrectionFactor[i]          = IQXPhaseCorrectionFactor[i];
  }
  //  Note:favoriteFreqs are written as they are saved.

  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    EEPROMData.lastFrequencies[i][0]    = lastFrequencies[i][0];
    EEPROMData.lastFrequencies[i][1]    = lastFrequencies[i][1];
  }

  EEPROMData.lastFrequencies[currentBand][activeVFO] = currentFreq;   // 4 bytes
  EEPROMData.lastFrequencies[currentBandA][VFO_A]     = currentFreqA;     // 4 bytes
  EEPROMData.lastFrequencies[currentBandB][VFO_B]     = currentFreqB;     // 4 bytes

  EEPROM.put(EEPROM_BASE_ADDRESS, EEPROMData);
} // end void eeProm SAVE

/*****
  Purpose: To show the current EEPROM values. Used for debugging

  Parameter list:
    struct config_t e[]       pointer to the EEPROM structure

  Return value;
    void
*****/
void EEPROMShow()
{
  int i;

  Serial.println("----- EEPROM Parameters: -----");

  Serial.print("Version              = "); Serial.println(EEPROMData.versionSettings);
  Serial.print("AGCMode              = "); Serial.println(EEPROMData.AGCMode);
  Serial.print("audioVolume          = "); Serial.println(EEPROMData.audioVolume);
  Serial.print("CWFilterIndex        = "); Serial.println(EEPROMData.CWFilterIndex);
  Serial.print("nrInUse              = "); Serial.println(EEPROMData.nrInUse);
  Serial.print("powerLevel            ="); Serial.println(EEPROMData.powerLevel);
  Serial.print("rfGainAllBands       = "); Serial.println(EEPROMData.rfGainAllBands);
  Serial.print("spect._display_scale = "); Serial.println(EEPROMData.spectrum_display_scale);
  Serial.print("currentScale         = "); Serial.println(EEPROMData.currentScale);
  Serial.print("spectrum_zoom        = "); Serial.println(EEPROMData.spectrum_zoom);
  Serial.print("freqCorrectionFactor = "); Serial.println(EEPROMData.freqCorrectionFactor);
  Serial.print("xmtMode              = "); Serial.println(EEPROMData.xmtMode);
   Serial.println("----- Current Frequencies & Bands: -----");
  Serial.print("currentVFO           = "); Serial.println(EEPROMData.currentVFO);
  Serial.print("centerFreq           = "); Serial.println( (long)EEPROMData.centerFreq);
  Serial.print("currentFreqA         = "); Serial.println(EEPROMData.currentFreqA);
  Serial.print("currentFreqB         = "); Serial.println(EEPROMData.currentFreqB);
  Serial.print("currentBand          = "); Serial.println(EEPROMData.currentBand);
  Serial.print("currentBandA         = "); Serial.println(EEPROMData.currentBandA);
  Serial.print("currentBandB         = "); Serial.println(EEPROMData.currentBandB);
  Serial.print("freqIncrement        = "); Serial.println(EEPROMData.freqIncrement);
  Serial.println("----- CW Parameters: -----");
  Serial.print("keyType              = "); Serial.println(EEPROMData.keyType);
  Serial.print("paddleDah            = "); Serial.println(EEPROMData.paddleDah);
  Serial.print("paddleDit            = "); Serial.println(EEPROMData.paddleDit);
  Serial.print("decoderFlag          = "); Serial.println(EEPROMData.decoderFlag);
  Serial.print("spectrumNoiseFloor   = "); Serial.println(EEPROMData.spectrumNoiseFloor);
  Serial.print("tuneIndex            = "); Serial.println(EEPROMData.tuneIndex);
  Serial.print("wordsPerMinute       = "); Serial.println(EEPROMData.wordsPerMinute);
  Serial.print("sidetoneVolume       = "); Serial.println(EEPROMData.sidetoneVolume, 5);
  Serial.print("cwTransmitDelay      = "); Serial.println(EEPROMData.cwTransmitDelay);
 
  Serial.println("----- Mic Compressor Parameters -----");
  Serial.print("micCompression       = "); Serial.println(EEPROMData.currentMicThreshold);
  Serial.print("currentMicCompRatio  = "); Serial.println(EEPROMData.currentMicCompRatio);
  Serial.print("currentMicAttack     = "); Serial.println(EEPROMData.currentMicAttack);
  Serial.print("currentMicRelease    = "); Serial.println(EEPROMData.currentMicRelease);
  Serial.print("currentMicGain       = "); Serial.println(EEPROMData.currentMicGain);
Serial.println("----- Favorite Frequencies -----");
  for (i = 0; i < MAX_FAVORITES; i++) {
    Serial.print("favoriteFreqs[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(EEPROMData.favoriteFreqs[i]);
  }
Serial.println("----- Power Out Calibration Parameters -----");
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("CWPowerCalFactor["); Serial.print(i); Serial.print("]= "); Serial.print(EEPROMData.CWPowerCalibrationFactor[i], 5);
    Serial.print("   SSBPowerCalFactor["); Serial.print(i); Serial.print("]= "); Serial.println(EEPROMData.SSBPowerCalibrationFactor[i], 5);
  }
  Serial.println(" ");
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("powerOutCW["); Serial.print(i); Serial.print("]= "); Serial.print(EEPROMData.powerOutCW[i], 5); //AFP 10-13-22
    Serial.print("   powerOutSSB["); Serial.print(i); Serial.print("]= "); Serial.println(EEPROMData.powerOutSSB[i], 5);
  }
Serial.println("----- I/Q Calibration Parameters -----");
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("IQAmplitudeCorrectionFactor["); Serial.print(i); Serial.print("]= ");
    Serial.print(EEPROMData.IQAmpCorrectionFactor[i], 3);
    Serial.print("   IQPhaseCorrectionFactor["); Serial.print(i); Serial.print("]= ");
    Serial.println(EEPROMData.IQPhaseCorrectionFactor[i], 3);
  }
  Serial.println(" ");
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("IQXAmplitudeCorrectionFactor["); Serial.print(i); Serial.print("]= ");
    Serial.print(EEPROMData.IQXAmpCorrectionFactor[i], 3);
    Serial.print("   IQXPhaseCorrectionFactor["); Serial.print(i); Serial.print("]= ");
    Serial.println(EEPROMData.IQXPhaseCorrectionFactor[i], 3);
  }
Serial.println("----- Equalizer Parameters -----");
  for (i = 0; i < EQUALIZER_CELL_COUNT; i++) {
    Serial.print("equalizerRec[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.print(EEPROMData.equalizerRec[i]);

    Serial.print("   equalizerXmt[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(EEPROMData.equalizerXmt[i]);
  }
Serial.println("----- Last Frequencies -----");

  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("lastFrequencies[");
    Serial.print(i);
    Serial.print("][0] ");
    Serial.print(EEPROMData.lastFrequencies[i][0]);
    Serial.print("   lastFrequencies[");
    Serial.print(i);
    Serial.print("][1] ");
    Serial.println(EEPROMData.lastFrequencies[i][1]);
  }
  Serial.println("----- Switch Matrix Values -----");
  for (i = 0; i < NUMBER_OF_SWITCHES; i++) {
    Serial.print("switchValues[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(EEPROMData.switchValues[i]);
  }
 
  Serial.println("----- End EEPROM Parameters -----");
}


/*****
  Purpose: To save the default setting for EEPROM variables

  Parameter list:
    struct config_t e[]       pointer to the EEPROM structure

  Return value;
    void
*****/
void EEPROMSaveDefaults()
{
  strncpy(EEPROMData.versionSettings, VERSION, sizeof(EEPROMData.versionSettings)); // Update version

  EEPROMData.AGCMode                    = 1;     // 1 byte
  EEPROMData.CWFilterIndex              = 5;     // Off
  EEPROMData.nrInUse                    = 0;     // 1 byte

  EEPROMData.currentVFO                 = VFO_A;  // 2 bytes

  EEPROMData.audioVolume                = 50; // 4 bytes
  EEPROMData.currentBand                = 1;  // 4 bytes
  EEPROMData.currentBandA               = 1;
  EEPROMData.currentBandB               = 1;
  EEPROMData.decoderFlag                = 0;  // Off

  for (int i = 0; i < EQUALIZER_CELL_COUNT; i++) {
    EEPROMData.equalizerRec[i] = 100;// 4 bytes each
    EEPROMData.equalizerXmt[i] = 100;
  }
  EEPROMData.freqIncrement              = 5;  // 4 bytes
  EEPROMData.keyType                    = 0;  // straight key = 0, keyer = 1
  EEPROMData.currentMicThreshold        = -10;// 4 bytes      // AFP 09-22-22
  EEPROMData.currentMicCompRatio        = 5.0;//
  EEPROMData.currentMicAttack           = 0.1;//
  EEPROMData.currentMicRelease          = 2.0;//
  EEPROMData.currentMicGain             = -10;

  EEPROMData.paddleDit                  = KEYER_DIT_INPUT_TIP;
  EEPROMData.paddleDah                  = KEYER_DAH_INPUT_RING;
  EEPROMData.rfGainAllBands             = 1;
  EEPROMData.spectrumNoiseFloor         = SPECTRUM_NOISE_FLOOR;    // AFP 09-26-22

  EEPROMData.switchValues[0]                 = 924;      // Your values will likely be different
  EEPROMData.switchValues[1]                 = 870;
  EEPROMData.switchValues[2]                 = 817;
  EEPROMData.switchValues[3]                 = 769;
  EEPROMData.switchValues[4]                 = 713;
  EEPROMData.switchValues[5]                 = 669;
  EEPROMData.switchValues[6]                 = 616;
  EEPROMData.switchValues[7]                 = 565;
  EEPROMData.switchValues[8]                 = 513;
  EEPROMData.switchValues[9]                 = 459;
  EEPROMData.switchValues[10]                = 407;
  EEPROMData.switchValues[11]                = 356;
  EEPROMData.switchValues[12]                = 298;
  EEPROMData.switchValues[13]                = 242;
  EEPROMData.switchValues[14]                = 183;
  EEPROMData.switchValues[15]                = 131;
  EEPROMData.switchValues[16]                = 67;
  EEPROMData.switchValues[17]                = 10;

  EEPROMData.tuneIndex                  = 5;
  EEPROMData.powerLevel                 = 10;
  EEPROMData.wordsPerMinute             = 15; // 4 bytes
  EEPROMData.xmtMode                    = SSB_MODE;                    // AFP 09-26-22

  EEPROMData.currentScale               = 1;
  EEPROMData.spectrum_zoom              = SPECTRUM_ZOOM_2;
  EEPROMData.spectrum_display_scale     = 20.0;// 4 bytes
  EEPROMData.sidetoneVolume             = 0.001;// 4 bytes AFP 10-19-22
  EEPROMData.cwTransmitDelay            = 750L;   // ms for xmt relay to cycle

  EEPROMData.freqCorrectionFactor          = 68000LL;
  EEPROMData.currentFreqA               = 7200000L;
  EEPROMData.currentFreqB               = 7030000L;

  EEPROMData.LPFcoeff                   = LPFcoeff;// 4 bytes
  EEPROMData.NR_PSI                     = 0.0;// 4 bytes
  EEPROMData.NR_alpha                   = 0.0;// 4 bytes
  EEPROMData.NR_beta                    = 0.0;// 4 bytes
  EEPROMData.omegaN                     = 0.0;// 4 bytes
  EEPROMData.pll_fmax                   = 4000.0;// 4 bytes

  EEPROMData.powerOutCW[0]                 = 0.188;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[1]                 = 0.21;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[2]                 = 0.34;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[3]                 = 0.44;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[4]                 = 0.31;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[5]                 = 0.31;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[6]                 = 0.31;// 4 bytes  AFP 10-21-22

  EEPROMData.powerOutSSB[0]                 = 0.188;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[1]                 = 0.11;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[2]                 = 0.188;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[3]                 = 0.21;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[4]                 = 0.23;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[5]                 = 0.23;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[6]                 = 0.24;// 4 bytes  AFP 10-21-22

  EEPROMData.CWPowerCalibrationFactor[0]   = 0.017;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[1]   = 0.011;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[2]   = 0.031;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[3]   = 0.04;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[4]   = 0.028;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[5]   = 0.028;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[6]   = 0.028;   //AFP 10-29-22

  EEPROMData.SSBPowerCalibrationFactor[0]  = 0.017;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[1]  = 0.019;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[2]  = 0.017;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[3]  = 0.019;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[4]  = 0.021;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[5]  = 0.020;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[6]  = 0.022;   //AFP 10-29-22

  EEPROMData.IQAmpCorrectionFactor[0]            = 1.008;
  EEPROMData.IQAmpCorrectionFactor[1]            = 1.024;
  EEPROMData.IQAmpCorrectionFactor[2]            = 1.057;
  EEPROMData.IQAmpCorrectionFactor[3]            = 1.061;
  EEPROMData.IQAmpCorrectionFactor[4]            = 1.06;
  EEPROMData.IQAmpCorrectionFactor[5]            = 1.092;
  EEPROMData.IQAmpCorrectionFactor[6]            = 1.105;

  EEPROMData.IQPhaseCorrectionFactor[0]          = 0.003;
  EEPROMData.IQPhaseCorrectionFactor[1]          = 0.007;
  EEPROMData.IQPhaseCorrectionFactor[2]          = -0.027;
  EEPROMData.IQPhaseCorrectionFactor[3]          = -0.041;
  EEPROMData.IQPhaseCorrectionFactor[4]          = -0.047;
  EEPROMData.IQPhaseCorrectionFactor[5]          = -0.032;
  EEPROMData.IQPhaseCorrectionFactor[6]          = -0.044;

  EEPROMData.IQXAmpCorrectionFactor[0]           = 1.049;
  EEPROMData.IQXAmpCorrectionFactor[1]           = 1.099;
  EEPROMData.IQXAmpCorrectionFactor[2]           = 1.009;
  EEPROMData.IQXAmpCorrectionFactor[3]           = .815;
  EEPROMData.IQXAmpCorrectionFactor[4]           = 0.9;
  EEPROMData.IQXAmpCorrectionFactor[5]           = 0.9;
  EEPROMData.IQXAmpCorrectionFactor[6]           = 0.9;

  EEPROMData.IQXPhaseCorrectionFactor[0]        = 0.101;
  EEPROMData.IQXPhaseCorrectionFactor[1]        = 0.199;
  EEPROMData.IQXPhaseCorrectionFactor[2]        = 0.589;
  EEPROMData.IQXPhaseCorrectionFactor[3]        = 0.849;
  EEPROMData.IQXPhaseCorrectionFactor[4]        = 0.75;
  EEPROMData.IQXPhaseCorrectionFactor[5]        = 0.75;
  EEPROMData.IQXPhaseCorrectionFactor[6]        = 0.75;

  EEPROMData.favoriteFreqs[0]                =  3560000L;             // These are CW/SSB calling frequencies for HF bands
  EEPROMData.favoriteFreqs[1]                =  3690000L;
  EEPROMData.favoriteFreqs[2]                =  7030000L;
  EEPROMData.favoriteFreqs[3]                =  7200000L;
  EEPROMData.favoriteFreqs[4]                = 14060000L;
  EEPROMData.favoriteFreqs[5]                = 14200000L;
  EEPROMData.favoriteFreqs[6]                = 21060000L;
  EEPROMData.favoriteFreqs[7]                = 21285000L;
  EEPROMData.favoriteFreqs[8]                = 28060000L;
  EEPROMData.favoriteFreqs[9]                = 28365000L;
  EEPROMData.favoriteFreqs[10]               =  5000000L;
  EEPROMData.favoriteFreqs[11]               = 10000000L;
  EEPROMData.favoriteFreqs[12]               = 15000000L;


  // The following are QRP calling frequencies
  EEPROMData.lastFrequencies[0][0] =  3985000L;  // 80 Phone
  EEPROMData.lastFrequencies[1][0] =  7200000L;  // 40
  EEPROMData.lastFrequencies[2][0] = 14285000L;  // 50
  EEPROMData.lastFrequencies[3][0] = 18130000L;  // 17
  EEPROMData.lastFrequencies[4][0] = 21385000L;  // 15
  EEPROMData.lastFrequencies[5][0] = 24950000L;  // 12
  EEPROMData.lastFrequencies[6][0] = 28385800L;  // 10

  EEPROMData.lastFrequencies[0][1] =  3560000L;  // 80 CW
  EEPROMData.lastFrequencies[1][1] =  7030000L;  // 40
  EEPROMData.lastFrequencies[2][1] = 14060000L;  // 20
  EEPROMData.lastFrequencies[3][1] = 18096000L;  // 17
  EEPROMData.lastFrequencies[4][1] = 21060000L;  // 15
  EEPROMData.lastFrequencies[5][1] = 24906000L;  // 12
  EEPROMData.lastFrequencies[6][1] = 28060000L;  // 10

  //centerFreq = EEPROMData.lastFrequencies[currentBand][activeVFO];   // 4 bytes
  //currentFreqA = EEPROMData.lastFrequencies[currentBand][VFO_A];     // 4 bytes
  //currentFreqB = EEPROMData.lastFrequencies[currentBand][VFO_B];
  EEPROM.put(EEPROM_BASE_ADDRESS, EEPROMData);                        // Write as one large chunk
}


/*****
  Purpose: Read default favorite frequencies

  Parameter list:
    struct config_t e[]       pointer to the EEPROM structure

  Return value;
    void
*****/
void EEPROMStuffFavorites(unsigned long current[])
{
  int i;

  for (i = 0; i < MAX_FAVORITES; i++) {
    current[i] = EEPROMData.favoriteFreqs[i];
  }
}

/*****
  Purpose: Used to save a favortie frequency to EEPROM

  Parameter list:

  Return value;
    void

  CAUTION: This code assumes you have set the curently active VFO frequency to the new
           frequency you wish to save. You them use the menu encoder to scroll through
           the current list of stored frequencies. Stop on the one that you wish to
           replace and press Select to save in EEPROM. The currently active VFO frequency
           is then stored to EEPROM.
*****/
void SetFavoriteFrequency()
{
  int index;
  int val;

  tft.setFontScale( (enum RA8875tsize) 1);

  index = 0;
  tft.setTextColor(RA8875_WHITE);
  tft.fillRect(SECONDARY_MENU_X, MENUS_Y, EACH_MENU_WIDTH, CHAR_HEIGHT, RA8875_MAGENTA);
  tft.setCursor(SECONDARY_MENU_X, MENUS_Y);
  tft.print(EEPROMData.favoriteFreqs[index]);
  while (true) {
    if (filterEncoderMove != 0) {                 // Changed encoder?
      index += filterEncoderMove;                 // Yep
      if (index < 0) {
        index = MAX_FAVORITES - 1;                // Wrap to last one
      } else {
        if (index > MAX_FAVORITES)
          index = 0;                                // Wrap to first one
      }
      tft.fillRect(SECONDARY_MENU_X, MENUS_Y, EACH_MENU_WIDTH, CHAR_HEIGHT, RA8875_MAGENTA);
      tft.setCursor(SECONDARY_MENU_X, MENUS_Y);
      tft.print(EEPROMData.favoriteFreqs[index]);
      filterEncoderMove = 0;
    }

    val = ReadSelectedPushButton();                               // Read pin that controls all switches
    val = ProcessButtonPress(val);
    MyDelay(150L);
    if (val == MENU_OPTION_SELECT) {                              // Make a choice??
      EraseMenus();
      EEPROMData.favoriteFreqs[index] = TxRxFreq;
      if (activeVFO == VFO_A) {
        currentFreqA = TxRxFreq;
      } else {
        currentFreqB = TxRxFreq;
      }
      EEPROMWrite();
      SetFreq();
      BandInformation();
      ShowBandwidth();
      FilterBandwidth();
      ShowFrequency();
      break;
    }
  }
}

/*****
  Purpose: Used to fetch a favortie frequency as stored in EEPROM. It then copies that
           frequency to the currently active VFO

  Parameter list:

  Return value;
    void
*****/
void GetFavoriteFrequency()
{
  int index = 0;
  int val;
  int tempIndex;
  int currentBand2;
  tft.setFontScale( (enum RA8875tsize) 1);

  tft.setTextColor(RA8875_WHITE);
  tft.fillRect(SECONDARY_MENU_X, MENUS_Y, EACH_MENU_WIDTH, CHAR_HEIGHT, RA8875_MAGENTA);
  tft.setCursor(SECONDARY_MENU_X, MENUS_Y);
  tft.print(EEPROMData.favoriteFreqs[index]);
  while (true) {
    if (filterEncoderMove != 0) {                 // Changed encoder?
      index += filterEncoderMove;                 // Yep
      if (index < 0) {
        index = MAX_FAVORITES - 1;                // Wrap to last one
      } else {
        if (index > MAX_FAVORITES)
          index = 0;                                // Wrap to first one
      }
      tft.fillRect(SECONDARY_MENU_X, MENUS_Y, EACH_MENU_WIDTH, CHAR_HEIGHT, RA8875_MAGENTA);
      tft.setCursor(SECONDARY_MENU_X, MENUS_Y);
      tft.print(EEPROMData.favoriteFreqs[index]);
      filterEncoderMove = 0;
    }

    val = ReadSelectedPushButton();                               // Read pin that controls all switches
    val = ProcessButtonPress(val);
    MyDelay(150L);

    centerFreq = EEPROMData.favoriteFreqs[index];    // current frequency  AFP 09-27-22
    if (centerFreq >= bands[BAND_80M].fBandLow && centerFreq <= bands[BAND_80M].fBandHigh) {
      currentBand2 = BAND_80M;
    } else if (centerFreq >= bands[BAND_80M].fBandHigh && centerFreq <= 7000000L) { // covers 5MHz WWV AFP 11-03-22
      currentBand2 = BAND_80M;
    } else if (centerFreq >= bands[BAND_40M].fBandLow && centerFreq <= bands[BAND_40M].fBandHigh) {
      currentBand2 = BAND_40M;
    } else if (centerFreq >= bands[BAND_40M].fBandHigh && centerFreq <= 14000000L) {   // covers 10MHz WWV AFP 11-03-22
      currentBand2 = BAND_40M;
    } else if (centerFreq >= bands[BAND_20M].fBandLow && centerFreq <= bands[BAND_20M].fBandHigh) {
      currentBand2 = BAND_20M;
    } else if (centerFreq >= 14000000L && centerFreq <= 18000000L) {      // covers 15MHz WWV AFP 11-03-22
      currentBand2 = BAND_20M;
    } else if (centerFreq >= bands[BAND_17M].fBandLow && centerFreq <= bands[BAND_17M].fBandHigh) {
      currentBand2 = BAND_17M;
    } else if (centerFreq >= bands[BAND_15M].fBandLow && centerFreq <= bands[BAND_15M].fBandHigh) {
      currentBand2 = BAND_15M;
    } else if (centerFreq >= bands[BAND_12M].fBandLow && centerFreq <= bands[BAND_12M].fBandHigh) {
      currentBand2 = BAND_12M;
    } else if (centerFreq >= bands[BAND_10M].fBandLow && centerFreq <= bands[BAND_10M].fBandHigh) {
      currentBand2 = BAND_10M;
    }
    currentBand = currentBand2;


    if (val == MENU_OPTION_SELECT) {                              // Make a choice??
      switch (activeVFO) {
        case VFO_A:
          if (currentBandA == NUMBER_OF_BANDS) {                         // Incremented too far?
            currentBandA = 0;                                            // Yep. Roll to list front.
          }
          currentBandA = currentBand2;
          TxRxFreq = centerFreq  + NCOFreq;
          break;

        case VFO_B:
          if (currentBandB == NUMBER_OF_BANDS) {                         // Incremented too far?
            currentBandB = 0;                                            // Yep. Roll to list front.
          }        // Same for VFO B
          currentBandB = currentBand2 ;
          TxRxFreq = centerFreq  + NCOFreq;
          break;
      }
    }
    if (val == MENU_OPTION_SELECT) {

      EraseSpectrumDisplayContainer();
      currentMode = bands[currentBand].mode;
      DrawSpectrumDisplayContainer();
      DrawFrequencyBarValue();
      SetBand();
      SetFreq();
      ShowFrequency();
      ShowSpectrumdBScale();
      EraseMenus();
      ResetTuning();
      FilterBandwidth();
      BandInformation();
      NCOFreq = 0L;
      DrawBandWidthIndicatorBar(); // AFP 10-20-22
      digitalWrite(bandswitchPins[currentBand], LOW);
      SetFreq();
      ShowSpectrumdBScale();
      ShowSpectrum();
      //bands[currentBand].mode = currentBand;
      return;
    }
  }
}
