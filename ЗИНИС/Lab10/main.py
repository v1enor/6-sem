from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import rsa, dsa, ec
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import padding
import time

# Генерация RSA-ключей
def generate_rsa_keys():
    private_key = rsa.generate_private_key(
        public_exponent=65537,
        key_size=2048
    )
    public_key = private_key.public_key()
    return private_key, public_key

# Генерация хеша сообщения
def hash_message(message):
    digest = hashes.Hash(hashes.SHA256())
    digest.update(message)
    return digest.finalize()

# Генерация ЭЦП RSA
def sign_rsa(message, private_key):
    signature = private_key.sign(
        message,
        padding.PSS(
            mgf=padding.MGF1(hashes.SHA256()),
            salt_length=padding.PSS.MAX_LENGTH
        ),
        hashes.SHA256()
    )
    return signature

# Верификация ЭЦП RSA
def verify_rsa(message, signature, public_key):
    try:
        public_key.verify(
            signature,
            message,
            padding.PSS(
                mgf=padding.MGF1(hashes.SHA256()),
                salt_length=padding.PSS.MAX_LENGTH
            ),
            hashes.SHA256()
        )
        return True
    except InvalidSignature:
        return False

# Генерация ключей Эль-Гамаля
def generate_elgamal_keys():
    private_key = dsa.generate_private_key(
        key_size=2048
    )
    public_key = private_key.public_key()
    return private_key, public_key

# Генерация ЭЦП Эль-Гамаля
def sign_elgamal(message, private_key):
    signature = private_key.sign(
        message,
        hashes.SHA256()
    )
    return signature

# Верификация ЭЦП Эль-Гамаля
def verify_elgamal(message, signature, public_key):
    try:
        public_key.verify(
            signature,
            message,
            hashes.SHA256()
        )
        return True
    except InvalidSignature:
        return False

# Генерация ключей Шнорра
def generate_schnorr_keys():
    private_key = ec.generate_private_key(
        ec.SECP256R1()
    )
    public_key = private_key.public_key()
    return private_key, public_key

# Генерация ЭЦП Шнорра
def sign_schnorr(message, private_key):
    signature = private_key.sign(
        message,
        ec.ECDSA(hashes.SHA256())
    )
    return signature

# Верификация ЭЦП Шнорра
def verify_schnorr(message, signature, public_key):
    try:
        public_key.verify(
            signature,
            message,
            ec.ECDSA(hashes.SHA256())
        )
        return True
    except InvalidSignature:
        return False

# Оценка времени выполнения операций
def measure_execution_time(operation, *args):
    start_time = time.time()
    result = operation(*args)
    end_time = time.time()
    execution_time = end_time - start_time
    return result, execution_time


# Пример использования

# Генерация и верификация RSA
private_key_rsa, public_key_rsa = generate_rsa_keys()
message = b"Hello, world!"
hashed_message = hash_message(message)
signature_rsa = sign_rsa(hashed_message, private_key_rsa)
is_valid_rsa = verify_rsa(hashed_message, signature_rsa, public_key_rsa)

# Генерация и верификация Эль-Гамаля
private_key_elgamal, public_key_elgamal = generate_elgamal_keys()
signature_elgamal = sign_elgamal(hashed_message, private_key_elgamal)
is_valid_elgamal = verify_elgamal(hashed_message, signature_elgamal, public_key_elgamal)

# Генерация и верификация Шнорра
private_key_schnorr, public_key_schnorr = generate_schnorr_keys()
signature_schnorr = sign_schnorr(hashed_message, private_key_schnorr)
is_valid_schnorr = verify_schnorr(hashed_message, signature_schnorr, public_key_schnorr)

# Оценка времени выполнения
signature_rsa, execution_time_rsa = measure_execution_time(sign_rsa, hashed_message, private_key_rsa)
is_valid_rsa, execution_time_rsa_verification = measure_execution_time(verify_rsa, hashed_message, signature_rsa, public_key_rsa)

signature_elgamal, execution_time_elgamal = measure_execution_time(sign_elgamal, hashed_message, private_key_elgamal)
is_valid_elgamal, execution_time_elgamal_verification = measure_execution_time(verify_elgamal, hashed_message, signature_elgamal, public_key_elgamal)

signature_schnorr, execution_time_schnorr = measure_execution_time(sign_schnorr, hashed_message, private_key_schnorr)
is_valid_schnorr, execution_time_schnorr_verification = measure_execution_time(verify_schnorr, hashed_message, signature_schnorr, public_key_schnorr)

print("Message:", message.decode())
print("Hashed Message:", hashed_message.hex())

print(f"\nRSA: Signature: {signature_rsa}, Valid: {is_valid_rsa}, Time: {execution_time_rsa} s")
print(f"RSA Verification: Valid: {is_valid_rsa}, Time: {execution_time_rsa_verification} s")

print("\nMessage:", message.decode())
print("Hashed Message:", hashed_message.hex())

print(f"\nElGamal: Signature: {signature_elgamal}, Valid: {is_valid_elgamal}, Time: {execution_time_elgamal} s")
print(f"ElGamal Verification: Valid: {is_valid_elgamal}, Time: {execution_time_elgamal_verification} s")

print("\nMessage:", message.decode())
print("Hashed Message:", hashed_message.hex())

print(f"\nSchnorr: Signature: {signature_schnorr}, Valid: {is_valid_schnorr}, Time: {execution_time_schnorr} s")
print(f"Schnorr Verification: Valid: {is_valid_schnorr}, Time: {execution_time_schnorr_verification} s")
