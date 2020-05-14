import os
from random import randint
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

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
    if randint(0,1):
        mode = modes.ECB()
    else:
        mode = modes.CBC()
        iv = os.urandom()
