from ai.src.player import *
from ai.src.order.fork import fork

def farm(player, _ = None):
    from ai.src.priority_order.ping import ping
    from ai.src.player import EnumHeader, EnumPriorityOrder, EnumObject
    from ai.src.game import msg_create
    ping(player)
    i = 0
    while True:
        player.broadcast("{} {} {} {} {} {}".format(player.uuid, EnumHeader.ANSWER.value, player.boss_uuid, EnumPriorityOrder.FARM.value, player.level, "nothing"))
        fork(player)
        i += 1
        if i == 3:
            player.take(EnumObject.FOOD.value)
            i = 0

def farm_answer(player, uuid, info):
    player.reaper += 1

