#include <RunningMedian.h>
// pins for data aquisition
int signalData = 33; // pin for signal
int valsig = 0;      // raw signal 0-4096
float fsigVolt;      // millivolt conversion

int fingerData = 32; // pin for finger
int valfing = 0;
float ffingVolt;

float fvoltageRatio = 0;
int bloodValue = 0;

RunningMedian signalSamples = RunningMedian(5001);
RunningMedian fingerSamples = RunningMedian(5001);

void Signal() {
  for (int i = 0; i < 5001; i++) {
    valsig = analogRead(signalData);
    signalSamples.add(valsig);
  }

  fsigVolt = ((signalSamples.getAverage(4000) * 3300) / (4095 * 48*2) * (vref / 1000)); // 48 is the multipler of the orignial cirucit 48x non-inverting opamp
  //sample is 12 bit so 4095, and voltage max is 3300 mv, vref is burned slop offset from manufacturer

}

void Finger() {
  for (int i = 0; i < 5001; i++) {
    valfing = analogRead(fingerData);
    fingerSamples.add(valfing);
   
  }
    ffingVolt = ((fingerSamples.getAverage(4000) * 3300) / (4095)) * (vref / 1000);
    //163 because adc is off and shifted by 163 mv, sample is 12 bit so 4095, and voltage max is 3300 mv

}
void bloodSugar() {
  Signal();
  Finger();
  fvoltageRatio = ffingVolt / fsigVolt;
  bloodValue = (fvoltageRatio - 94.882) / -0.6;
  int displayValue = round(bloodValue );
  String ratio = "blood sugar";
        tft.fillScreen(TFT_BLACK);
        tft.setTextDatum(MC_DATUM);
  tft.drawString(ratio,  tft.width() / 2, (tft.height() / 2 +64));
  ratio =  String(displayValue) + "mg/dl";
  String milli = String(ffingVolt);
  tft.drawString(ratio,  tft.width() / 2, (tft.height() / 2) + 96);
  tft.drawString(milli,  tft.width() / 2, (tft.height() / 2) + 32 );
  milli = String(fsigVolt);
  tft.drawString(milli, tft.width() / 2, (tft.height() / 2));


  SerialBT.println(displayValue);

    
 
  


}
