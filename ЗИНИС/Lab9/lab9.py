import hashlib

input_data = input('Введите сообщение: ')

hash_object = hashlib.sha256(input_data.encode())
hex_dig = hash_object.hexdigest()

print(hex_dig)



import hashlib
import timeit

input_data = "Hello, world!"

def sha256():
    hash_object = hashlib.sha256(input_data.encode())
    hex_dig = hash_object.hexdigest()
    return hex_dig

print(timeit.timeit(sha256, number=10000))