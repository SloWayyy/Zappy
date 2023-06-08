from ai.src.player import Player, EnumDirection, EnumObject, look_item

def first_pattern(list_item : list, player: Player, direction: EnumDirection):
    player.move()
    if (list_item == []):
        return
    for i in list_item[0]:
        player.take(i)
    player.turn(direction)
    player.move()
    for i in list_item[1]:
        player.take(i)

def second_pattern(list_item : list, player: Player):
    counter = 0

    for _ in range(0, 3):
        player.turn(EnumDirection.RIGHT)
        for _ in range(0, 2):
            player.move()
            for j in list_item[counter]:
                player.take(j)
            counter += 1
    for _ in range(0, 2):
        player.turn(EnumDirection.RIGHT)
        player.move()

def routine_boss(player: Player):
    list_item = []
    player.take(EnumObject.FOOD.value)
    for i in range(0, 4):
        tmp, _ = look_item(player)
        for j in tmp:
            list_item.append(j)
        player.turn(EnumDirection.RIGHT)
    i = 0
    while i < len(list_item):
        list_item.pop(i)
        i += 2

    first_pattern(list_item, player, EnumDirection.RIGHT)
    second_pattern(list_item[2:], player)
    player.take(EnumObject.FOOD.value)