Use this to publish data on mqtt:

mosquitto_pub -h localhost -t "pm_nexus" -m '{"temperatura": 55, "humidade": 50.9, "particulas": 30.3}'
