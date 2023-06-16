from ai.src.player import * 

def init_dump_item(player):
    from ai.src.player import EnumOrder
    player.job = int(EnumOrder.DUMP_ITEM.value)

def dump_item(player):
    init_dump_item(player)
    inventory = player.inventory()
    if (inventory == False or len(inventory) == 0):
        return False
    for i in range(1, len(inventory)):
        for _ in range(0, inventory[i]):
            if i == 1:
                if (player.set(player.EnumObject.LINEMATE) == False):
                    return False
            if i == 2:
                if (player.set(player.EnumObject.DERAUMERE) == False):
                    return False
            if i == 3:
                if (player.set(player.EnumObject.SIBUR) == False):
                    return False
            if i == 4:
                if (player.set(player.EnumObject.MENDIANE) == False):
                    return False
            if i == 5:
                if (player.set(player.EnumObject.PHIRAS) == False):
                    return False
            if i == 6:
                if (player.set(player.EnumObject.THYSTAME) == False):
                    return False
