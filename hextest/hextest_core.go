package hextest

import (
	"encoding/hex"
	"errors"
	"fmt"
	"strconv"
	"strings"
)

// все функции кроме  Process_Bytes видимы только на уровне пакета.
// пакет errors используется исключительно для красоты и возможной обработки ошибок.(тем более для го его наверное можно считать стандартным)
func check_bytes(bytes []byte) error {
	if bytes == nil {
		return errors.New("empty or incorrect input")
	}
	if len(bytes) < 4 {
		return errors.New("too short input")
	}
	if len(bytes) < 5 {
		return errors.New("too large input")
	}
	if len(bytes) == 5 {
		if bytes[2] != 0x05 && bytes[2] != 0x06 {
			return errors.New("incorrect lenght for not writing operation")
		}
	}
	if bytes[2] > 0x06 || bytes[2] == 0x00 {
		return errors.New("incorrect operation code")
	}
	return nil
}

// здесь используется функция для перевода строки в байты, не знаю, насколько это приемлемо, но эта часть кода, с учетом того, что она просто переводит
// системный аргумент в байты - не обязательна
// тут отлавливается, если значение не пригодно для декодирования (например, если одно из значений будет превышать один байт)
func transform_bytes(source string) []byte {
	var res []byte
	if source == "" {
		return nil
	}
	split := strings.Split(source, " ")
	for _, str := range split {
		buff, err := hex.DecodeString(str)
		if err != nil || len(buff) != 1 {
			return nil
		}
		res = append(res, buff[0])
	}
	return res
}

func Process_Bytes(Request string) string {
	bytes := transform_bytes(Request)
	if err := check_bytes(bytes); err != nil {
		return err.Error()
	}
	return form_final_str(bytes)
}
func form_final_str(bytes []byte) string {
	numbers := make([]int, len(bytes))
	for i := 0; i < len(bytes); i++ {
		hex_str := fmt.Sprintf("%X", bytes[i])
		num, _ := strconv.Atoi(hex_str)
		numbers[i] = num
	}
	if len(bytes) == 5 {
		return fmt.Sprintf("Адрес устройства: %d \n Код функции: %d \n Адрес ячейки памяти, куда идёт запись: %d \n Записываемое значение: %d CRC-8: %s", numbers[0], numbers[1], numbers[2], numbers[3], get_crc(bytes, 4, bytes[4]))
	}
	if len(bytes) == 4 {
		return fmt.Sprintf("Адрес устройства: %d  \n Код функции: %d \n Адрес ячейки памяти: %d  \n CRC-8: %s", numbers[0], numbers[1], numbers[2], get_crc(bytes, 3, bytes[3]))
	}
	return ""
}

// 0x31 - порождающий многочлен
// check - стартовый символ.
// len - длина массива -1, так как последний символ у нас check и он играет другую роль
// про табличную реализацию читал, но решил сделать таким образом.
func get_crc(bytes []byte, len int, check byte) string {
	var crc byte
	crc = check
	n := 0
	for n < len {
		crc ^= bytes[n]
		for i := 0; i < 8; i++ {
			if crc&0x80 == 1 {
				crc = crc<<1 ^ 0x31
			} else {
				crc = crc << 1
			}
		}
		n++
	}
	return string(crc)
}
