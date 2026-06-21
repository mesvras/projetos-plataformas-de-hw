
O projeto consiste num protótipo de sistema de monitoramento de condições ambientais de uma sala de servidores. Nele, os dados serão coletados por sensores DHT11 conectados microcontroladores ESP32 com compatibilidade a conexão WiFi. Os dados coletados serão publicados pelos microcontroladores para um broker MQTT Mosquitto, de onde serão coletadas pelo coletor Telegraf e armazenadas num banco de dados de séries temporais InfluxDB para serem consumidas pelo Grafana. No Grafana teremos um dashboard exibindo a série temporal e o valor atual desses dados, com recursos de alertas visuais para valores que necessitam de atenção.

- Pontos de coleta de dados e _publishers MQTT
- Broker MQTT
- Servidor VPN
- Servidor Grafana



### TODO:

- [ ] Corrigir o fato que registros de coleta de sessões diferentes estão sendo considerados como fontes diferentes no grafana (reconhece hosts diferentesa cada ciclo de vida dos containers)
- [ ] Passar o token do influxdb2 para o telegraf via injeção
- [ ] Configurar container de VPN server na "frente" da rede
- [ ] Melhorar o dashboard

## Como rodar?

### Pré-requisitos

- Docker


1. Clone o repositório

```bash
git clone git@github.com:mesvras/projeto-final-iot.git
```

2. Suba os containers

```bash
docker compose up
```

3. Acesse os serviços expostos em seus respectivos endereços:

- Painel Grafana

  http://localhost:3000


- Painel InfluxDB2

  http://localhost:8086


- Mosquitto Broker

  http://localhost:1883


## Criação de usuário no Mosquitto

A autenticação via credenciais de usuário é configurada em `mosquitto.conf` e as identidades são gerenciadas em `mosquitto.auth.` Há um usuário admin:admin pré-configurado.

Para criar um arquivo de identidades novo e adicionar um novo usuário execute

```bash
mosquitto_passwd -c [PASSWORDFILE] [USER]
```

Para adicionar novos usuários a um arquivo utilize:

```bash
  mosquitto_passwd -b [PASSWORDFILE] [USER] [PSWD]
```

## Permissões

Algumas das permissões abaixo podem ser necessárias para subir os containers:

```bash
sudo chown 1883:1883 mosquitto/config/mosquitto.auth
sudo chmod 640 mosquitto/config/mosquitto.auth
sudo chown -R 472:472 grafana/data
```
