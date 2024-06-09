#include <stdio.h>
//к сожалению спешил, так что ввод через хардкод переменной
unsigned char data[] = {01, 03 ,01 ,53};



int check_array (unsigned char byte[]){
    if (strlen(byte) == 0) {
        printf("empty input");
        return 0;
    }
    if (strlen(byte)/sizeof(char) < 4){
        printf ("too short input");
    }
    if (strlen(byte)/sizeof(char) > 5){
        printf ("too long input ");
    }
    if (strlen(byte)/sizeof(char) == 5){
        if (byte[2] != 0x05 && byte[2] != 0x06) {
            printf ("incorrect input for writing");
            return 0;
        }
    }
    if (byte[2] > 6 || byte[2] == 0) {
        printf ("incorrect operation code");
        return 0;
    }
    return 1;
}
unsigned char Crc8(unsigned char *data, unsigned int len, unsigned char check)
{
    unsigned char crc = check;
    unsigned int i;

    while (len--)
    {
        crc ^= *data++;

        for (i = 0; i < 8; i++)
            crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
    }

    return crc;
}

int main (){
    printf("%d",check_array(data));
    return 0;
}
