/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 16:49:34 by user              #+#    #+#             */
/*   Updated: 2020/06/04 19:07:40 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>
#include <sys/ioctl.h>

double		max_size_name(t_ls *ls)
{
    double size;
    char    *str;
    char    *next_str;

	size = 0;
	while (ls->next != NULL)
	{
        str = ls->name ? ls->name : ls->path;
        next_str = ls->next->name ? ls->next->name : ls->next->path;
		if ((ft_strlen(str) > ft_strlen(next_str)) && size < ft_strlen((str)))
			size = ft_strlen(str);
		ls = ls->next;
	}
	return (size);
}

int     max_size_list(t_ls *ls)
{
    int size;

    size = 0;
    while (ls)
    {
        size++;
        ls = ls->next;
    }
    return (size);
}

void    write_space(char *ptr, int max_len)
{
    int len;

    if (ptr == NULL)
        return ;
    len = ft_strlen(ptr);
    while (len < max_len)
    {
        ft_printf(" ");
        len++;
    }
}

mode_t	ls_mode(t_ls *ls, int size)
{
	int i;

	i = 0;
	while (ls && i < size)
	{
		ls = ls->next;
		i++;
	}
	return (ls->mode);
}

void    name_ls(char **ptr, t_columns columns, t_ls *ls)
{
    int i;
    int k;

	i = 0;
	while(i < columns.word_in_column)
	{
		set_color(ls_mode(ls, i), ls->flag.G);
		ft_printf("%s", ptr[i]);
		ft_putstr(RESET);
		write_space(ptr[i], columns.max_len);
		k = 1;
		while (k < columns.columns)
		{
			if ((i + columns.word_in_column * k) < columns.max_len_list)
			{
				set_color(ls_mode(ls, i + columns.word_in_column * k), ls->flag.G);
				ft_printf("%s", ptr[i + columns.word_in_column * k]);
				ft_putstr(RESET);
				write_space(ptr[i + columns.word_in_column * k], columns.max_len);
            }
            k++;
        }
        i++;
        ft_printf("\n");
    }
}

void		print(t_ls *ls)
{
	struct	winsize  window;
	t_columns   columns;
	char		**ptr;

	ptr = NULL;
    ioctl(0, TIOCGWINSZ, &window);
    columns.max_len = max_size_name(ls) + BTW_COL;
    columns.max_len_list = max_size_list(ls);
    columns.columns = window.ws_col / columns.max_len;
    if (columns.columns == 0 || ls->flag.one)
        columns.word_in_column = columns.max_len_list;
    else if (columns.max_len_list % columns.columns != 0)
        columns.word_in_column = columns.max_len_list / columns.columns + 1;
    else
        columns.word_in_column = columns.max_len_list / columns.columns;
    ptr = create_arr(ls, columns.max_len_list);
    name_ls(ptr, columns, ls);
    free(ptr);
}


