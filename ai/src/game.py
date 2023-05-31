import socket

from ai.src.player import Player, EnumObject

def game_loop(sock: socket.socket, name: str):
    player = Player(sock, name)
    # player.move()
    # player.turn(Direction.RIGHT)
    # player.look()
    player.set(EnumObject.FOOD)
    player.inventory()
    # player.take(food)
    # player.broadcast("test")
    sock.close()
