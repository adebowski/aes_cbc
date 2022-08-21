import argparse
from os import urandom
from binascii import unhexlify as decode, hexlify as encode
from random import random
from traceback import print_last
import binascii
import asyncio
from Crypto.Random import get_random_bytes
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from hashlib import md5

from base64 import b64encode


def setup_args():
    p = argparse.ArgumentParser(description="Creates encrypted orders data")
    p.add_argument(
        "executable_file", metavar="FIRMWARE_FILE", type=argparse.FileType("rb")
    )

    args = p.parse_args()
    return args


class AESCipher:
    def __init__(self, key):
        password = key.encode("utf-8")
        self.key = md5(password).digest()

    def encrypt(self, data):
        vector = get_random_bytes(AES.block_size)
        encryption_cipher = AES.new(self.key, AES.MODE_CBC, vector)

        encrypted = encryption_cipher.encrypt(pad(data, AES.block_size))
        return vector + encrypted

    def decrypt(self, data):
        file_vector = data[: AES.block_size]
        decryption_cipher = AES.new(self.key, AES.MODE_CBC, file_vector)
        return unpad(decryption_cipher.decrypt(data[AES.block_size :]), AES.block_size)


async def Callback(reader, writer):
    enc_key = "XhtBfSVHzDmWweev"

    while True:
        try:
            text = input("Type a message:\n").encode("utf-8")
            encrypt = AESCipher(enc_key).encrypt(text)
            print("encrypted: ", binascii.hexlify(encrypt))
            writer.write(encrypt)
        except:
            writer.close()


async def StartServer(port):
    server = await asyncio.start_server(Callback, "", port)
    async with server:
        await server.serve_forever()


def main():
    # args = setup_args()
    try:
        asyncio.run(
            StartServer(
                8888,
            )
        )
    except KeyboardInterrupt:
        print("Cannot start server")
        pass


if __name__ == "__main__":
    main()
