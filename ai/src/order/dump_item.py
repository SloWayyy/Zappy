from ai.src.player import * 

def init_dump_item(player):
    from ai.src.player import EnumOrder
    player.job = int(EnumOrder.DUMP_ITEM.value)

def dump_item(player):
    from ai.src.player import EnumObject
    init_dump_item(player)
    inventory = player.inventory()
    print("inventory: ", inventory, flush=True)
    if (inventory == False or len(inventory) == 0):
        return False
    # pk on start a 1 ici a voir
    for i in range(len(inventory)): 
        for _ in range(0, inventory[i]):
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
