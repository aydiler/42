char *ft_strcpy(char *s1, char *s2)
{
	int i;
	i = 0;
	while (*s2)
	{
		s1[i] = *s2;
		i++;
		s2++;
	}
	s1[i] = 0;
	return s1;
}
