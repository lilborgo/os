#include <string.h>
#include <macros.h>

//this function is responsabile to convert a type to the corresponding string
static u64 print_format(char* buff, char* format, u32 left, va_list* list){
	u64 size;

	switch(*format){
		//convert integer
		case 'd':
		case 'i':
			size = itoa(buff, (i64)va_arg(*list, i32), 10, left);
			break;
		//convert unsigned integer
		case 'u':
			size = utoa(buff, (u64)va_arg(*list, u32), 10, left);
			break;
		//convert unsigned integer to hex
		case 'x':
			size = utoa(buff, (u64)va_arg(*list, u32), 16, left);
			break;
		//long mode
		case 'l':
			format++;

			switch(*format){
				//convert integer
				case 'd':
				case 'i':
					size = itoa(buff, (i64)va_arg(*list, i64), 10, left);
					break;
				//convert unsigned integer
				case 'u':
					size = utoa(buff, (u64)va_arg(*list, u64), 10, left);
					break;
				//convert unsigned integer to hex
				case 'x':
					size = utoa(buff, (u64)va_arg(*list, u64), 16, left);
					break;
			}
			break;
		//print % character
		case '%':
			size = 1;
			*buff = '%';
			break;
		default:
			size = 0;
			break;
	}

	return size;
}

u64 vsnprintf(char* buff, char* format, u64 size, va_list list){
	u64 left;
	u64 used;

	//set the number of character that can be written
	left = size - 1;

	while(*format && left){
		if(*format == '%'){
			//print format section
			format++;

			used = print_format(buff, format, left, &list);

			//the writing of long require 2 character to format
			if(*format == 'l')
				format++;

			//if the used character are 0 it means the number was
			//not written because of the space.
			//so, if there is enougth space(left), print %- as a reminder
			if(!used && left >= 2){
				*buff = '%';
				buff++;
				*buff = '-';
				buff++;
				left = left - 2;
			}
			else{
				left = left - used;
				buff += used;
			}
		}
		else{
			//copy the normal string
			*buff = *format;
			buff++;
			left--;
		}
		format++;
	}

	*buff = '\0';

	//return the number of characters written, zero character ignored
	return size-left-1;
}

//print to a string
u64 snprintf(char* buff, char* format, u64 size, ...){
	va_list list;
	va_start(list, size);

	return vsnprintf(buff, format, size, list);
}

//copy string to another
void strcpy(char* dest, char* source, u64 size){
	while(size && *source){
		*dest = *source;
		dest++;
		source++;
		size--;
	}

	*dest = '\0';
}

//get the length of the string
u64 strlen(char* s){
	u64 size;

	size = 0;

	while(*s){
		s++;
		size++;
	}

	return size;
}

//convert regular integer to array
u8 itoa(char* buff, i64 val, i8 base, u64 size){
	u8 sum;

	sum = 0;

	if(val < 0){
		buff++;
		size--;
	}

	sum += utoa(buff, (u64)ABS(val), base, size);

	if(val < 0 && sum){
		*(buff-1) = '-';
		sum++;
	}

	return sum;
}

//convert unsigned integer to arrat
u8 utoa(char* buff, u64 val, i8 base, u64 size){
	u64 n;
	u8 digit;
	char* start;
	u8 i;

	n = val;
	digit = 0;

	//count the number of digit required
	do{
		n /= base;
		digit++;
	}while(n != 0);

	//if the number of digit is too much just return
	if((u64)digit+1 > size)
		return 0;

	start = buff;
	buff += digit;
	n = val;
	*(buff) = '\0';

	//convert the actual number to array
	do{
		buff--;
		i = (i8)(n%base);

		if(i >= 10)
			*buff = i - 10 + 'A';
		else
			*buff = i + '0';

		n /= base;
	}while(start != buff);

	//the number of digit does not include zero terminator
	return digit;
}
