#include <libc/string.h>
#include <libc/math.h>

int64_t strcpy(char* dest, char* source, int64_t maxlen){
	char* begin;

	begin = source;

    if(maxlen < 0){
        return -1;
	}

	while(maxlen && *source){
		*dest = *source;
		dest++;
		source++;
		maxlen--;
	}

	if(maxlen == 0 && *source != '\0'){
		*(dest-1) = '\0';
		return -1;
	}

	return (int64_t)(source-begin-1);
}

int64_t strlen(char* s){
	int64_t len;

	len = 0;

	while(*s){
		s++;
		len++;
	}

	return len;
}

//convert regular integer to array
int8_t itoa(char* buff, int64_t val, int8_t base, int64_t maxlen){
	uint8_t sum;

	sum = 0;

    if(maxlen < 1){
        return 0;
    }

	if(val < 0){
		buff++;
		maxlen--;
	}

	sum += utoa(buff, (uint64_t)ABS(val), base, maxlen);

	if(val < 0 && sum){
		*(buff-1) = '-';
		sum++;
	}

	return sum;
}

//convert unsigned integer to arrat
int8_t utoa(char* buff, uint64_t val, int8_t base, int64_t maxlen){
	uint64_t n;
	int8_t digit;
	char* start;
	uint8_t i;

	n = val;
	digit = 0;

	//count the number of digit required
	do{
		n /= base;
		digit++;
	}while(n != 0);

	//if the number of digit is too much just return
	if((int64_t)digit+1 > maxlen)
		return 0;

	start = buff;
	buff += digit;
	n = val;
	*(buff) = '\0';

	//convert the actual number to array
	do{
		buff--;
		i = (int8_t)(n%base);

		if(i >= 10)
			*buff = i - 10 + 'A';
		else
			*buff = i + '0';

		n /= base;
	}while(start != buff);

	//the number of digit does not include zero terminator
	return digit;
}


void memset(volatile void* buff, int32_t val, uint64_t b){
	while(b){
		*((int8_t*)buff) = (int8_t)val;
		b--;
	}
}

