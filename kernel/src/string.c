#include <string.h>
#include <macros.h>

//this function is responsabile to convert a type to the corresponding string
static u32 print_format(char* buff, char* format, u32 left, va_list* list){
	u32 size;

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

i32 vsnprintf(char* buff, char* format, u64 size, va_list list){
	u64 left;
	u32 used;

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
i32 snprintf(char* buff, char* format, u64 size, ...){
	va_list list;
	va_start(list, size);

	return vsnprintf(buff, format, size, list);
}

//convert regular integer to array
u32 itoa(char* buff, i64 val, i8 base, u64 size){
	i8 sum;

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
u32 utoa(char* buff, u64 val, i8 base, u64 size){
	u64 n;
	u32 digit;
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
	if(digit+1 > size)
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
