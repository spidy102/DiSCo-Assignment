#include <stdio.h>
#include <string.h>

#include "visualiser.c"

char **websites;
int **mat;
int rows = 0;
int columns = 0;

void copymat(int newmat[rows][columns])
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			newmat[i][j] = mat[i][j];
		}
	}
}

void tocsv(int newmat[rows][columns])
{
	FILE *fp = fopen("Output.csv", "w");
	for (int i = 0; i < rows; i++) {
		fprintf(fp, ",%s", websites[i]);
	}
	fprintf(fp, "\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (!j) {
				fprintf(fp, "%s", websites[i]);
			}
			fprintf(fp, ",%d", newmat[i][j]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);
}

void reflexive_closure(int newmat[rows][columns])
{
	for (int i = 0; i < rows; i++) {
		newmat[i][i] = 1;
	}
}

void symmetric_closure(int newmat[rows][columns])
{
	for (int i = 0; i < columns; i++) {
		for (int j = i + 1; j < rows; j++) {
			if (newmat[i][j] || newmat[j][i]) {
				newmat[j][i] = 1;
				newmat[i][j] = 1;
			}
		}
	}
}

void transitive_closure(int newmat[rows][columns])
{
	for (int k = 0; k < rows; k++) {
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < columns; j++) {
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
	if (cont) {
		switch (choice) {
		case 1: {
			int newmat[rows][columns];
			copymat(newmat);
			reflexive_closure(newmat);
			tocsv(newmat);
			plot("Output.csv");
		} break;
		case 2: {
			int newmat[rows][columns];
			copymat(newmat);
			symmetric_closure(newmat);
			tocsv(newmat);
			plot("Output.csv");
		} break;
		case 3: {
			int newmat[rows][columns];
			copymat(newmat);
			transitive_closure(newmat);
			tocsv(newmat);
			plot("Output.csv");
		} break;
		case 7: {
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
	if (cont) {
		int piece = 1;
		int alloted[rows];
		memset(alloted, 0, rows * sizeof(int));
		for (int i = 0; i < rows; i++) {
			if (!alloted[i]) {
				alloted[i] = 1;
				printf("Piece %d: %s", piece, websites[i]);
				for (int j = i + 1; j < columns; j++) {
					if (mat[i][j]) {
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
		if (!mat[i][i]) {
			return 0;
		}
	}
	return 1;
}

int is_symmetric()
{
	// Symmetric
	for (int i = 0; i < columns; i++) {
		for (int j = i + 1; j < rows; j++) {
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
	for (int k = 0; k < rows; k++) {
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < columns; j++) {
				if (!mat[i][j] && mat[i][k] && mat[k][j]) {
					return 0;
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
	for (int i = 0; i < columns; i++) {
		for (int j = i + 1; j < rows; j++) {
			if (mat[j][i] == 1 && mat[i][j] == 1) {
				return 0;
			}
		}
	}
	return 1;
}

int is_equivalent()
{
	// If relation is equivalence relation, its equivalence classes form a partition
	if (!is_reflexive() || !is_symmetric() || !is_transitive()) {
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
			ans = is_equivalent();
			printf(ans ? "Yes\n" : "No\n");
			if (!ans) {
				menu2(choice);
			} else {
				if (menu3()) {
					return;
				}
			}
			break;
		case 8:
			ans = is_poset(mat, rows, columns);
			printf(ans ? "Yes\n" : "No\n");
			if (ans) {
				// TODO
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
	if (fp == NULL) {
		printf("Error opening file");
		return 0;
	}
	while (fgets(buffer, 1024, fp) != NULL) {
		rows++;
	}
	char *tok = strtok(buffer, ",");
	while (tok != NULL) {
		columns++;
		tok = strtok(NULL, ",");
	}

	rows--;
	columns--;

	mat = malloc(rows * sizeof(int *));
	websites = malloc(rows * sizeof(char *));

	for (int i = 0; i < rows; i++) {
		mat[i] = malloc(columns * sizeof(int));
	}
	fclose(fp);

	fp = fopen("Input.csv", "r");

	int counter = 0;
	while (fgets(buffer, 1024, fp) != NULL) {
		counter++;
		if (counter == 1) {
			char *tken = strtok(buffer, ",\n");
			int i = 0;
			while (tken != NULL) {
				i++;
				websites[i - 1] = malloc((strlen(tken) + 1) * sizeof(char));
				strcpy(websites[i - 1], tken);
				tken = strtok(NULL, ",\n");
			}
		} else {
			char *tken;
			tken = strtok(buffer, ",\n");
			int i = 0;
			while (tken != NULL) {
				i++;
				if (i != 1) {
					mat[counter - 2][i - 2] = atoi(tken);
				}
				tken = strtok(NULL, ",\n");
			}
		}
	}

	menu1();

	return 0;
}
