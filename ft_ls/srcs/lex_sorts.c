/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lex_sorts.c                           			  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: egreen  <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/24 10:49:00 by egreen       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 20:18:23 by egreen      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../ft_ls.h"
/*
** lexicographically sort for ls -rl
*/
void	lex_sortrl(t_lists *lists)
{
	// char 	*temp;
	lists->i = 0;
	while (lists->i < lists->filecount)
	{
		lists->j = lists->i + 1;
		while (lists->j < lists->filecount)
		{
			if (ft_strcmp(lists->dest[lists->i], lists->dest[lists->j]) < 0)
			{
				swap(&lists->dest[lists->i], &lists->dest[lists->j]);
				// temp = ft_strdup(lists->dest[lists->i]);				
				// ft_bzero(lists->dest[lists->i], ft_strlen(lists->dest[lists->i]));
				// free(lists->dest[lists->i]);
				// lists->dest[lists->i] = ft_strdup(lists->dest[lists->j]);
				// ft_bzero(lists->dest[lists->j], ft_strlen(lists->dest[lists->j]));
				// free(lists->dest[lists->j]);
				// lists->dest[lists->j] = ft_strdup(temp);
				// ft_bzero(temp, ft_strlen(temp));
				// free(temp);
			}
			lists->j++;
		}
		lists->i++;
	}
}
/*
** - reverse lexicographically sort for -rla. There is somehow a difference
** between rlex_sotrl and lex_sortrl in terms of -rla. /shrug
*/
void	rlex_sortrl(t_lists *lists)
{
	// char 	*temp;
	lists->i = 0;
	while (lists->i < lists->filecount)
	{
		lists->j = lists->i + 1;
		while (lists->j < lists->filecount)
		{
			if (ft_strcmp(lists->dest[lists->i], lists->dest[lists->j]) > 0)
			{
				swap(&lists->dest[lists->i], &lists->dest[lists->j]);
				// temp = ft_strdup(lists->dest[lists->i]);				
				// ft_bzero(lists->dest[lists->i], ft_strlen(lists->dest[lists->i]));
				// free(lists->dest[lists->i]);
				// lists->dest[lists->i] = ft_strdup(lists->dest[lists->j]);
				// ft_bzero(lists->dest[lists->j], ft_strlen(lists->dest[lists->j]));
				// free(lists->dest[lists->j]);
				// lists->dest[lists->j] = ft_strdup(temp);
				// ft_bzero(temp, ft_strlen(temp));
				// free(temp);
			}
			lists->j++;
		}
		lists->i++;
	}
}

/*
** lexicographically sort for ls -r
*/
void	lex_sort(t_lists *lists)
{
	// char 	*temp;
	lists->i = 0;
	while (lists->i < lists->filecount)
	{
		lists->j = lists->i + 1;
		while (lists->j < lists->filecount)
		{
			if (ft_strcmp(lists->dest[lists->i], lists->dest[lists->j]) < 0)
			{
				swap(&lists->dest[lists->i], &lists->dest[lists->j]);
				// temp = ft_strdup(lists->dest[lists->i]);				
				// ft_bzero(lists->dest[lists->i], ft_strlen(lists->dest[lists->i]));
				// free(lists->dest[lists->i]);
				// lists->dest[lists->i] = ft_strdup(lists->dest[lists->j]);
				// ft_bzero(lists->dest[lists->j], ft_strlen(lists->dest[lists->j]));
				// free(lists->dest[lists->j]);
				// lists->dest[lists->j] = ft_strdup(temp);
				// ft_bzero(temp, ft_strlen(temp));
				// free(temp);
			}
			lists->j++;
		}
		lists->i++;
	}
	print_lists(lists);
}