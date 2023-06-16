from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes

def encrypt_message(key: bytes, message: str):
    rand = get_random_bytes(AES.block_size)
    cipher = AES.new(key, AES.MODE_CBC, rand)
    padded_message = pad(message.encode(), AES.block_size)
    encrypted_message = cipher.encrypt(padded_message)
    return rand + encrypted_message

def decrypt_message(key: bytes, encrypted_message):
    rand = encrypted_message[:AES.block_size]
    cipher = AES.new(key, AES.MODE_CBC, rand)
    decrypted_message = cipher.decrypt(encrypted_message[AES.block_size:])
    return unpad(decrypted_message, AES.block_size).decode()
