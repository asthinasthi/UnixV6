#include "dec.h"
char create_dir(char *dir_name)
{
struct inode dir;
struct superblock sblk;
direntry entryname;
//char direntry[16];
if (0 == strcmp(dir_name,"root")) {
	
	memset(&entryname,'\0',sizeof(direntry));	
	dir.flags = inode_allocated | directory | SU | rwx_o | rwx_g | rwx_ot;
	printf("%o\n",dir.flags);	
	memcpy(&sblk,filedata[1], sizeof(struct superblock));	
//	dir.uid = SU;
	dir.size1=3;
	dir.addr[0] = sblk.free[sblk.nfree];
	sblk.nfree--;
	//update the  superblock
	memcpy(filedata[1],&sblk, sizeof(struct superblock));
	//root directory creation	
	entryname.inodenum = 1;
	sprintf(entryname.dirname, ".");
	memcpy(filedata[dir.addr[0]],&entryname,sizeof(direntry));
	memset(&entryname,'\0',sizeof(direntry));
	//parent directory creation
	entryname.inodenum = 1;
	sprintf(entryname.dirname, "..");
	memcpy(filedata[dir.addr[0]],&entryname,sizeof(direntry));
	memset(&entryname,'\0',sizeof(direntry));
	//folder directory creation
	entryname.inodenum = 1;
	sprintf(entryname.dirname, "/");
	memcpy(filedata[dir.addr[0]],&entryname,sizeof(direntry));
	memcpy(filedata[1],&dir,sizeof(struct inode));	
}
 

}	

void main(int argc, char* argv[])
{
char* file_name = (char* )malloc(20*sizeof(char));

unsigned short cnt,free_list[100],free_list1[100];
int filelength,i,j,k;
cnt = maxlocations-1;

sscanf(argv[1],"%s",file_name);
printf("%s\n",file_name);
printf("%d\n",argc);

FILE* fnew = fopen(file_name,"r");
if(fnew == 0)
	{
	printf("file doesn't exist, so creating the file with the same name\n");

	fnew = fopen(file_name,"a");
	
	}
sb1.isize = 40; // maximum number of inodes
sb1.nfree = 99; // maximum number of free list allocated
sb1.free[0] = 42; // first data block

// iniatilization of free block
for(i=1;i<100;i++) {
sb1.free[100-i] = cnt; 
cnt--;
}
printf("%d\n",cnt);
memcpy(filedata[1],&sb1,sizeof(struct superblock));

while(k=cnt/100) {
memset (free_list, 0,100);
free_list[0] = 42 + (10-k);
free_list[1] = 98;
for(i=1;i<99;i++) {
	free_list[100-i] = cnt;
	cnt--;
	}
//for(i=0;i<100;i++)
//printf("%d ",free_list[i]);
//printf("\n");
memcpy(filedata[42 + (9-k)],free_list,100* sizeof(short));
}
j=cnt+1;
memset(free_list,0,100);
free_list[0] = 0;
free_list[1] = cnt+1;
for(i = 0 ;i < free_list[1];i++) {
	free_list[(free_list[1]+1)-i] = cnt;
	cnt --;
}
//for(i=0;i<=j+1;i++)
//printf("%d ",free_list[i]);
memcpy(filedata[51],free_list,100* sizeof(short));
for(j=42;j<52;j++) {
	
		memcpy(free_list1,filedata[j],100* sizeof(short));
		//for(i = 0;i < 100; i++)
		//printf("%d ",free_list1[i]);

	//printf("\n");
}		
	
//printf("%d ", filedata[j][i]);
	
//for(i=0;i<22;i++)
//	printf("%d ",filedata[52][i]);
create_dir("root");
fclose(fnew);
}


