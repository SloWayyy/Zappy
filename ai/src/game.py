import socket

from anyio import sleep

from ai.src.player import Player, EnumObject, EnumHeader

def game_init(sock: socket.socket, name: str) -> Player:
    player = Player(sock, name)
    player.broadcast(EnumHeader.ASKBOSS.value + " Who\n")
    player.look()
    player.take(EnumObject.FOOD.value)

    print('\n\n')

    if player.boss == 0:
        print("already a boss\n")
    else:
        player.boss = 1
        print("I'm the new boss\n")

    player.wait_answer()
    return player


def game_loop(sock: socket.socket, name: str):
    player = game_init(sock, name)
    sock.close()
