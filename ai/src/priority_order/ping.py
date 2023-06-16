from ai.src.player import *
import re

# ANSWER = lvl job

def ping(player):
    from ai.src.player import EnumHeader, EnumPriorityOrder
    player.broadcast("{} {} {} {} {} {}".format(player.uuid, EnumHeader.ANSWER.value, player.boss_uuid, EnumPriorityOrder.PING.value, str(player.level), player.job), False)

def ping_answer(player, uuid, info):
    data = re.findall("(\d+) (\d+)", info)
    for i in player.array_uuid:
        if i["uuid"] == uuid:
            i["level"] = int(data[0][0])
            i["job"] = int(data[0][1])
            print("i receive: from {}, He is level {}, Do job {}".format(uuid, data[0][0], data[0][1]))
            return True
    return False
