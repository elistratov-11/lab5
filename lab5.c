#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
struct nedviga
{
    char* adress; //любая длина
    char* kadastroviy_nomer; //11 символов
    float ploshad; // число
};

void free_nedviga(struct nedviga* a){
    free(a->adress);
    free(a->kadastroviy_nomer);
    free(a);
}

int srav(char* str1, char* str2){
    if (strlen(str1) == strlen(str2)){
        if (strcmp(str1, str2) < 0){
	    return 1;
	}
	if (strcmp(str1, str2) >0){
	    return 0;
	}
    }
    if (strlen(str1) < strlen(str2)){
        return 1;
    }
    if (strlen(str1) > strlen(str2)){
        return 0;
    }
}

void gnome_sort(struct nedviga* array, int size, int t){
    int i = 1;
    int j = 1;
    while (i < size){
	if (srav(array[i-1].adress, array[i].adress) == t){
	    i=j;
	    j+=1;
	}
	else{
	    struct nedviga swap = array[i-1];
	    array[i-1] = array[i];
	    array[i] = swap;
	    i = i-1;
	    if (i==0){
	        i=j;
		j+=1;
	    }
	}
    }
}

void out(struct nedviga* array, int n){
    for (int i=0; i<n; i++){
        printf("adress: %s, kadastr: %s, plosh: %f\n", array[i].adress, array[i].kadastroviy_nomer, array[i].ploshad);
    }
}

char* part(char* str, int ind){
	char* new_str =0;
	int n=0;
	while (str[n] != '\0'){
		n+=1;
	}
	new_str = realloc(new_str, (n-ind));
	int k = 0;
	for (int i = ind; i<n; i++){
		new_str[k]=str[i];
		k+=1;
	}
	return new_str;
}

int main(int argc, char** argv){
	int c;
	int n;
	struct nedviga* array = NULL;
	int vvod;
	int outvod;
	int sort;
	char* file = NULL;
	while ((c = getopt(argc, argv, "a:b:c:")) != -1){
		switch (c)
		{
			case 'a':
				//int a = atoi(optarg);
				if (optarg[0] == '0'){
					vvod = 0;
				}
				if (optarg[0] == '1'){
					vvod = 1;
					file = realloc(file, strlen(optarg));
					file = part(optarg, 2);
					file = realloc(file, strlen(part(optarg, 2)));
				}
				//if (a == 2){
				//	vvod = 2;
				//}
				break;
			case 'b':
				//int b = atoi(optarg);
				if (optarg[0] == '0'){
					outvod = 0;
				}
				break;
		}
}
	if (vvod == 0){
		printf("Введите количество объектов: "); scanf("%d", &n);
		struct nedviga* array = malloc(n*sizeof(struct nedviga));
		//printf("%d", n);
		for (int i=0; i<n; i++){
			struct nedviga a;
			char* adr = malloc(10);
			printf("введите адрес: "); scanf("%10s", adr);
			a.adress = adr;
			char* kad = malloc(11);
			printf("введите кадастровый номер(формат AA:BB:00:AA, А-цифра, B-буква): "); scanf("%11s", kad);
			a.kadastroviy_nomer = kad;
			float pl;
			printf("введите площадь: "); scanf("%f", &pl);
			a.ploshad = pl;
			array[i] = a;
			printf("%d\n", i);
			out(array, n);
			//printf("%d", i);
		}
		printf("%d", n);
	}
	if (vvod == 1){
		FILE* fp = fopen(file, "r");
		char buffer[256];
		if (fp){
			while ((fgets(buffer, 256, fp))!=NULL){
				printf("%s", buffer);
			}
		}
		fclose(fp);
	}
	if (outvod == 0){
		out(array, n);
	}
	return 0;
}

/* 
 * array[a[string, float], b[string, float]]
 * a[string, string, float]
 * b[string, string, float]
 * (array[0]).string == b.string */
