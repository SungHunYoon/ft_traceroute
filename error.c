/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:38:19 by sungyoon          #+#    #+#             */
/*   Updated: 2024/09/18 19:38:20 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

void	error_handling(char *str)
{
	dprintf(2, "ft_traceroute: %s\n", str);
	exit(FT_FAIL);
}

void	invalid_option(char *str, int idx, int flag)
{
	dprintf(2, "Bad option ");
	if (!flag)
		dprintf(2, "`-%s' ", str);
	else
		dprintf(2, "`-%c' ", *str);
	dprintf(2, "(argc %d)\n", idx);
	exit(FT_ERROR);
}

void	usage_error(char *str, int idx, t_parse type)
{
	if (type == PARSE_HOST)
	{
		dprintf(2, "%s: Name or service not known\n", str);
		dprintf(2, "Cannot handle \"host\" cmdline arg ");
		dprintf(2, "`%s' on Position 1 (argc %d)\n", str, idx);
	}
	else if (type == PARSE_EXTRA)
		dprintf(2, "Extra arg `%s' (position 2, argc %d)\n", str, idx);
	exit(FT_ERROR);
}

void	help_message(void)
{
	printf("Usage:\n  ft_traceroute host\n");
	printf("Options:\n");
	printf("  --help                      ");
	printf("Read this help and exit\n\n");
	printf("Arguments:\n");
	printf("+     host          The host to traceroute to\n");
	exit(FT_SUCCESS);
}
