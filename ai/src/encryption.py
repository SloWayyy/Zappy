from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes
from time import time_ns

class NonceException(Exception):
    pass

class Encryption:
    def __init__(self):
        self.nonces = {}

    def encrypt_message(self, key: bytes, message: str):
        rand = get_random_bytes(AES.block_size)
        cipher = AES.new(key, AES.MODE_CBC, rand)
        final_msg = str(time_ns()) + " " + message
        padded_message = pad(final_msg.encode(), AES.block_size)
        encrypted_message = cipher.encrypt(padded_message)
        return rand + encrypted_message

    def decrypt_message(self, key: bytes, encrypted_message):
        rand = encrypted_message[:AES.block_size]
        cipher = AES.new(key, AES.MODE_CBC, rand)
        decrypted_message = cipher.decrypt(encrypted_message[AES.block_size:])
        unpadded_message = unpad(decrypted_message, AES.block_size).decode()
        nonce, message = unpadded_message.split(" ", 1)
        if (self.nonces.get(nonce) is not None):
            raise NonceException()
        self.nonces[nonce] = True
        return message
