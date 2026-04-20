from flask import Flask, jsonify
from mqtt import MqttWorker
from database import Database


class SensorApp:
    def __init__(self, db_connection):
        self.app = Flask(__name__)
        self.conn = db_connection
        self.broker = "localhost"
        self.port = "1883"
        self.topic = "pm_nexus"
        self.db = Database()
        self.mqtt = MqttWorker(self.broker, self.port, self.topic, self.db)

        self.app.add_url_rule("/dados", "get_dados", self.get_dados)

    def get_dados(self):
        rows = self.db.get_data()
        return jsonify(rows)

    def run(self, debug=True, port=5000):
        self.app.run(debug=debug, port=port)


if __name__ == "__main__":
    # Aqui você passaria sua conexão real (ex: sqlite3.connect(...))
    # meu_db = sqlite3.connect('banco.db', check_same_thread=False)

    # Instanciamos e rodamos
    meu_app = SensorApp(db_connection=None)  # Substitua None pela sua conexão
    meu_app.run()
