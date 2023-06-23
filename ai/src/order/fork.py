from ai.src.player import *

def fork(player, _):
    from ai.src.priority_order.ping import ping
    ping(player)
    player.fork()
    duplicate(player.args)
    return True
