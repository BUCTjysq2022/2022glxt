#include<stdio.h>
#include<stdlib.h>
/****定义商品结构体****/
typedef struct item
{
	int id;//货号
	char category[10]; //类型
	char name[30];//名称
	int in_prize;//进价
	int out_prize;//售价
	int stock_quantity;//总库存
	int purchase_quantity;//进货量
	int manufacture_date[3];//生产日期
	int in_date[3];//进货日期
	int expiry_date[3];//保质期
};
int main()
{
	FILE *fp;
	if((fp=fopen("database.txt","r+"))==NULL)
	{
		printf("找不到数据库文件");
		exit(0);
	}
	
	struct item item_array[100];
	
	int input_num;
	int i;
	
	printf("请输入想要添加的商品数量\n");
	scanf("%d",&input_num);
	for(i=0;i<input_num;i++)
	{
		printf("第%d件商品",i+1);
		printf("请输入号商品信息：\n");
		
		printf("货号：\n");
		scanf("%d",&item_array[i].id);
		
		printf("类别：\n");
		fflush(stdin);
		gets(item_array[i].category);
		printf("名称：\n");
		fflush(stdin);
		gets(item_array[i].name);
		
		printf("进价：\n");
		scanf("%d",&item_array[i].in_prize);

		printf("售价：\n");
		scanf("%d",&item_array[i].out_prize);
		
		printf("%d %d %d",item_array[i].id, item_array[i].in_prize, &item_array[i].out_prize);
		
		printf("库存：（如为新增请输入“0”）\n");	
		scanf("%d",&item_array[i].stock_quantity);
		
		printf("进货量：\n");
		scanf("%d",&item_array[i].purchase_quantity);
		
		printf("%d %d %d %d %d",item_array[i].id, item_array[i].in_prize, &item_array[i].out_prize, &item_array[i].stock_quantity, &item_array[i].purchase_quantity);
		
		printf("*以下日期输入均为 yyyy mm dd 格式*\n");
		printf("生产日期：\n");
		fflush(stdin);
		scanf("%d ",&item_array[i].manufacture_date[0],&item_array[i].manufacture_date[1],&item_array[i].manufacture_date[2]);
		printf("进货日期：\n");
		fflush(stdin);
		scanf("%d",&item_array[i].in_date[0],&item_array[i].in_date[1],&item_array[i].in_date[2]);
		printf("过期日期：\n");
		fflush(stdin);
		scanf("%d",&item_array[i].expiry_date[0],&item_array[i].expiry_date[1],&item_array[i].expiry_date[2]);
		printf("\n第%d件商品录入完成\n",i+1);
	}
	if(input_num>1)
		printf("全部商品录入完成!\n");
	for(i=0;i<input_num;i++)
	{
		fprintf(fp,"%d %s %s %d %d %d %d %d %d %d %d %d %d %d %d %d\n",item_array[i].id, item_array[i].category, item_array[i].name,   &item_array[i].in_prize, &item_array[i].out_prize, item_array[i].stock_quantity, item_array[i].purchase_quantity,   &item_array[i].manufacture_date[0], &item_array[i].manufacture_date[1], &item_array[i].manufacture_date[2],   &item_array[i].in_date[0], &item_array[i].in_date[1], &item_array[i].in_date[2],   &item_array[i].expiry_date[0], &item_array[i].expiry_date[1], &item_array[i].expiry_date[2]);
	}
	
	printf("文件写入完成!");
	fclose(fp);
}
