import paho.mqtt.client as mqtt
import json
from logger import LogManager
from database import Database


class MqttWorker:
    def __init__(self, broker, port, topic, db):
        self.client = mqtt.Client()
        self.broker = broker
        self.port = port
        self.topic = topic
        self.db: Database = db

        log = LogManager("MQTT")
        self.logger = log.get_logger()

        # Callbacks
        self.client.on_connect = self._on_connect
        self.client.on_message = self._on_message

        self.start()

    def _on_connect(self, client, userdata, flags, rc):
        self.logger.info(f"Conectado ao Broker com código: {rc}")
        client.subscribe(self.topic)

    def _on_message(self, client, userdata, msg):
        try:
            payload = json.loads(msg.payload.decode())

            self.logger.info(f"Conteúdo recebido: {payload}")

            self.db.save_data(payload)

            self.logger.info(f"Dados salvos com sucesso: {payload}")

        except Exception as e:
            self.logger.error(f"Erro ao processar mensagem: {e}")

    def start(self):
        self.client.connect(str(self.broker), int(self.port), 60)
        self.client.loop_start()
