import os
from math import ceil
from random import randint
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend

AES_DEFAULT_KEY_LENGTH = 16
AES_BLOCK_SIZE = 16

def numBlocksRequired(message, blockSize):
    return 

def encrypt(mode, key, iv, inputBytes):

    backend = default_backend()
    encryptor = Cipher(
        algorithms.AES(key),
        mode,
        backend=backend
        ).encryptor()

    if isinstance(mode, modes.CBC):
        length = ceil(len(inputBytes) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE
    else:
        length = len(inputBytes) + AES_BLOCK_SIZE - 1
    buf = bytearray(length)
    lenEncrypted = encryptor.update_into(inputBytes, buf)
    ct = bytes(buf[:lenEncrypted]) + encryptor.finalize()
    return ct

def decrypt(mode, key, ct):
    backend = default_backend()
    decryptor = Cipher(
        algorithms.AES(key),
        mode,
        backend=backend
        ).decryptor()
    return decryptor.update(ct) + decryptor.finalize()


def padWithRandomBytes(message):
    """
    Appends 5-10 bytes of random data onto the start and end of 
    a message. The count is chosen randomly at both ends.

    Parameters:
    - message: raw bytes
    """
    assert(isinstance(message, bytes))
    return os.urandom(randint(5, 10)) \
            + message \
            + os.urandom(randint(5, 10))
    

def randomAESEncrypt(message):
    """
    AES encrypts data using a random 16-byte key.
    Appends 5-10 bytes (count chosen randomly) to the start and end 
    of the message before encryption.
    Chooses randomly between ECB and CBC mode, with each having
    probability 1/2 of being chosen.
    """
    message = padWithRandomBytes(message)
    key = os.urandom(AES_DEFAULT_KEY_LENGTH)
    iv = os.urandom(AES_BLOCK_SIZE)

    if randint(0,1):
        mode = modes.ECB()
    else:
        mode = modes.CBC(iv)

    return encrypt(mode, key, iv, message)
