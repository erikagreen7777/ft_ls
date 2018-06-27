/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   quadruples.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: egreen  <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/21 20:44:53 by egreen       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 20:18:23 by egreen      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../ft_ls.h"

/*
** - Rrlta
*/
void	everything(const char *name, int flag, t_lists *lists)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_type == DT_DIR) 
        {
                char path[1024];
                if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
                    continue;
                recursive_cat(path, name, entry);
                if (flag == 0)
                {
                    everything_helper(path, 0, lists);
                    everything(path, 0, lists);
                }
                else
                {
                    everything_helper(path, 1, lists);
                    everything(path, 1, lists);
                }
        }    
    }
    closedir(dir);
}

/*
** -lta helper
*/
void    lta_helper(t_lists *lists, char *str)
{
    DIR             *dip;
    char            arg[WORD_MAX];


    dip = opendir(str);
    ft_strcpy(arg, str);
    if (ft_strcmp(arg, "/dev") == 0)
        lists->flag = 1;
    if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
        ft_strcat(arg, "/");
    if (closedir(dip) == -1)
        ft_error("closedir");
    lists->filecount = directory_count(dip, str, 1);
    dip = opendir(str);
    read_helper_a(lists, 1, arg, dip);
    ft_switch_time(lists);
    if (closedir(dip) == -1)
        ft_error("closedir");

}

/*
** - rlt helper
*/
void    rlt_helper_helper(t_lists *lists, char *str)
{
    DIR             *dip;
    char            arg[WORD_MAX];

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
    ft_switch_time(lists);
    if (closedir(dip) == -1)
        ft_error("closedir");

}

/*
** - rla helper helper
*/
void    rla_helper_helper(t_lists *lists, char *str)
{
    DIR             *dip;
    char            arg[WORD_MAX];

    dip = opendir(str);
    ft_strcpy(arg, str);
    if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
        ft_strcat(arg, "/");
    lists->filecount = directory_count(dip, str, 1);
    read_helper_a(lists, 0, arg, dip);
    if (closedir(dip) == -1)
        ft_error("closedir");
    rlex_sortrl(lists);
}

