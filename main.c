#include <stdio.h>
#include <string.h>

#include "visualiser.c"

int **mat;
int rows = 0;
int columns = 0;

void menu2(int choice)
{
	printf("Do you want to visualize how the network will look if we add minimum links to satisfy this property? 1 for yes, 0 for no\n");
	int cont;
	scanf("%d", &cont);
	if (cont) {
		// TODO
		switch (choice) {
		case 1:
			plot("SampleInput.csv");
		}
	}
}

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

int is_reflexive()
{
	// Reflexive
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (mat[i][j] == 0) {
				return 0;
			}
		}
	}
	return 1;
}

int is_symmetric()
{
	// Symmetric
	for (int i = 0; i < columns; i++) {
		for (int j = i; j < rows; j++) {
			if ((mat[j][i] == 0 && mat[i][j] == 1) || (mat[j][i] == 1 && mat[i][j] == 0)) {
				return 0;
			}
		}
	}
	return 1;
}

int is_transitive()
{
	// Transitive
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (mat[i][j]) {
				for (int k = 0; k < columns; k++) {
					if (mat[j][k] && !mat[i][k]) {
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

int choice4()
{
	// Changed
	for (int i = 0; i < rows; i++) {
		if (mat[i][i]) {
			return 1;
		}
	}
	return 0;
}

int choice5()
{
	// Changed
	for (int i = 0; i < columns; i++) {
		for (int j = i; j < rows; j++) {
			if (mat[j][i] == 1 && mat[i][j] == 1) {
				return 0;
			}
		}
	}
	return 1;
}

int is_anti_symmetric()
{
	// Anti-Symmetric
	// Changed
	for (int i = 0; i < columns; i++) {
		for (int j = i + 1; j < rows; j++) {
			if (mat[j][i] == 1 && mat[i][j] == 1) {
				return 0;
			}
		}
	}
	return 1;
}

int choice7()
{
	// If relation is equivalence relation, its equivalence classes form a partition
	// Completed
	if (!is_reflexive() || !is_symmetric() || !is_transitive()) {
		return 0;
	}
	return 1;
}

int is_poset()
{
	// Changed
	return is_reflexive() && is_transitive() && is_anti_symmetric() ? 1 : 0;
}

void menu1()
{
	while (1) {
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

		switch (choice) {
		case 1:
			ans = is_reflexive();
			printf(ans ? "Yes\n" : "No\n");
			if (!ans) {
				menu2(choice);
			}
			break;
		case 2:
			ans = is_symmetric();
			printf(ans ? "Yes\n" : "No\n");
			if (!ans) {
				menu2(choice);
			}
			break;
		case 3:
			ans = is_transitive();
			printf(ans ? "Yes\n" : "No\n");
			if (!ans) {
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
			ans = choice7();
			printf(ans ? "Yes\n" : "No\n");
			if (!ans) {
				menu2(choice);
			}
			break;
		case 8:
			ans = is_poset(mat, rows, columns);
			printf(ans ? "Yes\n" : "No\n");
			if (!ans) {
				// TODO
				menu4();
			}
			break;
		case 9:
			return;
		}
	}
}

int main()
{
	char buffer[1024];
	FILE *fp = fopen("SampleInput.csv", "r");
	if (fp == NULL) {
		printf("Error opening file");
		return 0;
	}
	// int rows = 0;
	while (fgets(buffer, 1024, fp) != NULL) {
		rows++;
	}
	char *tok = strtok(buffer, ",");
	// int columns = 0;
	while (tok != NULL) {
		columns++;
		tok = strtok(NULL, ",");
	}

	rows--;
	columns--;
	// int **mat = malloc((rows - 1) * sizeof(int *));
	mat = malloc(rows * sizeof(int *));

	for (int i = 0; i < rows; i++) {
		mat[i] = malloc(columns * sizeof(int));
	}
	fclose(fp);
	fp = fopen("SampleInput.csv", "r");
	int counter = 0;
	while (fgets(buffer, 1024, fp) != NULL) {
		counter++;
		if (counter == 1) {
			continue;
		} else {
			char *tken;
			tken = strtok(buffer, ",");
			int i = 0;
			while (tken != NULL) {
				i++;
				if (i == 1) {
					tken = strtok(NULL, ",");
					continue;
				} else {
					mat[counter - 2][i - 2] = atoi(tken);
					tken = strtok(NULL, ",");
				}
			}
		}
	}
	// printf("Rows: %d, Columns: %d\n", rows, columns);

	menu1();
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
	return 0;
}
