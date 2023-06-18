from ai.src.order.square_collect import *
from ai.src.order.take_around import *
from ai.src.order.join_boss import *

def go_front(player, data):
    orientation = int(data)
    map_size = 0
    cpt = 0
    if (look_this_orientation(player, orientation) == False):
        return False
    if (player.map_size.x > player.map_size.y):
        map_size = player.map_size.y
    else:
        map_size = player.map_size.x
    for i in range(map_size):
        cpt += 1
        player.move()
        if (i > 4 and i != map_size - 1):
            _, foot_case = look_item(player)
            for j in range (1, len(foot_case)):
                if (foot_case[j] != "player"):
                    player.take(foot_case[j])
    player.pos_boss = -1
    if (locate_boss(player) == False):
        if (player.map_size.x < player.map_size.y):
            map_size = player.map_size.y
        else:
            map_size = player.map_size.x
        for i in range(map_size - cpt):
            player.move()
            if (i != map_size - cpt - 1):
                _, foot_case = look_item(player)
                for j in range (1, len(foot_case)):
                    if (foot_case[j] != "player"):
                        player.take(foot_case[j])
    

    
