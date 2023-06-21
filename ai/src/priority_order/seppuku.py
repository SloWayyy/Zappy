def seppuku(player):
    from ai.src.player import EnumHeader, EnumPriorityOrder, EnumObject
    from ai.src.game import msg_create
    player.broadcast(msg_create(player, player.boss_uuid, EnumHeader.ANSWER.value, EnumPriorityOrder.SEPPUKU.value))
    inventory = player.inventory()
    if (inventory == False or len(inventory) == 0):
        return False
    for i in range(len(inventory)): 
        for __ in range(0, inventory[i]):
            if i == 0:
               if (player.set(EnumObject.FOOD) == False):
                    return False 
            if i == 1:
                if (player.set(EnumObject.LINEMATE) == False):
                    return False
            if i == 2:
                if (player.set(EnumObject.DERAUMERE) == False):
                    return False
            if i == 3:
                if (player.set(EnumObject.SIBUR) == False):
                    return False
            if i == 4:
                if (player.set(EnumObject.MENDIANE) == False):
                    return False
            if i == 5:
                if (player.set(EnumObject.PHIRAS) == False):
                    return False
            if i == 6:
                if (player.set(EnumObject.THYSTAME) == False):
                    return False


def seppuku_answer(player, uuid, _):
    for i in player.array_uuid:
        if i["uuid"] == uuid:
            player.array_uuid.remove(i)
            return True
    return False
