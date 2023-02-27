import time
from graph import prrint_freg,count_frequencies

def affine_cipher_encrypt(plaintext, a, b, alphabet):
    ciphertext = ""
    for char in plaintext:
        if char in alphabet:
            char_index = alphabet.index(char)
            new_index = (a * char_index + b) % len(alphabet)
            ciphertext += alphabet[new_index]
        else:
            ciphertext += char
    return ciphertext

def affine_cipher_decrypt(ciphertext, a, b, alphabet):
    plaintext = ""
    for char in ciphertext:
        if char in alphabet:
            char_index = alphabet.index(char)
            # Вычисляем обратный элемент a в кольце вычетов по модулю len(alphabet)
            inverse_a = pow(a, -1, len(alphabet))
            new_index = (inverse_a * (char_index - b)) % len(alphabet)
            plaintext += alphabet[new_index]
        else:
            plaintext += char
    return plaintext

def count_frequencies(text, alphabet):
    # функция для подсчета частот появления символов в тексте
    frequencies = {char: 0 for char in alphabet}
    for char in text:
        if char in frequencies:
            frequencies[char] += 1
    return frequencies


alphabet = "AĄBCĆDEĘFGHIJKLŁMNOÓPRSSŚTUWYZŹŻ"
a = 5
b = 7


with open('Text.txt', 'r', encoding='utf-8') as f:
    text = f.read().upper()


start_encrypt = time.time()
ciphertext = affine_cipher_encrypt(text, a, b, alphabet)
end_encrypt = time.time()
print("Зашифрованный текст:", ciphertext)

start_decrypt = time.time()
decrypted_plaintext = affine_cipher_decrypt(ciphertext, a, b, alphabet)
end_decrypt = time.time()
print('-'*55)
print("Расшифрованный текст:",decrypted_plaintext)

print("Encryption time:", end_encrypt - start_encrypt, "seconds")
print("Decryption time:", end_decrypt - start_decrypt, "seconds")


# подсчет частот символов
plain_freq = count_frequencies(text, alphabet)
cipher_freq = count_frequencies(ciphertext, alphabet)


prrint_freg(plain_freq,cipher_freq)