#include "../ft_ls.h"


char    *extract_path(char *str)
{
    int             len;
    char            *newstr;

    newstr = (char *)malloc(sizeof(char));
    len = ft_strlen(str) - ft_strlen(ft_strstr(str, "/"));
    ft_strncpy(newstr, str, len);
    printf("newstr: %s\n", newstr);
    return (newstr);
}


int ls_stat(char *str)
{
    struct stat     fileStat;
    struct passwd   *pwd;
    struct group    *grp;
    char            *foo;
    char            **timearray;
    char            *hourmin;
    // DIR             *dip = NULL;
    // struct dirent   *dit;

    hourmin = (char *)malloc(sizeof(char));

    if(stat(str, &fileStat) < 0) 
    {
        ft_error("Yo: No such file or directory");
    }
    //file permissions
    // ft_printf("File Permissions: \t");
    ft_printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    ft_printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    ft_printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    ft_printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    ft_printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    ft_printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    ft_printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    ft_printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    ft_printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    ft_printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    ft_printf("\t");

//number of links
    // ft_printf("Number of Links: \t%d\n",fileStat.st_nlink);
    ft_printf("%d\t",fileStat.st_nlink);

            
    //print %s of userid. else, print numerical version
    if ((pwd = getpwuid(fileStat.st_uid)) != NULL)
        // ft_printf("UserID: \t\t%s\n", pwd->pw_name);
        ft_printf("%s\t", pwd->pw_name);
    else
        // ft_printf("UserID (numerical): \t\t%d\n", fileStat.st_uid);
        ft_printf("%d\t", fileStat.st_uid);

            
    //print %s of groupid. else, print numerical version
    if ((grp = getgrgid(fileStat.st_gid)) != NULL)
        // ft_printf("GroupID: \t\t%s\n", grp->gr_name);
        ft_printf("%s\t", grp->gr_name);
    else
        // ft_printf("GroupID (numerical): \t\t%d\n", fileStat.st_gid);
        ft_printf("%d\t", fileStat.st_gid);


    //file size
    // ft_printf("File Size: \t\t%llu bytes\n",fileStat.st_size);
    ft_printf("%llu\t",fileStat.st_size);


    //last modification date
    foo = ctime(&(fileStat.st_mtime));
    timearray = ft_strsplit(foo, ' ');
    ft_strncpy(hourmin, timearray[3], 5);
    // ft_printf("Last modification date: %s %s %s\n", timearray[1], timearray[2], hourmin);
    ft_printf("%s %s %s\t", timearray[1], timearray[2], hourmin);
    ft_printf("filename: %s\n", str);
    free(hourmin);
         
    //device type?
    // printf("device type: \t\t%d\n", fileStat.st_rdev);

    //file type
    // if (S_ISDIR(fileStat.st_mode) == 1)
    //     printf("File type: \t\tDirectory\n");
    // else if ((fileStat.st_mode & S_IFMT) == S_IFIFO)
    //     printf("File type: \t\tNamed Pipe (FIFO)\n");
    // else if ((fileStat.st_mode & S_IFMT) == S_IFCHR)
    //     printf("File type: \t\tCharacter Device\n");
    // else if ((fileStat.st_mode & S_IFMT) == S_IFBLK)
    //     printf("File type: \t\tBlock Device\n");
    // else if ((fileStat.st_mode & S_IaFMT) == S_IFSOCK)
    //     printf("File type: \t\tSocket\n");
    // else if ((fileStat.st_mode & S_IFMT) == S_IFREG)
    //     printf("File type: \t\tRegular File\n");
    // else if ((fileStat.st_mode & S_IFMT) == S_IFLNK)
            //     printf("File type: \t\tSymbolic Link\n");
    // else
    //     printf("Some sort of file type error\n");

//symbolic link?ø
    // ft_printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");


    return (0);
}
