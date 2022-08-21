#include "Parser.h"
#include <string>

#define IV_SIZE 16

std::string Parser::DecryptData(const uint8_t* data, size_t bufferSize){
    if (data == nullptr || bufferSize == 0 ) {
        return "";
    }

    AesCbc aesCbc;
    std::vector<uint8_t> buffer(data, data + bufferSize);
    printf("\nEncrypted: ");
    for (auto i : buffer)
    {
         printf("%x ", i);
    }
    printf("\n");

    EVP_CIPHER_CTX* ctx;
    int len;
    int ciphertext_len;
    char key[16 + 1] = "XhtBfSVHzDmWweev";

    const auto keyHash = AesCbc::md5_hash_data((uint8_t*)&key, sizeof(key)-1);
    const auto ivEnd = buffer.begin() + IV_SIZE;
    const std::vector<uint8_t> iv(buffer.begin(), ivEnd);
    const std::vector<uint8_t> dataEncrypted(ivEnd, buffer.end());

    std::vector<uint8_t> toDecrypt(0, dataEncrypted.size());    

    aesCbc.Reset(keyHash.data(), iv.data());
    const size_t decryptedSize = aesCbc.Decrypt((uint8_t *)&dataEncrypted[0], dataEncrypted.size(),toDecrypt);

    std::string decryptedData(toDecrypt.begin(), toDecrypt.begin() +  decryptedSize);

    return decryptedData;
}