#include "ft_ls.h"

static int	digit_length(long num)
{
	if (num < 10)
		return (1);
	return (1 + digit_length(num / 10));
}

static int	biggest_str(char *s1, char *s2)
{
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	return (len1 > len2 ? len1 : len2);
}

t_print		print_utils(t_ls *ls)
{
	t_print	p;
	t_print	tmp;

	p.max_size = 0;
	while (ls)
	{
		if (!p.max_size)
		{
			p.max_mode = ft_strlen(ls->chmod);
			p.max_nlink = digit_length(ls->nlink);
			p.max_name = biggest_str(ls->uname, ls->gname);
			p.max_size = digit_length(ls->size);
		}
		if ((tmp.max_mode = ft_strlen(ls->chmod)) > p.max_mode)
			p.max_mode = tmp.max_mode;
		if ((tmp.max_nlink = digit_length(ls->nlink)) > p.max_nlink)
			p.max_nlink = tmp.max_nlink;
		if ((tmp.max_name = biggest_str(ls->uname, ls->gname)) > p.max_name)
			p.max_name = tmp.max_name;
		if ((tmp.max_size = digit_length(ls->size)) > p.max_size)
			p.max_size = tmp.max_size;
		ls = ls->next;
	}
	return (p);
}