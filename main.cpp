#include <hidapi.h>
#include <cstdio>
#include <ctime>

int main(int argc, char **argv) {
    
    hid_device *handle = hid_open(0x16c0, 0x0480, nullptr);
    if (!handle) {
        fprintf(stderr, "No temperature sensor found!\n");
        return 1;
    }
    
    const int MAX_STR = 255;
    wchar_t wstr[MAX_STR];
    
    printf("Device Info:\n");
    int res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
    if (res == -1) {
        fprintf(stderr, "Could not get manufacturer string!\n");
        return 2;
    }
    printf("\tManufacturer String: %ls\n", wstr);
    
    res = hid_get_product_string(handle, wstr, MAX_STR);
    if (res == -1) {
        fprintf(stderr, "Could not get product string!\n");
        return 3;
    }
    printf("\tProduct String: %ls\n", wstr);
    
    unsigned char buf[65];
    for (;;) {
        int num = hid_read(handle, buf, 64);
        if (num < 0) {
            fprintf(stderr, "Could not read from device!\n");
            return 4;
        }
        if (num == 64) {
            time_t now;
            time(&now);
            tm loctm;
            localtime_r(&now, &loctm);
            
            short temperature;
            // The temperature is stored as type short in the bytebuffer in two seperate fields.
            // We have to merge the bytes at position 3 (also shift it) and 4 together.
            temperature  = (short)buf[3] << sizeof(unsigned char);
            temperature += (short)buf[4];
            printf("<%02d:%02d:%02d> sensor: %d of %d, temp: %+.1f°\n", loctm.tm_hour, loctm.tm_min, loctm.tm_sec, buf[1], buf[0], (float)temperature/10.0f);
        }
    }
    return 0;
}

