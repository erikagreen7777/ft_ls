#include "../ft_ls.h"

static int    R_helper(const char *str)
{
    DIR             *dip;
    struct dirent   *dit;
    struct stat     fileStat;

    dip = opendir(str);
    if (dip == NULL)
    {
            /*
            ** TODO: create own function for this because it happens often?
            */
    
        if(stat(str,&fileStat) < 0) 
        {
            ft_printf("./ft_ls: %s: No such file or directory\n", str);
            return (-1);
        } 
        printf("%s\n", str);
        return (-1);
            /*
            ** end function here?
            */
    }
        while ((dit = readdir(dip)) != NULL)
        {
            if (dit->d_name[0] != '.')
                ft_printf("%s\n", dit->d_name);
        }
        if (closedir(dip) == -1)
            ft_error("closedir");
        return (0);
}



void list_dirbigr(const char *name)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) 
    {
        // if ((entry->d_name[0] != '.') && (entry->d_type == DT_REG))
        // {
        //         printf("before: %s\n", entry->d_name);
        // }
        if (entry->d_type == DT_DIR) 
        {

                char path[1024];
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                    continue;
                // snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
                ft_strcpy(path, name);
                // printf("name: %s\n", name);
                ft_strcat(path, "/");
                ft_strcat(path, entry->d_name);
                // printf("entry->d_name: %s\n", entry->d_name);
                printf("\n%s: \n", path);
                R_helper(path);
                // ft_printf("%s\n", newpath);
                list_dirbigr(path);
        }    
    }
    closedir(dir);
}

// void list_dirbigr(char **argv, const char *dir_name, t_lists *lists)
// {
//     // char    *newpath;
//     // int     dir_name_length;
//     // int     d_name_length;
//     struct stat     fileStat;
//     DIR             *d;

//     d = opendir(dir_name);
//     if (d == NULL)
//     {
//         if(stat(argv[2],&fileStat) < 0)
//         {
//             if ((fileStat.st_mode & S_IFMT) != S_IFSOCK)
//             {
//                 printf("Cannot open directory '%s': %s\n", dir_name, strerror(errno));
//                 exit(EXIT_FAILURE);
//             }
//             ft_error("ls -r: No such file or directory");
//         }
//         printf("meh %s\n", argv[2]);
//         exit(1);
//     }
//     // if (d == NULL)
//     // {
//     //     if (lists->i == 0)
//     //     {
//     //         if(stat(argv[2],&fileStat) < 0)
//     //         {
//     //             if ((fileStat.st_mode & S_IFMT) != S_IFSOCK)
//     //             {
//     //                 printf("Cannot open directory '%s': %s\n", dir_name, strerror(errno));
//     //                 exit(EXIT_FAILURE);
//     //             }
//     //         }
//     //         // printf("d == null %s\n", argv[2]);
//     //         // exit(1);
//     //     }
//     //     else if (lists->i > 0)
//     //     {
//     //         if(stat(lists->newpath,&fileStat) < 0)
//     //         {
//     //             printf("Cannot open directory '%s': %s\n", dir_name, strerror(errno));
//     //             exit(EXIT_FAILURE);
//     //         }
//     //     }
//     // }
//     while (1) 
//     {
//         struct dirent *entry;
//         const char *d_name;
//         entry = readdir(d);
//         if (!entry)
//         {
//             break;
//         }
//         d_name = entry->d_name;
//         if (d_name[0] != '.')
//         {
//            ft_printf("hello: %s\n", d_name);
//         }
//         if (entry->d_type & DT_DIR) 
//         {
//             /* Check that the directory is not "d" or d's parent. */
//             if (ft_strcmp(d_name, "..") != 0 && ft_strcmp(d_name, ".") != 0) 
//             {
//                 int  temp_length;
//                 temp_length = ft_strlen(lists->newpath);
//                 ft_strcpy(lists->newpath, dir_name);
//                 if (ft_strcmp(argv[2], "/") != 0)
//                     ft_strcat(lists->newpath, "/");
//                 ft_strcat(lists->newpath, d_name);
//                 ft_printf("\n%s\n", lists->newpath);
//                 if (temp_length >= PATH_MAX)
//                     ft_error("Path length too long");
//                     /* Recursively call "list_dir" with the new path. */
//                 list_dirbigr(argv, lists->newpath, lists);
//             }
//         }
//     }
//     /* After going through all the entries, close the directory. */
//     if (closedir (d)) {
//             ft_error("closedir");
//         exit (EXIT_FAILURE);
//     }
// }