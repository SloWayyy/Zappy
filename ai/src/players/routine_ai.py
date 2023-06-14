from asyncio import sleep
from ai.src.player import Player, EnumDirection, EnumObject, EnumHeader
from ai.src.players.routine_boss import look_item

def first_pattern_ai(list_item: list, player: Player):
    player.move()
    for i in list_item[0]:
        player.take(i)
    player.turn(EnumDirection.LEFT)
    player.move()
    for i in list_item[1]:
        player.take(i)

def second_pattern_ai(list_item: list, player: Player):
    player.turn(EnumDirection.LEFT)
    player.move()
    player.move()
    for i in list_item[0]:
        player.take(i)
    player.turn(EnumDirection.LEFT)
    player.move()
    for i in list_item[1]:
        player.take(i)
    player.move()
    for i in list_item[2]:
        player.take(i)
    player.turn(EnumDirection.LEFT)
    player.move()
    player.move()
    for i in list_item[3]:
        player.take(i)

def look_aroud_ai(player: Player):
    list_item = []
    for _ in range(0, 3):
        player.move()
    tmp, foot_case = look_item(player)
    for i in tmp:
        list_item.append(i)
    for _ in range(0, 2):
        player.turn(EnumDirection.RIGHT)
    tmp, _ = look_item(player)
    for j in tmp:
        list_item.append(j)
    if (len(list_item) > 1):
        list_item.insert(0, list_item.pop())
    return list_item, foot_case

def return_to_boss(player: Player):
    player.turn(EnumDirection.LEFT)
    player.move()
    player.turn(EnumDirection.RIGHT)
    player.move()
    # player.move() faut le remettre c'est juste pour test le serveur de merde mdr ahahaaahah

def routine_ai(player: Player):
    list_item, foot_case = look_aroud_ai(player)
    for i in foot_case:
        player.take(i)
    list_item.reverse()
    first_pattern_ai(list_item, player)
    second_pattern_ai(list_item[2:], player)
    return_to_boss(player)
    print("inventory ai: ", player.inventory())
    if player.level == 1:
        player.take(EnumObject.FOOD.value)
        player.take(EnumObject.LINEMATE.value)
        player.take(EnumObject.DERAUMERE.value)
        player.take(EnumObject.SIBUR.value)
        player.take(EnumObject.MENDIANE.value)
        player.take(EnumObject.PHIRAS.value)
        player.take(EnumObject.THYSTAME.value)
        player.set(EnumObject.LINEMATE, 1)
        print("ai: ", player.look())
        print("ai: ", player.incantation())
        player.level += 1
    while(1):
        pass
