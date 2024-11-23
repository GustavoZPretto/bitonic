import random
import string
import os
import argparse

output_dir = "data" # diretorio onde vao ser guardados os arquivos
os.makedirs(output_dir, exist_ok=True)

# funcao que gera uma string com um charset de um tamanho pre definido
def generate_random_string(length, char_set):
    return ''.join(random.choices(char_set, k=length))

# cria o arquivo .in no formato desejado com os parametros passados
def generate_file(num_strings, string_length, char_set, file_name):
    with open(file_name, "w") as f:
        # numero de strings no inicio do arquivo
        f.write(f"{num_strings}\n")
        # gera as strings
        for _ in range(num_strings):
            f.write(generate_random_string(string_length, char_set) + "\n")

def main():
    parser = argparse.ArgumentParser(description="Generate files with random strings or digits.")
    parser.add_argument("char_type", choices=["s", "d", "sd"], help="Type of characters: s (strings), d (digits), sd (strings and digits)")
    parser.add_argument("num_strings", type=int, choices=[
        1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768,
        65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608,
        16777216, 33554432, 67108864, 134217728, 268435456, 536870912,
        1073741824
    ], help="Number of strings to generate (must be a power of 2)")
    parser.add_argument("string_length", type=int, help="Length of each string")

    args = parser.parse_args()

    if args.char_type == "s":
        char_set = string.ascii_letters
    elif args.char_type == "d":
        char_set = string.digits
    else:
        char_set = string.ascii_letters + string.digits

    file_name = os.path.join(output_dir, f"{args.char_type}_{args.num_strings}x{args.string_length}.in")
    generate_file(args.num_strings, args.string_length, char_set, file_name)
    print(f"Arquivo gerado: {file_name}")

if __name__ == "__main__":
    main()
