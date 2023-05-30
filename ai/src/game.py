

def wait_answer(sock):
    donnees = sock.recv(1024)
    if not donnees:
        return
    donnees = donnees.split(b'\n')
    for i, x in enumerate(donnees):
        donnees[i] = x.decode()
    print("Données reçues :", donnees)
    return donnees

def connection(sock, name):
    donnees = wait_answer(sock)
    if (donnees[0] == "WELCOME"):
        sock.send((name + "\n").encode())
        print("Envoi du nom de l'équipe... ({})".format(name))
    donnees = wait_answer(sock)
    if (int(donnees[0]) > 1):
        return True
    return False

def game_loop(sock, name):
    if (connection(sock, name) == True):
        sock.send("Look\n".encode())
        wait_answer(sock)
        sock.send("Inventory\n".encode())
        wait_answer(sock)
        sock.send("Set food\n".encode())
        wait_answer(sock)
        sock.send("Inventory\n".encode())
        wait_answer(sock)
        




    sock.close()
