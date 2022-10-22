#include <asm/segment.h>//��get_fs_XXX��ͷ�ļ�
#include <errno.h>
#include<string.h>

char my_name[24];
int sys_iam(const char *name){
	printk("input myname..\n");
	char tem[25];
	int i=0;
	while(i<23){
		tem[i]=get_fs_byte(name+i);
		//printk("%d,%c\n",i,tem[i]);
		if(tem[i++]=='\0')break;
	}
	if(i>23){
		errno = EINVAL;
        i = -1;
	}
	else{
		strcpy(my_name,tem);
	}
	//printk("%s\n",tem);
	//printk("%s\n",my_name);
	return i;
} 
int sys_whoami(char* name, unsigned int size){
	int length = strlen(my_name);
	//printk("%s\n",my_name);
	if(length>size){
		errno = EINVAL;
		return -1;
	}
	int i;
	for( i=0;i<length;i++){
		put_fs_byte(my_name[i],name+i);
	}
	return length;
}
