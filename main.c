#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void menu4()
{
    printf("1. Display the hasse diagram\n");
    printf("2. Display the website whose link is available in every website\n");
    printf("3. Display the website which has links of every website\n");
    printf("4. Display the websites that do not have links to any other website except itself\n");
    printf("5. Display the websites which cant be reached from any other website except itself\n");
    printf("6. Given some websites, display the websites which are rechable from all of them\n");
    printf("7. Given some websites, display the websites from which you can reach all those websites\n");
    printf("8. Is this relation an example of lattice?\n");
    printf("9. Return to main menu\n");
}

int choice1(int **mat, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (mat[i][j] == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

int choice2(int **mat, int rows, int columns)
{
    for (int i = 0; i < columns; i++)
    {
        for (int j = i; j < rows; j++)
        {
            if ((mat[j][i] == 0 && mat[i][j] == 1) || (mat[j][i] == 1 && mat[i][j] == 0))
            {
                return 0;
            }
        }
    }
    return 1;
}

int choice3(int **mat, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (mat[i][j])
            {
                for (int k = 0; k < columns; k++)
                {
                    if (mat[j][k] && !mat[i][k])
                    {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

int choice4(int **mat, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (mat[i][j] == 1)
            {
                return 1;
            }
        }
    }
    return 0;
}

int choice5(int **mat, int rows, int columns)
{
    if (choice2(mat, rows, columns))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int choice6(int **mat, int rows, int columns)
{
    for (int i = 0; i < columns; i++)
    {
        for (int j = i + 1; j < rows; j++)
        {
            if ((mat[j][i] == 0 && mat[i][j] == 1) || (mat[j][i] == 1 && mat[i][j] == 0))
            {
                return 1;
            }
        }
    }
    return 0;
}

int choice7(int **mat, int rows, int columns)
{
}

int choice8(int **mat, int rows, int columns)
{
    return (choice1(mat, rows, columns) && choice2(mat, rows, columns) && choice3(mat, rows, columns)) ? (1) : (0);
}

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
    int **mat = malloc((rows - 1) * sizeof(int *));

    for (int i = 0; i < rows - 1; i++)
    {
        mat[i] = malloc((columns - 1) * sizeof(int));
    }
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
    while (1)
    {
        printf("Main Menu");
        printf("\n");
        printf("1. Does every website has a link to itself\n");
        printf("2. Is it possible to always return back to the previous website from the current website in one step?\n");
        printf("3. Does every website has all the links to the website which are reachable from it?\n");
        printf("4. Does there exist any website that contains a link to itself?\n");
        printf("5. Is it impossible to return to the previous website from the current website in one step?\n");
        printf("6. Is it impossible to return to the previous website from the current website in one step (excluding the cases where the current and previous website are the same)\n");
        printf("7. Is it possible to divide the network into multiple pieces such that every website in a piece is reachable from every other website in that piece?\n");
        printf("8. Is this relation an example of poset?\n");
        printf("9. Exit\n");
        int choice;
        scanf("%d", &choice);

        if (choice == 1)
        {
            int ans = choice1(mat, rows - 1, columns - 1);
            if (ans == 0)
            {
                printf("No\n");
                printf("Do you want to visualize how the network will look if we add minimum links to satisfy this property?1 for yes, 0 for no\n");
                int choice_;
                scanf("%d", &choice_);
                if (choice == 1)
                {
                    printf("Hello");
                }
                else
                {
                    continue;
                }
            }
            else
            {
                printf("Yes\n");
                continue;
            }
        }
        else if (choice == 2)
        {
            int ans = choice2(mat, rows - 1, columns - 1);
            if (ans == 0)
            {
                printf("No\n");
                printf("Do you want to visualize how the network will look if we add minimum links to satisfy this property?1 for yes, 0 for no\n");
                int choice_;
                scanf("%d", &choice_);
                if (choice == 1)
                {
                    printf("Hello");
                }
                else
                {
                    continue;
                }
            }
            else
            {
                printf("Yes\n");
                continue;
            }
        }
        else if (choice == 3)
        {
            int ans = choice3(mat, rows, columns);
            if (ans == 0)
            {
                printf("No\n");
                printf("Do you want to visualize how the network will look if we add minimum links to satisfy this property?1 for yes, 0 for no\n");
                int choice_;
                scanf("%d", &choice_);
                if (choice == 1)
                {
                    printf("Hello");
                }
                else
                {
                    continue;
                }
            }
            else
            {
                printf("Yes\n");
                continue;
            }
        }
        else if (choice == 4)
        {
            int ans = choice4(mat, rows, columns);
            if (ans == 0)
            {
                printf("No\n");
                printf("Do you want to visualize how the network will look if we add minimum links to satisfy this property?1 for yes, 0 for no\n");
                int choice_;
                scanf("%d", &choice_);
                if (choice == 1)
                {
                    printf("Hello");
                }
                else
                {
                    continue;
                }
            }
            else
            {
                printf("Yes\n");
                continue;
            }
        }
        else if (choice == 5)
        {
            int ans = choice5(mat, rows, columns);
            if (ans == 0)
            {
                printf("No\n");
                printf("Do you want to visualize how the network will look if we add minimum links to satisfy this property?1 for yes, 0 for no\n");
                int choice_;
                scanf("%d", &choice_);
                if (choice == 1)
                {
                    printf("Hello");
                }
                else
                {
                    continue;
                }
            }
            else
            {
                printf("Yes\n");
                continue;
            }
        }
        else if (choice == 6)
        {
            int ans = choice6(mat, rows, columns);
            if (ans == 0)
            {
                printf("No\n");
                printf("Do you want to visualize how the network will look if we add minimum links to satisfy this property?1 for yes, 0 for no\n");
                int choice_;
                scanf("%d", &choice_);
                if (choice == 1)
                {
                    printf("Hello");
                }
                else
                {
                    continue;
                }
            }
            else
            {
                printf("Yes\n");
                continue;
            }
        }
        else if (choice == 7)
        {
            int ans = choice7(mat, rows, columns);
            if (ans == 0)
            {
                printf("No\n");
                printf("Do you want to visualize how the network will look if we add minimum links to satisfy this property?1 for yes, 0 for no\n");
                int choice_;
                scanf("%d", &choice_);
                if (choice == 1)
                {
                    printf("Hello");
                }
                else
                {
                    continue;
                }
            }
            else
            {
                printf("Yes\n");
                continue;
            }
        }
        else if (choice == 8)
        {
            int ans = choice8(mat, rows, columns);
            if (ans == 0)
            {
                printf("No\n");
                // printf("Do you want to visualize how the network will look if we add minimum links to satisfy this property?1 for yes, 0 for no\n");
                // int choice_;
                // scanf("%d", &choice_);
                // if (choice == 1)
                // {
                //     printf("Hello");
                // }
                // else
                // {
                //     continue;
                // }
            }
            else
            {
                printf("Yes\n");
                // continue;
            }
        }
        else if (choice == 9)
        {
            break;
        }
    }
    return 0;
}
