def game_loop(args, connexion, adresse):

    while True:
        donnees = connexion.recv(1024)
        if not donnees:
            break
        print("Données reçues :", donnees.decode())

    connexion.close()
