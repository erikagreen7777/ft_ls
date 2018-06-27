/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doubles.c                             			  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: egreen  <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/16 11:53:29 by egreen       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 20:18:23 by egreen      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../ft_ls.h"
/*
** -aother backwards helper
*/
void	back_helper(t_lists *lists)
{
	lists->i = 0;
	while (lists->i < lists->filecount)
	{
		lists->size += add_stat(lists->dest[lists->i]);
		lists->i++;
	}
	if (lists->size > 0)
		ft_printf("total %d\n", lists->size);
	else if (lists->flag == 1)
		ft_printf("total 0\n");
	lists->i = lists->filecount;
	while (--lists->i > -1)
	{
		ls_stat(lists->dest[lists->i], lists);
	}
}
/*
** -recursive lstat() helpers
*/
void 	recursive_ls_stat_helper(t_lists *lists)
{
    lists->i = 0;
    while (lists->i < lists->filecount)
    {
        lists->size += add_stat(lists->dest[lists->i]);
        lists->i++;
    }
    ft_printf("total %d\n", lists->size);
    if (lists->flag == 1)
        ft_printf("total 0\n");
    lists->i = -1;
    while (++lists->i < lists->filecount)
        ls_stat(lists->dest[lists->i], lists);
}
/*
** - recurstive lstat() helper for -r
*/
void 	r_recursive_ls_stat_helper(t_lists *lists)
{
	lists->i = -1;
    while (++lists->i < lists->filecount)
        lists->size += add_stat(lists->dest[lists->i]);
    ft_printf("total %d\n", lists->size);
    if (lists->flag == 1)
        ft_printf("total 0\n");
    lists->i = lists->filecount;
    while (--lists->i > -1)
        ls_stat(lists->dest[lists->i], lists);
}
/*
** -lstat()_helper
*/
void	ls_stat_helper(t_lists *lists)
{
	int 			size;

	size = 0;
	lists->i = 0;
	while (lists->i < lists->filecount)
	{
		size += add_stat(lists->dest[lists->i]);
		lists->i++;
	}
	if (size > 0)
		ft_printf("total %d\n", size);
	else if (lists->flag == 1)
		ft_printf("total 0\n");
	lists->i = -1;
	while (++lists->i < lists->filecount)
		ls_stat(lists->dest[lists->i], lists);
}

/*
** find out how many files are in a directory
*/
int		directory_count(DIR *dip, char *str, int flag)
{
	int		filecount;
	struct 	dirent *dit;
	filecount = 0;

	dip = opendir(str);

	while ((dit = readdir(dip)) != NULL)
	{
		if (flag == 0)
		{
			if (dit->d_name[0] != '.')
				filecount++;
		}
		else if (flag == 1)
			filecount++;
	}
	if (closedir(dip) == -1)
		ft_error("closedir");
	return (filecount);
}




