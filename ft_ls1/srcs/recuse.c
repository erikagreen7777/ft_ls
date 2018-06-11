void list_dirbigr(char **argv, const char *dir_name, t_lists *lists)
{
    // char    *newpath;
    // int     dir_name_length;
    // int     d_name_length;
    struct stat     fileStat;
    DIR             *d;

    d = opendir(dir_name);
    if (d == NULL)
    {
        if(stat(argv[2],&fileStat) < 0)  
            ft_error("ls -r: No such file or directory");
        printf("%s\n", argv[2]);
        exit(1);
    }
    while (1) 
    {
        struct dirent *entry;
        const char *d_name;
        entry = readdir(d);

        if (!entry)
        {
            break;
        }
        d_name = entry->d_name;
        if (d_name[0] != '.')
	       ft_printf("%s\n", d_name);
        if (entry->d_type & DT_DIR) 
        {
            /* Check that the directory is not "d" or d's parent. */
            if (ft_strcmp(d_name, "..") != 0 && ft_strcmp(d_name, ".") != 0) 
            {
                // dir_name_length = ft_strlen(dir_name);
                // d_name_length = ft_strlen(d_name);
                // newpath = (char *)malloc(sizeof(dir_name_length + d_name_length + 2));
                // ft_strcpy(newpath, dir_name);
                // ft_strcat(newpath, "/");
                // ft_strcat(newpath, d_name);
                // ft_printf("%s\n", newpath);
                // dir_name_length = 0;
                // d_name_length = 0;
                // ft_bzero(newpath, ft_strlen(newpath));
                // list_dirbigr(newpath);

                char newpath[PATH_MAX];
                int  newpath_length;
                newpath_length = ft_strlen(newpath);
                ft_strcpy(newpath, dir_name);
                if (ft_strcmp(argv[2], "/") != 0){
                    ft_strcat(newpath, "/");
                }
                ft_strcat(newpath, d_name);
                ft_printf("%s\n", newpath);
                if (newpath_length >= PATH_MAX)
                    ft_error("Path length too long");
                    /* Recursively call "list_dir" with the new path. */
                list_dirbigr(argv, newpath, lists);
            }
    	}
    }
    /* After going through all the entries, close the directory. */
    if (closedir (d)) {
            ft_error("closedir");
        exit (EXIT_FAILURE);
    }
}