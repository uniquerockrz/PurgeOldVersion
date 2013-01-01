#include <stdio.h>
#include <string.h>
#include <ctype.h>
char buffer[10000][200], choppedfilename[10000][200]; // to store all the filenames in filelist file
int main(int argc, char *argv[])
{
    char filename[20];
    int lines;
    int copytobuffer(char *);
    void findduplicates(int);
    if(argc==1){
        printf("Please enter filelist\'s filename : ");
        scanf("%s", filename);
    }
    else
        strcpy(filename, argv[1]);
    lines=copytobuffer(filename);
    if(lines==-1)
        return 0;
    findduplicates(lines);
    return 0;
}
int copytobuffer(char filename[20]){
    int n=0;
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("Cannot open file!\n");
        return -1;
    }
    while(fgets(buffer[n],200,fp)!=NULL)
        n++;
    fclose(fp);
return n;
}
void findduplicates(int files){
    int i, l;
    char str[200];
    int chop(char *, char *);
    void finddup(int);
    for(i=0;i<=files;i++){
        l=chop(buffer[i], str);
        strncpy(choppedfilename[i], str, l);
        choppedfilename[i][l+1]='\0';
    }
    finddup(files);
}
int chop(char fullfilename[200], char dest[100]){
    int i;
    for(i=0;i<strlen(fullfilename);i++){
        if(fullfilename[i]=='-' && isdigit(fullfilename[i+1]))
            break;
    }
    strncpy(dest, fullfilename, i);
    return i;
}
void finddup(int files){
    int i, j;
    char str[100];
    int strcompare(char *, char *);
    void cutslashn(char *);
    i=files;
    FILE *fp;
    fp=fopen("todo.sh","w");
    fputs("mkdir oldfiles\n",fp);
    while(i>0){
        j=i-1;
        if(strcompare(choppedfilename[i],choppedfilename[j])){
                fputs("mv ", fp);
                cutslashn(buffer[j]);
                strcpy(str, buffer[j]);
                fputs(str, fp);
                fputs(" oldfiles\n", fp);
                choppedfilename[j][0]='\0';
        }
   i--;
   }
   fclose(fp);
}
int strcompare(char str1[200], char str2[200]){
    int i=0;
    if(str1[0]=='\0' || str2[0]=='\0')
        return 0;
    else{
        while(str1[i]!='\0'){
            if(str1[i]!=str2[i])
                return 0;
            i++;
        }
    }
    return 1;
}
void cutslashn(char str[200]){
    str[strlen(str)-1]='\0';
}
