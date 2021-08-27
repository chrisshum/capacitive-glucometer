// Battery voltage to percent array 
float fvoltBatt[21][2] = 
{{4.2,100},{4.15,95},{4.11,90},{4.08,85},{4.02,80},{3.98,75},{3.95,70},{3.91,65},{3.87,60},{3.85,55},
{3.84,50},{3.82,45},{3.8,40},{3.79,35},{3.77,30},{3.75,25},{3.73,20},{3.71,15},{3.69,10},{3.61,5},{3.27,0}};



void showVoltage()
{
    static uint64_t timeStamp = 0;
    if (millis() - timeStamp > 1000) { // set loop to repeat every 1 second 
        timeStamp = millis();
        uint16_t v = analogRead(ADC_PIN);
        float fbatteryVolt = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
        // read resolution is 12bit so 4095, 2 for voltage is measured on voltage divider divided by 2, 3.3 for max voltage reading
        // vref/1000 to correct slope offset of adc which was part of chip
        int i, perc;
        perc = 100;
        for(i=20; i>=0; i--) {
          if(fvoltBatt[i][0] >= fbatteryVolt) {
            perc = fvoltBatt[i + 1][1];
            break; // convert voltage to percent with resolution of 5% when it is in range of voltage then stops code and sets perc
    }
  }
       
        String voltage = String(perc) + "%";

         bloodSugar();
        tft.drawString("Battery:",  tft.width() / 2, tft.height() / 2 -96);
        tft.drawString(voltage,  tft.width() / 2, tft.height() / 2 -64);

        
    }
}
