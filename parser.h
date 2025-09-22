#ifndef PARSER_H
#define PARSER_H


typedef struct {
    double latitude;    
    double longitude;   
    char time[16];      
} GPSData;


int checksum_valid(const char *sentence);                 
double convert_lat_long(const char *field, char hemi);    
int parse_gga(const char *sentence, GPSData *data);       

#endif
