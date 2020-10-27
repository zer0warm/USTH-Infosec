#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int value;
    unsigned int length;
} LFSR;

void step(LFSR *reg);
int getBit(LFSR *reg, int bitPos);
int getMajorBit();
void decideRegistersToStep();
int genStreamBit();
void genA51KeyStreamToStdout(int n);
LFSR *makeRegister(unsigned int value, unsigned int length);
void deleteRegister(LFSR *reg);

LFSR *X, *Y, *Z;

int main(void)
{
    X = makeRegister(0b1111101010101010101, 19);
    Y = makeRegister(0b1100110011001100110011, 22);
    Z = makeRegister(0b11100001111000011110000, 23);

    printf("N = ");
    int keyStreamLength;
    scanf("%d", &keyStreamLength);
    genA51KeyStreamToStdout(keyStreamLength);
    printf("\n");

    deleteRegister(X);
    deleteRegister(Y);
    deleteRegister(Z);
}

LFSR *makeRegister(unsigned int value, unsigned int length)
{
    LFSR *newRegister = malloc(sizeof *newRegister);
    newRegister->value = value;
    newRegister->length = length;
    return newRegister;
}

void deleteRegister(LFSR *reg)
{
    free(reg);
    reg = NULL;
}

void genA51KeyStreamToStdout(int n)
{
    printf("Key stream: ");
    for (int i = 0; i < n; i++) {
        printf("%d", genStreamBit());
        decideRegistersToStep();
    }
}

int genStreamBit()
{
    return getBit(X, 18) ^ getBit(Y, 21) ^ getBit(Z, 22);
}

void decideRegistersToStep()
{
    int major = getMajorBit();
    if (getBit(X, 8) == major) {
        step(X);
    }
    if (getBit(Y, 10) == major) {
        step(Y);
    }
    if (getBit(Z, 10) == major) {
        step(Z);
    }
}

int getMajorBit()
{
    int sum = getBit(X, 8) + getBit(Y, 10) + getBit(Z, 10);
    return (sum <= 1 ? 0 : 1);
}

int getBit(LFSR *reg, int bitPos)
{
    return (reg->value >> (reg->length - 1 - bitPos)) & 1;
}

void step(LFSR *reg)
{
    int msb;
    switch (reg->length) {
        case 19:
            msb = getBit(reg, 13) ^ getBit(reg, 16) ^ getBit(reg, 17) ^ getBit(reg, 18);
            break;
        case 22:
            msb = getBit(reg, 20) ^ getBit(reg, 21);
            break;
        case 23:
            msb = getBit(reg, 20) ^ getBit(reg, 21) ^ getBit(reg, 22);
            break;
    }
    reg->value = (reg->value >> 1) | (msb << (reg->length - 1));
}
