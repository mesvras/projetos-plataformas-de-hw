#include <DHT.h>
#include <PubSubClient.h>
#include <WiFi.h>

#define DHT_PIN 4
#define DHT_TYPE DHT22


#define END_IP_BROKER "broker.emqx.io"
#define PORTA_BROKER 1883


const char* ssid = "Wokwi-GUEST";
const char* password = "";
#define USUARIO_BROKER "";
#define SENHA_BROKER "";
#define ID_ESP32 "esp_genipabu"

DHT dht(DHT_PIN, DHT_TYPE);


unsigned long last_dht_read = 0;
const unsigned long dht_interval = 2000;


const char* mqtt_server = END_IP_BROKER;
const int mqtt_port = PORTA_BROKER;

const char* un = USUARIO_BROKER;
const char* pw = SENHA_BROKER;
const char* id = ID_ESP32;

WiFiClient espClient;
PubSubClient client(espClient);


void callback(char* topic, byte* payload, unsigned int lenght) {
  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("]: ");

  for (int i = 0; i < lenght; i++)
    Serial.print((char) payload[i]);

  Serial.println("");
}


void setup() {
  Serial.begin(9600);
  

  dht.begin();  
  delay(2000); //tempo para dht estabilizar


  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);



  bool mqttConectado = client.connect(id, un, pw);

  if (mqttConectado) {
    Serial.println("===== Conectado =====");
    client.subscribe("/genipabu/temperatura");
    client.subscribe("/genipabu/umidade");
  } else {
    Serial.println("===== ERRO AO CONECTAR AO MQTT =====");
    Serial.println(client.state());
    Serial.println("====================================");
  }
}

void loop() {

  client.loop();

  unsigned long current_time = millis();  
  if (current_time - last_dht_read >= dht_interval) {
    last_dht_read = current_time;
    
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (isnan(h) || isnan(t)) {
      Serial.println("Erro: Falha na leitura do barramento DHT.");
      return; 
    }

    char h_str[12];
    char t_str[12];

    snprintf(h_str, sizeof(h_str), "%.2f", h);
    snprintf(t_str, sizeof(t_str), "%.2f", t);
    
  
    client.publish("/genipabu/umidade", h_str);
    client.publish("/genipabu/temperatura", t_str);

    // log    
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.print(" °C | Umidade: ");
    Serial.print(h);
    Serial.println(" %");
  }
}
