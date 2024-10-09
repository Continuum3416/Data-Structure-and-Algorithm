#pragma once
#include <cctype>  // provides isupper() function
#include <string>

namespace dsac::array {

/// Class for doing encryption and decryption using the Caesar Cipher.
class CaesarCipher {
  private:
    // pre-size strings to 26 characters (to be specified by the constructor)
    std::string encoder = std::string(26, '?');           // Encryption string
    std::string decoder = std::string(26, '?');           // Decryption string

  public:
    /// Constructor that initializes the encryption and decryption strings
    /// @param rotation  the amount of forward shift (default: 1)
    CaesarCipher(int rotation = 1) {
        for (int k = 0; k < 26; k++) {
            encoder[k] = 'A' + (k + rotation) % 26;
            decoder[k] = 'A' + (k - rotation + 26) % 26;
        }
    }

    /// Returns an encrypted version of an original message.
    /// @param message   the original message
    /// @return  the encrypted message
    std::string encrypt(const std::string& message) {
        return transform(message, encoder);      // use encoder string
    }

    /// Returns a decrypted message, given the encrypted secret.
    /// @param secret   the encrypted message
    /// @return  the original (unencrypted) message
    std::string decrypt(const std::string& secret) {
        return transform(secret, decoder);       // use decoder string
    }

  private:
    /// Returns transformation of original string using given code
    /// @param original    the original message
    /// @param code        the 26-character string designating the replacement code
    /// @return the encoded message
    std::string transform(const std::string& original, const std::string& code) {
        std::string result{original};
        for (int k = 0; k < original.size(); k++)
            if (isupper(original[k])) {          // we have a letter to change
                int j{original[k] - 'A'};        // will be value from 0 to 25
                result[k] = code[j];             // replace the character
            }
        return result;
    }
};

}  // namespace dsac::array
