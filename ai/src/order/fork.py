from ai.src.player import *

def fork(player, _):
    from ai.src.priority_order.ping import ping
    print("je fork")
    player.fork()
    ping(player)
    duplicate(player.args)
    ping(player)
    return True
