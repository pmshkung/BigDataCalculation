#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define DATA_SIZE   64

void bigDataMultiToString(char *buffer, int length, unsigned int data, unsigned int scale) {
    int count = 0, scaleCount = 0, tmp1, tmp2;    
    unsigned int tmpData = data;
    unsigned int scaleData = scale;    
    int i, j;
    char *scaleArray;
    char **buf;
    char result[64];
    
    do {
        scaleCount++;
        scaleData = scaleData / 10;
    } while (scaleData != 0);
        
    scaleArray = (char *)malloc(sizeof(char) * scaleCount);
    scaleData = scale;
    for (i = 0; i < scaleCount; i++) {
        scaleArray[i] = scaleData % 10;
        scaleData = scaleData / 10;
    }       
        
    buf = (char **)malloc(sizeof(char *) * scaleCount);
    for (i = 0; i < scaleCount; i++) {
        buf[i] = (char *)malloc(sizeof(char) * DATA_SIZE);
        memset(&buf[i][0], '0', DATA_SIZE);
    }       
                    
    memset(result, '0', sizeof(result));
    do {
        buf[0][DATA_SIZE - 1 - count] = (tmpData % 10) + '0';
        count++;        
        tmpData = tmpData / 10;
    } while (tmpData != 0);            
    
    for (i = 0; i < (scaleCount - 1); i++) {
        memcpy(&buf[i + 1][DATA_SIZE - count - i - 1], &buf[0][DATA_SIZE - count], count);
    }                             
    
    for (i = 0; i < scaleCount; i++) {
        tmp2 = 0;
        for (j = (DATA_SIZE - 1); j >= 0; j--) {
            tmp1 = buf[i][j] - '0';
            buf[i][j] = (tmp1 * scaleArray[i] + tmp2) % 10 + '0';
            tmp2 = (tmp1 * scaleArray[i] + tmp2) / 10;            
        }
    }         
    
    tmp1 = tmp2 = 0;
    for (i = (DATA_SIZE - 1); i >= 0; i--) {
        tmp1 = 0;
        for (j = 0; j < scaleCount; j++) {
            tmp1 += (buf[j][i] - '0');                        
        }
        tmp1 += tmp2;
        tmp2 = tmp1 / 10;
        result[i] = (tmp1 % 10) + '0';
    }
    
    for (i = 0; i < DATA_SIZE; i++) {
        if (result[i] != '0') {            
            break;
        }
    }       
    
    count = DATA_SIZE - i;
    memset(buffer, 0, length);
    memcpy(buffer, &result[i], DATA_SIZE - i);         
    
    free(scaleArray);
    
    for (i = 0; i < scaleCount; i++) {
        free(buf[i]);
    }
    free(buf);
}

int main(int argc, char *argv[]) {
	char buffer[DATA_SIZE];

    bigDataMultiToString(buffer, DATA_SIZE, 1, 1024);
    printf("%d * %d = %s\n", 1, 1024, buffer);

    bigDataMultiToString(buffer, DATA_SIZE, 1000000000, 1024);
    printf("%d * %d = %s\n", 1000000000, 1024, buffer);

    bigDataMultiToString(buffer, DATA_SIZE, 0xFFFFFFFF, 1024);
    printf("%u * %d = %s\n", 0xFFFFFFFF, 1024, buffer);

	return 0;
}
