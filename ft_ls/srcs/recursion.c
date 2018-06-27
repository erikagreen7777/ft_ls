/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   recursion.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: egreen  <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/28 09:20:35 by egreen       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 20:18:23 by egreen      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../ft_ls.h"
/*
** ls -R pre-helper
*/
void    R_first(char *str, int flag)
{
    DIR             *dip;
    struct dirent   *dit;
    struct stat     fileStat;

    dip = opendir(str);
    if (dip == NULL)
    {
        if(stat(str,&fileStat) < 0) 
        {
            ft_printf("./ft_ls: %s: No such file or directory\n", str);
            exit (-1);
        } 
        ft_printf("%s\n", str);
        exit(0);
    }
    while ((dit = readdir(dip)) != NULL)
    {
        if (flag == 0)
        {
            if (dit->d_name[0] != '.')
                ft_printf("%s\n", dit->d_name);
        }
        else
            ft_printf("%s\n", dit->d_name);
    }
    if (closedir(dip) == -1)
        ft_error("closedir");
}

// void    R_first(int argc, char **argv, int flag, int j)
// {
//     DIR             *dip;
//     struct dirent   *dit;
//     struct stat     fileStat;
//     int             k;
//     k = j;
//     while (j < argc)
//     {
//         if (j > k && j < argc)
//             write(1, "\n", 1);
//         dip = opendir(argv[j]);
//         if (dip == NULL)
//         {
//             if(stat(argv[j],&fileStat) < 0) 
//             {
//                 ft_printf("./ft_ls: %s: No such file or directory\n", argv[j]);
//                 exit (-1);
//             } 
//             ft_printf("%s\n", argv[j]);
//             exit(0);
//         }
//         while ((dit = readdir(dip)) != NULL)
//         {
//             if (flag == 0)
//             {
//                 if (dit->d_name[0] != '.')
//                     ft_printf("%s\n", dit->d_name);
//             }
//             else
//                 ft_printf("%s\n", dit->d_name);
//         }
//         if (closedir(dip) == -1)
//             ft_error("closedir");
//         j++;
//     }
// }


/*
** -R
*/

void list_dirbigr(const char *name, int flag)
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
                    // R_helper(path, 0);
                    list_dirbigr(path, 0);
                }
                else
                {
                    // R_helper(path, 1);
                    list_dirbigr(path, 1);
                }
        }
        else
            ft_printf("%s\n", entry->d_name);  
    }
    closedir(dir);
}

/*
** -Rt R part
*/
void   list_dirbigrt(const char *name, int flag, t_lists *lists)
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
                    Rt_helper(path, 0, lists);
                    list_dirbigrt(path, 0, lists);
                }
                else
                {
                    Rt_helper(path, 1, lists);
                    list_dirbigrt(path, 1, lists);
                }
        }    
    }
    closedir(dir);
}

/*
** ls -Rl
*/
void    list_dirbigrl(const char *name, int flag, t_lists *lists)
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
                    Rl_helper(path, 0, lists);
                    list_dirbigrl(path, 0, lists);
                }
                else
                {
                    Rl_helper(path, 1, lists);
                    list_dirbigrl(path, 1, lists);
                }
        }    
    }
    closedir(dir);
}
