#ifndef ZXING_H
#define ZXING_H
extern "C" {
    int decodeQR(const char* imgPath, int* type, char* output, int maxLen);
}

#endif // ZXING_H
