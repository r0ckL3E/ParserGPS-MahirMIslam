#include "parser.h"
#include <stdio.h>

int main() {
    FILE *fp = fopen("sample_data.txt", "r");
    if (!fp) {
        printf("Error: could not open sample_data.txt\n");
        return 1;
    }

    char line[128];
    GPSData data;

    while (fgets(line, sizeof(line), fp)) {
        if (parse_gga(line, &data)) {
            printf("Time: %s | Lat: %.6f | Lon: %.6f\n",
                   data.time, data.latitude, data.longitude);
        } else {
            printf("Invalid sentence: %s", line);
        }
    }

    fclose(fp);
    return 0;
}
