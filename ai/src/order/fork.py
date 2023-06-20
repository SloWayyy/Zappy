from ai.src.player import *

def fork(player, _):
    player.fork()
    duplicate(player.args)
    return True
