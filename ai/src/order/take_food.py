def take_food(player, _):
    from ai.src.player import EnumObject
    print("JE PRENDS----------------")
    player.take(EnumObject.FOOD.value)
