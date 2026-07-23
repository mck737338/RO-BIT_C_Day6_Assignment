#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _student {
	int num;
	char name[20];
	char address[4][30];
	int score;
}student;

void sort(student* list, int people);
void numSort(student* list, int sIndex, int eIndex);
void nameSort(student* list, int sIndex, int eIndex);
void adrSort(student* list, int ad, int sIndex, int eIndex);
void scoreSort(student* list, int sIndex, int eIndex);
void searchStd(student* list, int people);
void apdStud(student** list, int* people);
void delStd(student** list, int* people);
void saveStd(student* list, int people);
void loadStd(student** list, int* people);
int comp_str(char* str1, char* str2);
int readStr();

int main() {
	student* list;
	list = (student*)malloc(sizeof(student));
	int people = 0;

	int func;
	while (1) {
		func = readStr();

		switch (func) {
		case 0:
			sort(list, people);
			break;
		case 1:
			searchStd(list, people);
			break;
		case 2:
			apdStud(&list, &people);
			break;
		case 3:
			delStd(&list, &people);
			break;
		case 4:
			saveStd(list, people);
			break;
		case 5:
			loadStd(&list, &people);
			break;
		case 6:
			free(list);
			return 0;
		default:;
		}
	}

}


void sort(student* list, int people) {
	char criteria[4][8] = {
		"number", "name", "address", "score"
	};

	char ip[100];
	printf("select criteria\n(number, name, address, score): ");
	scanf("%s", ip);

	int sortType = -1;
	for (int i = 0; i < 4; i++) {
		if (comp_str(ip, criteria[i]) == 1) {
			sortType = i;
			break;
		}
	}

	switch (sortType) {
	case 0:
		numSort(list, 0, people);
		break;
	case 1:
		nameSort(list, 0, people);
		break;
	case 2:
		adrSort(list, 0, 0, people);
		break;
	case 3:
		scoreSort(list, 0, people);
		break;
	default:;
	}

	for (int i = 0; i < people; i++) {
		printf("num: %d, name: %s, address: %s %s %s %s, score: %d\n",
			list[i].num, list[i].name,
			list[i].address[0], list[i].address[1], list[i].address[2], list[i].address[3],
			list[i].score);
	}
}

void numSort(student* list, int sIndex, int eIndex) {
	student temp;
	int end = eIndex;		//정렬 범위 뒤쪽 경계, 한 바퀴 돌 때마다 하나씩 줄어듦

	for (int i = 0; i < eIndex - sIndex; i++) {
		int index = sIndex;
		temp = list[index];
		for (int j = sIndex; j < end; j++) {
			if (temp.num < list[j].num) {
				index = j;
				temp = list[j];
			}
		}
		list[index] = list[end - 1];
		list[end - 1] = temp;
		end--;
	}
}

void nameSort(student* list, int sIndex, int eIndex) {
	student temp;
	int index;
	int end = eIndex;

	for (int i = 0; i < eIndex - sIndex; i++) {
		index = sIndex;
		temp = list[index];
		for (int j = sIndex; j < end; j++) {
			for (int k = 0; k < 20; k++) {
				if (temp.name[k] < list[j].name[k]) {
					index = j;
					temp = list[j];
					break;
				}
				else if (temp.name[k] > list[j].name[k]) {
					break;
				}
			}
		}
		list[index] = list[end - 1];
		list[end - 1] = temp;
		end--;
	}

	index = sIndex;
	for (int i = sIndex; i < eIndex; i++) {
		if (comp_str(list[index].name, list[i].name) == 0) {
			numSort(list, index, i);
			index = i;
		}
	}
	numSort(list, index, eIndex);
}

void adrSort(student* list, int ad, int sIndex, int eIndex) {
	student temp;
	int index;
	int end = eIndex;

	for (int i = 0; i < eIndex - sIndex; i++) {
		index = sIndex;
		temp = list[index];
		for (int j = sIndex; j < end; j++) {
			for (int k = 0; k < 30; k++) {
				if (temp.address[ad][k] < list[j].address[ad][k]) {
					index = j;
					temp = list[j];
					break;
				}
				else if (temp.address[ad][k] > list[j].address[ad][k]) {
					break;
				}
			}
		}
		list[index] = list[end - 1];
		list[end - 1] = temp;
		end--;
	}

	index = sIndex;
	for (int i = sIndex; i < eIndex; i++) {
		if (comp_str(list[index].address[ad], list[i].address[ad]) == 0) {
			if (ad < 3) {
				adrSort(list, ad + 1, index, i);
			}
			else {
				numSort(list, index, i);
			}
			index = i;
		}
	}
	if (ad < 3) {
		adrSort(list, ad + 1, index, eIndex);
	}
	else {
		numSort(list, index, eIndex);
	}
}

void scoreSort(student* list, int sIndex, int eIndex) {
	student temp;
	int index;
	int end = eIndex;

	for (int i = 0; i < eIndex - sIndex; i++) {
		index = sIndex;
		temp = list[index];
		for (int j = sIndex; j < end; j++) {
			if (temp.score > list[j].score) {
				index = j;
				temp = list[j];
			}
		}
		list[index] = list[end - 1];
		list[end - 1] = temp;
		end--;
	}

	index = sIndex;
	for (int i = sIndex; i < eIndex; i++) {
		if (list[index].score != list[i].score) {
			numSort(list, index, i);
			index = i;
		}
	}
	numSort(list, index, eIndex);
}

void searchStd(student* list, int people) {
	int* ptr = (int*)malloc(sizeof(int));
	int search = 0;

	char ip[100];
	printf("select criteria\n(number, address, score): ");
	scanf("%s", ip);

	char criteria[3][8] = {
		"number", "address", "score"
	};

	int findType = -1;
	for (int i = 0; i < 3; i++) {
		if (comp_str(ip, criteria[i]) == 1) {
			findType = i;
			break;
		}
	}

	if (findType != -1) {

		if (findType == 0) {
			int number;
			printf("number: ");
			scanf("%d", &number);

			for (int i = 0; i < people; i++) {
				if (list[i].num == number) {
					search++;
					ptr = (int*)realloc(ptr, sizeof(int) * search);
					ptr[search - 1] = i;
				}
			}
		}

		if (findType == 1) {
			printf("select detail: ");
			char adr[4][9] = {
				"country", "province", "city", "district"
			};
			scanf("%s", ip);

			int adrType = -1;
			for (int i = 0; i < 4; i++) {
				if (comp_str(ip, adr[i]) == 1) {
					adrType = i;
					break;
				}
			}

			if (adrType != -1) {
				printf("address: ");
				scanf("%s", ip);

				for (int i = 0; i < people; i++) {
					if (comp_str(ip, list[i].address[adrType]) == 1) {
						search++;
						ptr = (int*)realloc(ptr, sizeof(int) * search);
						ptr[search - 1] = i;
					}
				}
			}
		}

		if (findType == 2) {
			int scr;
			printf("score: ");
			scanf("%d", &scr);

			for (int i = 0; i < people; i++) {
				if (list[i].score == scr) {
					search++;
					ptr = (int*)realloc(ptr, sizeof(int) * search);
					ptr[search - 1] = i;
				}
			}
		}

		for (int i = 0; i < search; i++) {
			printf("%s\n", list[ptr[i]].name);
		}
	}

	free(ptr);
}


void apdStud(student** list, int* people) {
	(*people)++;
	*list = (student*)realloc(*list, sizeof(student) * (*people));
	student* std = &(*list)[*people - 1];

	printf("number: ");
	scanf("%d", &std->num);
	printf("name: ");
	scanf("%s", std->name);
	printf("address(country province city district): ");
	scanf("%s", std->address[0]);
	scanf("%s", std->address[1]);
	scanf("%s", std->address[2]);
	scanf("%s", std->address[3]);
	printf("score: ");
	scanf("%d", &std->score);
}


void delStd(student** list, int* people) {
	int* ptr = (int*)malloc(sizeof(int));
	int search = 0;

	char ip[100];
	printf("select criteria\n(number, name, address, score): ");
	scanf("%s", ip);

	char criteria[4][8] = {
		"number", "name", "address", "score"
	};

	int findType = -1;
	for (int i = 0; i < 4; i++) {
		if (comp_str(ip, criteria[i]) == 1) {
			findType = i;
			break;
		}
	}

	if (findType != -1) {

		if (findType == 0) {
			int number;
			printf("number: ");
			scanf("%d", &number);

			for (int i = 0; i < *people; i++) {
				if ((*list)[i].num == number) {
					search++;
					ptr = (int*)realloc(ptr, sizeof(int) * search);
					ptr[search - 1] = i;
				}
			}
		}

		if (findType == 1) {
			char name[20];
			printf("name: ");
			scanf("%s", name);

			for (int i = 0; i < *people; i++) {
				if (comp_str(name, (*list)[i].name) == 1) {
					search++;
					ptr = (int*)realloc(ptr, sizeof(int) * search);
					ptr[search - 1] = i;
				}
			}
		}

		if (findType == 2) {
			printf("select detail: ");
			char adr[4][9] = {
				"country", "province", "city", "district"
			};
			scanf("%s", ip);

			int adrType = -1;
			for (int i = 0; i < 4; i++) {
				if (comp_str(ip, adr[i]) == 1) {
					adrType = i;
					break;
				}
			}

			if (adrType != -1) {
				printf("address: ");
				scanf("%s", ip);

				for (int i = 0; i < *people; i++) {
					if (comp_str(ip, (*list)[i].address[adrType]) == 1) {
						search++;
						ptr = (int*)realloc(ptr, sizeof(int) * search);
						ptr[search - 1] = i;
					}
				}
			}
		}

		if (findType == 3) {
			int scr;
			printf("score: ");
			scanf("%d", &scr);

			for (int i = 0; i < *people; i++) {
				if ((*list)[i].score == scr) {
					search++;
					ptr = (int*)realloc(ptr, sizeof(int) * search);
					ptr[search - 1] = i;
				}
			}
		}

		if (search == 0) {
			printf("no matching student found\n");
			free(ptr);
			return;
		}

		int target = ptr[0];

		if (search > 1) {		//중복된 경우 선택하여 삭제
			printf("%d duplicate students found. select one to delete:\n", search);
			for (int i = 0; i < search; i++) {
				printf("[%d] num: %d, name: %s, address: %s %s %s %s, score: %d\n", i,
					(*list)[ptr[i]].num, (*list)[ptr[i]].name,
					(*list)[ptr[i]].address[0], (*list)[ptr[i]].address[1],
					(*list)[ptr[i]].address[2], (*list)[ptr[i]].address[3],
					(*list)[ptr[i]].score);
			}
			int sel;
			printf("select index to delete: ");
			scanf("%d", &sel);
			if (sel < 0 || sel >= search) {
				printf("invalid selection\n");
				free(ptr);
				return;
			}
			target = ptr[sel];
		}

		for (int i = target; i < *people - 1; i++) {
			(*list)[i] = (*list)[i + 1];
		}
		(*people)--;
		*list = (student*)realloc(*list, sizeof(student) * (*people));

		printf("student deleted\n");
		free(ptr);
	}
	else {
		printf("wrong criteria\n");
		free(ptr);
	}

}

void saveStd(student* list, int people) {
	FILE* fp = fopen("students.txt", "w");

	fprintf(fp, "%d\n", people);
	for (int i = 0; i < people; i++) {
		fprintf(fp, "%d %s %s %s %s %s %d\n",
			list[i].num,
			list[i].name,
			list[i].address[0], list[i].address[1], list[i].address[2], list[i].address[3],
			list[i].score);
	}

	fclose(fp);
	printf("student list saved\n");
}


void loadStd(student** list, int* people) {
	FILE* fp = fopen("students.txt", "r");
	if (fp == NULL) {		//파일이 없으면 에러 출력
		printf("no saved file found\n");
		return;
	}

	int loadedPeople;
	fscanf(fp, "%d", &loadedPeople);

	student* newList = (student*)malloc(sizeof(student) * loadedPeople);
	for (int i = 0; i < loadedPeople; i++) {
		fscanf(fp, "%d %s %s %s %s %s %d",
			&newList[i].num,
			newList[i].name,
			newList[i].address[0], newList[i].address[1], newList[i].address[2], newList[i].address[3],
			&newList[i].score);
	}

	fclose(fp);

	free(*list);
	*list = newList;
	*people = loadedPeople;

	printf("attendance list loaded (%d students)\n", *people);
}


int comp_str(char* str1, char* str2) {
	int i = 0;
	while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i]) {
		i++;
	}
	if (str1[i] == str2[i]) {
		return 1;
	}
	else {
		return 0;
	}
}

int readStr() {
	char func_name[7][7] = {		//함수 이름
		"sort", "search", "append", "delete", "save", "load", "exit"
	};

	char str[100];
	printf("\n");
	scanf("%s", str);		//문자열 입력 받기

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {		//func_name의 한 행 크기(7)를 넘어가지 않도록 수정
			if (str[j] != func_name[i][j]) {		//문자열과 함수 이름이 다르면 스킵
				break;
			}
			if (str[j] == '\0' || func_name[i][j] == '\0') {		//문자열이 끝나면 함수 종류를 반환
				return i;
			}
		}
	}

	return -1;
}