from enum import Enum
import socket
from tokenize import String

class ErrorConnection(Exception):
    pass

OBJECT = {
    "food": 0,
    "linemate": 1,
    "deraumere": 2,
    "sibur": 3,
    "mendiane": 4,
    "phiras": 5,
    "thystame": 6
}

class Direction(Enum):
    RIGHT = 0,
    LEFT = 1

def wait_answer(sock: socket.socket):
    donnees = sock.recv(1024)
    if not donnees:
        return
    donnees = donnees.split(b'\n')
    for i, x in enumerate(donnees):
        donnees[i] = x.decode()
    print("Données reçues :", donnees)
    if (donnees[0] == "dead"):
        raise ErrorConnection("Error: player dead")
    return donnees

def connection(sock: socket.socket, name: str):
    donnees = wait_answer(sock)
    if (donnees[0] == "WELCOME"):
        sock.send((name + "\n").encode())
        print("Envoi du nom de l'équipe... ({})".format(name))
    donnees = wait_answer(sock)
    if (donnees[0] == "ko"):
        raise ErrorConnection("Error: connection failed")
    if (int(donnees[0]) > 1):
        return True
    return False

class Player:
    def __init__(self, sock: socket.socket, name: str):
        self.sock = sock
        if (connection(self.sock, name) == False):
            ErrorConnection("Error: connection failed")

    def move(self):
        self.sock.send("Forward\n".encode())
        if (wait_answer(self.sock)[0] == "ko"):
            return False
        return True

    def turn(self, direction: Direction):
        if (direction == Direction.RIGHT):
            self.sock.send("Right\n".encode())
        else:
            self.sock.send("Left\n".encode())
        if (wait_answer(self.sock)[0] == "ko"):
            return False
        return True

    def look(self):
        self.sock.send("Look\n".encode())
        return wait_answer(self.sock)[0]

    def inventory(self):
        self.sock.send("Inventory\n".encode())
        return wait_answer(self.sock)[0]

    def broadcast(self, message: str):
        self.sock.send(("Broadcast " + message + "\n").encode())
        if (wait_answer(self.sock)[0] == "ko"):
            return False
        return True

    def connect_nbr(self):
        self.sock.send("Connect_nbr\n".encode())
        tmp = wait_answer(self.sock)[0]
        if (tmp == "ko"):
            raise ErrorConnection("Connect nbr failed\n")
        return int(tmp)

    def fork(self):
        self.sock.send("Fork\n".encode())
        if (wait_answer(self.sock)[0] == "ko"):
            return False
        return True

    def eject(self):
        self.sock.send("Eject\n".encode())
        if (wait_answer(self.sock)[0] == "ko"):
            return False
        return True

    def take(self, str: String):
        self.sock.send(("Take " + OBJECT[str] + "\n").encode())
        if (wait_answer(self.sock)[0] == "ko"):
            return False
        return True

    def set(self, str: String):
        self.sock.send(("Set " + OBJECT[str] + "\n").encode())
        if (wait_answer(self.sock)[0] == "ko"):
            return False
        return True

    def incantation(self):
        self.sock.send("Incantation\n".encode())
        if (wait_answer(self.socksock)[0] == "ko"):
            return False
        return True
