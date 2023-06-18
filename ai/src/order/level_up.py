from ai.src.order.dump_item import *

def level_up(player, _):
    from ai.src.priority_order.ping import ping
    ping(player)
    print("-------------------------level_up-------------------------------", player.uuid)
    print("lvl ", player.incantation())
    print("-------------------------Done-----------------------------------", player.uuid)
