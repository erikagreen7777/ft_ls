#include "../ft_ls.h"

int main(int argc, char **argv)
{
    if(argc != 2)    
        return 1;
 
    struct stat fileStat;
    struct passwd *pwd;
    struct group *grp;
    char    *foo;
    char    **timearray;
    char    *hourmin;

    hourmin = (char *)malloc(sizeof(char));

    if(stat(argv[1],&fileStat) < 0)  
        return 1;
    ft_printf("Information for %s\n",argv[1]);
    ft_printf("---------------------------\n");
    ft_printf("Number of Links: \t%d\n",fileStat.st_nlink);
    
    //print %s of userid. else, print numerical version
    if ((pwd = getpwuid(fileStat.st_uid)) != NULL)
        printf("UserID: \t\t%s\n", pwd->pw_name);
    else
        printf("UserID (numerical): \t\t%d\n", fileStat.st_uid);
    
    //print %s of groupid. else, print numerical version
    if ((grp = getgrgid(fileStat.st_gid)) != NULL)
        printf("GroupID: \t\t%s\n", grp->gr_name);
    else
        printf("GroupID (numerical): \t\t%d\n", fileStat.st_gid);

    //file size
    ft_printf("File Size: \t\t%llu bytes\n",fileStat.st_size);

    //last modification date
    foo = ctime(&(fileStat.st_mtime));
    timearray = ft_strsplit(foo, ' ');
    ft_strncpy(hourmin, timearray[3], 5);
    printf("Last modification date: %s %s %s\n", timearray[1], timearray[2], hourmin);
    free(hourmin);

    //file permissions
    ft_printf("File Permissions: \t");
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
    ft_printf("\n\n");
 
    //device type?
    printf("device type: \t\t%d\n", fileStat.st_rdev);

    //file type
    if (S_ISDIR(fileStat.st_mode) == 1)
        printf("File type: \t\tDirectory\n");
    else if ((fileStat.st_mode & S_IFMT) == S_IFIFO)
        printf("File type: \t\tNamed Pipe (FIFO)\n");
    else if ((fileStat.st_mode & S_IFMT) == S_IFCHR)
        printf("File type: \t\tCharacter Device\n");
    else if ((fileStat.st_mode & S_IFMT) == S_IFBLK)
        printf("File type: \t\tBlock Device\n");
    else if ((fileStat.st_mode & S_IFMT) == S_IFSOCK)
        printf("File type: \t\tSocket\n");
    else if ((fileStat.st_mode & S_IFMT) == S_IFREG)
        printf("File type: \t\tRegular File\n");
    else if ((fileStat.st_mode & S_IFMT) == S_IFLNK)
        printf("File type: \t\tSymbolic Link\n");
    else
        printf("Some sort of file type error\n");

    //symbolic link?
    ft_printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");
 
    return 0;
}

    // ft_printf("File inode: \t\t%lld\n",fileStat.st_ino);
    // ft_printf("UserID: \t\t%d\n", getpwuid(fileStat.st_uid));
    // ft_printf("GroupID: \t\t%u\n", fileStat.st_gid);



