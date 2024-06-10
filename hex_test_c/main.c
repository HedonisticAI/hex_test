#include <stdio.h>
//к сожалению спешил, так что ввод через хардкод переменной
#define SIZE 4
unsigned char data[SIZE] = {01, 03 ,01 ,53};



int check_array (unsigned char byte[SIZE]){
    if (sizeof(byte) == 0) {
        printf("empty input");
        return 0;
    }
    if (sizeof(byte)/sizeof(char) < 4){
        printf ("too short input");
    }
    if (sizeof(byte)/sizeof(char) > 5){
        printf ("too long input ");
    }
    if (sizeof(byte)/sizeof(char) == 5){
        if (byte[2] != 0x05 && byte[2] != 0x06) {
            printf ("incorrect input for writing");
            return 0;
        }
    }
    if (byte[2] > 0x06 || byte[2] == 0x00) {
        printf ("incorrect operation code");
        return 0;
    }
    return 1;
}
unsigned char get_crc(unsigned char *data, unsigned int len, unsigned char check)
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

int Process_Array(unsigned char byte[SIZE]){
    if (check_array(&byte) ==0 ){
        return 0;
    }
    if (sizeof(*byte) == 4){
        printf("Адрес устройства: %ud  \n Код функции: %ud \n Адрес ячейки памяти: %ud  \n CRC-8: %ud", byte[0], byte[1], byte[2], get_crc(byte, SIZE, byte[SIZE-1]));
    }
<<<<<<< HEAD
    if (sizeof(byte) == 5){
=======
    if (sizeof(*byte) == 5){
>>>>>>> cb70a7fd0def806ec7000bead278c83282897a22
        printf("Адрес устройства: %ud  \n Код функции: %ud \n Адрес ячейки памяти: %ud %d \n Записываемое значение: %ud \n CRC-8: %ud", byte[0], byte[1], byte[2], byte[3], get_crc(byte, SIZE, byte[SIZE-1]) );
    }
    return 1;
}

int main (){
    return 0;
}
