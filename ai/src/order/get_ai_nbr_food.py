from ai.src.player import *

def get_ai_nbr_food(player, _):
    from ai.src.priority_order.ping import ping_send_food_nbr, ping
    # ping(player)
    ping_send_food_nbr(player)
    # ping_send_food_nbr(player)
    return True
