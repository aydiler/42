#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

int ft_scanf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int count = 0;
    int c;

    while (*format)
	{
        if (*format == '%')
		{
            format++;
            if (*format == 'd')
			{
                int *d = va_arg(args, int *);
                int num = 0, sign = 1;

                while ((c = fgetc(stdin)) != EOF && isspace(c))
                    ;

                if (c == '-' || c == '+')
				{
					if (c == '-')
                    	sign = -1;
                    c = fgetc(stdin);
                }

                if (!isdigit(c))
				{
                    ungetc(c, stdin);
                    break;
                }

                while (isdigit(c))
				{
                    num = num * 10 + (c - '0');
                    c = fgetc(stdin);
                }
				if (c != EOF)
                	ungetc(c, stdin);
                *d = num * sign;
                count++;
            }
            else if (*format == 's')
			{
                char *str = va_arg(args, char *);
                
                while ((c = fgetc(stdin)) != EOF && isspace(c))
                    ;

                while (c != EOF && !isspace(c))
				{
                    *str++ = c;
                    c = fgetc(stdin);
                }
                *str = '\0';
                if (c != EOF)
                    ungetc(c, stdin);
                count++;
            }
            else if (*format == 'c')
			{
                char *ch = va_arg(args, char *);

               /*  while ((c = fgetc(stdin)) != EOF && isspace(c))
                    ; */
				c = fgetc(stdin);
                if (c != EOF)
				{
                    *ch = c;
                    count++;
                }
                else
					break ;
            }
            else
                break;
            format++;
        }
        else
		{
            // Vérifier le caractère fixe
            c = fgetc(stdin);
            if (c != *format)
			{
                ungetc(c, stdin);
                break;
            }
            format++;
        }
    }
    va_end(args);
    return count;
}

int main (int ac, char **av)
{
    char name[50];
    int age;
    char c; // Utiliser 'char' au lieu de 'int' pour stocker un caractère

    printf("Please enter your name:\n");
    ft_scanf("%s", name); // Lecture du nom

    printf("Ok, nice to meet you. Now your age:\n");
    ft_scanf("%d", &age); // Lecture de l'âge


    printf("Please enter your initial:\n");
    ft_scanf("%c", &c); // Lecture de l'initiale

    printf("Your name is: %s\n", name);
    printf("Your age is: %d\n", age);
    printf("Your initial is: %c\n", c);

    return 0;
}
