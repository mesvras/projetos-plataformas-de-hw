
O projeto consiste num protótipo de sistema de monitoramento de condições ambientais de uma sala de servidores. Nele, os dados serão coletados por sensores DHT11 conectados microcontroladores ESP32 com compatibilidade a conexão WiFi. Os dados coletados serão publicados pelos microcontroladores para um broker MQTT Mosquitto, de onde serão coletadas pelo coletor Telegraf e armazenadas num banco de dados de séries temporais InfluxDB para serem consumidas pelo Grafana. No Grafana teremos um dashboard exibindo as principais 

- Pontos de coleta de dados e _publishers MQTT
- Broker MQTT
- Servidor VPN
- Servidor Grafana



Como configurar autenticação no mosquitto:


### Criação de usuário no Mosquitto

A autenticação via credenciais de usuário é configurada em `mosquitto.conf` e as identidades são gerenciadas em `mosquitto.auth.`

Para criar o arquivo de identidades e adicionar o usuário execute

````bash
mosquitto_passwd -c [PASSWORDFILE] [USER]
```

Para adicionar novos usuários a esse arquivo utilize:

```bash
  mosquitto_passwd -b [PASSWORDFILE] [USER] [PSWD]
```

# necessário para o mosquitto subir
sudo chown 1883:1883 mosquitto/config/mosquitto.auth
sudo chmod 640 mosquitto/config/mosquitto.auth

sudo chown 1883:1883 mosquitto/config/mosquitto.conf
sudo chmod 644 mosquitto/config/mosquitto.conf
