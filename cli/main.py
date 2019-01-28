import os
import click


def print_menu():
    files = [ name for name in os.listdir("../data") ]

    for idx, name in enumerate(files):
        print("{}) {}".format(idx+1, name))

    print()


if __name__ == "__main__":
    print()
    print("Choose a problem instance:\n")
    print_menu()
    value = click.prompt('Please enter a valid integer', type=int)
