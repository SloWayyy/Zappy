from ai.src.player import *
import re

# ANSWER = lvl job pos_boss

def ping(player):
    from ai.src.player import EnumHeader, EnumPriorityOrder
    player.broadcast("{} {} {} {} {} {} {}".format(player.uuid,
            EnumHeader.ANSWER.value, player.boss_uuid, EnumPriorityOrder.PING.value, player.level, player.job, player.pos_boss), False)

def ping_send_food_nbr(player):
    from ai.src.player import EnumHeader, EnumPriorityOrder
    ai_inventory = list(player.inventory())
    print("je lui repond ", ai_inventory[0], player.broadcast("{} {} {} {} {}".format(player.uuid,
            EnumHeader.ANSWER.value, player.boss_uuid, EnumPriorityOrder.PING_SEND_FOOD_NBR.value, ai_inventory[0]), False))

def ping_answer(player, uuid, info):
    data = re.findall("(\d+) (\d+) (\d+)", info)
    for i in player.array_uuid:
        if i["uuid"] == uuid:
            if (int(data[0][0]) > i["level"]):
                i["level"] = int(data[0][0])
            i["job"] = int(data[0][1])
            i["pos"] = int(data[0][2])
            # print("ping answer: {} {} {} {}".format(uuid, i["level"], i["job"], i["pos"]))
            if i["level"] == 7:
                player.level7 = True
            return True
    return False

def ping_answer_food_nbr(boss, uuid, info):
    data = re.findall("(\d+)", info)
    print("ping answer_food_nbr", data, "uuid", uuid, flush=True)
    # for i in boss.array_uuid:
    #     if i["uuid"] == uuid:
    #         i["job"] = 9
    if boss.ai_enought_food[0] == -1:
        boss.ai_enought_food[0] = 0
    boss.ai_enought_food[0] += 1
    if int(data[0][0]) < 5:
        pass
    else:
        print("AI NBR BOUFF AVANT", boss.ai_enought_food[1], flush=True)
        boss.ai_enought_food[1] += 1
        print("AI NBR BOUFF APRES", boss.ai_enought_food[1], flush=True)
    print("en sortit", boss.ai_enought_food, flush=True)

