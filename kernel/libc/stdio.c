#include <libc/stdio.h>
#include <libc/string.h>

int64_t vsnprintf(char* buff, char* format, int64_t maxlen, va_list list){
	int64_t left;
	int64_t used;

	//set the number of character that can be written
	left = maxlen - 1;

	while(*format && left){
		if(*format == '%'){
			//print format section
			format++;

			switch(*format){
                //convert integer
                case 'd':
                case 'i':
                    used = itoa(buff, (int64_t)va_arg(list, int32_t), 10, left);
                    break;
                //convert unsigned integer
                case 'u':
                    used = utoa(buff, (uint64_t)va_arg(list, uint32_t), 10, left);
                    break;
                //convert unsigned integer to hex
                case 'x':
                    used = utoa(buff, (uint64_t)va_arg(list, uint32_t), 16, left);
                    break;
                //long mode
                case 'l':
                    format++;

                    switch(*format){
                        //convert integer
                        case 'd':
                        case 'i':
                            used = itoa(buff, (int64_t)va_arg(list, int64_t), 10, left);
                            break;
                        //convert unsigned integer
                        case 'u':
                            used = utoa(buff, (uint64_t)va_arg(list, uint64_t), 10, left);
                            break;
                        //convert unsigned integer to hex
                        case 'x':
                            used = utoa(buff, (uint64_t)va_arg(list, uint64_t), 16, left);
                            break;
                    }
                    break;
                //print % character
                case '%':
                    used = 1;
                    *buff = '%';
                    break;
                default:
                    used = -1;
                    break;
            }

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
				left = left - (used == -1? 0 : used);
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
	return maxlen-left-1;
}

int64_t snprintf(char* buff, char* format, uint64_t maxlen, ...){
	va_list list;
	va_start(list, maxlen);

	return vsnprintf(buff, format, maxlen, list);
}

int64_t vsprintf(char* buff, char* format, va_list list){
    return vsnprintf(buff, format, -1, list);
}

int64_t sprintf(char* buff, char* format, ...){
	va_list list;
	va_start(list, format);

	return vsnprintf(buff, format, -1, list);
}

