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
  freqIncrement                         = EEPROMData.freqIncrement;  // 4 bytes
  keyType                               = EEPROMData.keyType;  // straight key = 0, keyer = 1
  micCompression                        = EEPROMData.micCompression;// 4 bytes      // AFP 09-22-22  
  paddleDit                             = EEPROMData.paddleDit;
  paddleDah                             = EEPROMData.paddleDah;
  rfGainAllBands                        = EEPROMData.rfGainAllBands;
  spectrumNoiseFloor                    = EEPROMData.spectrumNoiseFloor;    // AFP 09-26-22
//  int switchValues[NUMBER_OF_SWITCHES];      18 // 64 bytes
  tuneIndex                             = EEPROMData.tuneIndex;
  transmitPowerLevel                    = EEPROMData.powerLevel;
  currentWPM                            = EEPROMData.wordsPerMinute; // 4 bytes
  xmtMode                               = EEPROMData.xmtMode;                    // AFP 09-26-22

  currentScale                          = EEPROMData.currentScale;

  spectrum_zoom                         = EEPROMData.spectrum_zoom;

  centerFreq                            = EEPROMData.lastFrequencies[currentBand][activeVFO]; // 4 bytes
  currentFreqA                          = EEPROMData.lastFrequencies[currentBand][VFO_A];     // 4 bytes
  currentFreqB                          = EEPROMData.lastFrequencies[currentBand][VFO_B];     // 4 bytes
  
  frequencyCorrectionFactor             = EEPROMData.calibrationFactor;
  frequencyCorrection                   = EEPROMData.frequencyOffset;
  if (EEPROMData.lastFrequencies[0][1] < 3560000L || EEPROMData.lastFrequencies[0][0] > 3985000L) {  // Already set?
    EEPROMData.lastFrequencies[0][0] =  3985000L;  // 80 Phone
    EEPROMData.lastFrequencies[1][0] =  7285000L;  // 40
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
  LPFcoeff                              = EEPROMData.LPFcoeff;// 4 bytes
  NR_PSI                                = EEPROMData.NR_PSI;// 4 bytes
  NR_alpha                              = EEPROMData.NR_alpha;// 4 bytes
  NR_beta                               = EEPROMData.NR_beta;// 4 bytes
  omegaN                                = EEPROMData.omegaN;// 4 bytes
  pll_fmax                              = EEPROMData.pll_fmax;// 4 bytes
  powerOutCW                            = EEPROMData.powerOutCW;// 4 bytes  //AFP 10-21-22
  powerOutSSB                           = EEPROMData.powerOutSSB;     // 4 bytes AFP 10-21-22
  CWPowerCalibrationFactor              = EEPROMData.CWPowerCalibrationFactor;  // 0.019;   //AFP 10-21-22
  SSBPowerCalibrationFactor             = EEPROMData.SSBPowerCalibrationFactor; // 0.008;   //AFP 10-21-22
  
  spectrum_display_scale                = EEPROMData.spectrum_display_scale;// 4 bytes
  sidetoneVolume                        = EEPROMData.sidetoneVolume;// 4 bytes
  IQ_amplitude_correction_factor        = EEPROMData.IQ_AmpCorFactor;
  IQ_phase_correction_factor            = EEPROMData.IQ_PhaseCorFactor;
  IQ_Xamplitude_correction_factor       = EEPROMData.IQ_XAmpCorFactor;
  IQ_Xphase_correction_factor           = EEPROMData.IQ_XPhanseCorFactor;

  cwTransmitDelay                       = EEPROMData.cwTransmitDelay;   // 4 bytes
//  long favoriteFreqs[MAX_FAVORITES];               // 40 bytes
  frequencyCorrection                       = EEPROMData.frequencyOffset;     // 4 bytes  
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
  strcpy(EEPROMData.versionSettings, VERSION);        // Save version number

  EEPROMData.AGCMode                    = AGCMode;     // 1 byte
  EEPROMData.nrInUse                    = nrOptionSelect;     // 1 byte

  EEPROMData.currentVFO                 = activeVFO;  // 2 bytes

  EEPROMData.audioVolume                = audioVolume; // 4 bytes
  EEPROMData.CWFilterIndex              = CWFilterIndex;
  EEPROMData.currentBand                = currentBand; // 4 bytes
  EEPROMData.currentBandA               = currentBandA;
  EEPROMData.currentBandB               = currentBandB;
  EEPROMData.decoderFlag                = decoderFlag; 
  EEPROMData.freqIncrement              = freqIncrement;  // 4 bytes
  EEPROMData.keyType                    = keyType;  // straight key = 0, keyer = 1
  EEPROMData.micCompression             = micCompression;// 4 bytes      // AFP 09-22-22  
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

  EEPROMData.lastFrequencies[currentBand][activeVFO] = centerFreq;   // 4 bytes
  EEPROMData.lastFrequencies[currentBand][VFO_A]     = currentFreqA;     // 4 bytes
  EEPROMData.lastFrequencies[currentBand][VFO_B]     = currentFreqB;     // 4 bytes
  
  EEPROMData.calibrationFactor          = frequencyCorrectionFactor;
  EEPROMData.currentFreqA               = currentFreqA / NEW_SI5351_FREQ_MULT;
  EEPROMData.currentFreqB               = currentFreqB / NEW_SI5351_FREQ_MULT;
  EEPROMData.frequencyOffset            = frequencyCorrection;
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    EEPROMData.lastFrequencies[i][0]    = lastFrequencies[i][0];
    EEPROMData.lastFrequencies[i][1]    = lastFrequencies[i][1];
  }

  EEPROMData.LPFcoeff                   = LPFcoeff;// 4 bytes
  EEPROMData.NR_PSI                     = NR_PSI;// 4 bytes
  EEPROMData.NR_alpha                   = NR_alpha;// 4 bytes
  EEPROMData.NR_beta                    = NR_beta;// 4 bytes
  EEPROMData.omegaN                     = omegaN;// 4 bytes
  EEPROMData.pll_fmax                   = pll_fmax;// 4 bytes
  EEPROMData.powerOutCW                 = powerOutCW;// 4 bytes //AFP 10-21-22
  EEPROMData.powerOutSSB                = powerOutSSB;     // 4 bytes AFP 10-21-22
  EEPROMData.CWPowerCalibrationFactor   = CWPowerCalibrationFactor;  // 0.019;   //AFP 10-21-22
  EEPROMData.SSBPowerCalibrationFactor  = SSBPowerCalibrationFactor; // 0.008;   //AFP 10-21-22
 
  EEPROMData.spectrum_display_scale     = spectrum_display_scale;// 4 bytes
  EEPROMData.sidetoneVolume             = sidetoneVolume;// 4 bytes
  EEPROMData.cwTransmitDelay            = cwTransmitDelay;   // 4 bytes
  EEPROMData.frequencyOffset            = frequencyCorrection;    // 4 bytes
                        
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
  Serial.println("In EEPROM:");

  Serial.print("Version            = ");
  Serial.println(EEPROMData.versionSettings);
  Serial.print("AGCMode            = ");
  Serial.println(EEPROMData.AGCMode);
  Serial.print("CWFilterIndex      = ");
  Serial.println(EEPROMData.CWFilterIndex);
  Serial.print("nrInUse            = ");
  Serial.println(EEPROMData.nrInUse);
  Serial.print("xmtMode            = ");
  Serial.println(EEPROMData.xmtMode);
  Serial.print("currentVFO        = ");
  Serial.println(EEPROMData.currentVFO);
  Serial.print("audioVolume      = ");
  Serial.println(EEPROMData.audioVolume);
  Serial.print("freqIncrement     = ");
  Serial.println(EEPROMData.freqIncrement);
  Serial.print("keyType           = ");
  Serial.println(EEPROMData.keyType);

  Serial.print("paddleDah        = ");
  Serial.println(EEPROMData.paddleDah);
  Serial.print("paddleDit        = ");
  Serial.println(EEPROMData.paddleDit);

  Serial.print("spectrumNoiseFloor = ");
  Serial.println(EEPROMData.spectrumNoiseFloor);

  Serial.print("tuneIndex        = ");
  Serial.println(EEPROMData.tuneIndex);
  Serial.print("wordsPerMinute   = ");
  Serial.println(EEPROMData.wordsPerMinute);

  Serial.print("currentScale     = ");
  Serial.println(EEPROMData.currentScale);
  Serial.print("spectrum_zoom    = ");
  Serial.println(EEPROMData.spectrum_zoom);
  Serial.print("calibrationFactor = ");
  Serial.println(EEPROMData.calibrationFactor);

  Serial.print("currentFreq      = ");
  Serial.println(EEPROMData.centerFreq);
  Serial.print("currentFreqA      = ");
  Serial.println(EEPROMData.currentFreqA);
  Serial.print("currentFreqB      = ");
  Serial.println(EEPROMData.currentFreqB);
  Serial.print("currentBand      = ");
  Serial.println(EEPROMData.currentBand);
  Serial.print("currentBandA     = ");
  Serial.println(EEPROMData.currentBandA);
  Serial.print("currentBandB     = ");
  Serial.println(EEPROMData.currentBandB);
  Serial.print("decoderFlag      = ");
  Serial.println(EEPROMData.decoderFlag);

  for (i = 0; i < MAX_FAVORITES; i++) {
    Serial.print("favoriteFreqs[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(EEPROMData.favoriteFreqs[i]);
  }

  Serial.print("centerFreq                = ");
  Serial.println( (long)EEPROMData.centerFreq);
  Serial.print("LPFcoeff                  = ");
  Serial.println(EEPROMData.LPFcoeff);
  Serial.print("micCompression            = ");
  Serial.println(EEPROMData.micCompression);
  Serial.print("NR_PSI                    = ");
  Serial.println(EEPROMData.NR_PSI);
  Serial.print("NR_alpha                  = ");
  Serial.println(EEPROMData.NR_alpha);
  Serial.print("NR_beta                   = ");
  Serial.println(EEPROMData.NR_beta);
  Serial.print("omegaN                    = ");
  Serial.println(EEPROMData.omegaN);
  Serial.print("pll_fmax                  = ");
  Serial.println(EEPROMData.pll_fmax);
  Serial.print("powerLevel                =");
  Serial.println(EEPROMData.powerLevel);
  Serial.print("spectrum_display_scale    = ");
  Serial.println(EEPROMData.spectrum_display_scale);
  Serial.print("powerOutCW                =");  //AFP 10-21-22
  Serial.println(EEPROMData.powerOutCW, 5);   //AFP 10-13-22
  Serial.print("powerOutSSB               =");  //AFP 10-21-22
  Serial.println(EEPROMData.powerOutSSB, 5);   //AFP 10-13-22
  Serial.print("CWPowerCalibrationFactor  =");  //AFP 10-21-22
  Serial.println(EEPROMData.CWPowerCalibrationFactor, 5);   //AFP 10-13-22
  Serial.print("SSBPowerCalibrationFactor =");  //AFP 10-21-22
  Serial.println(EEPROMData.SSBPowerCalibrationFactor, 5);   //AFP 10-13-22

  Serial.print("IQ_amplitude_correction_factor = ");
  Serial.println(EEPROMData.IQ_AmpCorFactor);
  Serial.print("IQ_phase_correction_factor = ");
  Serial.println(EEPROMData.IQ_PhaseCorFactor);
  Serial.print("IQ_Xamplitude_correction_factor = ");
  Serial.println(EEPROMData.IQ_XAmpCorFactor);
  Serial.print("IQ_Xphase_correction_factor = ");
  Serial.println(EEPROMData.IQ_XPhanseCorFactor);
  Serial.print("sidetoneVolume           = ");
  Serial.println(EEPROMData.sidetoneVolume, 5);
  Serial.print("cwTransmitDelay          = ");
  Serial.println(EEPROMData.cwTransmitDelay);

  for (i = 0; i < EQUALIZER_CELL_COUNT; i++) {
    Serial.print("equalizerRec[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(EEPROMData.equalizerRec[i]);
  }
  Serial.println("");
  for (i = 0; i < EQUALIZER_CELL_COUNT; i++) {
    Serial.print("equalizerXmt[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(EEPROMData.equalizerXmt[i]);
  }
  Serial.println("");

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

  for (i = 0; i < NUMBER_OF_SWITCHES; i++) {
    Serial.print("switchValues[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(EEPROMData.switchValues[i]);
  }
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
  EEPROMData.micCompression             = 10;// 4 bytes      // AFP 09-22-22  
  EEPROMData.paddleDit                  = KEYER_DIT_INPUT_TIP;
  EEPROMData.paddleDah                  = KEYER_DAH_INPUT_RING;
  EEPROMData.rfGainAllBands             = 1;
  EEPROMData.spectrumNoiseFloor         = SPECTRUM_NOISE_FLOOR;    // AFP 09-26-22

  EEPROMData.switchValues[0]                 = 921;      // Your values will likely be different
  EEPROMData.switchValues[1]                 = 869;
  EEPROMData.switchValues[2]                 = 817;
  EEPROMData.switchValues[3]                 = 766;
  EEPROMData.switchValues[4]                 = 716;
  EEPROMData.switchValues[5]                 = 665;
  EEPROMData.switchValues[6]                 = 614;
  EEPROMData.switchValues[7]                 = 563;
  EEPROMData.switchValues[8]                 = 510;
  EEPROMData.switchValues[9]                 = 459;
  EEPROMData.switchValues[10]                = 407;
  EEPROMData.switchValues[11]                = 353;
  EEPROMData.switchValues[12]                = 298;
  EEPROMData.switchValues[13]                = 242;
  EEPROMData.switchValues[14]                = 185;
  EEPROMData.switchValues[15]                = 124;
  EEPROMData.switchValues[16]                = 65;
  EEPROMData.switchValues[17]                = 3;

  EEPROMData.tuneIndex                  = 5;
  EEPROMData.powerLevel                 = 10;
  EEPROMData.wordsPerMinute             = 15; // 4 bytes
  EEPROMData.xmtMode                    = SSB_MODE;                    // AFP 09-26-22

  EEPROMData.currentScale               = 1;  

  EEPROMData.spectrum_zoom              = 1;

  centerFreq = EEPROMData.lastFrequencies[currentBand][activeVFO];   // 4 bytes
  currentFreqA = EEPROMData.lastFrequencies[currentBand][VFO_A];     // 4 bytes
  currentFreqB = EEPROMData.lastFrequencies[currentBand][VFO_B];     // 4 bytes
  
  EEPROMData.calibrationFactor          = 230000LL;
  EEPROMData.currentFreqA               = currentFreqA / NEW_SI5351_FREQ_MULT;
  EEPROMData.currentFreqB               = currentFreqB / NEW_SI5351_FREQ_MULT;
  EEPROMData.frequencyOffset            = 230000L;

  EEPROMData.lastFrequencies[0][0] =  3985000L;  // 80 SSB
  EEPROMData.lastFrequencies[1][0] =  7285000L;  // 40
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

  EEPROMData.LPFcoeff                   = LPFcoeff;// 4 bytes
  EEPROMData.NR_PSI                     = 0.0;// 4 bytes
  EEPROMData.NR_alpha                   = 0.0;// 4 bytes
  EEPROMData.NR_beta                    = 0.0;// 4 bytes
  EEPROMData.omegaN                     = 0.0;// 4 bytes
  EEPROMData.pll_fmax                   = 4000.0;// 4 bytes
  EEPROMData.powerOutCW                 = 0.2;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB                = 0.03;     // 4 bytes AFP 10-21-22
  EEPROMData.CWPowerCalibrationFactor   = 0.019;   //AFP 10-21-22
  EEPROMData.SSBPowerCalibrationFactor  = 0.008;   //AFP 10-21-22
  
  EEPROMData.spectrum_display_scale     = 0.0;// 4 bytes
  EEPROMData.sidetoneVolume             = 0.001;// 4 bytes AFP 10-19-22

  EEPROMData.IQ_AmpCorFactor            = 1.0;
  EEPROMData.IQ_PhaseCorFactor          = 0.0;
  EEPROMData.IQ_XAmpCorFactor           = 1.0;
  EEPROMData.IQ_XPhanseCorFactor        = 0.0;

  EEPROMData.cwTransmitDelay            = 750L;   // ms for xmt relay to cycle

  EEPROMData.favoriteFreqs[0]                =  3560000L;             // These are CW/SSB calling frequencies for HF bands
  EEPROMData.favoriteFreqs[1]                =  3690000L;
  EEPROMData.favoriteFreqs[2]                =  7030000L;
  EEPROMData.favoriteFreqs[3]                =  7285000L;
  EEPROMData.favoriteFreqs[4]                = 14060000L;
  EEPROMData.favoriteFreqs[5]                = 14200000L;
  EEPROMData.favoriteFreqs[6]                = 21060000L;
  EEPROMData.favoriteFreqs[7]                = 21285000L;
  EEPROMData.favoriteFreqs[8]                = 28060000L;
  EEPROMData.favoriteFreqs[9]                = 28365000L;

  EEPROMData.frequencyOffset            = 0L; // 4 bytes
                                                 // The following are QRP calling frequencies
  EEPROMData.lastFrequencies[0][0] =  3985000L;  // 80 Phone
  EEPROMData.lastFrequencies[1][0] =  7285000L;  // 40
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
    if (val == MENU_OPTION_SELECT) {                              // Make a choice??
      EraseMenus();
      TxRxFreq = EEPROMData.favoriteFreqs[index];    // current frequency  AFP 09-27-22
      if (activeVFO == VFO_A) {
        currentFreqA = TxRxFreq;    //AFP 09-27-22
      } else {
        currentFreqB = TxRxFreq;  //AFP 09-27-22
      }
      SetFreq();
      BandInformation();
      ShowBandwidth();
      FilterBandwidth();
      ShowFrequency();
      break;
    }
  }
}
