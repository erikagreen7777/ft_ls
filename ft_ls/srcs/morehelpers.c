/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   morehelpers.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: egreen  <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/23 15:11:43 by egreen       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 20:18:23 by egreen      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../ft_ls.h"
/*
** checks that file/directory exists if dip == null
*/
void null_check(const char *str)
{
    struct stat     fileStat;

    if(lstat(str, &fileStat) < 0) 
    {
        ft_printf("./ft_ls: %s: No such file or directory\n", str);
        exit (-1);
    } 
    ft_printf("%s\n", str);
    exit (-1);
}

/*
** - rl helpers helper
*/
void 	rl_helper_helper(DIR *dip, t_lists *lists, char *arg, int flag)
{
	struct dirent   *dit;
	char            temp[WORD_MAX];
	
	if (flag == 0)
        lists->filecount = directory_count(dip, arg, 0);
    else if (flag == 1)
        lists->filecount = directory_count(dip, arg, 1);
    lists->dest = (char **)ft_memalloc(sizeof(char *) * (lists->filecount + 1));
    ft_strcpy(temp, arg);
    while ((dit = readdir(dip)) != NULL)
    {
        if (flag == 0)
            read_helper_guts(lists, arg, dit, temp, 0);
        else if (flag == 1)
            read_helper_guts_a(lists, arg, dit, temp, 0);
    }
}
void    rlt_rt_helper_helper(DIR *dip, t_lists *lists, char *arg, int flag)
{
    struct dirent   *dit;
    char            temp[WORD_MAX];

    if (flag == 0)
        lists->filecount = directory_count(dip, arg, 0);
    else if (flag == 1)
        lists->filecount = directory_count(dip, arg, 1);
    lists->dest = (char **)ft_memalloc(sizeof(char *) * (lists->filecount + 1));
    lists->timearray = (int *)ft_memalloc(sizeof(int) * lists->filecount);
    lists->timearrayflag++;
    ft_strcpy(temp, arg);
    while ((dit = readdir(dip)) != NULL)
    {
        if (flag == 0)
            read_helper_guts(lists, arg, dit, temp, 1);
        else if (flag == 1)
            read_helper_guts_a(lists, arg, dit, temp, 1);
    }
}

/*
** - rt helpers helper
*/
void	rt_helper_helper(DIR *dip, t_lists *lists, char *arg, int flag)
{
	struct dirent   *dit;
	char            temp[WORD_MAX];

    if (flag == 0)
        lists->filecount = directory_count(dip, arg, 0);
    else if (flag == 1)
        lists->filecount = directory_count(dip, arg, 1);
    lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
    lists->timearray = (int *)ft_memalloc(sizeof(int) * lists->filecount);
    lists->timearrayflag++;
    ft_strcpy(temp, arg);
    while ((dit = readdir(dip)) != NULL)
    {
        if (flag == 0)
            read_helper_guts(lists, arg, dit, temp, 1);
        else if (flag == 1)
            read_helper_guts_a(lists, arg, dit, temp, 1);
    }
}

/*
** -lt helper
*/
void		lt_helper(t_lists *lists, char *str)
{
	DIR				*dip;
	char			arg[WORD_MAX];


	dip = opendir(str);
	ft_strcpy(arg, str);
	if (ft_strcmp(arg, "/dev") == 0)
		lists->flag = 1;
	if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
		ft_strcat(arg, "/");
	if (closedir(dip) == -1)
		ft_error("closedir");
	lists->filecount = directory_count(dip, str, 0);
	dip = opendir(str);
	read_helper(lists, 1, arg, dip);
	if (closedir(dip) == -1)
		ft_error("closedir");
}
