#include "traceroute.h"

int	error_handling(char *str, int ret)
{
	dprintf(2, "%s", str);
	return (ret);
}

int	invalid_option(char *str, int idx, int flag)
{
	dprintf(2, "Bad option ");
	if (!flag)
		dprintf(2, "`-%s' ", str);
	else
		dprintf(2, "`-%c' ", *str);
	dprintf(2, "(argc %d)\n", idx);
	return (PARSE_INVALID);
}

int	usage_error(char *str, int idx, t_parse type)
{
	if (type == PARSE_HOST)
	{
		dprintf(2, "%s: Name or service not known\n", str);
		dprintf(2, "Cannot handle \"host\" cmdline arg ");
		dprintf(2, "`%s' on Position 1 (argc %d)\n", str, idx);
	}
	else if (type == PARSE_EXTRA)
		dprintf(2, "Extra arg `%s' (position 2, argc %d)\n", str, idx);
	return (type);
}

int	help_message(void)
{
	printf("Usage:\n  ft_traceroute host\n");
	printf("Options:\n");
	printf("  --help                      ");
	printf("Read this help and exit\n\n");
	printf("Arguments:\n");
	printf("+     host          The host to traceroute to\n");
	return (PARSE_HELP);
}

int	root_error(void)
{
	dprintf(2, "ft_traceroute: ");
	dprintf(2, "please check root privilege.\n");
	return (FT_FAIL);
}
