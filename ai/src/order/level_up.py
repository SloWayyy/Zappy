from ai.src.order.dump_item import *

def level_up(player, _):
    from ai.src.priority_order.ping import ping
    ping(player)
    player.incantation()

