from ai.src.player import *

def fork(player, _):
    from ai.src.priority_order.ping import ping
    player.fork()
    ping(player)
    duplicate(player.args)
    return True
