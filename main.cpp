#include <hidapi.h>
#include <cstdio>

int main(int argc, char **argv) {
#define MAX_STR 255
    wchar_t wstr[MAX_STR];
    
    hid_device *handle = hid_open(0x16c0, 0x0480, nullptr);
    if (!handle) {
        fprintf(stderr, "No temperature sensor found!\n");
        return 1;
    }
    
    printf("Device Info:\n");
    int res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
    printf("\tManufacturer String: %ls\n", wstr);
    
    res = hid_get_product_string(handle, wstr, MAX_STR);
    printf("\tProduct String: %ls\n", wstr);
    
    unsigned char buf[65];
    for (;;) {
        int num = hid_read(handle, buf, 64);
        if (num < 0) {
            fprintf(stderr, "Could not read from device!\n");
            return 2;
        }
        if (num == 64) {
            short temp = *(short *)&buf[4]; //holy fuck!
            printf("temp: %+.1f°C\n", (float)temp/10.0f);
        }
    }
    return 0;
}

