
O projeto consiste num protótipo de sistema de monitoramento de condições ambientais de uma sala de servidores. Nele, os dados serão coletados por sensores DHT11 conectados microcontroladores ESP32 com compatibilidade a conexão WiFi. Os dados coletados serão publicados pelos microcontroladores para um broker MQTT Mosquitto, de onde serão coletadas pelo coletor Telegraf e armazenadas num banco de dados de séries temporais InfluxDB para serem consumidas pelo Grafana. No Grafana teremos um dashboard exibindo a série temporal e o valor atual desses dados, com recursos de alertas visuais para valores que necessitam de atenção.

- Pontos de coleta de dados e _publishers MQTT
- Broker MQTT
- Servidor VPN
- Servidor Grafana


### TODO:

- [ ] Passar o token do influxdb2 para o telegraf via injeção
- [ ] Configurar container de VPN server na "frente" da rede
- [ ] Melhorar o dashboard

### Criação de usuário no Mosquitto

A autenticação via credenciais de usuário é configurada em `mosquitto.conf` e as identidades são gerenciadas em `mosquitto.auth.`

Para criar o arquivo de identidades e adicionar o usuário execute

```bash
mosquitto_passwd -c [PASSWORDFILE] [USER]
```

Para adicionar novos usuários a esse arquivo utilize:

```bash
  mosquitto_passwd -b [PASSWORDFILE] [USER] [PSWD]
```

### Permissões

Algumas das permissões abaixo podem ser necessárias para subir os containers:

```bash
sudo chown 1883:1883 mosquitto/config/mosquitto.auth
sudo chmod 640 mosquitto/config/mosquitto.auth

sudo chown 1883:1883 mosquitto/config/mosquitto.conf
sudo chmod 644 mosquitto/config/mosquitto.conf

sudo chown -R 472:472 grafana/data
```
