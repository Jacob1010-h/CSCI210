#include "types.h"

struct NODE *root;
struct NODE *cwd;
char *cmd[] = {"mkdir", "rmdir", "ls", "cd", "pwd", "touch", "rm",
 "menu", "tree", "quit", NULL};

/*
Uses the user's input to determine what command will be used
Called by the switch case in main
*/
int findCMD(char* command){
    int i = 0;
    while(cmd[i]){
        if(!strcmp(command, cmd[i])){
            return i;
        }
        i++;
    }
    return -1;
}

/*
Initializes the root node and
sets the current working directory, "cwd", to the root
*/
void initialize(){
    root = (struct NODE *)malloc(sizeof(struct NODE));
    root->parentPtr = NULL;
    root->siblingPtr = NULL;
    strcpy(root->name, "/");
    root->fileType = 'D';
    root->childPtr = NULL;
    cwd = root;
}

int main(){

    initialize();

    int index;
    char line[128];
    char command[16];
    char path[64];

    //this while loop runs until 'quit' is entered
    while(1){
        strcpy(path, "/");
        fprintf(stderr,"input a command line : ");
        fgets(line, 128, stdin);
        line[strlen(line)-1] = 0;
        sscanf(line, "%s %s", command, path);
	// note that when no path is entered it will default to "/"
        index = findCMD(command);

        switch(index){
            case 0: mkdir(path); break;
            case 1: rmdir(path); break;
            case 2: ls(path); break;
            case 3: cd(path); break;
            case 4: pwd(); printf("\n"); break;
            case 5: touch(path); break;
            case 6: rm(path); break;
            case 7: menu(); break;
            case 8: printTree(); break;
            case 9: return quit();
            default: printf("invalid command %s\n", command);
        }
    }
}

//prints all possible commands that the user can use
void menu(){
    printf("Commands:\nmkdir [pathname], touch [pathname], rmdir [pathname], rm [pathname], ls [pathname], cd [pathname], pwd, menu, print, quit\n");
}

//prints the file system in a tree-like format
void printTree(){
    printf("%s", root->name);

    struct NODE *directory = root->childPtr;
    printf("\n");
    printHelper(directory, 0);
}

//recursive function helper to print the tree
void printHelper(struct NODE *directory, int depth){

    //iterates over siblings
    while(directory != NULL){

        struct NODE *temp = directory;
        char spacing[128] = "";
        char t[128] = "";

        //depth is how deep the file/directory is from root
        for(int i = 0; i < depth; i++){
            if(temp->parentPtr->siblingPtr == NULL){
                strcpy(t, "    ");
            }
            else{
                strcpy(t, "|   ");
            }

            strcat(t, spacing);
            strcpy(spacing, t);

            temp = temp->parentPtr;
        }

        printf("%s", spacing);

        if(directory->siblingPtr == NULL){
		printf("|   \n"); 
            
		struct NODE *temp = directory;
		char spacing[128] = "";
		char t[128] = "";

		for(int i = 0; i < depth; i++){
			if(temp->parentPtr->siblingPtr == NULL){
			strcpy(t, "    ");
			}
			else{
				strcpy(t, "|   ");
			}
	
			strcat(t, spacing);
			strcpy(spacing, t);

			temp = temp->parentPtr;
		}

		printf("%s", spacing);
            
		printf("`---");
        }
        else{
            printf("|---");
        }


        printf("%s\n", directory->name);
        if(directory->childPtr != NULL){
            printHelper(directory->childPtr, depth + 1);
        }

        directory = directory->siblingPtr;
    }  
}

//quits the program
int quit(){ return 0; }
