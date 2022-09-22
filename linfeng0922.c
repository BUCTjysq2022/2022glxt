#include<stdio.h>
#include<stdlib.h>
#include<string.h>


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



//***自定义函数定义***//
void establish();//进货功能
int menu();//主菜单功能
void back();//退货函数
void disstore();//显示库存函数
void shop();//购物车功能
void calculate();//计算功能
void search();//查找功能


//***全局变量定义***//
int input_method;
int input_num;
int input_id;
int mode;
int i;
int to_be_deleted,delete_num;
int whether_continue=1;
struct item item_array[100];


//***主函数整体***//
int main()
{
    printf("***********************************\n");
	printf("     欢迎进入超市管理系统\n");
	printf("***********************************\n");
	
	
	while(1)
    {
        switch(menu())//***选择函数，选择功能***//
        {
            case 1:
            establish();break;
            
            case 2:
            back();break;

            case 3:
            disstore();break;

            case 4:
            shop();break;

            case 5:
            calculate();break;
			
	    case 6:
            search();break;
			
            case 7:
			printf("感谢使用，再见!\n");
			exit(0);
        }
    }
			
}

//***菜单选择函数定义***//
int menu()
{
    char str[5];
	int  select;
	printf("\n\n请选择数字进行操作\n");
	printf("1.进货\n");
	printf("2.退货\n");
	printf("3.显示所有信息\n");
	printf("4.购物车\n");
	printf("5.结算\n");
	printf("6.查找\n");
    	printf("7.退出程序\n");
	printf("请选择对应数字1--7:\n");

	while (1)
	{
		fflush(stdin);//***清空输入缓存流***//
		gets(str);
		select = atoi(str);
		if (select<1 || select>7)
			printf("输入错误，请重新输入:");
		else
			break;

	}
	return select;
}


//***定义进货函数***//
void establish()
{

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
				printf("保质期至：\n");
				scanf("%d %d %d",&item_array[i].expiry_date[0],&item_array[i].expiry_date[1],&item_array[i].expiry_date[2]);
				printf("\n第%d件商品录入完成！\n\n",i+1);
			}
			if(input_num==i)
				printf("全部商品录入完成!\n");
			for(i=0;i<input_num;i++)
			{
				item_array[i].stock_quantity+=item_array[i].purchase_quantity;
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
				fprintf(fp,"%d ",item_array[i].purchase_quantity);
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
				printf("%d %d %d | ",item_array[i].manufacture_date[0],item_array[i].manufacture_date[1],item_array[i].manufacture_date[2]);
				printf("%d %d %d | ",item_array[i].in_date[0],item_array[i].in_date[1],item_array[i].in_date[2]);
				printf("%d %d %d\n",item_array[i].expiry_date[0],item_array[i].expiry_date[1],item_array[i].expiry_date[2]);
			}
			if(input_num==i)
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
				fprintf(fp,"%d %d %d ",item_array[i].manufacture_date[0],item_array[i].manufacture_date[1],item_array[i].manufacture_date[2]);
				fprintf(fp,"%d %d %d ",item_array[i].in_date[0],item_array[i].in_date[1],item_array[i].in_date[2]);
				fprintf(fp,"%d %d %d\n",item_array[i].expiry_date[0],item_array[i].expiry_date[1],item_array[i].expiry_date[2]);
			}
			
			/*输入成功提示*/
			printf("文件写入完成!");
			
			fclose(fp);
			break;
        }
}



//***退货函数定义***//
void back()
{

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
			printf("货号：%d ||",item_array[i].id);
			printf("类别：%s ",item_array[i].category);
			printf("名称：%s ||",item_array[i].name);
			printf("进价：%d ",item_array[i].in_prize);
			printf("售价：%d ",item_array[i].out_prize);
			printf("库存：%d ",item_array[i].stock_quantity);
			printf("生产日期：%d年 %d月 %d日 | ",item_array[i].manufacture_date[0],item_array[i].manufacture_date[1],item_array[i].manufacture_date[2]);
			printf("进货日期：%d年 %d月 %d日 | ",item_array[i].in_date[0],item_array[i].in_date[1],item_array[i].in_date[2]);
			printf("保质期至：%d年 %d月 %d日\n",item_array[i].expiry_date[0],item_array[i].expiry_date[1],item_array[i].expiry_date[2]);
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
}

void disstore()//***显示库存功能1.0,下一阶段准备进行美观,目前时间不够***//
{
     /***检测数据库文件是否存在***/
	FILE *fp;
	if((fp=fopen("database.txt","a+"))==NULL)
	{
		printf("找不到数据库文件");
		exit(0);
	}


	char a;
	printf("品名 进价 卖价 库存 进货量 生产日期 进货日期 保质期\n");//***过于简单不做注释批注***//
	while((a=fgetc(fp))!=EOF)
	{
        printf("%c",a);
	}

	return 0;
}

void shop()//***购物车功能（未完成开发）
{
    printf("\n功能待开发，谢谢支持！ （づ￣3￣）づ╭?～\n");
}

void calculate()//***计算功能（未完成开发）
{
    printf("\n功能待开发，谢谢支持！ （づ￣3￣）づ╭?～\n");
}
//***查找函数定义***//
void search()
{

    /***检测数据库文件是否存在***/
	FILE *fp;
	if((fp=fopen("database.txt","a+"))==NULL)
	{
		printf("找不到数据库文件");
		exit(0);
	}

    /***查找***/
		printf("请输入想要读取和编辑商品条数：\n");
		scanf("%d",&input_num);
		printf("请输入想要查找商品的货号：\n");
		scanf("%d",&input_id);
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
		/**搜索商品**/
		for(i=0;i<input_num;i++)
		{	
			if(item_array[i].id==input_id){
				printf("库中仍有此商品，商品信息为：\n");
				printf("货号：%d \n",item_array[i].id);
				printf("类别：%s \n",item_array[i].category);
				printf("名称：%s \n",item_array[i].name);
				printf("进价：%d \n",item_array[i].in_prize);
				printf("售价：%d \n",item_array[i].out_prize);
				printf("库存：%d \n",item_array[i].stock_quantity);
				printf("生产日期：%d %d %d \n",item_array[i].manufacture_date[0],item_array[i].manufacture_date[1],item_array[i].manufacture_date[2]);
				printf("进货日期：%d %d %d \n",item_array[i].in_date[0],item_array[i].in_date[1],item_array[i].in_date[2]);
				printf("保质期至：%d %d %d \n",item_array[i].expiry_date[0],item_array[i].expiry_date[1],item_array[i].expiry_date[2]);
				break;
			}
			
		}
		if(i==input_num){
			printf("查无此商品\n");	
		}
		
}
