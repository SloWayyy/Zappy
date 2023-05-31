import socket

from ai.src.player import Player, EnumObject, EnumHeader

def game_loop(sock: socket.socket, name: str):
    player = Player(sock, name)
    # player.move()
    # player.turn(Direction.RIGHT)
    # player.look()
    player.broadcast(EnumHeader.BOSS.value + " test")
    player.wait_answer()
    print("\n\n")
    player.broadcast("$2$ test2")
    player.wait_answer()

    # player.take(food)
    # player.broadcast("test")
    sock.close()
