#include "AESUtils.h"
#include <cstring>
#include <string>
#include <iostream>


AesCbc::~AesCbc() {
   if(m_ctx) {
        EVP_CIPHER_CTX_cleanup(m_ctx);
   }
}
bool AesCbc::Reset(const uint8_t* key, const uint8_t* iv16) {
    if (!(m_ctx = EVP_CIPHER_CTX_new())) {
        printf ("EVP_CIPHER_CTX_new() failed\n");
        return false;
    }
    if (EVP_DecryptInit_ex(m_ctx, EVP_aes_128_cbc(), NULL, key, iv16)!=1) {
        printf ("EVP_DecryptInit_ex failed\n");
        return false;

    }
    return true;
}

size_t AesCbc::Decrypt(uint8_t* input, int len, std::vector<uint8_t> &decryptedData ) {     
    if(m_ctx == nullptr) {
        printf ("Cipher not created ! \n");         
        return 0;
    }

    if(input == nullptr || len == 0) {
        printf ("Incorrect arguments\n");         
        return 0;
    }

    decryptedData.resize(len);

    int update_len, final_len;
    if (EVP_DecryptUpdate(m_ctx, &decryptedData[0], &update_len, input, len) != 1) {
        printf ("EVP_ENcryptUpdate failed\n");
        return 0;
    }

    EVP_DecryptFinal_ex (m_ctx, &decryptedData[0] + update_len, &final_len);
    return final_len;
}

std::vector<uint8_t> AesCbc::md5_hash_data(uint8_t * data, size_t size) {
    std::vector<uint8_t> hashVector(16, 0);
    if (data == nullptr || size == 0) {
        return {};
    }
    
    MD5(data, size, &hashVector[0]);
    return hashVector;
}