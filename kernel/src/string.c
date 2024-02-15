
#include <types.h>
#include <macros.h>
#include <string.h>

int sprintf(char* str, char* format, ...){
	va_list list;

	va_start(list, format);

	while(*format){
		if(*format == '%'){
			format++;


			switch(*format){
				case 'd':
					str += itoa(str, (i64)va_arg(list, i32));
					break;
			}
		}
		else
			*str = *format;

		format++;
		str++;
	}

	*str = '\0';

	return 0;
}


i32 itoa(char* str, i64 val){
	i64 n;
	i32 digit;
	char* start;

	n = val;
	digit = 0;

	while(n != 0){
		n /= 10;
		digit++;
	}

	if(val <= 0)
		digit++;

	start = str;
	str += digit;
	n = val;
	*(str+1) = '\0';

	while(start != str){
		*str = (n%10) + '0';
		n /= 10;
		str--;
	}

	if(val < 0)
		*start = '-';

	return digit;
}