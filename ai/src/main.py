#!/usr/bin/env python3

import sys

from ai.src.game import game_loop
from ai.src.handle_args import pars_args, BadArgumentException
from ai.src.handle_packets import get_socket, BadConnectionException

def main():
    try:
        args = pars_args()
        print (args.address)
        connexion, adresse = get_socket(args.port, args.address if args.address is not None else "")
        game_loop(args, connexion, adresse)
        sys.exit(0)
    except BadArgumentException as e:
        print(e)
    except BadConnectionException as e:
        print(e)
    sys.exit(84)

if __name__ == "__main__":
    main()
