#include "ft_ls.h"
#include <stdio.h>

void 		set_flag(int rez, t_flag *flag)
{
	if (rez == 'a')
		flag->a_flag = 1;
	else if (rez == 'd')
		flag->d_flag = 1;
	else if (rez == 'f')
		flag->f_flag = 1;
	else if (rez == 'g')
		flag->g_flag = 1;
	else if (rez == 'l')
		flag->l_flag = 1;
	else if (rez == 'R')
		flag->rec_flag = 1;
	else if (rez == 'r')
		flag->r_flag = 1;
	else if (rez =='t')
		flag->t_flag = 1;
	else
		flag->u_flag = 1;
}

void 		collect_flags(int *args, t_flag *flag, t_input input)
{
	t_opt	*opt;
	int 	rez;
	int 	opt_index;
	t_input	tmp;

	tmp = input;
	opt = NULL;
	while (tmp.ac && tmp.av)
	{
		while ((rez = ft_getopt_long(tmp, &opt, g_lopt, &opt_index)) != -1)
		{
			if (rez == '?')
			{
				free(opt);
				perror("ls: invalid option -- ");
				exit(0);
			}
			else
				set_flag(rez, flag);
		}
		tmp.ac--;
		tmp.av += opt->optind;
		if (*(tmp.av) == NULL || *(tmp.av + 1) == NULL || opt->optchar == '?')
			break;
	}
}

int 		get_num_of_array_index(t_input input)
{
	int 	num;
	int 	i;
	int 	j;

	i = 1;
	num = 0;
	while (i < input.ac)
	{
		while (input.av[i]  != NULL)
		{
			j = 0;
			if (input.av[i] && input.av[i][j] == '-'
				&& input.av[i][j + 1] != '-' && input.av[i][j + 1] != '\0')
			{
				while (input.av[i][++j])
					num++;
				i++;
				break;
			}
			num++;
			i++;
		}
	}
	return (num);
}

void		reset_flags(t_flag *flag)
{
	flag->a_flag = 0;
	flag->d_flag = 0;
	flag->f_flag = 0;
	flag->g_flag = 0;
	flag->l_flag = 0;
	flag->rec_flag = 0;
	flag->r_flag = 0;
	flag->t_flag = 0;
	flag->u_flag = 0;
}

int			main(int ac, char **av)
{
	t_flag	flag;
	int		args[get_num_of_array_index((t_input){ac, av})];

	reset_flags(&flag);
	collect_flags(args, &flag, (t_input){ac, av});
	return (0);
}