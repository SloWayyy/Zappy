from ai.src.player import *

def fork(player, _ = None):
    from ai.src.priority_order.ping import ping
    ping(player)
    player.fork()
    duplicate(player.args)
    return True
