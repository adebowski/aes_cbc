#include <gmock/gmock.h>
#include "../Parser.h"
#include "../AESUtils.h"


using namespace ::testing;

TEST(ParserTest, emptyDataNoThrow){    
  EXPECT_NO_THROW(Parser::DecryptData(nullptr, 0));
  ASSERT_EQ(Parser::DecryptData(nullptr, 0),"");
}

TEST(ParserTest, decryptMessageExpectOK) {
    std::vector<uint8_t> toDecode = {0xc0, 0xde, 0x1a, 0x55, 0xd8, 0xf2, 0x07, 0x3f, 0x99, 0x63, 0x5a, 0xfe, 0xd7, 0xc8, 0x8b, 0xba, 0xa2, 0x7a, 0x04, 0x12, 0xb3, 0x26, 0xa6, 0x63, 0x0a, 0x12, 0x2d, 0x6d, 0x06, 0xb3, 0x64, 0xed};
    auto decodedText = Parser::DecryptData(toDecode.data(), toDecode.size());

    ASSERT_EQ(decodedText, "example text");
}

TEST(ParserTest, md5_emptyDataNoThrow){    
  EXPECT_NO_THROW(AesCbc::md5_hash_data(nullptr, 0));

  std::vector<uint8_t> expected = {};
  ASSERT_EQ(AesCbc::md5_hash_data(nullptr, 0),expected);
}

TEST(ParserTest, md5_HashString){
    std::string toHash("text to hash");
    std::vector<uint8_t> expected = {0x27, 0x70, 0x39, 0x45, 0xb9, 0xbc, 0xea, 0xcb, 0x09, 0x54, 0x6d, 0x2e, 0x10, 0x3a, 0xd3, 0x60};
    ASSERT_EQ(AesCbc::md5_hash_data((uint8_t* )&toHash[0], toHash.size()), expected);
}

TEST(ParserTest, md5_HashEmptyString){
    std::string toHash("");
    std::vector<uint8_t> expected = {};

    ASSERT_EQ(AesCbc::md5_hash_data((uint8_t* )&toHash[0], toHash.size()), expected);
}

TEST(ParserTest, md5_HashSpaceCharString){
    std::string toHash(" ");
    std::vector<uint8_t> expected = {0x72, 0x15, 0xee, 0x9c, 0x7d, 0x9d, 0xc2, 0x29, 0xd2, 0x92, 0x1a, 0x40, 0xe8, 0x99, 0xec, 0x5f};
    
    ASSERT_EQ(AesCbc::md5_hash_data((uint8_t* )&toHash[0], toHash.size()), expected);
}