/*
 * Copyright (c) 2006-2014, Bryan Drewery <bryan@shatow.net>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTIRBUTORS ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Base64.h
 */

#ifndef _BD_BASE64_H
#define _BD_BASE64_H 1

#include "bdlib.h"
#include "String.h"

BDLIB_NS_BEGIN
class Base64 {
};

const char b64_charset[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char b64_indexes[256] = {
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
  52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
  -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
  15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
  -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
  41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};



/**
  * @brief Encode a plaintext string into base64 (returns a buffer)
  * @param src A c-style string to encode
  * @param len Reference to length of string (to be updated on return)
  * @param charset The charset to use.
  * @return An encoded NULL-terminated c-style string (must be free()d later)
  */
char *b64enc(const unsigned char *src, size_t *len, const char* charset = nullptr);

/**
 * @brief Base64 encode a string
 * @param string The string to encode
 * @param charset Optional charset to use. None will use standard base64
 * @return A new, encoded string
 */
String base64Encode(const String& string, const char* charset = nullptr);

/**
  * @brief Encode a plaintext string into base64 (using a given buffer)
  * @param data The c-style string to encode
  * @param len Reference to length of string (to be updated on return)
  * @param dest Reference to the buffer to encode into
  * @param charset The charset to use.
  */
void b64enc_buf(const unsigned char *data, size_t *len, char *dest, const char* charset = nullptr);

/**
  * @brief Decode a base64 encoded string into plaintext (returns a buffer)
  * @param data A c-style string to decode
  * @param len Reference to length of string (to be updated on return)
  * @param charset The charset to use.
  * @return A decoded NULL-terminated c-style string (must be free()d later)
  */
char *b64dec(const unsigned char *data, size_t *len, const char* charset = nullptr);

/**
 * @brief Base64 decode a string
 * @param string The string to decode
 * @param charset Optional charset to use. None will use standard base64
 * @return A new, decoded string
 */
String base64Decode(const String& string, const char* charset = nullptr);

/**
  * @brief Decode a base64 encoded string into plaintext (using a given buffer)
  * @param data The c-style string to decode
  * @param len Reference to length of string (to be updated on return)
  * @param dest Reference to the buffer to decode into
  * @param charset_index The character set to use
  */
void b64dec_buf(const unsigned char *data, size_t *len, char *dest, const char* charset_index = nullptr);

BDLIB_NS_END
#endif /* _BD_BASE64_H */ 
/* vim: set sts=2 sw=2 ts=8 et: */
