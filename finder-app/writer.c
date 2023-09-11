#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <libgen.h>

int main(int argc, char **argv) {
    //open the logger connection and write to it
    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);
    // Check args
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *writefile = argv[1];
    char *writestr = argv[2];

    //copy the original writefile 
    char *writefile_copy = strdup(writefile);
    //print the args
    printf("writefile: %s\n", writefile);
    printf("writestr: %s\n", writestr);

   // Extract the directory path from writefile
    char *dirpath = strdup(dirname(writefile));

    // Create the directory if it does not exist
    struct stat st;
    if (stat(dirpath, &st) == -1) {
        if (mkdir(dirpath, 0777) == -1) {
            fprintf(stderr, "Error creating directory\n");
            syslog(LOG_ERR, "Error creating directory %s", dirpath);
            exit(EXIT_FAILURE);
        } else {
            printf("Directory created successfully\n");
        }
    }

    syslog(LOG_INFO, "Writing string %s to file %s", writestr, writefile);
    printf("Writing string %s to file %s\n", writestr, writefile);
    // open and create the file if it does not exist
    FILE *fp = fopen(writefile_copy, "w");

    if (fp == NULL) {
        fprintf(stderr, "Error: Could not open %s\n", writefile_copy);
        syslog(LOG_ERR, "Error: Could not open %s", writefile_copy);
        exit(EXIT_FAILURE);
    }
    
    //write the string to the file
    if (fprintf(fp, "%s\n", writestr) < 0) {
        fprintf(stderr, "Error: Could not write to %s\n", writefile_copy);
        syslog(LOG_ERR, "Error: Could not write to %s", writefile_copy);
        exit(EXIT_FAILURE);
    }

    //check if the file was written successfully
    if (errno != 0) {
        fprintf(stderr, "Error: Could not write to %s\n", writefile_copy);
        syslog(LOG_ERR, "Error: Could not write to %s", writefile_copy);
        exit(EXIT_FAILURE);
    }

    printf("Text written to %s\n", writefile_copy);
    exit(EXIT_SUCCESS);
}