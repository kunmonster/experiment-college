#include<stdio.h>
#include <stdlib.h>
#include<cstring>
int main(){
	

	int size = 0;
	
	scanf("%d",&size);
	
	if(size<=20 && size >0){
	
		int ** arr =  (int**) malloc(sizeof(int*)*size);
		int i=0,j=0;
		for(i=0;i<size;i++){
			arr[i] = (int *) malloc(sizeof(int)*size);
			memset(arr[i],0,size * sizeof(int));
		}

		arr[0][0]=1 ;
		printf("%d \n",arr[0][0]);
		for(i=1;i<size;i++){
			arr[i][0] = 1;
			printf("%d ",arr[i][0]);
			for(j=1;j<=i;j++){
				arr[i][j] = arr[i-1][j] + arr[i-1][j-1];
				if(i==j)printf("%d",arr[i][j]);
				else printf("%d ",arr[i][j]);
			}
			printf("\n");
		}
	}
	
	
	
	return 0;
	
}
