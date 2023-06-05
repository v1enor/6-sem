import binascii
from Crypto.Cipher import DES
import time
import hashlib

def pad(data):
    # дополнение данных до кратности 8 байтам
    padding_len = 8 - (len(data) % 8)
    data += bytes([padding_len] * padding_len)
    return data

def unpad(data):
    # удаление дополнения данных
    padding_len = data[-1]
    return data[:-padding_len]

def des_encrypt(key, data):
    # шифрование блока данных
    cipher = DES.new(key, DES.MODE_ECB)
    return cipher.encrypt(data)

def des_decrypt(key, data):
    # дешифрование блока данных
    cipher = DES.new(key, DES.MODE_ECB)
    return cipher.decrypt(data)

def triple_des_encrypt(key, data):
    # шифрование данных с использованием Triple DES (DES-EDE2)
    key1, key2 = key[:8], key[8:16]
    data = pad(data)
    data = des_encrypt(key1, data)
    data = des_decrypt(key2, data)
    data = des_encrypt(key1, data)
    return data

def triple_des_decrypt(key, data):
    # дешифрование данных с использованием Triple DES (DES-EDE2)
    key1, key2 = key[:8], key[8:16]
    data = des_decrypt(key1, data)
    data = des_encrypt(key2, data)
    data = des_decrypt(key1, data)
    data = unpad(data)
    return data

# пример использования
key = "my secret key"
key_bytes = key.encode("utf-8") # переводим строку в байты
key_hash = hashlib.md5(key_bytes).hexdigest() # хэшируем байты и переводим хэш в шестнадцатеричное представление
key = binascii.unhexlify(key_hash)
data = b'Hello, from univer in my python code'



start_time = time.time()
encrypted_data = triple_des_encrypt(key, data)
end_time = time.time()
encryption_time = end_time - start_time

print("MSG",data)
print("-" * 20)
print("Encr MSG:",binascii.hexlify(encrypted_data))

start_time = time.time()
decrypted_data = triple_des_decrypt(key, encrypted_data)
end_time = time.time()
decryption_time = end_time - start_time

print("Decr MSG:",decrypted_data)
print("-" * 20)
print("Encryption time: ", encryption_time)
print("Decryption time: ", decryption_time)

print("-" * 20)
print("Лавиный эффект")
print("-" * 20)

d=0
keyka = "my secret key"
for d in range(0,len(key)):
    d=d+1 
    keyka = keyka[:-1]
    key = keyka
    key_bytes = key.encode("utf-8") # переводим строку в байты
    key_hash = hashlib.md5(key_bytes).hexdigest() # хэшируем байты и переводим хэш в шестнадцатеричное представление
    key = binascii.unhexlify(key_hash)
    encrypted_data = triple_des_encrypt(key, data)
    print("Key:",keyka)
    print("Encr MSG:",binascii.hexlify(encrypted_data))
    print("-" * 20)




