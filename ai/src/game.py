import socket

from ai.src.game_start import find_boss, join_boss
from ai.src.player import Player

# def get_mineral(player: Player):
#     if player.boss == 1:
#         print (player.look())
#     else:
#         for _ in range(0, 3):
#             player.move()
#         player.look()
#         player.turn(EnumDirection.LEFT.value)

def game_loop(sock: socket.socket, args):
    player = Player(sock, args)
    find_boss(player)
    join_boss(player)
    print(player.inventory())
    while (1):
        pass
    sock.close()
