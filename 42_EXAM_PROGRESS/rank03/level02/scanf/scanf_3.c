#include <stdarg.h>
#include <ctype.h>
#include <stdio.h>

void skip_input_space()
{
    int c;
    
    // Skip whitespace characters
    while ((c = fgetc(stdin)) != EOF && isspace(c))
        continue;
    
    // Put back the non-whitespace character
    if (c != EOF)
        ungetc(c, stdin);
}

int scan_char(va_list ap)
{
    int c;
    char *ptr;
    
    ptr = va_arg(ap, char*);
    if ((c = fgetc(stdin)) == EOF)
        return 0;
    
    *ptr = (char)c;
    return 1;
}

int scan_int(va_list ap)
{
    int c;
    int *num;
    int result = 0;
    int sign = 1;
    
    num = va_arg(ap, int*);
    skip_input_space();
    
    // Handle sign
    c = fgetc(stdin);
    if (c == '-' || c == '+') {
        if (c == '-')
            sign = -1;
        c = fgetc(stdin);
    }
    
    // Read digits
    if (!isdigit(c)) {
        if (c != EOF)
            ungetc(c, stdin);
        return 0;
    }
    
    while (isdigit(c)) {
        result = result * 10 + (c - '0');
        c = fgetc(stdin);
    }
    
    if (c != EOF)
        ungetc(c, stdin);
    
    *num = result * sign;
    return 1;
}

int scan_string(va_list ap)
{
    int c;
    char *str;
    int chars_read = 0;
    
    str = va_arg(ap, char*);
    
    // Read characters until whitespace or EOF
    while ((c = fgetc(stdin)) != EOF && !isspace(c)) {
        str[chars_read++] = (char)c;
    }
    
    if (chars_read == 0)
        return 0;
    
    str[chars_read] = '\0';
    
    if (c != EOF)
        ungetc(c, stdin);
    
    return 1;
}

int receive_input(const char **format, va_list ap)
{
    switch (**format)
    {
        case 'c':
            return scan_char(ap);
        case 'd':
            return scan_int(ap);
        case 's':
            skip_input_space();
            return scan_string(ap);
        default:
            return 1;
    }
}

int ft_scanf(const char *format, ...)
{
    int i = 0;
    int result = 0;
    va_list ap;
    
    va_start(ap, format);
    
    while (format[i] != '\0')
    {
        if (format[i] == '%')
        {
            i++;
            if (receive_input(&(format[i]), ap) != 1)
                break;
            else
                result++;
        }
        i++;
    }
    
    va_end(ap);
    return (result);
}