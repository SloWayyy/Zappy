import socket

from ai.src.game_start import find_boss, join_boss
from ai.src.player import Player
from ai.src.ordre.square_collect import square_collect
from ai.src.players.routine_boss import routine_boss

def game_loop(sock: socket.socket, args):
    player = Player(sock, args)
    find_boss(player)
    join_boss(player)
    if player.boss == 1:
        routine_boss(player)
        pass
    else:
        square_collect(player, 0)
        pass
    player.incantation()    
    sock.close()
