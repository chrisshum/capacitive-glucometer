// modifiable parameters for waveforms________________________________________________________
float freq = 1000;  //Hz  set frequency 
float fAmpm = .05;    //Volts    set amplitude in volts

#define DAC1 25      // setup pin 25 to make sine wave 
float fAmp = fAmpm *2;
int SineValues[256];       // an array to store our values for our waveform 
float fMax; 
float fDelt= 700*256;   //time period per exectution 
int sample;
float RadAngle;



  void waveform(){
//waveform setup 
fMax = 3.2/fAmp; // set max amplitude 
sample =fDelt/freq; // set sample rate based on frequency and smallest del t             
float ConversionFactor=(2*PI)/sample;      // converts a full circle into increments based on the max samples in a frequency  
  // Angle in Radians calculate sine values
  for(int MyAngle=0;MyAngle<sample;MyAngle++) {
    RadAngle=MyAngle*ConversionFactor;//*fFreq;               // 8 bit angle converted to radians
    SineValues[MyAngle]=((sin(RadAngle)*127)+128)/fMax;  // get the sine of this angle and 'shift' up so
    } 

    
  for(;;){    
    for(int i=0;i<sample;i++){
      dacWrite(25,SineValues[i]);
      }
    
    }
  }
