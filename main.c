#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    char buffer[1024];
    FILE *fp = fopen("SampleInput.csv", "r");
    if (fp == NULL)
    {
        printf("Error opening file");
        return 0;
    }
    int rows = 0;
    while (fgets(buffer, 1024, fp) != NULL)
    {
        rows++;
    }
    char *tok = strtok(buffer, ",");
    int columns = 0;
    while (tok != NULL)
    {
        columns++;
        tok = strtok(NULL, ",");
    }
    int mat[rows - 1][columns - 1];
    fclose(fp);
    fp = fopen("SampleInput.csv", "r");
    int counter = 0;
    while (fgets(buffer, 1024, fp) != NULL)
    {
        counter++;
        if (counter == 1)
        {
            continue;
        }
        else
        {
            char *tken;
            tken = strtok(buffer, ",");
            int i = 0;
            while (tken != NULL)
            {
                i++;
                if (i == 1)
                {
                    tken = strtok(NULL, ",");
                    continue;
                }
                else
                {
                    mat[counter - 2][i - 2] = atoi(tken);
                    tken = strtok(NULL, ",");
                }
            }
        }
    }
    //Print the 2d array parsed from the SampleInput.csv file
    // for (int i = 0; i < rows - 1; i++)
    // {
    //     for (int j = 0; j < columns - 1; j++)
    //     {
    //         printf("%d", mat[i][j]);
    //         printf(" ");
    //     }
    //     printf("\n");
    // }
    printf("Main Menu");
    printf("\n");
    printf("1. Does every website has a link to itself\n");
    printf("2. Is it possible to always return back to the previous website from the current website in one step?\n");
    printf("3. Does every website has all the links to the website which are reachable from it?\n");
    printf("4. Does there exist any website that contains a link to itself?\n");
    printf("5. Is it impossible to return to the previous website from the current website in one step?\n")
        printf("6. Is it impossible to return to the previous website from the current website in one step (excluding the cases where the current and previous website are the same)\n");
    printf("7. Is it possible to divide the network into multiple pieces such that every website in a piece is reachable from every other website in that piece?\n");
    printf("8. Is thsi relation an example of poset?\n")
        printf("9. Exit\n");

    return 0;
}