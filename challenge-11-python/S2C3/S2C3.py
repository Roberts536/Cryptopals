import AESUtils
import os
from cryptography.hazmat.primitives.ciphers import modes

mode = modes.ECB()
message = "YELLOW SUBMARINE".encode('utf-8')
key = os.urandom(AESUtils.AES_DEFAULT_KEY_LENGTH)
iv = os.urandom(AESUtils.AES_BLOCK_SIZE)

ciphertext = AESUtils.randomAESEncrypt(message)
print(ciphertext)
