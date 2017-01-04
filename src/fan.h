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

   t_f = dht.readTemperature(true);


   // Check if any reads failed and exit early (to try again).
   if (isnan(t_f)) {
     Serial.println("Could not read temp");
     return;
   }

   Serial.println(t_f);

   r_h = dht.readHumidity();

   if (isnan(r_h)) {
     Serial.println("Could not read humidity");
     return;
   }

   Serial.print("humidity ");
   Serial.println(r_h);


   long newMS;
   newMS = (millis() - readTempLastMS) ;


   if ( sampleMSTotal + newMS >= msPerSample ) {
     sampleTotal = sampleTotal - ( sampleMSTotal + newMS - msPerSample  ) * sampleTotal / sampleMSTotal;
     sampleTotalRH = sampleTotalRH - ( sampleMSTotal + newMS - msPerSample  ) * sampleTotalRH / sampleMSTotal;

     sampleMSTotal = msPerSample - newMS;
   }
   sampleTotal += t_f * newMS;
   sampleTotalRH += r_h * newMS;

   sampleMSTotal += newMS;



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

}
