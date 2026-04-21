from flask import Flask, jsonify, request
from mqtt import MqttWorker
from database import Database
from flask_cors import CORS
from logger import LogManager


class SensorApp:
    def __init__(self, db_connection):
        self.app = Flask(__name__)

        CORS(
            self.app,
            resources={
                r"/*": {"origins": "*", "methods": ["GET", "POST", "DELETE", "OPTIONS"]}
            },
        )
        log = LogManager("FLASK")
        self.logger = log.get_logger()
        self.conn = db_connection
        self.broker = "localhost"
        self.port = "1883"
        self.topic = "pm_nexus"
        self.db = Database()
        self.mqtt = MqttWorker(self.broker, self.port, self.topic, self.db)

        self.app.add_url_rule("/dados", "get_dados", self.get_dados)
        self.app.add_url_rule(
            "/config", "save_config", self.save_config, methods=["POST"]
        )
        self.app.add_url_rule(
            "/limpar",
            "delete_data",
            self.delete_data,
            methods=["DELETE", "OPTIONS"],  # Certifique-se de que DELETE está aqui
        )

    def get_dados(self):
        rows = self.db.get_data()

        dados_formatados = []
        for r in rows:
            dados_formatados.append(
                {
                    "id": r[0],
                    "temperatura": r[1],
                    "humidade": r[2],
                    "particulas": r[3],
                    "timestamp": r[4],
                }
            )

        return jsonify(dados_formatados)

    def save_config(self):
        try:
            params = request.get_json()

            new_host = params.get("host")
            new_port = int(params.get("port"))
            new_topic = params.get("topic")

            self.mqtt.client.loop_stop()
            self.mqtt.client.disconnect()

            self.mqtt.broker = new_host
            self.mqtt.port = new_port
            self.mqtt.topic = new_topic

            self.mqtt.start()

            self.logger.info(
                f"Configuração atualizada: {new_host}:{new_port} " f"-> {new_topic}"
            )

            return (
                jsonify(
                    {
                        "status": "success",
                        "message": "Broker MQTT reiniciado com novas configurações",
                    }
                ),
                200,
            )

        except Exception as e:
            print(e)
            return jsonify({"status": "error", "message": str(e)}), 400

    def delete_data(self):
        try:
            # Chama o método que acabamos de corrigir na classe Database
            self.db.clear_data()
            return (
                jsonify(
                    {"status": "success", "message": "Histórico industrial apagado."}
                ),
                200,
            )
        except Exception as e:
            return (
                jsonify(
                    {"status": "error", "message": f"Falha ao limpar banco: {str(e)}"}
                ),
                500,
            )

    def run(self, debug=True, port=5000):
        self.app.run(debug=debug, port=port)


if __name__ == "__main__":
    meu_app = SensorApp(db_connection=None)
    meu_app.run()
