from typing import Final
import socket
import os

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
    donnees = sock.recv(5000)
    if not donnees:
        return
    donnees = donnees.split(b'\n')
    for i, x in enumerate(donnees):
        donnees[i] = x.decode()
    return donnees

def receive_debug(sock: socket.socket):
    donnees = sock.recv(4096)
    if not donnees:
        return
    donnees = donnees.split(b'\n')
    for i, x in enumerate(donnees):
        donnees[i] = x.decode()
    print("Debug :", donnees)
    return

def duplicate(args):
    pid = os.fork()
    if pid < 0:
        return 84
    if pid == 0:
        return 0
    os.execve("./zappy_ai", ["./zappy_ai", "-p", str(args.port), "-n", args.name,], os.environ)
