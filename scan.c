#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <limits.h>

void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;
    struct passwd *pwd;
    struct stat fileStat;
    if (!(dir = opendir(name)))
        return;
    while ((entry = readdir(dir)) != NULL) {
     if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            printf("%*s[%s]\t", indent, "", entry->d_name);
	char fname[1024];    
    	sprintf(fname,"%s/%s",name,entry->d_name);
        stat(fname,&fileStat);
        printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
        printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
        if (fileStat.st_mode & S_IFDIR)
                printf("\tdirectory  ");
        if (fileStat.st_mode & S_IFCHR)
                printf("\tchracter file  ");
        if (fileStat.st_mode & S_IFREG)
                printf("\treggular file  ");
                pwd = getpwuid(fileStat.st_uid);
                if(pwd == NULL) {
                        perror("getpwuid");
                } else {
                printf(" %s ", pwd->pw_name);
                }
        printf( " %s ",ctime(&fileStat.st_atime));
	char path[1024];
	snprintf(path,sizeof(path), "%s/%s", name, entry->d_name);           
 	listdir(path, indent + 2);
     } else {
        printf("%*s- %s\t", indent, "", entry->d_name);  
	char fname[1024];
	sprintf(fname," %s/%s ",name,entry->d_name);
        stat(fname,&fileStat);
        printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
        printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
        if (fileStat.st_mode & S_IFDIR)
                printf("\tdirectory  ");
        if (fileStat.st_mode & S_IFCHR)
                printf("\tchracter file  ");
        if (fileStat.st_mode & S_IFREG)
                printf("\treggular file  ");
                pwd = getpwuid(fileStat.st_uid);
                if(pwd == NULL) {
                        perror("getpwuid");
                } else {
                printf("%s ", pwd->pw_name);
                }
   	//printf("%s", (S_ISLNK(fileStat.st_mode)) ? " link " : " ");
	//printf(" %d ", (int)fileStat.st_nlink);
     	printf( "%s",ctime(&fileStat.st_atime));
	}	
    }
    closedir(dir);
}

int main(void) {
    listdir(".", 0);
    return 0;
}
