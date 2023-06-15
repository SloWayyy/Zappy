import socket

from ai.src.player import Player, EnumHeader
from ai.src.game_start import find_boss
from ai.src.order.square_collect import square_collect
from ai.src.order.take_around import take_around
from ai.src.order.join_boss import join_boss
from ai.src.order.go_front import go_front

def game_loop(sock: socket.socket, args):
    player = Player(sock, args)
    find_boss(player)
    join_boss(player)
    if player.boss == 1:
        while 1:
            player.broadcast(EnumHeader.IMBOSS.value + " IMBOSS\n")
        # take_around(player)
        pass
    else:
        go_front(player, 0)
        # square_collect(player, 0)
        pass
    # print("j'ai fait une incantation :", player.incantation())
    sock.close()
