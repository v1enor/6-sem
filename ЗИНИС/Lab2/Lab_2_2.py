    import time
    from graph import prrint_freg,count_frequencies

    def generate_vigenere_table(alphabet):
        # функция для генерации таблицы Виженера на основе заданного алфавита
        table = {}
        n = len(alphabet)
        for i, char in enumerate(alphabet):
            row = []
            for j in range(n):
                row.append(alphabet[(i+j) % n])
            table[char] = row
        return table

    def porta_cipher_encrypt(plaintext, key, alphabet):
        # функция для шифрования текста шифром Порты
        key = key.lower()
        key_length = len(key)
        key_pos = [alphabet.index(char) for char in key]
        vigenere_table = generate_vigenere_table(alphabet)
        ciphertext = ''
        for i, char in enumerate(plaintext):
            if char in alphabet:
                col = alphabet.index(char)
                row = vigenere_table[key[i % key_length]][key_pos[i % key_length]]
                ciphertext += vigenere_table[row][col]
            else:
                ciphertext += char
        return ciphertext

    def porta_cipher_decrypt(ciphertext, key, alphabet):
        # функция для дешифрования текста, зашифрованного шифром Порты
        key = key.lower()
        key_length = len(key)
        key_pos = [alphabet.index(char) for char in key]
        vigenere_table = generate_vigenere_table(alphabet)
        plaintext = ''
        for i, char in enumerate(ciphertext):
            if char in alphabet:
                row = vigenere_table[key[i % key_length]][key_pos[i % key_length]]
                col = vigenere_table[row].index(char)
                plaintext += alphabet[col]
            else:
                plaintext += char
        return plaintext



    alphabet = "aąbcćdeęfghijklłmnoóprssśtuwyzźż"
    key = "ilua"


    with open('Text.txt', 'r', encoding='utf-8') as f:
        text = f.read().lower()

    # Зашифровка
    start_encrypt = time.time()
    ciphertext = porta_cipher_encrypt(text, key, alphabet)
    end_encrypt = time.time()
    print("Зашифрованный текст:", ciphertext)

    # Расшифровка
    start_decrypt = time.time()
    decrypted_text = porta_cipher_decrypt(ciphertext, key, alphabet)
    end_decrypt = time.time()
    print('-'*55)
    print("Расшифрованный текст:", decrypted_text)

    print("Encryption time:", end_encrypt - start_encrypt, "seconds")
    print("Decryption time:", end_decrypt - start_decrypt, "seconds")


    # подсчет частот символов
    plain_freq = count_frequencies(text, alphabet)
    cipher_freq = count_frequencies(ciphertext, alphabet)


    prrint_freg(plain_freq,cipher_freq)