/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   recuse.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: egreen  <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/11 14:54:00 by egreen       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 20:18:23 by egreen      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../ft_ls.h"

/*
** ls -Rr
*/
void    list_dirbigrr(const char *name, int flag, t_lists *lists)
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
                // ft_strcpy(path, name);
                // ft_strcat(path, "/");
                // ft_strcat(path, entry->d_name);
                // printf("\n%s: \n", path);
                /*
                ** 0 flag, no -a. 1 flag -a
                */
                if (flag == 0)
                {
                    Rr_helper(path, 0, lists);
                    list_dirbigrr(path, 0, lists);
                }
                else
                {
                    Rr_helper(path, 1, lists);
                    list_dirbigrr(path, 1, lists);
                }
        }    
    }
    closedir(dir);
}

/*
** - Rlt
*/
void    rlt(const char *name, int flag, t_lists *lists)
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
                // ft_strcpy(path, name);
                // ft_strcat(path, "/");
                // ft_strcat(path, entry->d_name);
                // printf("\n%s: \n", path);
                /*
                ** 0 flag, no -a. 1 flag -a
                */
                if (flag == 0)
                {
                    rlt_helper(path, 0, lists);
                    rlt(path, 0, lists);
                }
                else
                {
                    rlt_helper(path, 1, lists);
                    rlt(path, 1, lists);
                }
        }    
    }
    closedir(dir);
}