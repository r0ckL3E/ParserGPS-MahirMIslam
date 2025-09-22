#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int checksum_valid(const char *sentence) {
    if (sentence[0] != '$') return 0;

    unsigned char checksum = 0;
    int i = 1;
    while (sentence[i] != '*' && sentence[i] != '\0') {
        checksum ^= sentence[i]; 
        i++;
    }

    if (sentence[i] == '\0') return 0;

    unsigned int sent_checksum;
    sscanf(sentence + i + 1, "%2X", &sent_checksum);

    return (checksum == sent_checksum);
}


double convert_lat_long(const char *field, char hemi) {
    if (strlen(field) < 4) return 0.0;

    double raw = atof(field);
    int degrees = (int)(raw / 100);          
    double minutes = raw - (degrees * 100);  

    double decimal = degrees + (minutes / 60.0);
    if (hemi == 'S' || hemi == 'W') decimal = -decimal;

    return decimal;
}


int parse_gga(const char *sentence, GPSData *data) {
    if (!checksum_valid(sentence)) return 0;

    char buffer[128];
    strcpy(buffer, sentence);  

    char *token = strtok(buffer, ",");
    int fieldIndex = 0;

    char lat[16] = {0}, lon[16] = {0};
    char ns = 'N', ew = 'E';

    while (token != NULL) {
        switch (fieldIndex) {
            case 1: strncpy(data->time, token, sizeof(data->time)); break;
            case 2: strncpy(lat, token, sizeof(lat)); break;
            case 3: ns = token[0]; break;
            case 4: strncpy(lon, token, sizeof(lon)); break;
            case 5: ew = token[0]; break;
        }
        token = strtok(NULL, ",");
        fieldIndex++;
    }

    data->latitude = convert_lat_long(lat, ns);
    data->longitude = convert_lat_long(lon, ew);

    return 1;
}
