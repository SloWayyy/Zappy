import re
import socket
import hashlib
import uuid

from enum import Enum
from ai.src.encryption import Encryption, NonceException
from ai.src.handle_packets import *
from ai.src.order.dump_item import *
from ai.src.order.join_boss import *
from ai.src.order.square_collect import *
from ai.src.order.take_around import *
from ai.src.priority_order.ping import *
from ai.src.order.manage_order import *
from ai.src.priority_order.seppuku import *
from ai.src.order.level_up import *
from ai.src.order.go_front import *
from ai.src.order.fork import *
from ai.src.order.take_far import *
from ai.src.order.farm import *
from ai.src.order.take_food import *

class ErrorConnection(Exception):
    pass

ALL = "00000000-0000-0000-0000-000000000000"
UUID_REGEX = "([0-9a-fA-F]{8}\\b-[0-9a-fA-F]{4}\\b-[0-9a-fA-F]{4}\\b-[0-9a-fA-F]{4}\\b-[0-9a-fA-F]{12})"

class EnumObject (Enum):
    FOOD = "food"
    LINEMATE = "linemate"
    DERAUMERE = "deraumere"
    SIBUR = "sibur"
    MENDIANE = "mendiane"
    PHIRAS = "phiras"
    THYSTAME = "thystame"

class EnumBoss (Enum):
    IM = 1
    IMNOT = 0
    IDK = -1

class EnumHeader (Enum):
    ASKBOSS = "$1$"
    IMBOSS = "$2$"
    ANSWER = "$3$"
    ORDER = "$4$"
    PRIORITY_ORDER = "$5$"


class EnumDirection(Enum):
    RIGHT = 0
    LEFT = 1


class SizeMap ():
    def __init__(self, x, y):
        self.x = x
        self.y = y

class EnumOrder(Enum):
    NOTHING = "0"
    DUMP_ITEM = "1"
    JOIN_BOSS = "2"
    TAKE_AROUND = "3"
    GO_FRONT = "4"
    LEVEL_UP = "5"
    FORK = "6"
    TAKE_FAR = "7"
    TAKE_FOOD = "8"

class EnumPriorityOrder(Enum):
    PING = "0"
    SEPPUKU = "1"
    FARM = "2"

levelUpArray = [
                [1, 0, 1, 0, 0, 0, 0, 0],
                [2, 0, 1, 1, 1, 0, 0, 0],
                [2, 0, 2, 0, 1, 0, 2, 0],
                [4, 0, 1, 1, 2, 0, 1, 0],
                [4, 0, 1, 2, 1, 3, 0, 0],
                [6, 0, 1, 2, 3, 0, 1, 0],
                [6, 0, 2, 2, 2, 2, 2, 1]
               ]

ANSWER_FUNC = [ping_answer, seppuku_answer, farm_answer]
PRIORITY_ORDER_FUNC = [ping, seppuku, farm]
ORDER_FUNC = [None, dump_item, join_boss, take_around, go_front, level_up, fork, take_far, take_food]

class Player:

    def __init__(self, sock: socket.socket, args):
        self.sock = sock
        self.boss = -1
        self.pos_boss = -1
        self.level7 = False
        self.level = 1
        self.slot = 0
        self.reaper = 0
        self.uuid = str(uuid.uuid1())
        self.boss_uuid = None
        self.job = 0

        self.order_food = 0
        self.level6 = False

        self.boss_food = 0
        self.bigger_level = -1
        self.player_food = 0
        self.array_uuid = []
        self.farmer_uuid = None
        self.ai_enought_food = [-1, 0]
        print("UUID: " + self.uuid)
        self.map_size = SizeMap(0, 0)
        self.args = args
        self.key = hashlib.sha256(self.args.name.encode()).digest()
        self.encryption = Encryption()
        if (self.connection(args) == False):
            ErrorConnection("Error: connection failed")

    # x[0][0] = pos, x[0][1] = sender uuid, x[0][2] = header, x[0][3] = receiver uuid, x[0][4] = message

    def update_info(self, x):
        order = re.findall("(\d+) (.*)", x[0][4])
        ANSWER_FUNC[int(order[0][0])](self, x[0][1], order[0][1])

    def execute_order(self, x):
        order = re.findall("(\d+) (.*)", x[0][4])
        self.job = int(order[0][0])

        self.take(EnumObject.FOOD.value)
        self.take(EnumObject.FOOD.value)
        self.take(EnumObject.FOOD.value)

        ORDER_FUNC[int(order[0][0])](self, order[0][1])
        self.job = 0
        ping(self)

    def boss_reaction(self, x):
        from ai.src.game import msg_create
        if x[0][2] == EnumHeader.ASKBOSS.value:
            self.broadcast(self.uuid + " " + EnumHeader.IMBOSS.value + " " + ALL + " IMBOSS")
            if self.farmer_uuid == 0:
                self.farmer_uuid = x[0][1]
                self.broadcast(msg_create(self, self.farmer_uuid, EnumHeader.PRIORITY_ORDER.value, EnumPriorityOrder.FARM.value))
            elif self.reaper > 0:
                print("you time is counted")
                print("reaper: ", self.reaper)
                print("target: ", x[0][1])
                self.broadcast(msg_create(self, x[0][1], EnumHeader.PRIORITY_ORDER.value, EnumPriorityOrder.SEPPUKU.value))
                self.reaper -= 1
            else:
                self.array_uuid.append(dict(uuid = x[0][1], level = 1, job = 0, pos = int(x[0][0])))
                if self.bigger_level == 6:
                    self.level6 = True
                if self.level6 == False:
                    self.array_uuid = self.array_uuid[:4]
                else:
                    print("SLICE 8")
                    self.array_uuid = self.array_uuid[:8]
                print("LEVEL IN APPEND: ", self.bigger_level)
                self.pos_boss = 0
        if x[0][2] == EnumHeader.ANSWER.value:
            self.update_info(x)

    def anonymous_reaction(self, x):
        if x[0][2] == EnumHeader.IMBOSS.value:
            self.boss = EnumBoss.IMNOT.value
            self.boss_uuid = x[0][1]
            self.pos_boss = int(x[0][0])

    def normal_reaction(self, x):
        if x[0][1] == self.boss_uuid:
            self.pos_boss = int(x[0][0])
        if x[0][2] == EnumHeader.ORDER.value and self.job == 0:
            self.execute_order(x)
        if x[0][2] == EnumHeader.PRIORITY_ORDER.value:
            order = re.findall("(\d+) (.*)", x[0][4])
            PRIORITY_ORDER_FUNC[int(order[0][0])](self)

    def handle_header(self, x):
        if self.boss == EnumBoss.IM.value:
            self.boss_reaction(x)
        elif self.boss == EnumBoss.IMNOT.value:
            self.normal_reaction(x)
        elif self.boss == EnumBoss.IDK.value:
            self.anonymous_reaction(x)

    def clear_data(self, donnees):
        if donnees == None:
            return donnees
        i = 0
        while i < len(donnees):
            pattern = r'message \d+'
            x = re.findall(pattern, donnees[i])
            if len(x):
                donnees.remove(donnees[i])
                i = 0
                continue
            i += 1
        return donnees

    def handle_broadcast(self, donnees: str):
        for i in donnees:
            if i.find("Current level") != -1:
                self.level = int(i.split(" ")[2])
                print("JE DEVIENS LEVEL -> Level: " + str(self.level))
                self.job = 0
                ping(self)
            else:
                x = re.findall("^message ([0-8]), " + UUID_REGEX + " (\$[0-9]\$) " + UUID_REGEX + " (.*)$", i)
                if len(x) and (x[0][3] == self.uuid or x[0][3] == ALL):
                    donnees = self.handle_header(x)
        return self.clear_data(donnees)

    def decrypt_donnees(self, donnees):
        array_decrypt = []
        if (donnees == None):
            return None
        for i in donnees:
            if i.find("message") != -1:
                array = i.split(", ")
                if (len(array) == 2 and len(array[1]) % 16) == 0:
                    try:
                        msg_decode = self.encryption.decrypt_message(self.key, bytes.fromhex(array[1]))
                        msg_decode = msg_decode.replace("\n", "")
                        array_decrypt.append(array[0] + ", " + msg_decode)
                    except NonceException:
                        print("Replay attack detected")
                    except:
                        pass
            else:
                array_decrypt.append(i)
        return array_decrypt

    def wait_answer(self):
        donnees = receive_packet(self.sock)
        array_decrypt = self.decrypt_donnees(donnees)
        if (array_decrypt == None):
            return self.wait_answer()
        self.handle_broadcast(array_decrypt)
        self.clear_data(array_decrypt)
        if len(array_decrypt) <= 1:
            return self.wait_answer()
        if (array_decrypt[0] == "dead"):
            raise ErrorConnection("Error: player dead")
        return array_decrypt

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
        array_decrypt = self.decrypt_donnees(donnees)
        if (array_decrypt == None):
            return self.wait_answer()
        for i in array_decrypt:
            if i.find("level") != -1:
                print("broad: ", i)
        self.handle_broadcast(array_decrypt)
        if (array_decrypt[0] == "dead"):
            raise ErrorConnection("Error: player dead")
        return

    def connection(self, args):
        donnees = self.wait_return()
        if (donnees[0] == "WELCOME"):
            self.sock.send((args.name + "\n").encode())
            print("Envoi du nom de l'équipe... ({})".format(args.name))
        donnees = self.wait_return()
        if (donnees[0] == "ko"):
            raise ErrorConnection("Error: connection failed")
        self.map_size.x = int(donnees[1].split(" ")[0])
        self.map_size.y = int(donnees[1].split(" ")[1])
        if (int(donnees[0]) > 0):
            self.slot = int(donnees[0])
        return False

    def move(self, return_only: bool = False):
        self.sock.send("Forward\n".encode())
        if (return_only == True):
            if (self.wait_return()[0] == "ko"):
                return False
        else:
            if (self.wait_answer()[0] == "ko"):
                return False
        return True

    def turn(self, direction: EnumDirection, return_only: bool = False):
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

    def inventory(self, return_only: bool = False):
        self.sock.send("Inventory\n".encode())
        if (return_only == True):
            string = self.wait_return()[0]
        else:
            string = self.wait_answer()[0]
        number = re.findall(r'\b\d+\b', string)
        if len(number) == 0:
            return False
        return [int(num) for num in number]

    def broadcast(self, message: str, return_only: bool = False, encrypt: bool = True):
        message_encrypt = self.encryption.encrypt_message(self.key, message).hex() if encrypt else message
        self.sock.send(("Broadcast " + message_encrypt + "\n").encode())
        if (return_only == True):
            if (self.wait_return()[0] == "ko"):
                return False
        else:
            if (self.wait_answer()[0] == "ko"):
                return False
        return True

    def connect_nbr(self, return_only: bool = False):
        self.sock.send("Connect_nbr\n".encode())
        if (return_only == True):
            tmp = self.wait_return()[0]
        else:
            tmp = self.wait_answer()[0]
        if (tmp == "ko"):
            raise ErrorConnection("Connect nbr failed\n")
        return int(tmp)

    def fork(self, return_only: bool = False):
        from ai.src.priority_order.ping import ping
        self.sock.send("Fork\n".encode())
        if (return_only == True):
            if (self.wait_return()[0] == "ko"):
                return False
        else:
            if (self.wait_answer()[0] == "ko"):
                return False
        ping(self)
        return True

    def eject(self, return_only: bool = False):
        self.sock.send("Eject\n".encode())
        if (return_only == True):
            if (self.wait_return()[0] == "ko"):
                return False
        else:
            if (self.wait_answer()[0] == "ko"):
                return False
        return True

    def take(self, enum: EnumObject, return_only: bool = False):
        self.sock.send(("Take " + enum + "\n").encode())
        if (return_only == True):
            if (self.wait_return()[0] == "ko"):
                return False
        else:
            if (self.wait_answer()[0] == "ko"):
                return False
        return True

    def set(self, enum: EnumObject, return_only: bool = False):
        self.sock.send(("Set " + enum.value + "\n").encode())
        if (return_only == True):
            if (self.wait_return()[0] == "ko"):
                return False
        else:
            if (self.wait_answer()[0] == "ko"):
                return False
        return True

    def incantation(self, return_only: bool = False):
        from ai.src.priority_order.ping import ping
        self.sock.send("Incantation\n".encode())
        if (return_only == True):
            if (self.wait_return()[0] == "ko"):
                return False
        else:
            if (self.wait_answer()[0] == "ko"):
                return False
        if (return_only == True):
            tmp = self.wait_return()[0]
            if (tmp == "ko"):
                return False
            else:
                return tmp
        else:
            tmp = self.wait_answer()[0]
            if (tmp == "ko"):
                return False
            else:
                return tmp
