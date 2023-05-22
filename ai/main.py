#!/usr/bin/env python3

import sys
import handle_args
import handle_packets

def main():
    try:
        args = handle_args.pars_args()
        handle_packets.get_socket(8080, "127.0.0.1")
    except handle_args.BadArgumentException as e:
        print(e)
        sys.exit(84)
    except handle_packets.BadConnectionException as e:
        print(e)
        sys.exit(84)

if __name__ == "__main__":
    main()
