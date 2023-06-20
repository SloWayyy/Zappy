from ai.src.player import *

import re

# ANSWER = lvl job pos_boss

def ping(player):
    from ai.src.game import msg_create
    from ai.src.player import EnumHeader, EnumPriorityOrder
    player.broadcast(msg_create(player, player.boss_uuid, EnumHeader.ANSWER.value, EnumPriorityOrder.PING.value, "{} {} {}".format(player.level, player.job, player.pos_boss)))
   

def ping_answer(player, uuid, info):
    data = re.findall("(\d+) (\d+) (\d+)", info)
    for i in player.array_uuid:
        if i["uuid"] == uuid:
            if (int(data[0][0]) > i["level"]):
                i["level"] = int(data[0][0])
            i["job"] = int(data[0][1])
            i["pos"] = int(data[0][2])
            # print("i receive: from {}, He is level {}, Do job {}, he his there {}".format(uuid, data[0][0], data[0][1], data[0][2]))
            return True
    return False
