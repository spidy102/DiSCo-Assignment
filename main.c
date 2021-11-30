#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "visualiser.c"

char **websites;
int **mat;
int rows = 0;
int columns = 0;

void copymat(int newmat[rows][columns])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            newmat[i][j] = mat[i][j];
        }
    }
}
void menu4();
void tocsv(int newmat[rows][columns])
{
    FILE *fp = fopen("Output.csv", "w");
    for (int i = 0; i < rows; i++)
    {
        fprintf(fp, ",%s", websites[i]);
    }
    fprintf(fp, "\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (!j)
            {
                fprintf(fp, "%s", websites[i]);
            }
            fprintf(fp, ",%d", newmat[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

int is_a_website(char *website)
{
    for (int i = 0; i < rows; i++)
    {
        if (strcmp(websites[i], website) == 0)
        {
            return i + 1;
        }
    }
    return 0;
}

int checkAlreadyPresent(char **arr, char *target, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        if (strncmp(arr[i], target, strlen(target)) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int populateReachableWebsites(int *websitesList, char **reachableWebsites, int len, int current)
{
    // for (int i = 0; i < rows; i++)
    // {
    //     if (strcmp(websites[i], website) == 0)
    //     {
    //         for (int j = 0; j < columns; j++)
    //         {
    //             if (mat[i][j])
    //             {
    //                 if (!checkAlreadyPresent(reachableWebsites, websites[j], current))
    //                 {
    //                     reachableWebsites[current] = malloc((strlen(websites[j])) * sizeof(char));
    //                     reachableWebsites[current] = websites[j];
    //                     current++;
    //                 }
    //             }
    //         }
    //     }
    // }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (!mat[websitesList[j]][i])
            {
                break;
            }
            if (j == len - 1)
            {
                reachableWebsites[current] = malloc((strlen(websites[i])) * sizeof(char));
                reachableWebsites[current] = websites[i];
                current++;
            }
        }
    }

    return current;
}

int populateReachableFromWebsites(int *websitesList, char **reachableWebsites, int len, int current)
{
    // for (int i = 0; i < columns; i++)
    // {
    //     if (strcmp(websites[i], website) == 0)
    //     {
    //         for (int j = 0; j < rows; j++)
    //         {
    //             if (mat[j][i])
    //             {
    //                 if (!checkAlreadyPresent(reachableWebsites, websites[j], current))
    //                 {
    //                     reachableWebsites[current] = malloc((strlen(websites[j])) * sizeof(char));
    //                     reachableWebsites[current] = websites[j];
    //                     current++;
    //                 }
    //             }
    //         }
    //     }
    // }
    // return current;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (!mat[i][websitesList[j]])
            {
                break;
            }
            if (j == len - 1)
            {
                reachableWebsites[current] = malloc((strlen(websites[i])) * sizeof(char));
                reachableWebsites[current] = websites[i];
                current++;
            }
        }
    }

    return current;
}

int checkLattice()
{
    int *upperBounds;
    int countU = 0;
    int *lowerBounds;
    int countL = 0;
    int foundLeastUpperBound = 0;
    int foundGreatestLowerBound = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = i + 1; j < rows; j++)
        {
            lowerBounds = malloc(rows * sizeof(int));
            countL = 0;
            for (int k = 0; k < rows; k++)
            {
                if (mat[k][i] && mat[k][j])
                {
                    lowerBounds[countL] = k;
                    countL++;
                }
            }

            upperBounds = malloc(rows * sizeof(int));
            countU = 0;
            for (int k = 0; k < rows; k++)
            {
                if (mat[i][k] && mat[j][k])
                {
                    upperBounds[countU] = k;
                    countU++;
                }
            }

            for (int k = 0; k < countL; k++)
            {
                for (int l = 0; l < countL; l++)
                {
                    if (k != l)
                    {
                        if (!mat[lowerBounds[l]][lowerBounds[k]])
                        {
                            break;
                        }
                    }
                    if (l == countL - 1)
                    {
                        foundGreatestLowerBound = 1;
                        k = countL;
                        break;
                    }
                }
            }
            for (int k = 0; k < countU; k++)
            {
                for (int l = 0; l < countU; l++)
                {
                    if (k != l)
                    {
                        if (!mat[upperBounds[k]][upperBounds[l]])
                        {
                            break;
                        }
                    }
                    if (l == countU - 1)
                    {
                        foundLeastUpperBound = 1;
                        k = countU;
                        break;
                    }
                }
            }

            if (!foundGreatestLowerBound || !foundLeastUpperBound)
            {
                return 0;
            }
            else
            {
                foundGreatestLowerBound = 0;
                foundLeastUpperBound = 0;
            }
        }
    }
    return 1;
}

void handleCase1(char *websiteA, char *websiteB)
{
    int indexA = -1;
    int indexB = -1;
    for (int i = 0; i < rows; i++)
    {
        if (strcmp(websiteA, websites[i]) == 0)
        {
            indexA = i;
        }
        if (strcmp(websiteB, websites[i]) == 0)
        {
            indexB = i;
        }
        if (indexA != -1 && indexB != -1)
        {
            break;
        }
    }

    int *reachableFromAB = malloc(rows * sizeof(int));
    int count = 0;
    for (int i = 0; i < columns; i++)
    {
        if (mat[indexA][i] == 1 && mat[indexB][i] == 1)
        {
            reachableFromAB[count] = i;
            count++;
        }
    }

    int *answer = malloc(rows * sizeof(int));
    int answerCount = 0;
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (!mat[reachableFromAB[i]][reachableFromAB[j]])
            {
                break;
            }
            if (j == count - 1)
            {
                answer[answerCount] = reachableFromAB[i];
                answerCount++;
            }
        }
    }

    if (answerCount == 0)
    {
        printf("\nNo such wesbites exist\n");
    }
    else
    {
        printf("\nThe following are the websites which satisfy the properties:\n");
        for (int i = 0; i < answerCount; i++)
        {
            printf("%s\n", websites[answer[i]]);
        }
    }
    return;
}

void handleCase2(char *websiteA, char *websiteB)
{
    int indexA = -1;
    int indexB = -1;
    for (int i = 0; i < rows; i++)
    {
        if (strcmp(websiteA, websites[i]) == 0)
        {
            indexA = i;
        }
        if (strcmp(websiteB, websites[i]) == 0)
        {
            indexB = i;
        }
        if (indexA != -1 && indexB != -1)
        {
            break;
        }
    }

    int *reachableToAB = malloc(rows * sizeof(int));
    int count = 0;
    for (int i = 0; i < rows; i++)
    {
        if (mat[i][indexA] == 1 && mat[i][indexB] == 1)
        {
            reachableToAB[count] = i;
            count++;
        }
    }

    int *answer = malloc(rows * sizeof(int));
    int answerCount = 0;
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (!mat[reachableToAB[j]][reachableToAB[i]])
            {
                break;
            }
            if (j == count - 1)
            {
                answer[answerCount] = reachableToAB[i];
                answerCount++;
            }
        }
    }

    if (answerCount == 0)
    {
        printf("\nNo such wesbites exist\n");
    }
    else
    {
        printf("\nThe following are the websites which satisfy the properties:\n");
        for (int i = 0; i < answerCount; i++)
        {
            printf("%s\n", websites[answer[i]]);
        }
    }
    return;
}

int getLUB(int a, int b)
{
    int *upperBounds = malloc(rows * sizeof(int));
    int countU = 0;
    for (int k = 0; k < rows; k++)
    {
        if (mat[a][k] && mat[b][k])
        {
            upperBounds[countU] = k;
            countU++;
        }
    }
    for (int k = 0; k < countU; k++)
    {
        for (int l = 0; l < countU; l++)
        {
            if (k != l)
            {
                if (!mat[upperBounds[k]][upperBounds[l]])
                {
                    break;
                }
            }
            if (l == countU - 1)
            {
                return upperBounds[k];
            }
        }
    }
    return 0;
}

int getGLB(int a, int b)
{
    int *lowerBounds = malloc(rows * sizeof(int));
    int countL = 0;
    for (int k = 0; k < rows; k++)
    {
        if (mat[k][a] && mat[k][b])
        {
            lowerBounds[countL] = k;
            countL++;
        }
    }
    for (int k = 0; k < countL; k++)
    {
        for (int l = 0; l < countL; l++)
        {
            if (k != l)
            {
                if (!mat[lowerBounds[l]][lowerBounds[k]])
                {
                    break;
                }
            }
            if (l == countL - 1)
            {
                return lowerBounds[k];
            }
        }
    }
    return 0;
}

int handleCase3()
{
    for (int a = 0; a < rows; a++)
    {
        for (int b = a + 1; b < rows; b++)
        {
            for (int c = b + 1; c < rows; c++)
            {
                int res1 = getLUB(getGLB(a, b), getGLB(a, c));
                int res2 = getGLB(a, getLUB(b, c));
                if (res1 == res2)
                {
                    int res3 = getLUB(a, getGLB(b, c));
                    int res4 = getGLB(getLUB(a, b), getLUB(b, c));
                    if (res3 != res4)
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void reflexive_closure(int newmat[rows][columns])
{
    for (int i = 0; i < rows; i++)
    {
        newmat[i][i] = 1;
    }
}

void symmetric_closure(int newmat[rows][columns])
{
    for (int i = 0; i < columns; i++)
    {
        for (int j = i + 1; j < rows; j++)
        {
            if (newmat[i][j] || newmat[j][i])
            {
                newmat[j][i] = 1;
                newmat[i][j] = 1;
            }
        }
    }
}

void transitive_closure(int newmat[rows][columns])
{
    for (int k = 0; k < rows; k++)
    {
        for (int i = 0; i < columns; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                newmat[i][j] = newmat[i][j] | (newmat[i][k] & newmat[k][j]);
            }
        }
    }
}

void menu2(int choice)
{
    printf("Do you want to visualize how the network will look if we add minimum links to satisfy this property? 1 for yes, 0 for no\n");
    int cont;
    scanf("%d", &cont);
    if (cont)
    {
        switch (choice)
        {
        case 1:
        {
            int newmat[rows][columns];
            copymat(newmat);
            reflexive_closure(newmat);
            tocsv(newmat);
            plot("Output.csv");
        }
        break;
        case 2:
        {
            int newmat[rows][columns];
            copymat(newmat);
            symmetric_closure(newmat);
            tocsv(newmat);
            plot("Output.csv");
        }
        break;
        case 3:
        {
            int newmat[rows][columns];
            copymat(newmat);
            transitive_closure(newmat);
            tocsv(newmat);
            plot("Output.csv");
        }
        break;
        case 7:
        {
            int newmat[rows][columns];
            copymat(newmat);
            reflexive_closure(newmat);
            symmetric_closure(newmat);
            transitive_closure(newmat);
            tocsv(newmat);
            plot("Output.csv");
        }
        }
    }
}

int menu3()
{
    printf("Do you want to know the nodes in each piece? 1 for yes, 0 for no\n");
    int cont;
    scanf("%d", &cont);
    if (cont)
    {
        int piece = 1;
        int alloted[rows];
        memset(alloted, 0, rows * sizeof(int));
        for (int i = 0; i < rows; i++)
        {
            if (!alloted[i])
            {
                alloted[i] = 1;
                printf("Piece %d: %s", piece, websites[i]);
                for (int j = i + 1; j < columns; j++)
                {
                    if (mat[i][j])
                    {
                        alloted[j] = 1;
                        printf(" %s", websites[j]);
                    }
                }
                printf("\n");
                piece++;
            }
        }
    }
    return cont;
}

void make_irreflexive(int newmat[rows][columns])
{
    for (int i = 0; i < rows; i++)
    {
        newmat[i][i] = 0;
    }
}

void remove_transitivity(int newmat[rows][columns])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (newmat[i][j])
            {
                for (int k = 0; k < rows; k++)
                {
                    if (newmat[k][j] && newmat[i][k])
                    {
                        newmat[i][j] = 0;
                        break;
                    }
                }
            }
        }
    }
}

void menu5()
{
    printf("1. Given two websites A and B, display the website which is reachable by both A and B and can also reach to all such websites that both A and B can reach.\n");
    printf("2. Given two websites A and B, display the website which can reach to both A and B and is also reachable from all such websites which can reach to both A and B.\n");
    printf("3. Is the lattice distributive?\n");
    printf("4. Return to menu 4\n");
    int choice;
    scanf("%d", &choice);
    getchar();
    switch (choice)
    {
    case 1:
    {
        printf("Enter both the websites:\n");
        char *websiteA = malloc(1024 * sizeof(char));
        char *websiteB = malloc(1024 * sizeof(char));
        fgets(websiteA, 1024, stdin);
        websiteA[strcspn(websiteA, "\n")] = 0;
        while (!is_a_website(websiteA))
        {
            printf("Please enter a valid website\n");
            fgets(websiteA, 1024, stdin);
            websiteA[strcspn(websiteA, "\n")] = 0;
        }
        fgets(websiteB, 1024, stdin);
        websiteB[strcspn(websiteB, "\n")] = 0;
        while (!is_a_website(websiteB))
        {
            printf("Please enter a valid website\n");
            fgets(websiteB, 1024, stdin);
            websiteB[strcspn(websiteB, "\n")] = 0;
        }
        handleCase1(websiteA, websiteB);
    }
    case 2:
    {
        printf("Enter both the websites:\n");
        char *websiteA = malloc(1024 * sizeof(char));
        char *websiteB = malloc(1024 * sizeof(char));
        fgets(websiteA, 1024, stdin);
        websiteA[strcspn(websiteA, "\n")] = 0;
        while (!is_a_website(websiteA))
        {
            printf("Please enter a valid website\n");
            fgets(websiteA, 1024, stdin);
            websiteA[strcspn(websiteA, "\n")] = 0;
        }
        fgets(websiteB, 1024, stdin);
        websiteB[strcspn(websiteB, "\n")] = 0;
        while (!is_a_website(websiteB))
        {
            printf("Please enter a valid website\n");
            fgets(websiteB, 1024, stdin);
            websiteB[strcspn(websiteB, "\n")] = 0;
        }
        handleCase2(websiteA, websiteB);
    }
    break;
    case 3:
    {
        int res = handleCase3();
        if (res)
        {
            printf("\nYes\n");
        }
        else
        {
            printf("\nNo\n");
        }
    }
    break;
    case 4:
    {
        menu4();
    }
    }
}

void menu4()
{
    printf("1. Display the hasse diagram.\n");
    printf("2. Display the website whose link is available in every website.\n");
    printf("3. Display the website which has links of every website.\n");
    printf("4. Display the websites that do not have links to any other website except itself.\n");
    printf("5. Display the websites which can't be reached from any other website except itself.\n");
    printf("6. Given some websites, display the websites which are rechable from all of them.\n");
    printf("7. Given some websites, display the websites from which you can reach all those websites.\n");
    printf("8. Is this relation an example of lattice?\n");
    printf("9. Return to Main Menu\n");

    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
    {
        int newmat[rows][columns];
        copymat(newmat);
        make_irreflexive(newmat);
        remove_transitivity(newmat);
        tocsv(newmat);
        plot("Output.csv");
    }
    break;
    case 2:
    {
        for (int i = 0; i < columns; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                if (!mat[j][i])
                {
                    break;
                }
                if (j == rows - 1)
                {
                    printf("%s ", websites[i]);
                }
            }
        }
        printf("\n");
    }
    break;
    case 3:
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (!mat[i][j])
                {
                    break;
                }
                if (j == columns - 1)
                {
                    printf("%s ", websites[i]);
                }
            }
        }
        printf("\n");
    }
    break;
    case 4:
    {
        for (int i = 0; i < rows; i++)
        {
            if (mat[i][i])
            {
                for (int j = 0; j < columns; j++)
                {
                    if (j != i && mat[i][j])
                    {
                        break;
                    }
                    if (j == columns - 1)
                    {
                        printf("%s ", websites[i]);
                    }
                }
            }
        }
        printf("\n");
    }
    break;
    case 5:
    {
        for (int i = 0; i < columns; i++)
        {
            if (mat[i][i])
            {
                for (int j = 0; j < rows; j++)
                {
                    if (j != i && mat[j][i])
                    {
                        break;
                    }
                    if (j == rows - 1)
                    {
                        printf("%s ", websites[i]);
                    }
                }
            }
        }
        printf("\n");
    }
    break;
    case 6:
    {
        char *website;
        printf("Enter the number of websites:");
        int x;
        scanf("%d", &x);
        getchar();
        char **reachableWebsites = malloc(rows * sizeof(char *));
        int current = 0;
        int *enteredWebsites = malloc(rows * sizeof(int));
        int counter = 0;
        for (int i = 0; i < x; i++)
        {
            website = malloc(1024 * sizeof(char));
            fgets(website, 1024, stdin);
            website[strcspn(website, "\n")] = 0;
            int res = is_a_website(website);
            if (res != 0)
            {
                enteredWebsites[counter] = res - 1;
                counter++;
            }
            else
            {
                printf("Website does not exist, please input another:");
                i--;
            }
        }

        current = populateReachableWebsites(enteredWebsites, reachableWebsites, counter, current);
        printf("\nThe websites are:\n");
        for (int i = 0; i < current; i++)
        {
            printf("%s", reachableWebsites[i]);
            printf("\n");
        }
        printf("\n");
    }
    break;
    case 7:
    {
        char *website = malloc(1024 * sizeof(char));
        printf("Enter the number of websites:");
        int x;
        scanf("%d", &x);
        getchar();
        char **reachableWebsites = malloc(rows * sizeof(char *));
        int *enteredWebsites = malloc(rows * sizeof(int));
        int counter = 0;
        int current = 0;
        for (int i = 0; i < x; i++)
        {
            realloc(website, 1024 * sizeof(char));
            fgets(website, 1024, stdin);
            website[strcspn(website, "\n")] = 0;
            int res = is_a_website(website);
            if (res != 0)
            {
                enteredWebsites[counter] = res - 1;
                counter++;
            }
            else
            {
                printf("Website does not exist, please input another:");
                i--;
            }
        }
        current = populateReachableFromWebsites(enteredWebsites, reachableWebsites, counter, current);

        printf("\nThe websites are:\n");
        for (int i = 0; i < current; i++)
        {
            printf("%s", reachableWebsites[i]);
            printf("\n");
        }
        printf("\n");
    }
    break;
    case 8:
    {
        int res = checkLattice();
        if (res == 1)
        {
            printf("Yes\n");
            menu5();
        }
        else
        {
            printf("No\n");
        }
    }
    break;
    case 9:
        return;
    }
}

int is_reflexive()
{
    // Reflexive
    for (int i = 0; i < rows; i++)
    {
        if (!mat[i][i])
        {
            return 0;
        }
    }
    return 1;
}

int is_symmetric()
{
    // Symmetric
    for (int i = 0; i < columns; i++)
    {
        for (int j = i + 1; j < rows; j++)
        {
            if ((mat[j][i] == 0 && mat[i][j] == 1) || (mat[j][i] == 1 && mat[i][j] == 0))
            {
                return 0;
            }
        }
    }
    return 1;
}

int is_transitive()
{
    // Transitive
    for (int k = 0; k < rows; k++)
    {
        for (int i = 0; i < columns; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (!mat[i][j] && mat[i][k] && mat[k][j])
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

int choice4()
{
    for (int i = 0; i < rows; i++)
    {
        if (mat[i][i])
        {
            return 1;
        }
    }
    return 0;
}

int choice5()
{
    for (int i = 0; i < columns; i++)
    {
        for (int j = i; j < rows; j++)
        {
            if (mat[j][i] == 1 && mat[i][j] == 1)
            {
                return 0;
            }
        }
    }
    return 1;
}

int is_anti_symmetric()
{
    // Anti-Symmetric
    for (int i = 0; i < columns; i++)
    {
        for (int j = i + 1; j < rows; j++)
        {
            if (mat[j][i] == 1 && mat[i][j] == 1)
            {
                return 0;
            }
        }
    }
    return 1;
}

int is_equivalent()
{
    // If relation is equivalence relation, its equivalence classes form a partition
    if (!is_reflexive() || !is_symmetric() || !is_transitive())
    {
        return 0;
    }
    return 1;
}

int is_poset()
{
    return is_reflexive() && is_transitive() && is_anti_symmetric() ? 1 : 0;
}

void menu1()
{
    while (1)
    {
        printf("Main Menu");
        printf("\n");
        printf("1. Does every website has a link to itself?\n");
        printf("2. Is it possible to always return back to the previous website from the current website in one step?\n");
        printf("3. Does every website has all the links to the websites which are reachable from it?\n");
        printf("4. Does there exist any website that contains a link to itself?\n");
        printf("5. Is it impossible to return to the previous website from the current website in one step?\n");
        printf("6. Is it impossible to return to the previous website from the current website in one step (excluding the cases where the current and previous website are the same)?\n");
        printf("7. Is it possible to divide the network into multiple pieces such that every website in a piece is reachable from every other website in that piece?\n");
        printf("8. Is this relation an example of poset?\n");
        printf("9. Exit\n");
        int choice, ans;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            ans = is_reflexive();
            printf(ans ? "Yes\n" : "No\n");
            if (!ans)
            {
                menu2(choice);
            }
            break;
        case 2:
            ans = is_symmetric();
            printf(ans ? "Yes\n" : "No\n");
            if (!ans)
            {
                menu2(choice);
            }
            break;
        case 3:
            ans = is_transitive();
            printf(ans ? "Yes\n" : "No\n");
            if (!ans)
            {
                menu2(choice);
            }
            break;
        case 4:
            ans = choice4();
            printf(ans ? "Yes\n" : "No\n");
            break;
        case 5:
            ans = choice5();
            printf(ans ? "Yes\n" : "No\n");
            break;
        case 6:
            ans = is_anti_symmetric();
            printf(ans ? "Yes\n" : "No\n");
            break;
        case 7:
            ans = is_equivalent();
            printf(ans ? "Yes\n" : "No\n");
            if (!ans)
            {
                menu2(choice);
            }
            else
            {
                if (menu3())
                {
                    return;
                }
            }
            break;
        case 8:
            ans = is_poset(mat, rows, columns);
            printf(ans ? "Yes\n" : "No\n");
            if (ans)
            {
                menu4();
            }
            break;
        case 9:
            free(websites);
            free(mat);
            return;
        }
    }
}

int main()
{
    char buffer[1024];
    FILE *fp = fopen("Input.csv", "r");
    if (fp == NULL)
    {
        printf("Error opening file");
        return 0;
    }
    while (fgets(buffer, 1024, fp) != NULL)
    {
        rows++;
    }
    char *tok = strtok(buffer, ",");
    while (tok != NULL)
    {
        columns++;
        tok = strtok(NULL, ",");
    }

    rows--;
    columns--;

    mat = malloc(rows * sizeof(int *));
    websites = malloc(rows * sizeof(char *));

    for (int i = 0; i < rows; i++)
    {
        mat[i] = malloc(columns * sizeof(int));
    }
    fclose(fp);

    fp = fopen("Input.csv", "r");

    int counter = 0;
    while (fgets(buffer, 1024, fp) != NULL)
    {
        counter++;
        if (counter == 1)
        {
            char *tken = strtok(buffer, ",\n");
            int i = 0;
            while (tken != NULL)
            {
                i++;
                websites[i - 1] = malloc((strlen(tken) + 1) * sizeof(char));
                strcpy(websites[i - 1], tken);
                tken = strtok(NULL, ",\n");
            }
        }
        else
        {
            char *tken;
            tken = strtok(buffer, ",\n");
            int i = 0;
            while (tken != NULL)
            {
                i++;
                if (i != 1)
                {
                    mat[counter - 2][i - 2] = atoi(tken);
                }
                tken = strtok(NULL, ",\n");
            }
        }
    }
    menu1();

    return 0;
}
