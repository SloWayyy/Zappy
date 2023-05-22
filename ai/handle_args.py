import argparse

class BadArgumentException(Exception):
    pass

def handle_args():
    parser = argparse.ArgumentParser(add_help=False, exit_on_error=False)
    unknown, args = parser.parse_known_args()
    num_args = len(args)
    num_unknown = len(vars(unknown))
    if num_args < 4 or num_args > 6 or num_unknown :
        raise BadArgumentException("Error: bad arguments")
    return parser

def pars_args():
    parser = handle_args()
    parser.add_argument('-p', '--port', type=int)
    parser.add_argument('-n', '--name', type=str)
    parser.add_argument('-h', '--adress', type=str)
    args = parser.parse_args()
    return args
