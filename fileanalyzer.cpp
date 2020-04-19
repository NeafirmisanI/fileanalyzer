#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/sysmacros.h>
#include "errnoversion.hpp"


using namespace std;



void printaboutfile(const int fp, const char* path){
	struct stat buffer;

	if(stat(path, &buffer) == 0){

	           printf("ID of containing device:  [%lx,%lx]\n", (long) major(buffer.st_dev), (long) minor(buffer.st_dev));

           printf("File type:                ");

           switch (buffer.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }

           printf("I-node number:            %ld\n", (long) buffer.st_ino);

           printf("Mode:                     %lo (octal)\n", (unsigned long) buffer.st_mode);

           printf("Link count:               %ld\n", (long) buffer.st_nlink);
           printf("Ownership:                UID=%ld   GID=%ld\n", (long) buffer.st_uid, (long) buffer.st_gid);

           printf("Preferred I/O block size: %ld bytes\n", (long) buffer.st_blksize);
           printf("File size:                %lld bytes\n",  (long long) buffer.st_size);
           printf("Blocks allocated:         %lld\n", (long long) buffer.st_blocks);

           printf("Last status change:       %s", ctime(&buffer.st_ctime));
           printf("Last file access:         %s", ctime(&buffer.st_atime));
           printf("Last file modification:   %s", ctime(&buffer.st_mtime));




	} else if(lstat(path, &buffer)){
			           printf("ID of containing device:  [%lx,%lx]\n", (long) major(buffer.st_dev), (long) minor(buffer.st_dev));

           printf("File type:                ");

           switch (buffer.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }

           printf("I-node number:            %ld\n", (long) buffer.st_ino);

           printf("Mode:                     %lo (octal)\n", (unsigned long) buffer.st_mode);

           printf("Link count:               %ld\n", (long) buffer.st_nlink);
           printf("Ownership:                UID=%ld   GID=%ld\n", (long) buffer.st_uid, (long) buffer.st_gid);

           printf("Preferred I/O block size: %ld bytes\n", (long) buffer.st_blksize);
           printf("File size:                %lld bytes\n",  (long long) buffer.st_size);
           printf("Blocks allocated:         %lld\n", (long long) buffer.st_blocks);

           printf("Last status change:       %s", ctime(&buffer.st_ctime));
           printf("Last file access:         %s", ctime(&buffer.st_atime));
           printf("Last file modification:   %s", ctime(&buffer.st_mtime));

	}


}


int main(int argc, char* argv[]){
			
	// if we do't have any argument
	if(argc <= 1){
		perror("using: ./fileanalyzer <file_path>", 1);		
	}

	int fp;
	for(int i = 1; i<argc; i++){
		fp = open(argv[i], O_RDWR);
		if(fp != -1){
			printaboutfile(fp, argv[i]);	

		} else{
			perror("Failed to open a file", 1); 
		}	
	}

	return 0;
}

