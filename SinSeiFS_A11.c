#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static  const  char *dirpath = "/home/erzajanitra/Downloads";
//char atz[10]="/AtoZ_";

// Encryption and Decryption function
char *atbash(char message[])
{
	int len=strlen(message);
	char *cipher;
	//char ascii_char[1024];
	
	for(int i=0;i<len;i++){
		
			//ascii_char = message[i];                         // Storing ASCII value of alphabet
			if(message[i]>='A' && message[i]<='Z')
				message[i] = 'Z'-(message[i]-'A');    // If character is in upper case(minus 65 from its ASCII value to get reversed character)
			else if (message[i]>='a' && message[i]<='z')
				message[i] = 'z'-(message[i]-'a');    // If character is in upper case(minus 97 from its ASCII value to get reversed character)
		
		cipher=message;		
	}
	
	return cipher;
}

char *process(const char *path){
	int cek=0;
	char fpath[1024];
	//cek apakah folder bernama /AtoZ
	char *atoz;
	if(strcmp(path,"/") != 0){
		atoz=strstr(path,"/AtoZ_");
		if(atoz){
			cek=1;
			atoz++; //ambil AtoZ
		}
	}
	char atez[1024];
	strcpy(atez,atoz);
	char newPath[1024];
    if(strcmp(path,"/") == 0) //dari root
    {
        path=dirpath;
        sprintf(fpath,"%s",path);
    } 
	
    else if (cek){ //ada AtoZ
		char dirAsli[1024];
		strncpy(dirAsli,path,strlen(path)-strlen(atoz));
		// dirAsli=/home/erzajanitra/Downloads/
		int x;
		char *encName; char *cut=atez;
		//char temp[1024];
		//folder yg akan di enkripsi
		while((encName=strtok_r(cut,"/",&cut))){
			if(x==0){
				strcat(dirAsli,encName);
				x=1;
				continue;
			}
			bzero(newPath,1024);
			strcpy(newPath,dirAsli); strcat(newPath,"/");
			strcat(newPath,encName);

			//cek file
		}
		sprintf(fpath,"%s",newPath);
	}
	else sprintf(fpath,"%s%s",dirpath,path);

}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
	char fpath[1000];
	strcpy(fpath,path);
	//comPath(fpath,dirpath,path);
	//strcpy(fpath,path);
	int res=0;
	res = lstat(process(fpath), stbuf);
	if (res == -1)
		return -errno;

	return 0;
}

// rename nama encode/decode w/ atbash cipher
static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
    char fpath[1000];
	strcpy(fpath,path);
	
	int res = 0;
    DIR *dp;
    struct dirent *de;
    (void) offset;
    (void) fi;

    dp = opendir(process(fpath));

    if (dp == NULL) return -errno;

    while ((de = readdir(dp)) != NULL) {
        struct stat st;

        memset(&st, 0, sizeof(st));

        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;//mode file

        //cek directory 
        if(de->d_type==DT_DIR){
			
            //kalau ketemu file namanya AtoZ_
			if(strncmp(de->d_name,"AtoZ_",5)==0){
				//de->d_name[strlen(de->d_name)-4]='\0';
           		res = (filler(buf, de->d_name, &st, 0));
			}
			else{
				char temp[1024];
				strcpy(temp,atbash(de->d_name));
				
           		res = (filler(buf, temp, &st, 0));
			}
        }
        //file
        else if (de->d_type==DT_REG){
			
			char *ext=strchr(de->d_name,'.');
			char temp[1024];
			if(ext){
				strncpy(temp,de->d_name,strlen(de->d_name)-strlen(ext));
				
				strcpy(temp,atbash(temp));
				strcat(temp,ext);
			}
           	res = (filler(buf, temp, &st, 0));
        }
        
        //filler : ngisi buffer dgn nama file
        if(res!=0) break;
    }

    closedir(dp);

    return 0;
}


static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
	char fpath[1024];
	strcpy(fpath,path);
	int fd;
	int res;

	(void) fi;
	fd = open(process(path), O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}


static struct fuse_operations xmp_oper = {
    .getattr = xmp_getattr,
    .readdir = xmp_readdir,
    .read = xmp_read,
};

int  main(int  argc, char *argv[])
{
    umask(0);

    return fuse_main(argc, argv, &xmp_oper, NULL);
}
