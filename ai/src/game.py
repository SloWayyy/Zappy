import socket

from ai.src.player import Player, EnumObject, EnumHeader

def find_boss(sock: socket.socket, name: str, player: Player):
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

def game_loop(sock: socket.socket, name: str):
    player = Player(sock, name)

    find_boss(sock, name, player)
    sock.close()
