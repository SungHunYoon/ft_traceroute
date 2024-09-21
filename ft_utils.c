/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:38:17 by sungyoon          #+#    #+#             */
/*   Updated: 2024/09/18 19:38:18 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;

	if (n == 0)
		return (0);
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (n--)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		else if (*p1 == '\0' || *p2 == '\0')
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	return (*(p1 - 1) - *(p2 - 1));
}

void	ft_bzero(void *s, size_t n)
{
	char	*p;
	size_t	idx;

	p = (char *)s;
	idx = 0;
	while (idx < n)
		p[idx++] = 0;
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	char	*p;

	p = dest;
	while (n > 0)
	{
		if (*src != '\0')
		{
			*dest = *src;
			src++;
		}
		else
			*dest = '\0';
		dest++;
		n--;
	}
	return (p);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*p1;
	char	*p2;
	size_t	idx;

	if (dst == NULL && src == NULL)
		return (NULL);
	p1 = (char *)dst;
	p2 = (char *)src;
	idx = 0;
	while (idx < n)
	{
		p1[idx] = p2[idx];
		idx++;
	}
	return (dst);
}
