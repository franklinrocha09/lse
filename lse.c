/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lse.c // lsE
 * Version: 0.5 artigo LinuxMachine
 * Author: Franklin S Rocha
 * Programa: lista diretórios e arquivos
 * Created on 28 de dezembro de 2020, 14:21
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[00m"

int main(int argc, char **argv) {
            
    char ver[]="0.5";
    DIR *folder;
    struct dirent *entry;
    struct stat entry_stat;
    char path[512] = ".";
    int entries = 0; int files = 0;
    long long files_size = 0;
    
    printf(ANSI_COLOR_RED"lsE v%s  "ANSI_COLOR_RESET,ver);
    
    if (argc == 2) strcpy(path, argv[1]);
  
    folder = opendir(path);
    if (folder != NULL)
        printf("Path: %s\n\n", path);
    else {
        puts("Path: Incorrect!\n");
        return(1);
    }
                                  
    while ( entry = readdir(folder) ) {
        entries++;
        stat(entry->d_name,&entry_stat);
        if ( S_ISDIR(entry_stat.st_mode) )
            printf(ANSI_COLOR_BLUE"%-24s %s\n"ANSI_COLOR_RESET, "<DIR>", entry->d_name);
        else {
            printf("%s %18ld %s \n", " <f> ", entry_stat.st_size, entry->d_name);
            files++;
            files_size += entry_stat.st_size;
        }
    }
    
    printf(ANSI_COLOR_GREEN"\n>>> Entry(s)-> %d | File(s)-> %d Size %ld bytes\n"ANSI_COLOR_RESET, entries, files, files_size);
    closedir(folder);
    
    return (EXIT_SUCCESS);
}