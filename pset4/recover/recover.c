#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    if (argc != 2){
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL) {
        fprintf(stderr, "can not open %s\n", argv[1]);
        return 2;
    }
    
    unsigned char buffer[512];
    
    int image_count = 0;
    FILE *image = NULL;
    
    while(fread(buffer, 512, 1, infile) == 1){
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {
            if(image != NULL) {
                fclose(image);
            }
            char name[8];
            sprintf(name, "%03d.jpg", image_count);
            image_count++;
            image = fopen(name, "w");
        }
        
        if (image != NULL) {
            fwrite(buffer, 512, 1, image);
        }
    }
    fclose(image);
    fclose(infile);
    return 0;
}