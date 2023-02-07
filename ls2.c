#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ls2.h"

/**
 * @brief counts the number of items in a directory not including . and ..
 * @return the number of items found
 */
int countls2(char *path)
{
    DIR *d = opendir(path);
    struct dirent *result;

    // find the total number of items in the path
    int totalResults = 0;
    while ((result = readdir(d)) != NULL)
    {
        totalResults++;
    }

    // close the directoy
    closedir(d);

     // remove two from total results for . and ..
    totalResults -= 2;
    return totalResults;
}

/**
 * returns the item in the folder given at that index
 */
char *ls2(char *path, int index)
{
 

    // repeat
    // get all files in the path
    DIR *d = opendir(path);
    struct dirent *result;
    int pos = 0;

    char* outVal;

    while ((result = readdir(d)) != NULL)
    {

        char *name = result->d_name;
        if (strcmp(name, ".") && strcmp(name, ".."))
        {
            if(pos == index){
                outVal = name;
                break;
            }
            pos++;
        }
        else{
          
        }
    }

    // close the directoy
    closedir(d);

    return outVal;


}