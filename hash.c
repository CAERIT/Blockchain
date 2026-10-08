#include "hash.h"

unsigned char* SSHA(const unsigned char* msg, size_t length) {
    unsigned char A, B, C, D, E,a,b,c,d,e; //Initial Seed Value
    A = 56;
    B = 99;
    C = 102;
    D = 67;
    E = 76;
    a, b, c, d, e = 0;

    for (int i = 0; i < length; i++) {
        for (int round = 0; round < 8; round++) {
            a = E;
            b = A;
            c = E + (A >> 2);
            d = (A >> 2) ^ (B >> 1);
            e = msg[i] + (B >> 2) + ((B & C) | (C & D));

            A = a & 0xff;
            B = b & 0xff;
            C = c & 0xff;
            D = d & 0xff;
            E = e & 0xff;

            /*
            unsigned char g = (B & C) | (C & D); 
            unsigned char old_A = A;
            A = (A + (msg[i] ^ B)) & 0xFF;
            B = (B ^ g) & 0xFF;
            E = ((g + msg[i]) ^ B) & 0xFF;
            D = (A ^ B) & 0xFF;
            C = (A + E) & 0xFF;
            A = E;
            B = old_A;
            */
        }
    }

    unsigned char* digest = (unsigned char*)malloc(DIGEST_SIZE * sizeof(unsigned char));
    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;
    return digest;
}

unsigned char* SSHA2(const unsigned char* msg, size_t length) {
    // Initial Seed Values
    unsigned char A = 56;
    unsigned char B = 99;
    unsigned char C = 102;
    unsigned char D = 67;
    unsigned char E = 76;
    unsigned char a = 0, b = 0, c = 0, d = 0, e = 0;

    for (size_t i = 0; i < length; i++) {
        for (int round = 0; round < 8; round++) {
            // Flowchart operations
            a = E;
            b = A;
            c = ((A >> 2) ^ (B >> 1)) + E;
            d = (B & C) | (C & D);
            e = (B >> 1) + d + msg[i];

            // Update registers
            A = a;
            B = b;
            C = c;
            D = d;
            E = e;
        }
    }

    // Allocate memory for the 5-byte hash result
    unsigned char* hash = (unsigned char*)malloc(5 * sizeof(unsigned char));
    if (hash != NULL) {
        hash[0] = A;
        hash[1] = B;
        hash[2] = C;
        hash[3] = D;
        hash[4] = E;
    }

    return hash;
}

int digest_equal(struct Digest digest1, struct Digest digest2) {
    return ((digest1.hash0 == digest2.hash0) &&
        (digest1.hash1 == digest2.hash1) &&
        (digest1.hash2 == digest2.hash2) &&
        (digest1.hash3 == digest2.hash3) &&
        (digest1.hash4 == digest2.hash4));
}

void printDigest(struct Digest digest) {
    printf("%d %d %d %d %d\n", digest.hash0, digest.hash1, digest.hash2, digest.hash3, digest.hash4);
}