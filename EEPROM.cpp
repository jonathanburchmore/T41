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

  EEPROM.get(EEPROM_BASE_ADDRESS, EEPROMData);                            // Read as one large chunk
  
  currentWPM           = EEPROMData.wordsPerMinute;       // AFP 09-26-22
  paddleDit            = EEPROMData.paddleDit;
  paddleDah            = EEPROMData.paddleDah;
  spectrumNoiseFloor   = EEPROMData.spectrumNoiseFloor;    // AFP 09-26-22
  spectrum_zoom        = EEPROMData.spectrum_zoom; 
  currentBand          = EEPROMData.currentBand;
  activeVFO            = EEPROMData.currentVFO;             // AFP 09-26-22
  nrOptionSelect       = EEPROMData.nrInUse;                              // The filter selected
  NR_Filter_Value      = EEPROMData.NR_Filter_Values[nrOptionSelect];     // The filter encoder value

  micCompression       = EEPROMData.micCompression;           // AFP 09-26-22
  transmitPowerLevel   = EEPROMData.powerLevel;
  powerOut             = EEPROMData.powerOut;                  // AFP 09-26-22
  xmtMode              = EEPROMData.xmtMode;                    // AFP 09-26-22

  rfGainAllBands       = EEPROMData.rfGainAllBands;
  AGCMode              = EEPROMData.AGCMode;                     // AFP 09-26-22
  tuneIndex            = EEPROMData.tuneIndex;
 
  frequencyCorrectionFactor = EEPROMData.calibrationFactor;
  frequencyCorrection       = EEPROMData.frequencyOffset;

  IQ_amplitude_correction_factor  = EEPROMData.IQ_AmpCorFactor;
  IQ_phase_correction_factor      = EEPROMData.IQ_PhaseCorFactor;
  IQ_Xamplitude_correction_factor = EEPROMData.IQ_XAmpCorFactor;
  IQ_Xphase_correction_factor     = EEPROMData.IQ_XPhanseCorFactor;
 
  sidetoneVolume        = EEPROMData.sidetoneVolume;
  cwTransmitDelay       = EEPROMData.cwTransmitDelay;               // AFP 09-27-22
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {                         
    lastFrequencies[i][0] = EEPROMData.lastFrequencies[i][0];      
    lastFrequencies[i][1] = EEPROMData.lastFrequencies[i][1];       
  }
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
  strcpy(EEPROMData.version_of_settings, VERSION);        // Save version number
  EEPROMData.attenuator         = attenuator;
  EEPROMData.currentBand        = currentBand;
  EEPROMData.centerFreq         = centerFreq;
  EEPROMData.currentFreqA       = currentFreqA / NEW_SI5351_FREQ_MULT;
  EEPROMData.currentFreqB       = currentFreqB / NEW_SI5351_FREQ_MULT;
  EEPROMData.currentVFO         = activeVFO;
  EEPROMData.freqIncrement      = freqIncrement;
  EEPROMData.frequencyOffset    = frequencyCorrection;
  EEPROMData.IQ_AmpCorFactor    = IQ_amplitude_correction_factor;
  EEPROMData.IQ_PhaseCorFactor  = IQ_phase_correction_factor;
  EEPROMData.IQ_XAmpCorFactor   = IQ_Xamplitude_correction_factor;
  EEPROMData.IQ_XPhanseCorFactor = IQ_Xphase_correction_factor;
  EEPROMData.micCompression     = micCompression;
  EEPROMData.NR_Filter_Value    = NR_Filter_Value;
  EEPROMData.nrInUse            = nrOptionSelect;
  EEPROMData.paddleDit          = paddleDit;
  EEPROMData.paddleDah          = paddleDah;
  EEPROMData.powerLevel         = transmitPowerLevel;
  EEPROMData.powerOut           = powerOut;

  EEPROMData.rfGainAllBands             = rfGainAllBands;
  EEPROMData.spectrumNoiseFloor = spectrumNoiseFloor;
  EEPROMData.powerLevel         = transmitPowerLevel;
  EEPROMData.tuneIndex          = tuneIndex;
  EEPROMData.calibrationFactor = frequencyCorrectionFactor;
  EEPROMData.wordsPerMinute     = currentWPM;
  EEPROMData.xmtMode            = xmtMode;
  EEPROMData.sidetoneVolume     = sidetoneVolume;
  EEPROMData.cwTransmitDelay    = cwTransmitDelay;
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    EEPROMData.lastFrequencies[i][0] = lastFrequencies[i][0];
    EEPROMData.lastFrequencies[i][1] = lastFrequencies[i][1];
  }
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
  Serial.println(EEPROMData.version_of_settings);
  Serial.print("AGCMode            = ");
  Serial.println(EEPROMData.AGCMode);
  Serial.print("auto_IQ_correction = ");
  Serial.println(EEPROMData.auto_IQ_correction);
  Serial.print("attenuator     = ");
  Serial.println(EEPROMData.attenuator);
  Serial.print("dcfParityBit       = ");
  Serial.println(EEPROMData.dcfParityBit);
  Serial.print("rate               = ");
  Serial.println(EEPROMData.rate);
  Serial.print("nrInUse            = ");
  Serial.println(EEPROMData.nrInUse);
  Serial.print("NR Parameter       = ");
  Serial.println(EEPROMData.NR_Filter_Values[EEPROMData.nrInUse]); 
  Serial.print("show_spectrum_flag = ");
  Serial.println(EEPROMData.show_spectrum_flag);
  Serial.print("xmtMode            = ");
  Serial.println(EEPROMData.xmtMode);

  for (i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("pixel_offset[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(EEPROMData.pixel_offset[i]);
  }
  Serial.print("currentVFO        = ");
  Serial.println(EEPROMData.currentVFO);
  Serial.print("agc_thresh        = ");
  Serial.println(EEPROMData.agc_thresh);
  Serial.print("agc_decay         = ");
  Serial.println(EEPROMData.agc_decay);
  Serial.print("agc_slope         = ");
  Serial.println(EEPROMData.agc_slope);
  for (i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("AGC_thresh[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(EEPROMData.AGC_thresh[i]);
  }
  Serial.print("audioVolume      = ");
  Serial.println(EEPROMData.audioVolume);
  for (i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("bwu[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.print(EEPROMData.bwu[i]);
    Serial.print("    bwl =");
    Serial.println(EEPROMData.bwl[i]);
  }
  Serial.print("currentBand       = ");
  Serial.println(EEPROMData.currentBand);
  Serial.print("dcfCount          = ");
  Serial.println(EEPROMData.dcfCount);
  Serial.print("dcfLevel          = ");
  Serial.println(EEPROMData.dcfLevel);
  Serial.print("dcfSilenceTimer   = ");
  Serial.println(EEPROMData.dcfSilenceTimer);
  Serial.print("dcfTheSecond      = ");
  Serial.println(EEPROMData.dcfTheSecond);
  Serial.print("dcfPulseTime      = ");
  Serial.println(EEPROMData.dcfPulseTime);
  Serial.print("freqIncrement     = ");
  Serial.println(EEPROMData.freqIncrement);
  Serial.print("keyType           = ");
  Serial.println(EEPROMData.keyType);
  Serial.print("keyerSidetone     = ");
  Serial.println(EEPROMData.keyerSidetone);
  for (i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("mode[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(EEPROMData.mode[i]);
  }
  Serial.print("paddleDah        = ");
  Serial.println(EEPROMData.paddleDah);
  Serial.print("paddleDit        = ");
  Serial.println(EEPROMData.paddleDit);
  Serial.print("PowerLevel       = ");
  Serial.println(EEPROMData.powerLevel);
  for (i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("rfg[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(EEPROMData.rfg[i]);
  }
  Serial.print("spectrumNoiseFloor = ");
  Serial.println(EEPROMData.spectrumNoiseFloor);

  Serial.print("tuneIndex        = ");
  Serial.println(EEPROMData.tuneIndex);
  Serial.print("wordsPerMinute   = ");
  Serial.println(EEPROMData.wordsPerMinute);
  Serial.print("crc              = ");
  Serial.println(EEPROMData.crc);
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
  for (i = 0; i < MAX_FAVORITES; i++) {
    Serial.print("favoriteFreqs[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(EEPROMData.favoriteFreqs[i]);
  }

  Serial.print("centerFreq              = ");
  Serial.println( (long)EEPROMData.centerFreq);
  Serial.print("bitSamplePeriod         = ");
  Serial.println(EEPROMData.bitSamplePeriod);
  Serial.print("bitSampleTimer          = ");
  Serial.println(EEPROMData.bitSampleTimer);
  Serial.print("dcfMean                 = ");
  Serial.println(EEPROMData.dcfMean);
  Serial.print("dcfSum                  = ");
  Serial.println(EEPROMData.dcfSum);
  Serial.print("dcfRefLevel             = ");
  Serial.println(EEPROMData.dcfRefLevel);
  Serial.print("Tsample                 = ");
  Serial.println(EEPROMData.Tsample);
  Serial.print("bass                    = ");
  Serial.println(EEPROMData.bass);
  Serial.print("LPFcoeff                = ");
  Serial.println(EEPROMData.LPFcoeff);
  Serial.print("micCompression          = ");
  Serial.println(EEPROMData.micCompression);
  Serial.print("midbass                 = ");
  Serial.println(EEPROMData.midbass);
  Serial.print("mid                     = ");
  Serial.println(EEPROMData.mid);
  Serial.print("midtreble               = ");
  Serial.println(EEPROMData.midtreble);
  Serial.print("NR_Filter_Value         = ");
  Serial.println(EEPROMData.NR_Filter_Value);
  Serial.print("NR_PSI                  = ");
  Serial.println(EEPROMData.NR_PSI);
  Serial.print("NR_alpha                = ");
  Serial.println(EEPROMData.NR_alpha);
  Serial.print("NR_beta                 = ");
  Serial.println(EEPROMData.NR_beta);
  Serial.print("offsetDisplayDB         = ");
  Serial.println(EEPROMData.offsetDisplayDB);
  Serial.print("omegaN                  = ");
  Serial.println(EEPROMData.omegaN);
  Serial.print("pll_fmax                = ");
  Serial.println(EEPROMData.pll_fmax);
  Serial.print("powerLevel           =");
  Serial.println(EEPROMData.powerLevel);
  Serial.print("powerOut                =");
  Serial.println(EEPROMData.powerOut);  
  Serial.print("spectrum_display_scale  = ");
  Serial.println(EEPROMData.spectrum_display_scale);
  Serial.print("stereo_factor           = ");
  Serial.println(EEPROMData.stereo_factor);
  Serial.print("treble                  = ");
  Serial.println(EEPROMData.treble);

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
  strncpy(EEPROMData.version_of_settings, VERSION, sizeof(EEPROMData.version_of_settings)); // Update version
  EEPROMData.AGCMode                         = 1;  // 1 byte
  EEPROMData.auto_IQ_correction              = 1;  // 1 byte
  EEPROMData.attenuator                      = 2;  // 1 byte
  EEPROMData.xmtMode                         = 0;  // 4 byte  //AFP 09-26-22

  EEPROMData.dcfParityBit                    = 3; // 1 byte
  EEPROMData.rate                            = 4; // 1 byte
  EEPROMData.NR_Filter_Values[0]              = 0.5; // 4 byte
  EEPROMData.nrInUse                         = 0;
  EEPROMData.show_spectrum_flag              = 6; // 1 byte

  EEPROMData.pixel_offset[0]                 = 7;                     // 14 bytes
  EEPROMData.pixel_offset[1]                 = 0;
  EEPROMData.pixel_offset[2]                 = 0;
  EEPROMData.pixel_offset[3]                 = 0;
  EEPROMData.pixel_offset[4]                 = 0;
  EEPROMData.pixel_offset[5]                 = 0;
  EEPROMData.pixel_offset[6]                 = 0;

  EEPROMData.currentVFO                      = 0;                      // 2 bytes, 0 = A, 1 = B
  EEPROMData.agc_thresh                      = 0;                      // 4 bytes
  EEPROMData.agc_decay                       = 0;                      // 4 bytes
  EEPROMData.agc_slope                       = 0;                      // 4 bytes

  EEPROMData.AGC_thresh[0]                   = 1;                      // 28 bytes
  EEPROMData.AGC_thresh[1]                   = 1;
  EEPROMData.AGC_thresh[2]                   = 1;
  EEPROMData.AGC_thresh[3]                   = 1;
  EEPROMData.AGC_thresh[4]                   = 1;
  EEPROMData.AGC_thresh[5]                   = 1;
  EEPROMData.AGC_thresh[6]                   = 1;

  EEPROMData.audioVolume                     = 50;                     // 4 bytes

  EEPROMData.bwu[0]                          = 0;                     // 28 bytes
  EEPROMData.bwu[1]                          = 0;
  EEPROMData.bwu[2]                          = 0;
  EEPROMData.bwu[3]                          = 0;
  EEPROMData.bwu[4]                          = 0;
  EEPROMData.bwu[5]                          = 0;
  EEPROMData.bwu[6]                          = 0;

  EEPROMData.bwl[0]                          = 0;                     // 28 bytes
  EEPROMData.bwl[1]                          = 0;
  EEPROMData.bwl[2]                          = 0;
  EEPROMData.bwl[3]                          = 0;
  EEPROMData.bwl[4]                          = 0;
  EEPROMData.bwl[5]                          = 0;
  EEPROMData.bwl[6]                          = 0;

  EEPROMData.currentBand                     = 1;                     // 4 bytes  1 = 40M
  EEPROMData.dcfCount                        = 0;                     // 4 bytes
  EEPROMData.dcfLevel                        = 0;                     // 4 bytes
  EEPROMData.dcfSilenceTimer                 = 0;                     // 4 bytes
  EEPROMData.dcfTheSecond                    = 0;                     // 4 bytes
  EEPROMData.dcfPulseTime                    = 0;                     // 4 bytes

  for (int i = 0; i < EQUALIZER_CELL_COUNT; i++) {                    // 14 * 2 * 4 = 112
    EEPROMData.equalizerRec[i] = 100;
    EEPROMData.equalizerXmt[i] = 100;
  }
  
  EEPROMData.freqIncrement                   = 4;                     // 4 bytes
  EEPROMData.keyType                         = 0;                     // straight key = 0, keyer = 1
  EEPROMData.keyerSidetone                   = 750;                   // Hz

  EEPROMData.mode[0]                         = 0;                     // 28 bytes
  EEPROMData.mode[1]                         = 0;
  EEPROMData.mode[2]                         = 0;
  EEPROMData.mode[3]                         = 0;
  EEPROMData.mode[4]                         = 0;
  EEPROMData.mode[5]                         = 0;
  EEPROMData.mode[6]                         = 0;

  EEPROMData.NR_Filter_Value                 = 0;
  EEPROMData.paddleDah                       = 0;                     // 4 bytes
  EEPROMData.paddleDit                       = 0;                     // 4 bytes
  EEPROMData.powerLevel                      = 20;                    // 4 bytes (Watts)

  EEPROMData.rfg[0]                          = 0;                     // 28 bytes
  EEPROMData.rfg[1]                          = 0;
  EEPROMData.rfg[2]                          = 0;
  EEPROMData.rfg[3]                          = 0;
  EEPROMData.rfg[4]                          = 0;
  EEPROMData.rfg[5]                          = 0;
  EEPROMData.rfg[6]                          = 0;

  EEPROMData.spectrumNoiseFloor              = SPECTRUM_NOISE_FLOOR;  // 4 bytes

  EEPROMData.switchValues[0]                 = 919;      // Your values will likely be different
  EEPROMData.switchValues[1]                 = 868;
  EEPROMData.switchValues[2]                 = 816;
  EEPROMData.switchValues[3]                 = 767;
  EEPROMData.switchValues[4]                 = 715;
  EEPROMData.switchValues[5]                 = 665;
  EEPROMData.switchValues[6]                 = 614;
  EEPROMData.switchValues[7]                 = 562;
  EEPROMData.switchValues[8]                 = 511;
  EEPROMData.switchValues[9]                 = 461;
  EEPROMData.switchValues[10]                = 406;
  EEPROMData.switchValues[11]                = 353;
  EEPROMData.switchValues[12]                = 298;
  EEPROMData.switchValues[13]                = 243;
  EEPROMData.switchValues[14]                = 185;
  EEPROMData.switchValues[15]                = 126;
  EEPROMData.switchValues[16]                = 65;
  EEPROMData.switchValues[17]                = 4;

  EEPROMData.tuneIndex                       = 4;                     // $ bytes
  EEPROMData.wordsPerMinute                  = 15;                    // 4 bytes
  EEPROMData.xmtMode                         = 0;                     // 4 bytes

  EEPROMData.crc                             = 0;                     // 2 bytes, added when saving
  EEPROMData.currentScale                    = 1;                     // 2 bytes,

  EEPROMData.spectrum_zoom                   = 1;         // 4 bytes AFP 09-26-22

  EEPROMData.calibrationFactor               = 230000LL;              // 8 bytes
  EEPROMData.centerFreq                      = 7150000L;              // 4 bytes
  EEPROMData.currentFreqA                    = 7150000L;              // 4 bytes
  EEPROMData.currentFreqB                    = 7030000L;              // 4 bytes
  EEPROMData.cwTransmitDelay                 = 1500L;                 // 4 bytes, how long between Morse atoms before relay kicks off
  
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

  EEPROMData.frequencyOffset                 = 0L;                    // 4 bytes

  EEPROMData.lastFrequencies[0][0] =  3700000L;  // 80
  EEPROMData.lastFrequencies[1][0] =  7150000L;  // 40
  EEPROMData.lastFrequencies[2][0] = 14200000L;  // 50
  EEPROMData.lastFrequencies[3][0] = 18100000L;  // 17
  EEPROMData.lastFrequencies[4][0] = 21200000L;  // 15
  EEPROMData.lastFrequencies[5][0] = 24900000L;  // 12
  EEPROMData.lastFrequencies[6][0] = 28300000L;  // 10

  EEPROMData.lastFrequencies[0][1] =  3530000L;  // 80
  EEPROMData.lastFrequencies[1][1] =  7060000L;  // 40
  EEPROMData.lastFrequencies[2][1] = 14030000L;  // 20
  EEPROMData.lastFrequencies[3][1] = 18100000L;  // 17
  EEPROMData.lastFrequencies[4][1] = 21060000L;  // 15
  EEPROMData.lastFrequencies[5][1] = 24900000L;  // 12
  EEPROMData.lastFrequencies[6][1] = 28060000L;  // 10
  
  EEPROMData.bitSamplePeriod                 = 0.002;                 // 4 bytes 1.0 / 500.0;
  EEPROMData.bitSampleTimer                  = 0.0;                   // 4 bytes
  EEPROMData.dcfMean                         = 0.0;                   // 4 bytes
  EEPROMData.dcfSum                          = 0.0;                   // 4 bytes
  EEPROMData.dcfRefLevel                     = 0.0;                   // 4 bytes
  EEPROMData.Tsample                         = 0.00008333;            // 4 bytes 1.0 / 12000.0

  EEPROMData.bass                            = 0.0;                   // 4
  EEPROMData.LPFcoeff                        = 0.0;                   // 4
  EEPROMData.micCompression                  = -18;                   // 4 bytes // AFP 09-22-22
  EEPROMData.midbass                         = 0.0;                   // 4
  EEPROMData.mid                             = 0.0;                   // 4
  EEPROMData.midtreble                       = 0.0;                   // 4
  EEPROMData.NR_PSI                          = 0.0;                   // 4
  EEPROMData.NR_alpha                        = 0.0;                   // 4
  EEPROMData.NR_beta                         = 0.0;                   // 4
  EEPROMData.offsetDisplayDB                 = 0.0;                   // 4
  EEPROMData.omegaN                          = 0.0;                   // 4
  EEPROMData.pll_fmax                        = 4000.0;                // 4 bytes
  EEPROMData.powerLevel                      = 20;
  EEPROMData.powerOut                        = 0.130;                 // 4 bytes, 20W

  EEPROMData.spectrum_display_scale          = 0.0;                   // 4
  EEPROMData.stereo_factor                   = 0.0;                   // 4
  EEPROMData.tuneIndex                       = 4;                     // 4
  EEPROMData.treble                          = 0.0;                   // 4

  EEPROMData.IQ_AmpCorFactor                 = 1.0;                   // 4  0.73
  EEPROMData.IQ_PhaseCorFactor               = 0.0;                   // 4 -0.14
  EEPROMData.IQ_XAmpCorFactor                = 1.0;                   // 4  1.04
  EEPROMData.IQ_XPhanseCorFactor             = 0.0;                   // 4  1.01
  EEPROMData.sidetoneVolume                  = 0.001;                 // 4

  EEPROM.put(EEPROM_BASE_ADDRESS, EEPROMData);                        // Write as one large chunk
}                        //                                     -----------
//              Total:                                            608 bytes   (need to confirm this number)



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
