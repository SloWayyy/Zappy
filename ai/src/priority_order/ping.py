from ai.src.player import *
import re

# ANSWER = lvl job pos_boss

def ping(player):
    from ai.src.player import EnumHeader, EnumPriorityOrder
    player.broadcast("{} {} {} {} {} {} {}".format(player.uuid, EnumHeader.ANSWER.value, player.boss_uuid, EnumPriorityOrder.PING.value, player.level, player.job, player.pos_boss), False)

def ping_answer(player, uuid, info):
    data = re.findall("(\d+) (\d+) (\d+)", info)
    for i in player.array_uuid:
        if i["uuid"] == uuid:
            i["level"] = int(data[0][0])
            i["job"] = int(data[0][1])
            i["pos"] = int(data[0][2])
            # print("i receive: from {}, He is level {}, Do job {}, he his there {}".format(uuid, data[0][0], data[0][1], data[0][2]))
            return True
    return False
