import os
import click
import subprocess


FILES = [ name for name in os.listdir("./data") ]

def print_menu():
    for idx, name in enumerate(FILES):
        print("{}) {}".format(idx+1, name))

    print()

def solve(instance_id):
    filepath = "./data/" + FILES[instance_id - 1]
    print(filepath)
    p = subprocess.run(["./bin/knapsack", filepath], stdout=subprocess.PIPE)
    output_data = p.stdout.decode("utf-8").strip()

    return output_data


if __name__ == "__main__":
    print()
    print("Choose a problem instance:\n")
    print_menu()
    value = click.prompt('Please enter a valid integer', type=int)

    print(solve(value))
