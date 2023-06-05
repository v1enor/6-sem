class RC4:
    def __init__(self, key):
        self.S = list(range(256))
        j = 0
        for i in range(256):
            j = (j + self.S[i] + key[i % len(key)]) % 256
            self.S[i], self.S[j] = self.S[j], self.S[i]
        self.i = self.j = 0

    def generate_keystream(self, n):
        keystream = []
        for _ in range(n):
            self.i = (self.i + 1) % 256
            self.j = (self.j + self.S[self.i]) % 256
            self.S[self.i], self.S[self.j] = self.S[self.j], self.S[self.i]
            keystream.append(self.S[(self.S[self.i] + self.S[self.j]) % 256])
        return keystream

key = [123, 125, 41, 84, 203]
plaintext = "This is a test message."

rc4 = RC4(key)
keystream = rc4.generate_keystream(len(plaintext))

# XOR plaintext and keystream to get the ciphertext
ciphertext = [ord(p) ^ k for p, k in zip(plaintext, keystream)]

# Print the ciphertext in hex format
print("Ciphertext:", "".join(f"{c:02x}" for c in ciphertext))

# Reuse the same RC4 object with the same key
rc4 = RC4(key)

# Decrypt the ciphertext using the same keystream
keystream = rc4.generate_keystream(len(ciphertext))
plaintext = "".join(chr(c ^ k) for c, k in zip(ciphertext, keystream))

print("Plaintext:", plaintext)


import time
 
# Generate 1MB keystream and measure the time
start_time = time.time()
keystream = rc4.generate_keystream(1024*1024)
end_time = time.time()

print("Time taken to generate 1MB keystream:", end_time - start_time, "seconds")
