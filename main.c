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
	/***选中进货/退货模式***/
	
	/***检测数据库文件是否存在***/
	FILE *fp;
	if((fp=fopen("database.txt","a+"))==NULL)
	{
		printf("找不到数据库文件");
		exit(0);
	}
	
	/***输入文件指针定义***/
	FILE *infp;
	FILE *new_fp;
	
	/***创建数组***/
	struct item item_array[100];
	
	/***变量定义***/
	int input_method;
	int input_num;
	int mode;
	int i;
	int to_be_deleted,delete_num;
	int whether_continue=1;
	
	/***模式选择***/
	printf("请选择模式：\n");
	printf("1.进货\n");
	printf("2.退货\n");
	scanf("%d",&mode);
	
	switch (mode)
	{
	case 1:
	/***进货***/
		printf("请选择录入方式：\n");
		printf("1.手动录入\n");
		printf("2.文件录入\n");
		scanf("%d",&input_method);
		switch (input_method) 
		{
		case 1:
		/**手动录入**/
			printf("请输入想要添加的商品数量\n");
			scanf("%d",&input_num);
			/*输入数组*/
			for(i=0;i<input_num;i++)
			{
				printf("正在录入第%d件商品：\n",i+1);
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
				printf("库存：（如为新增请输入“0”）\n");
				scanf("%d",&item_array[i].stock_quantity);
				printf("进货量：\n");
				scanf("%d",&item_array[i].purchase_quantity);
				printf("*以下日期输入均为 yyyy mm dd 格式*\n");
				printf("生产日期：\n");
				scanf("%d %d %d",&item_array[i].manufacture_date[0],&item_array[i].manufacture_date[1],&item_array[i].manufacture_date[2]);
				printf("进货日期：\n");
				scanf("%d %d %d",&item_array[i].in_date[0],&item_array[i].in_date[1],&item_array[i].in_date[2]);
				printf("保质期：\n");
				scanf("%d %d %d",&item_array[i].expiry_date[0],&item_array[i].expiry_date[1],&item_array[i].expiry_date[2]);
				printf("\n第%d件商品录入完成！\n\n",i+1);
			}
			if(input_num>1)
				printf("全部商品录入完成!\n");
			for(i=0;i<input_num;i++)
			{
				item_array[i].stock_quantity+=item_array[i].purchase_quantity;
				item_array[i].purchase_quantity=0;
			}
			/*输入文件*/
			for(i=0;i<input_num;i++)
			{
				fprintf(fp,"\n%d ",item_array[i].id);
				fprintf(fp,"%s ",item_array[i].category);
				fprintf(fp,"%s ",item_array[i].name);
				fprintf(fp,"%d ",item_array[i].in_prize);
				fprintf(fp,"%d ",item_array[i].out_prize);
				fprintf(fp,"%d ",item_array[i].stock_quantity);
				fprintf(fp,"%d ",item_array[i].purchase_quantity);
				fprintf(fp,"%d %d %d ",item_array[i].manufacture_date[0],item_array[i].manufacture_date[1],item_array[i].manufacture_date[2]);
				fprintf(fp,"%d %d %d ",item_array[i].in_date[0],item_array[i].in_date[1],item_array[i].in_date[2]);
				fprintf(fp,"%d %d %d\n",item_array[i].expiry_date[0],item_array[i].expiry_date[1],item_array[i].expiry_date[2]);
			}
			
			printf("文件写入完成!");
			fclose(fp);
			break;
			
			
			

		case 2:
		/**文件录入**/
			printf("请输入想要添加的商品数量\n");
			scanf("%d",&input_num);
			/*检测输入文件是否存在*/
			if((infp=fopen("input.txt","r"))==NULL)
			{
				printf("找不到输入文件");
				exit(0);
			}

			/*输入数组*/
			for(i=0;i<input_num;i++)
			{
				fscanf(infp,"%d",&item_array[i].id);
				fscanf(infp,"%s",&item_array[i].category);
				fscanf(infp,"%s",&item_array[i].name);
				fscanf(infp,"%d",&item_array[i].in_prize);
				fscanf(infp,"%d",&item_array[i].out_prize);
				fscanf(infp,"%d",&item_array[i].stock_quantity);
				fscanf(infp,"%d",&item_array[i].purchase_quantity);
				fscanf(infp,"%d %d %d",&item_array[i].manufacture_date[0],&item_array[i].manufacture_date[1],&item_array[i].manufacture_date[2]);
				fscanf(infp,"%d %d %d",&item_array[i].in_date[0],&item_array[i].in_date[1],&item_array[i].in_date[2]);
				fscanf(infp,"%d %d %d",&item_array[i].expiry_date[0],&item_array[i].expiry_date[1],&item_array[i].expiry_date[2]);
			}
			fclose(infp);
			
			for(i=0;i<input_num;i++)
			{
				item_array[i].stock_quantity+=item_array[i].purchase_quantity;
				item_array[i].purchase_quantity=0;
			}
			/*成功录入数组提示*/
			printf("成功检测到如下项目：\n");
			for(i=0;i<input_num;i++)
			{
				printf("%d ||",item_array[i].id);
				printf("%s ",item_array[i].category);
				printf("%s ||",item_array[i].name);
				printf("%d ",item_array[i].in_prize);
				printf("%d ",item_array[i].out_prize);
				printf("%d ",item_array[i].stock_quantity);
				printf("%d ||",item_array[i].purchase_quantity);
				printf("%d %d %d | ",item_array[i].manufacture_date[0],item_array[i].manufacture_date[1],item_array[i].manufacture_date[2]);
				printf("%d %d %d | ",item_array[i].in_date[0],item_array[i].in_date[1],item_array[i].in_date[2]);
				printf("%d %d %d\n",item_array[i].expiry_date[0],item_array[i].expiry_date[1],item_array[i].expiry_date[2]);
			}
			if(input_num>1)
				printf("全部商品录入完成!\n");
			
			
			/*输入数据库*/
			fprintf(fp,"\n");
			for(i=0;i<input_num;i++)
			{
				fprintf(fp,"%d ",item_array[i].id);
				fprintf(fp,"%s ",item_array[i].category);
				fprintf(fp,"%s ",item_array[i].name);
				fprintf(fp,"%d ",item_array[i].in_prize);
				fprintf(fp,"%d ",item_array[i].out_prize);
				fprintf(fp,"%d ",item_array[i].stock_quantity);
				fprintf(fp,"%d ",item_array[i].purchase_quantity);
				fprintf(fp,"%d %d %d ",item_array[i].manufacture_date[0],item_array[i].manufacture_date[1],item_array[i].manufacture_date[2]);
				fprintf(fp,"%d %d %d ",item_array[i].in_date[0],item_array[i].in_date[1],item_array[i].in_date[2]);
				fprintf(fp,"%d %d %d\n",item_array[i].expiry_date[0],item_array[i].expiry_date[1],item_array[i].expiry_date[2]);
			}
			
			/*输入成功提示*/
			printf("文件写入完成!");
			
			fclose(fp);
			break;
		}
		break;
	
	
	case 2:
	/***退货***/
		printf("请输入想要读取和编辑商品条数：\n");
		scanf("%d",&input_num);
		/**数据库导入数组**/
		for(i=0;i<input_num;i++)
		{
			fscanf(fp,"%d",&item_array[i].id);
			fscanf(fp,"%s",&item_array[i].category);
			fscanf(fp,"%s",&item_array[i].name);
			fscanf(fp,"%d",&item_array[i].in_prize);
			fscanf(fp,"%d",&item_array[i].out_prize);
			fscanf(fp,"%d",&item_array[i].stock_quantity);
			fscanf(fp,"%d",&item_array[i].purchase_quantity);
			fscanf(fp,"%d %d %d",&item_array[i].manufacture_date[0],&item_array[i].manufacture_date[1],&item_array[i].manufacture_date[2]);
			fscanf(fp,"%d %d %d",&item_array[i].in_date[0],&item_array[i].in_date[1],&item_array[i].in_date[2]);
			fscanf(fp,"%d %d %d",&item_array[i].expiry_date[0],&item_array[i].expiry_date[1],&item_array[i].expiry_date[2]);
		}
		/**展示数据库**/
		printf("数据库中有如下商品：\n");
		for(i=0;i<input_num;i++)
		{
			printf("%d ||",item_array[i].id);
			printf("%s ",item_array[i].category);
			printf("%s ||",item_array[i].name);
			printf("%d ",item_array[i].in_prize);
			printf("%d ",item_array[i].out_prize);
			printf("%d ",item_array[i].stock_quantity);
			printf("%d ||",item_array[i].purchase_quantity);
			printf("%d %d %d | ",item_array[i].manufacture_date[0],item_array[i].manufacture_date[1],item_array[i].manufacture_date[2]);
			printf("%d %d %d | ",item_array[i].in_date[0],item_array[i].in_date[1],item_array[i].in_date[2]);
			printf("%d %d %d\n",item_array[i].expiry_date[0],item_array[i].expiry_date[1],item_array[i].expiry_date[2]);
		}
		
		/**对数组修改**/
		while(whether_continue==1)
		{
			/*获取想要删除商品的货号/数量*/
			printf("\n请输入想要退货的商品货号：\n");
			scanf("%d",&to_be_deleted);
			to_be_deleted-=1;
			printf("\n请输入想要退货的数量:\n");
			printf("(目前库存%d件)\n",item_array[to_be_deleted].stock_quantity);
			scanf("%d",&delete_num);
			
			/*删除操作*/
			item_array[to_be_deleted].stock_quantity-=delete_num;
			printf("\n操作成功！\n");
			
			/*继续操作*/
			printf("是否继续删除？\n");
			printf("1.继续删除\n");
			printf("2.停止删除\n");
			scanf("%d",&whether_continue);
		}
		
		/**将数组写入新文件**/
		
		/*新建数据库*/
		if((new_fp=fopen("database_new.txt","w"))==NULL)
		{
			printf("已新建数据库文件");
			exit(0);
		}
		/*写入*/
		for(i=0;i<input_num;i++)
		{
			fprintf(new_fp,"%d ",item_array[i].id);
			fprintf(new_fp,"%s ",item_array[i].category);
			fprintf(new_fp,"%s ",item_array[i].name);
			fprintf(new_fp,"%d ",item_array[i].in_prize);
			fprintf(new_fp,"%d ",item_array[i].out_prize);
			fprintf(new_fp,"%d ",item_array[i].stock_quantity);
			fprintf(new_fp,"%d ",item_array[i].purchase_quantity);
			fprintf(new_fp,"%d %d %d ",item_array[i].manufacture_date[0],item_array[i].manufacture_date[1],item_array[i].manufacture_date[2]);
			fprintf(new_fp,"%d %d %d ",item_array[i].in_date[0],item_array[i].in_date[1],item_array[i].in_date[2]);
			fprintf(new_fp,"%d %d %d\n",item_array[i].expiry_date[0],item_array[i].expiry_date[1],item_array[i].expiry_date[2]);
		}
		printf("新数据库写入完成！");
		
		break;
	}

}