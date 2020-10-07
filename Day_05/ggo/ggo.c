#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


int main(int argc, char* argv[]){
    char *path = argv[argc-1]; // 경로
    // 파일 목록 읽기
    DIR *dir;
    struct dirent *ent;
    dir = opendir(path);
    char* srcs = "";
    if(dir == NULL) printf("잘못된 경로\n");
    else {
        while((ent = readdir(dir))!=NULL) {
            char *ptr = strstr(ent->d_name,".c");
            if(ptr != NULL){
                if(srcs == ""){
                    srcs = ent->d_name;
                } else {
                    strcat(srcs," ");
                    strcat(srcs, ent->d_name);
                }
                // printf("%s\n",srcs);
            }
        }
        closedir (dir);
    }
    printf("%s\n",srcs);
    // CMakeLists.txt 작성
    char touch[255];
    sprintf(touch,"touch %sCMakeLists.txt",path);
    system(touch);
    FILE *fp = fopen("temp.txt","wb");
    fprintf(fp,"ADD_EXECUTABLE(ggo %s)",srcs);
    fclose(fp);
    char cat[255];
    sprintf(cat,"cat ./temp.txt >> %sCMakeLists.txt",path);
    system(cat);
    // Cmake
    char cmake[255];
    sprintf(cmake,"cmake %sCMakeLists.txt",path);
    system(cmake);
    // make
    char make[255];
    sprintf(make,"make -C %s",path);
    system(make);
    // exe
    char exe[255];
    sprintf(exe,"%sggo",path);
    system(exe);
    return 0;
}
