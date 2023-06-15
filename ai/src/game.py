import socket

from ai.src.player import Player
from ai.src.game_start import find_boss
from ai.src.order.square_collect import square_collect
from ai.src.order.take_around import take_around
from ai.src.order.join_boss import join_boss

def game_loop(sock: socket.socket, args):
    player = Player(sock, args)
    find_boss(player)
    join_boss(player)
    if player.boss == 1:
        take_around(player)
        pass
    else:
        square_collect(player, 0)
        pass
    print("j'ai fait une incantation :", player.incantation())
    sock.close()
