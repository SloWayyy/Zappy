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

def receive_packet(sock: socket.socket):
    donnees = sock.recv(1024)
    if not donnees:
        return
    donnees = donnees.split(b'\n')
    print("Debug :", donnees)
    for i, x in enumerate(donnees):
        donnees[i] = x.decode()
    return donnees

def receive_debug(sock: socket.socket):
    donnees = sock.recv(1024)
    if not donnees:
        return
    donnees = donnees.split(b'\n')
    for i, x in enumerate(donnees):
        donnees[i] = x.decode()
    print("Debug :", donnees)
    return
