import sqlite3
from logger import LogManager


class Database:
    def __init__(self, db_path="pm_nexus.db"):
        self.db_path = db_path
        log = LogManager("DATABASE")
        self.logger = log.get_logger()
        self._create_table()

    def _create_table(self):
        try:
            with sqlite3.connect(self.db_path) as conn:
                query = """
            CREATE TABLE IF NOT EXISTS sensores (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                temperatura REAL,
                humidade REAL,
                particulas REAL,
                timestamp DATETIME DEFAULT (datetime('now', 'localtime'))
            )
        """
                conn.execute(query)
                if self.logger:
                    self.logger.info(
                        "Banco de Dados: Verificação" " de tabela concluida."
                    )
        except Exception as e:
            if self.logger:
                self.logger.error(f"Banco de Dados: Erro ao inicializar: {e}")

    def save_data(self, dados):
        t = dados.get("temperatura")
        h = dados.get("humidade")
        p = dados.get("particulas")

        query = """
            INSERT INTO sensores (temperatura, humidade, particulas)
            VALUES (?, ?, ?)
        """

        try:
            with sqlite3.connect(self.db_path) as conn:
                cursor = conn.cursor()
                cursor.execute(query, (t, h, p))
                conn.commit()

            if self.logger:
                self.logger.info(f"DB: Dados salvos (T:{t}, H:{h}, P:{p})")

        except Exception as e:
            if self.logger:
                self.logger.error(f"DB Erro ao salvar: {e}")

    def get_data(self, limite=100):
        with sqlite3.connect(self.db_path) as conn:
            cursor = conn.cursor()
            cursor.execute(
                """SELECT * FROM sensores ORDER BY
                timestamp DESC LIMIT ?""",
                (limite,),
            )
            return cursor.fetchall()
