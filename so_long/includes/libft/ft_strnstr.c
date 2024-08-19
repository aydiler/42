/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:27:38 by adiler            #+#    #+#             */
/*   Updated: 2023/11/27 12:03:47 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int			bigi;
	size_t		len2;
	const char	*littlestart;

	littlestart = little;
	if (*little == '\0')
		return ((char *)big);
	while (*big && len > 0)
	{
		bigi = 0;
		len2 = len;
		little = littlestart;
		while (*little && *(big + bigi) == *little && len2 > 0)
		{
			bigi++;
			len2--;
			little++;
		}
		if (*little == '\0') 
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
