def game_loop(sock):

    while True:
        donnees = sock.recv(1024)
        if not donnees:
            break
        print("Données reçues :", donnees.decode())

    sock.close()
