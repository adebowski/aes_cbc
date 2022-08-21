#pragma once

#include <cstdint>


#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/md5.h>
#include <vector>


#define BLOCK_SIZE 16
class AesCbc {
   protected:
    uint8_t m_aes_ecb_input[BLOCK_SIZE]{};
    EVP_CIPHER_CTX *m_ctx;

    uint8_t m_available = BLOCK_SIZE;
    std::size_t m_count = 0;

   public:
    AesCbc() = default;
    ~AesCbc();

    bool Reset(const uint8_t* key, const uint8_t* iv16);
    size_t Decrypt(uint8_t* input, int len, std::vector<uint8_t> &decryptedData);
    static std::vector<uint8_t> md5_hash_data(uint8_t * data, size_t size);

    AesCbc(const AesCbc&) = delete;
    AesCbc(AesCbc&&) = delete;
    AesCbc& operator=(const AesCbc&) = delete;
    AesCbc& operator=(AesCbc&&) = delete;
};
