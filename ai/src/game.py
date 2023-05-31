import socket

from ai.src.player import Player, Direction

def game_loop(sock: socket.socket, name: str):
    player = Player(sock, name)
    player.move()
    player.turn(Direction.RIGHT)
    player.look()
    player.inventory()
    player.broadcast("test")
    sock.close()
