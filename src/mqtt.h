

WiFiClient mqtt_wifi_client;
PubSubClient mqtt_client(mqtt_wifi_client);


void callback(char* topic, byte* payload, unsigned int length) {

  int z_value;

  payload[length] = '\0'; // finish off the String

  Serial.print(topic);
  Serial.print(" => ");
  Serial.println((char *)payload);


  /*
  if ( !strcmp(topic, NICKNAME_FEED) ) {
    Serial.println("NICKNAME ");
    // calculate power feed, subscribe
    strcpy(mqtt_nickname, (char *)payload);
    strcat(mqtt_nickname, "-");

    // set mqtt_topic_root ... somewhere?
    // may have to move the following

    strcpy(POWER_FEED, mqtt_nickname);
    strcat(POWER_FEED, POWER_FEED_SUFFIX);

    strcpy(TEMPERATURE_FEED, mqtt_nickname);
    strcat(TEMPERATURE_FEED, TEMPERATURE_FEED_SUFFIX);

    strcpy(HUMIDITY_FEED, mqtt_nickname);
    strcat(HUMIDITY_FEED, HUMIDITY_FEED_SUFFIX);

    mqtt_client.subscribe(POWER_FEED);

    mqtt_ready_to_pub = 1;

  }
  */

  if ( !strcmp(topic, POWER_FEED) ) {
    z_value = atoi( (char *)payload );
    Serial.print("POWER ");
    Serial.println(z_value);
    relay_power(z_value);
  }

  // test first char
  // (char)payload[0] == '1'

}

boolean my_publish(const char* topic, char* value) {
  Serial.print("pub: ");
  Serial.print(value);
  Serial.print(" => ");
  Serial.println(topic);
  if (!mqtt_client.connected() ) {
    Serial.println("mqtt not connected");
    return false;
  }

  return mqtt_client.publish(topic, value, true); // true = retained

}

void mqtt_reconnect() {
  // Loop until we're reconnected
  //while (!mqtt_client.connected()) {

    Serial.print("Attempting MQTT connection...");
    Serial.print(mqtt_server);
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (mqtt_client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //my_publish("outTopic", "hello world");
      // ... and resubscribe

      //strcpy(NICKNAME_FEED, macaddr);
      //strcat(NICKNAME_FEED, "/nickname");
      //Serial.print("nickname feed ");
      //Serial.println(NICKNAME_FEED);

      //mqtt_client.subscribe(NICKNAME_FEED);

      mqtt_client.subscribe(POWER_FEED);

    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");

      // Wait 5 seconds before retrying

      delay(5000);
    }

  //} // loop

}
