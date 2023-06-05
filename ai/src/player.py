import re
import socket

from enum import Enum
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

class EnumBoss (Enum):
    IAM = 1
    IMNOT = 0
    IDK = -1

class EnumHeader (Enum):
    ASKBOSS = "$1$"
    IMBOSS = "$2$"
    IMHERE = "$3$"

class EnumDirection(Enum):
    RIGHT = 0,
    LEFT = 1

class Player:

    def __init__(self, sock: socket.socket, args):
        self.sock = sock
        self.boss = -1
        self.pos_boss = -1
        self.nbr_ai = 0
        self.space = False
        self.args = args
        self.pos_bossitionned = False
        if (self.connection(args) == False):
            ErrorConnection("Error: connection failed")

    def handle_header(self, x, donnees):
        if x[0][1] == EnumHeader.ASKBOSS.value and self.boss == 1:
            self.broadcast(EnumHeader.IMBOSS.value + " IMBOSS")
            self.nbr_ai += 1
            self.pos_boss = 0
        if x[0][1] == EnumHeader.IMHERE.value and self.boss == 1:
            self.nbr_ai -= 1
        if x[0][1] == EnumHeader.IMBOSS.value and self.boss == -1:
            self.boss = 0
            self.pos_boss = int(x[0][0])
            self.broadcast(EnumHeader.ASKBOSS.value + "OK")
        if x[0][1] == EnumHeader.IMBOSS.value and self.boss == 0:
            self.pos_boss = int(x[0][0])
        return donnees

    def clear_data(self, donnees):
        i = 0
        while i < len(donnees):
            x = re.findall("^message ([0-8]), (\$[0-9]\$) (\w+)$", donnees[i])
            if len(x):
                donnees.remove(donnees[i])
                i = 0
                continue
            i += 1
        return donnees

    def handle_broadcast(self, donnees: str):
        for i in donnees:
            x = re.findall("^message ([0-8]), (\$[0-9]\$) (\w+)$", i)
            if len(x):
                donnees = self.handle_header(x, donnees)
        return self.clear_data(donnees)

    def wait_answer(self):
        donnees = receive_packet(self.sock)
        self.handle_broadcast(donnees)
        if len(donnees) <= 1:
            return self.wait_answer()
        if (donnees[0] == "dead"):
            raise ErrorConnection("Error: player dead")
        return donnees
    
    def wait_return(self):
        donnees = receive_packet(self.sock)
        self.clear_data(donnees)
        if len(donnees) <= 1:
            return self.wait_return()
        if (donnees[0] == "dead"):
            raise ErrorConnection("Error: player dead")
        return donnees

    def wait_broadcast(self):
        donnees = receive_packet(self.sock)
        self.handle_broadcast(donnees)
        if (donnees[0] == "dead"):
            raise ErrorConnection("Error: player dead")
        return

    def connection(self, args):
        donnees = self.wait_answer()
        if (donnees[0] == "WELCOME"):
            self.sock.send((args.name + "\n").encode())
            print("Envoi du nom de l'équipe... ({})".format(args.name))
        donnees = self.wait_answer()
        if (donnees[0] == "ko"):
            raise ErrorConnection("Error: connection failed")
        print(donnees[0])
        if (int(donnees[0]) > 0):
            self.space = True
        return False

    def move(self, return_only: bool = True):
        self.sock.send("Forward\n".encode())
        if (return_only == True):
            if (self.wait_return()[0] == "ko"):
                return False
        else:
            if (self.wait_answer()[0] == "ko"):
                return False
        return True

    def turn(self, direction: EnumDirection, return_only: bool = True):
        if direction == EnumDirection.RIGHT:
            self.sock.send("Right\n".encode())
        elif direction == EnumDirection.LEFT:
            self.sock.send("Left\n".encode())
        if return_only == True:
            if (self.wait_return()[0] == "ko"):
                return False
        else:
            if (self.wait_answer()[0] == "ko"):
                return False
        return True

    def look(self, return_only: bool = True):
        self.sock.send("Look\n".encode())
        if (return_only == True):
            return self.wait_return()[0]
        return self.wait_answer()[0]

    def inventory(self, return_only: bool = True):
        self.sock.send("Inventory\n".encode())
        if (return_only == True):
            return self.wait_return()[0]
        return self.wait_answer()[0]

    def broadcast(self, message: str, return_only: bool = False):
        self.sock.send(("Broadcast " + message + "\n").encode())
        if (return_only == True):
            if (self.wait_return()[0] == "ko"):
                return False
        else:
            if (self.wait_answer()[0] == "ko"):
                return False
        return True

    def connect_nbr(self, return_only: bool = True):
        self.sock.send("Connect_nbr\n".encode())
        if (return_only == True):
            tmp = self.wait_return()[0]
        else:
            tmp = self.wait_answer()[0]
        if (tmp == "ko"):
            raise ErrorConnection("Connect nbr failed\n")
        return int(tmp)

    def fork(self, return_only: bool = True):
        self.sock.send("Fork\n".encode())
        if (return_only == True):
            if (self.wait_return()[0] == "ko"):
                return False
        else:
            if (self.wait_answer()[0] == "ko"):
                return False
        return True

    def eject(self, return_only: bool = True):
        self.sock.send("Eject\n".encode())
        if (return_only == True):
            if (self.wait_return()[0] == "ko"):
                return False
        else:
            if (self.wait_answer()[0] == "ko"):
                return False
        return True

    def take(self, enum: EnumObject, return_only: bool = True):
        self.sock.send(("Take " + enum + "\n").encode())
        if (return_only == True):
            if (self.wait_return()[0] == "ko"):
                return False
        else:
            if (self.wait_answer()[0] == "ko"):
                return False
        return True

    def set(self, enum: EnumObject, return_only: bool = True):
        self.sock.send(("Set " + enum.value + "\n").encode())
        if (return_only == True):
            if (self.wait_return()[0] == "ko"):
                return False
        else:
            if (self.wait_answer()[0] == "ko"):
                return False
        return True

    def incantation(self, return_only: bool = True):
        self.sock.send("Incantation\n".encode())
        if (return_only == True):
            if (self.wait_return()[0] == "ko"):
                return False
        else:
            if (self.wait_answer()[0] == "ko"):
                return False
        return True
