from typing import Final
import socket

class BadConnectionException(Exception):
    pass

def get_socket(port: int, ip = "127.0.0.1"):
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((ip, port))
        print("Connexion établie avec le serveur sur le port {}".format(port))
        return sock
    except socket.error as e:
        raise BadConnectionException("Erreur lors de la création de la socket : " + str(e))
