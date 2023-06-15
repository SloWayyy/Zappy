import socket

from ai.src.player import Player, EnumBoss, EnumHeader, EnumOrder
from ai.src.game_start import find_boss
from ai.src.player import ALL

def boss_routine(player: Player):
    for i in range(0, len(player.array_uuid)):
        player.broadcast(player.uuid + " " + EnumHeader.ORDER.value + " " + player.array_uuid[i] + " " + EnumOrder.JOIN_BOSS.value, False)
    while True:
        player.broadcast(player.uuid + " " + EnumHeader.IMBOSS.value + " " + ALL + " " + "JAJAJA", False)

def game_loop(sock: socket.socket, args):
    player = Player(sock, args)
    find_boss(player)
    if player.boss == EnumBoss.IMNOT.value:
        while True:
            player.wait_broadcast()
    if player.boss == EnumBoss.IM.value:
        boss_routine(player)
    sock.close()
