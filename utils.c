/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:38:11 by sungyoon          #+#    #+#             */
/*   Updated: 2024/09/18 19:39:10 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

double	diff_timeval(struct timeval time)
{
	double			ret;
	struct timeval	now;

	if (gettimeofday(&now, NULL) < 0)
		error_handling("gettimeofday", errno);
	now.tv_sec -= time.tv_sec;
	now.tv_usec -= time.tv_usec;
	if (now.tv_usec < 0)
	{
		now.tv_usec += 1000000;
		now.tv_sec--;
	}
	ret = (now.tv_sec * 1000) + (now.tv_usec / 1000.0);
	return (ret);
}

int	domain_to_fqdn(char *domain, char *fqdn)
{
	int				ret;
	struct addrinfo	*res;
	struct addrinfo	*tmp;
	struct addrinfo	hints;

	ret = FT_FAIL;
	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_flags = AI_CANONNAME;
	if (getaddrinfo(domain, NULL, &hints, &res) != FT_SUCCESS)
		return (ret);
	tmp = res;
	while (tmp != NULL)
	{
		if (tmp->ai_canonname != NULL)
		{
			ft_strncpy(fqdn, tmp->ai_canonname, ft_strlen(tmp->ai_canonname));
			ret = FT_SUCCESS;
			break ;
		}
		tmp = tmp->ai_next;
	}
	freeaddrinfo(res);
	return (ret);
}

int	domain_to_ip(char *domain, char *ip)
{
	int				ret;
	struct addrinfo	*res;
	struct addrinfo	*tmp;
	struct addrinfo	hints;
	char			*str;

	ret = FT_FAIL;
	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	if (getaddrinfo(domain, NULL, &hints, &res) != FT_SUCCESS)
		return (ret);
	tmp = res;
	while (tmp != NULL)
	{
		if (tmp->ai_addr != NULL)
		{
			str = inet_ntoa(((struct sockaddr_in *)tmp->ai_addr)->sin_addr);
			ft_strncpy(ip, str, ft_strlen(str));
			ret = FT_SUCCESS;
			break ;
		}
		tmp = tmp->ai_next;
	}
	freeaddrinfo(res);
	return (ret);
}

char	*ip_to_domain(struct in_addr addr)
{
	struct hostent	*host;

	host = gethostbyaddr(&addr, sizeof(addr), AF_INET);
	if (!host)
		return (NULL);
	return (host->h_name);
}
