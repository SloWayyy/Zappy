from enum import Enum
import socket
import re

from ai.src.handle_packets import *

class ErrorConnection(Exception):
    pass

class EnumObject (Enum):
    FOOD = "food"
    LINEMATE = "linemate"
    DERAUMERE = "deraumere"
    SIBUR = "sibur"
    MENDIANE = "mendiane"
    PHIRAS = "phiras"
    THYSTAME = "thystame"

class EnumHeader (Enum):
    ASKBOSS = "$1$"
    IMBOSS = "$2$"

class Direction(Enum):
    RIGHT = 0,
    LEFT = 1

class Player:
    def __init__(self, sock: socket.socket, name: str):
        self.sock = sock
        self.boss = -1
        self.map_broadcast : dict = {}
        if (self.connection(name) == False):
            ErrorConnection("Error: connection failed")

    def handle_broadcast(self, donnees: str):
        for i in donnees:
            x = re.findall("^message ([0-8]), (\$[0-9]\$) (\w+)$", i)
            if len(x) != 0:
                if  x[0][1] == EnumHeader.ASKBOSS.value and self.boss == 1:
                    self.broadcast(EnumHeader.IMBOSS.value + " IMBOSS")
                elif x[0][1] == EnumHeader.IMBOSS.value and self.boss == -1:
                    self.boss = 0
                else:
                    self.map_broadcast.update({int(x[0][0]) : (x[0][1], x[0][2])})
                donnees.remove(i)

    def wait_answer(self):
        donnees = receive_packet(self.sock)
        self.handle_broadcast(donnees)
        if len(donnees) <= 1:
            return self.wait_answer()
        if (donnees[0] == "dead"):
            raise ErrorConnection("Error: player dead")
        return donnees

    def connection(self, name: str):
        donnees = self.wait_answer()
        if (donnees[0] == "WELCOME"):
            self.sock.send((name + "\n").encode())
            print("Envoi du nom de l'équipe... ({})".format(name))
        donnees = self.wait_answer()
        if (donnees[0] == "ko"):
            raise ErrorConnection("Error: connection failed")
        if (int(donnees[0]) > 1):
            return True
        return False

    def move(self):
        self.sock.send("Forward\n".encode())
        if (self.wait_answer()[0] == "ko"):
            return False
        return True

    def turn(self, direction: Direction):
        if (direction == Direction.RIGHT):
            self.sock.send("Right\n".encode())
        else:
            self.sock.send("Left\n".encode())
        if (self.wait_answer()[0] == "ko"):
            return False
        return True

    def look(self):
        self.sock.send("Look\n".encode())
        return self.wait_answer()[0]

    def inventory(self):
        self.sock.send("Inventory\n".encode())
        return self.wait_answer()[0]

    def broadcast(self, message: str):
        self.sock.send(("Broadcast " + message + "\n").encode())
        result = self.wait_answer()[0]
        if (result == "ko"):
            return False
        return True

    def connect_nbr(self):
        self.sock.send("Connect_nbr\n".encode())
        tmp = self.wait_answer()[0]
        if (tmp == "ko"):
            raise ErrorConnection("Connect nbr failed\n")
        return int(tmp)

    def fork(self):
        self.sock.send("Fork\n".encode())
        if (self.wait_answer()[0] == "ko"):
            return False
        return True

    def eject(self):
        self.sock.send("Eject\n".encode())
        if (self.wait_answer()[0] == "ko"):
            return False
        return True

    def take(self, enum: EnumObject):
        self.sock.send(("Take " + enum + "\n").encode())
        if (self.wait_answer()[0] == "ko"):
            return False
        return True

    def set(self, enum: EnumObject):
        self.sock.send(("Set " + enum.value + "\n").encode())
        if (self.wait_answer()[0] == "ko"):
            return False
        return True

    def incantation(self):
        self.sock.send("Incantation\n".encode())
        if (self.wait_answer()[0] == "ko"):
            return False
        return True
