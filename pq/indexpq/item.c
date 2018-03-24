#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
struct item { char *name; int value; };

Item ITEMscan(){
	char name[MAXC]; int value;
	printf("Name = "); scanf("%s", name);
	printf("Value = "); scanf("%d", &value);
	Item tmp = malloc(sizeof(*tmp));
	if(tmp == NULL) return ITEMsetvoid();
	else {
		tmp->name = strdup(name);
		tmp->value = value;
	}
	return tmp;
}

void ITEMprint(Item data){
	printf("Name=%s Value=%d\n", data->name, data->value);
}

Item ITEMsetvoid(){
	char name[MAXC]="";
	Item tmp = malloc(sizeof(*tmp));
	if(tmp != NULL){
		tmp->name = strdup(name);
		tmp->value = -1;
	}
	return tmp;
}

int ITEMcheckvoid(Item data){
	if(CMPname(data, ITEMsetvoid())==0)
		return 1;
	return 0;
}

Item ITEMchange(){
	char name[MAXC];
	int value;
	printf("Name of the item to modify: "); scanf("%s", name);
	printf("New priority: "); scanf("%d", &value);
	Item tmp = malloc(sizeof(*tmp));
	if(tmp == NULL)
		return ITEMsetvoid();
	else{
		tmp->name = strdup(name);
		tmp->value = value;
	}
	return tmp;
}

int CMPprio(Item data1, Item data2){
	KEYprio p1 = GETprio(data1), p2 = GETprio(data2);
	if(p1 < p2)
		return -1
	else if (p1 == p2)
		return 0;
	return -1;
}

int CMPname(Item data1, Item data2){
	KEYname k1 = GETname(data1), k2 = GETname(data2);
	return strcmp(k1,k2);
}

KEYname GETname(Item data){
	return data->name;
}

KEYprio GETprio(Item data){
	return data->value;
}