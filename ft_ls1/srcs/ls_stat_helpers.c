#include "../ft_ls.h"

/*
** - print file permissions for ls -l
*/    
void    permissions(struct stat fileStat)
{
    if (S_ISLNK(fileStat.st_mode))
        ft_printf("l");
    else if (S_ISDIR(fileStat.st_mode) == 1)
        ft_printf("d");
    else if ((fileStat.st_mode & S_IFMT) == S_IFIFO)
        ft_printf("p");
    else if ((fileStat.st_mode & S_IFMT) == S_IFCHR)
        ft_printf("c");
    else if ((fileStat.st_mode & S_IFMT) == S_IFBLK)
        ft_printf("b");
    else if ((fileStat.st_mode & S_IFMT) == S_IFSOCK)
        ft_printf("s");
    else if ((fileStat.st_mode & S_IFMT) == S_IFREG)
        ft_printf("-");
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
}

/*
** - print userid, groupid, file size (or for /dev major/minor device numbers)
*/
void    guidstuff(struct stat fileStat, t_lists *lists)
{
    struct passwd   *pwd;
    struct group    *grp;

    ft_printf("%5d\t",fileStat.st_nlink);      
    if ((pwd = getpwuid(fileStat.st_uid)) != NULL)
        ft_printf("%s\t", pwd->pw_name);
    else
        ft_printf("%d\t", fileStat.st_uid);
    if ((grp = getgrgid(fileStat.st_gid)) != NULL)
        ft_printf("%s\t", grp->gr_name);
    else
        ft_printf("%d\t", fileStat.st_gid);
    if (lists->flag == 0)
        ft_printf("%6llu\t",fileStat.st_size);
    else
        ft_printf("%4ld, %4ld ", (long) major(fileStat.st_rdev), (long) minor(fileStat.st_rdev));
}

/*
** - free timearray and hourmin used in timeinfo
*/
static void free_timearray(char **timearray, char *hourmin)
{
    int k = 0;
    while (k < 5)
    {
        free(timearray[k]);
        k++;
    }
    free(timearray);
    free(hourmin);
}

/*
** - if the date is more than 6 months in either direction, print month, date, year. 
** - else, print the month, date, and hour:min
*/
void    timeinfo(struct stat fileStat)
{
    char            **timearray;
    char            *hourmin;
    time_t          current;
    char            *foo;
    char            year[5];

    hourmin = (char *)malloc(sizeof(char) * (5 + 1));
    foo = ctime(&(fileStat.st_mtime));
    timearray = ft_strsplit(foo, ' ');
    ft_strncpy(hourmin, timearray[3], 5);
    ft_strncpy(year, timearray[4], 4);
    if (fileStat.st_mtime > time(&current) + 15780000 || \
        fileStat.st_mtime < time(&current) - 15780000)
        ft_printf("%s %2s %s  ", timearray[1], timearray[2], year);
    else
        ft_printf("%s %2s %s  ", timearray[1], timearray[2], hourmin);
    free_timearray(timearray, hourmin);
}



