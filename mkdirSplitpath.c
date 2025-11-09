#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern struct NODE* root;
extern struct NODE* cwd;

struct NODE* findChild(struct NODE* parent, const char* name) {
    struct NODE* curr = parent->childPtr;
    while(curr) {
        if (strcmp(curr->name, name) == 0) {
            return curr;
        }
        curr = curr-> siblingPtr;
    }
    return NULL;
}


//make directory
void mkdir(char pathName[]){

    if(strcmp(pathName, "/") == 0 ) {
        printf("MKDIR ERROR: no path provided\n");
        return;
    }

    char dirName[128];
    char baseName[128];
    struct NODE* parent = splitPath(pathName, baseName, dirName);

    if (parent == NULL) return;

    if (strcmp(baseName, "") == 0) {
        printf("MKDIR ERROR: no path provided\n");
        return;
    }

    struct NODE* existing = findChild(parent, baseName);
    if (existing != NULL) {
        printf("MKDIR ERROR: directory %s already exists\n", pathName);
        return;
    }

    struct NODE* new = (struct NODE*) malloc(sizeof(struct NODE));
    strcpy(new->name, baseName);
    new->fileType = 'D';
    new->childPtr = NULL;
    new->siblingPtr = NULL;
    new->parentPtr = parent;

    if (parent-> childPtr == NULL) {
        parent-> childPtr = new;
    } else {
        struct NODE* temp = parent->childPtr;
        while (temp-> siblingPtr != NULL) {
            temp = temp->siblingPtr;
        }
        temp->siblingPtr = new;
    }

    printf("MKDIR SUCCESS: node %s successfully created\n", pathName);
    return;
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){

    // TO BE IMPLEMENTED
    // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
    // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
    // SEE THE PROVIDED SOLUTION EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

    if(strcmp(pathName, "/") == 0) {
        strcpy(dirName, "/");
        strcpy(baseName, "");
        return root;
    }

    char* lastSlash = strrchr(pathName, '/');

    if (lastSlash == NULL) {
        strcpy(dirName, "");
        strcpy(baseName, pathName);
        return cwd;
    }

    int dirLen = lastSlash - pathName;
    if(dirLen == 0) {
        strcpy(dirName, "/");
    } else {
        strncpy(dirName, pathName, dirLen);
        dirName[dirLen] = '\0';
    }

    strcpy(baseName, lastSlash + 1);

    if (strcmp(dirName, "") == 0) {
        return cwd;
    }

    struct NODE* current; 
    if (dirName[0] == '/') {
        current = root;
    } else {
        current = cwd;
    }

    char temp[128];
    strcpy(temp, dirName);

    char* token = strtok(temp, "/");
    while ( token != NULL ) {
        struct NODE* next = findChild(current, token);
        if (!next || next->fileType != 'D') {
            printf("ERROR: directory %s does not exist\n", token);
            return NULL;
        }
        current = next;
        token = strtok(NULL, "/");
    }

    return current;
}
