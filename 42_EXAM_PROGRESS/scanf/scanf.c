#include <stdarg.h>
#include <ctype.h>

int my_scanf(const char* format, ...) {
   va_list args;
   va_start(args, format);
   
   int items_read = 0;
   char c;
   
   while (*format) {
       if (*format == '%') {
           format++; // skip %
           
           // Skip whitespace except for %c
           if (*format != 'c') {
               while (isspace(c = getchar()));
               ungetc(c, stdin);
           }
           
           if (*format == 'd') { // Integer
               int* d = va_arg(args, int*);
               int val = 0;
               int sign = 1;
               
               c = getchar();
               if (c == '-') {
                   sign = -1;
                   c = getchar();
               }
               
               while (isdigit(c)) {
                   val = val * 10 + (c - '0');
                   c = getchar();
               }
               ungetc(c, stdin);
               *d = sign * val;
               items_read++;
               
           } else if (*format == 'c') { // Character 
               char* ch = va_arg(args, char*);
               *ch = getchar();
               items_read++;
               
           } else if (*format == 's') { // String
               char* s = va_arg(args, char*);
               int i = 0;
               
               while ((c = getchar()) != EOF && !isspace(c)) {
                   s[i++] = c;
               }
               s[i] = '\0';
               ungetc(c, stdin);
               items_read++;
           }
           
       } else {
           // Match literal character
           c = getchar();
           if (c != *format) break;
       }
       format++;
   }
   
   va_end(args);
   return items_read;
}
