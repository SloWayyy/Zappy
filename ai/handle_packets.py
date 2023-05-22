from typing import Final
import socket

class BadConnectionException(Exception):
    pass

def get_socket(port: int, ip = "127.0.0.1"):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    sock.bind((ip, port))
    sock.listen(1)
    print("En attente de connexion...")

    connexion, adresse = sock.accept()
    print("Connexion établie depuis :", adresse)

    while True:
        donnees = connexion.recv(1024)
        if not donnees:
            break
        print("Données reçues :", donnees.decode())

    connexion.close()
