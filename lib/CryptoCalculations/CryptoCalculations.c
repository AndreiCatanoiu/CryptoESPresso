#include <stdio.h>    
#include <stdlib.h> 
#include <string.h>
#include <mbedtls/sha256.h>
#include "CryptoCalculations.h"

static char* sha256(const char* input) 
{
    unsigned char hash[32];
    char* hex_output = malloc(65);

    mbedtls_sha256_context ctx;
    mbedtls_sha256_init(&ctx);
    mbedtls_sha256_starts(&ctx, 0);
    mbedtls_sha256_update(&ctx, (const unsigned char*)input, strlen(input));
    mbedtls_sha256_finish(&ctx, hash);
    mbedtls_sha256_free(&ctx);

    for (int i = 0; i < 32; i++) {
        sprintf(hex_output + (i * 2), "%02x", hash[i]);
    }
    hex_output[64] = '\0';

    return hex_output;
}

const char* returnTheResult(const char* input_text, const char* algorithm) {
    if (strcmp(algorithm, "sha256") == 0 || strcmp(algorithm, "sha512") == 0 || strcmp(algorithm, "md5") == 0) 
    {
        if (strcmp(algorithm, "sha256") == 0)
        {
            return sha256(input_text);
        }
        else if (strcmp(algorithm, "sha512") == 0) 
        {
            return "NOT IMPLEMENTED YET";
        }
        else 
        {
            return "NOT IMPLEMENTED YET";
        }
    }
    else if (strcmp(algorithm, "hmac_sha256") == 0) 
    {
        return "NOT IMPLEMENTED YET";
    }
    else if (strcmp(algorithm, "aes128") == 0 || strcmp(algorithm, "aes256") == 0 || strcmp(algorithm, "des") == 0 || strcmp(algorithm, "3des") == 0 || strcmp(algorithm, "chacha20") == 0) 
    {
        return "NOT IMPLEMENTED YET";
    }
    else if (strcmp(algorithm, "rsa") == 0) {
        return "NOT IMPLEMENTED YET";
    }

    return NULL;
}