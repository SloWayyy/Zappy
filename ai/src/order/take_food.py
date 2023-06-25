def take_food(player, _):
    from ai.src.player import EnumObject
    player.take(EnumObject.FOOD.value)
