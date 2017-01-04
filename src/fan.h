void read_temperature() {

  Serial.print("read temp ");
  // Reading temperature or humidity takes about 250 milliseconds!
   // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
   //float h; //  = dht.readHumidity();
   //new_humidity = h;

   // Read temperature as Celsius (the default)
   //float t_c = dht.readTemperature();
   // Read temperature as Fahrenheit (isFahrenheit = true)
   float t_f;
   float r_h;

   /*
   int i;
   Serial.print("<");
   for (i=0; i<100; i++) {
     Serial.print( digitalRead(pinTemperature));
   }
   Serial.println(">");
   */

   t_f = dht.readTemperature(true);



   // Check if any reads failed and exit early (to try again).
   //if (isnan(h) || isnan(t) || isnan(f)) {
   if (isnan(t_f)) {
     Serial.println("Could not read temp");
     //new_temperature = old_temperature;
     //new_humidity = old_humidity;
     //new_heatIndex = old_heatIndex;
     return;
   }

   Serial.println(t_f);

   r_h = dht.readHumidity();

   if (isnan(r_h)) {
     Serial.println("Could not read humidity");
     //new_temperature = old_temperature;
     //new_humidity = old_humidity;
     //new_heatIndex = old_heatIndex;
     return;
   }

   Serial.print("humidity ");
   Serial.println(r_h);

   /*
   int secondsPerSample = 60;
   long sampleSecondsTotal = 0;
   float sampleTotal = 0;
   */

   long newMS;
   newMS = (millis() - readTempLastMS) ;

   //Serial.print("Seconds total ");
   //Serial.print(sampleSecondsTotal);
   //Serial.print(" newWeight ");
   //Serial.print(newWeight);
   //Serial.print(" seconds per sample ");
   //Serial.print(secondsPerSample);
   //Serial.print(" sample total ");
   //Serial.print(sampleTotal);
   //Serial.print(" temp ");
   //Serial.print(t_f);

   if ( sampleMSTotal + newMS >= msPerSample ) {
     sampleTotal = sampleTotal - ( sampleMSTotal + newMS - msPerSample  ) * sampleTotal / sampleMSTotal;
     sampleTotalRH = sampleTotalRH - ( sampleMSTotal + newMS - msPerSample  ) * sampleTotalRH / sampleMSTotal;

     sampleMSTotal = msPerSample - newMS;
   }
   sampleTotal += t_f * newMS;
   sampleTotalRH += r_h * newMS;

   sampleMSTotal += newMS;


   //Serial.print(" new total ");
   //Serial.print(sampleTotal);
  //Serial.print(" new average ");
   //Serial.println(sampleTotal / sampleMSTotal);

   if ( millis() - sampleTempLastMS > sampleTempLastMax or millis() < sampleTempLastMS ) {
     sampleTempLastMS = millis();
     new_temperature =  round(sampleTotal / sampleMSTotal);
     Serial.print(" new avg temp ");
      Serial.println(new_temperature);

       char msg[10];
       snprintf (msg, 10, "%i", new_temperature);
       //Serial.println(msg);

       my_publish( TEMPERATURE_FEED, msg);

       new_temperature = round(sampleTotalRH / sampleMSTotal);
       snprintf (msg, 10, "%i", new_temperature);
       //Serial.println(msg);

       my_publish( HUMIDITY_FEED, msg);

   }

   // Compute heat index in Fahrenheit (the default)
   //float hif = dht.computeHeatIndex(t_f, h);
   //new_heatIndex = hif;
   // Compute heat index in Celsius (isFahreheit = false)
   //float hic = dht.computeHeatIndex(t, h, false);

   //Serial.print("temp ");
   //Serial.println(new_temperature);

}


void relay_power(int aPower) {

  current_relay_power = aPower;

  Serial.print("relay_power: ");

  char msg[10];
  snprintf (msg, 10, "%i", aPower);

  Serial.println(msg);

digitalWrite(pinRelay, aPower ? RELAY_POWER_ON : RELAY_POWER_OFF );
// digitalWrite(pinLED, 1 - aPower); // fan on = 1, but led 0 is lit

//  if (aPower) {
//    digitalWrite(pinFanRelay, FAN_POWER_ON);
//  } else {
//    digitalWrite(pinFanRelay, FAN_POWER_OFF);
//  }

/*
  if ( aPower != current_fan_power) {
    current_fan_power = aPower;
    my_publish(POWER_FEED, msg);
  }
*/


}
