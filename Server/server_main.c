#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

//****定义商品结构体****//
struct item
{
    int id;                  //货号
    char category[10];       //类型
    char name[30];           //名称
    int in_prize;            //进价
    int out_prize;           //售价
    int stock_quantity;      //总库存
    int purchase_quantity;   //进货量
    int manufacture_date[3]; //生产日期
    int in_date[3];          //进货日期
    int expiry_date[3];      //保质期
};


//***自定义函数定义***//
void establish();  //***进货功能函数
int menu();		     //***主菜单功能函数
void back();	     //***退货函数
void disstore();   //***显示库存函数
void shop();	     //***购物车功能函数
void calculate();  //***计算功能函数
void search();	   //***查找功能函数
void disshop();	   //***显示商品信息函数
void chanshop();   //***修改购物车函数
int shop_menu();   //***购物车菜单函数
void rank();	     //***排序功能函数
void category();   //***按类别查找函数
void dismenu();	   //***显示函数的菜单函数
int menuGuest();   //***客人菜单函数
int menuCashier(); //***收银菜单函数
int menuAdmin();   //***管理员菜单函数
void vip();        //***会员管理函数
void sign_in();    //***员工签到函数
void shortage();    //***缺货提醒函数 
void plot();


//***全局变量定义***//
int input_method;
int input_num;
int input_id;
int mode;
int i, sum; // sum记录文件中有几行，用i进行遍历
struct item item_array[100];
int userType;
int GoBack;
int lijian=0;



//***1***主函数整体***//
int main()
{
	int choice;
	system("clear");
  	printf("1.顾客\n2.收银员\n3.管理员\n");
	scanf("%d", &userType);
	while (1)
	{
		//进入不同的用户界面
		switch (userType)
		{
		case 1:
			system("clear");
			choice = menuGuest();
			break;
		case 2:
			system("clear");
			choice = menuCashier();
			break;
		case 3:
			system("clear");
			choice = menuAdmin();
			break;
		}
		switch (choice) //选择函数，选择功能
		{
		case 1:
			system("clear");
			establish();          //***进货功能函数
			break;

		case 2:
			system("clear");
			back();               //***退货函数
			break;

		case 3:
			system("clear");
			dismenu();            //***显示函数的菜单函数
			break;

		case 4:
			system("clear");
			shop();              //***购物车功能函数
			break;

		case 5:
			system("clear");
			calculate();         //***计算功能函数
			break;

		case 6:
			system("clear");
			search();            //***查找功能函数
			break;
    
	    case 7:
			system("clear");
			vip();               //***会员管理函数
        break;
			
        case 8:
			system("clear");
			sign_in();           //***员工签到函数
        break;

        case 9:
			system("clear");
			printf("感谢使用，再见!\n");
			exit(0);
	
	    case 10:		
			system("clear");
			shortage();          //***缺货提醒函数 
			break; 

      case 11:		
			system("clear");
			plot();          //***缺货提醒函数 
			break; 
		}
	}
}




//***2.1***顾客菜单选择函数定义***//
int menuGuest()
{
	int select;
	int realSelect;
	printf("\t\t请选择数字进行操作\n");
	printf("\t\t1.显示所有商品\n");
	printf("\t\t2.购物车\n");
	printf("\t\t3.查找\n");
  printf("\t\t4.退出程序\n");
	printf("\t\t请选择对应数字1--4:\n");

	while (1)
	{
		fflush(stdin); //清空输入缓存流
		scanf("%d", &select);
		if (select < 1 || select > 4)
			printf("输入错误，请重新输入:");

		else
			break;
	}
	if (select == 1)
		realSelect = 3;

	else if (select == 2)
		realSelect = 4;

	else if (select == 3)
		realSelect = 6;

	else if (select == 4)
		realSelect = 9;
	
  
  return realSelect;
}




//***2.2***收营员菜单选择函数定义***//
int menuCashier()
{
	int select;
	int realSelect;
	printf("\t\t请选择数字进行操作\n");
	printf("\t\t1.显示所有商品\n");
	printf("\t\t2.结算\n");
	printf("\t\t3.查找\n");
	printf("\t\t4.员工考勤\n");
    printf("\t\t5.会员管理\n");
    printf("\t\t6.缺货提醒\n");
    printf("\t\t7.退出程序\n");
	printf("\t\t请选择对应数字1--7:\n");

	while (1)
	{
		fflush(stdin); //清空输入缓存流
		scanf("%d", &select);
		if (select < 1 || select > 7)
			printf("输入错误，请重新输入:");

		else
			break;
	}
	if (select == 1)
		realSelect = 3;

	else if (select == 2)
		realSelect = 5;

	else if (select == 3)
		realSelect = 6;
  
   else if (select == 4)
		realSelect = 8;

	else if (select == 5)
		realSelect = 7;
  
   else if (select == 6)
		realSelect = 10;

    else if (select == 7)
		realSelect = 9;
	return realSelect;
}




//***2.3***管理员菜单选择函数定义***//
int menuAdmin()
{
	int select;
	printf("\t\t请选择数字进行操作\n");
	printf("\t\t1.进货\n");
	printf("\t\t2.退货\n");
	printf("\t\t3.显示所有信息\n");
	printf("\t\t4.购物车\n");
	printf("\t\t5.结算\n");
	printf("\t\t6.查找\n");
	printf("\t\t7.会员功能\n");
    printf("\t\t8.员工考勤\n");
    printf("\t\t9.退出程序\n");
    printf("\t\t10.缺货提醒\n");
    printf("\t\t11.画图\n");
	printf("\t\t请选择对应数字1--11:\n");


	while (1)
	{
		fflush(stdin); //清空输入缓存流
		scanf("%d", &select);
		if (select < 1 || select > 11)
			printf("输入错误，请重新输入:");
		else
			break;
	}
	return select;
}




//***3***定义进货函数***//
void establish()
{

    /***检测数据库文件是否存在***/
    FILE *fp;
    if ((fp = fopen("database.txt", "a+")) == NULL)
    {
        printf("找不到数据库文件");
        exit(0);
    }

    /***输入文件指针定义***/
    FILE *infp;

    /***进货***/
    printf("请选择录入方式：\n");
    printf("1.手动录入\n");
    printf("2.文件录入\n");
    scanf("%d", &input_method);
    system("clear");
    switch (input_method)
    {
    case 1:
        /**手动录入**/
        printf("请输入想要添加的商品数量\n");
        scanf("%d", &input_num);
        system("clear");
        /*输入数组*/
        for (i = 0; i < input_num; i++)
        {
            printf("正在录入第%d件商品：\n", i + 1);
            printf("请输入号商品信息：\n");

            printf("货号：\n");
            scanf("%d", &item_array[i].id);

            printf("类别：\n");
            fflush(stdin);
            scanf("%s",&item_array[i].category);
            printf("名称：\n");
            fflush(stdin);
            scanf("%s",&item_array[i].name);

            printf("进价：\n");
            scanf("%d", &item_array[i].in_prize);
            printf("售价：\n");
            scanf("%d", &item_array[i].out_prize);
            printf("库存:(如为新增请输入“0”)\n");
            scanf("%d", &item_array[i].stock_quantity);
            printf("进货量：\n");
            scanf("%d", &item_array[i].purchase_quantity);
            printf("*以下日期输入均为 yyyy mm dd 格式*\n");
            printf("生产日期：\n");
            scanf("%d %d %d", &item_array[i].manufacture_date[0], &item_array[i].manufacture_date[1], &item_array[i].manufacture_date[2]);
            printf("进货日期：\n");
            scanf("%d %d %d", &item_array[i].in_date[0], &item_array[i].in_date[1], &item_array[i].in_date[2]);
            printf("保质期至：\n");
            scanf("%d %d %d", &item_array[i].expiry_date[0], &item_array[i].expiry_date[1], &item_array[i].expiry_date[2]);
            system("clear");
            printf("第%d件商品录入完成！\n", i + 1);
        }
        if (input_num == i && input_num!=1)
            printf("全部商品录入完成!\n");
        //进货加到库存
        for (i = 0; i < input_num; i++)
        {
            item_array[i].stock_quantity += item_array[i].purchase_quantity;
            item_array[i].purchase_quantity = 0;
        }
        /*输入文件*/
        for (i = 0; i < input_num; i++)
        {
            fprintf(fp, "\n%d ", item_array[i].id);
            fprintf(fp, "%s ", item_array[i].category);
            fprintf(fp, "%s ", item_array[i].name);
            fprintf(fp, "%d ", item_array[i].in_prize);
            fprintf(fp, "%d ", item_array[i].out_prize);
            fprintf(fp, "%d ", item_array[i].stock_quantity);
            fprintf(fp, "%d ", item_array[i].purchase_quantity);
            fprintf(fp, "%d %d %d ", item_array[i].manufacture_date[0], item_array[i].manufacture_date[1], item_array[i].manufacture_date[2]);
            fprintf(fp, "%d %d %d ", item_array[i].in_date[0], item_array[i].in_date[1], item_array[i].in_date[2]);
            fprintf(fp, "%d %d %d\n", item_array[i].expiry_date[0], item_array[i].expiry_date[1], item_array[i].expiry_date[2]);
        }

        printf("文件写入完成!\n");
        fclose(fp);
        sleep(2);
        break;

    case 2:
        /**文件录入**/
        system("clear");
        /*检测输入文件是否存在*/
        if ((infp = fopen("input.txt", "r")) == NULL)
        {
            printf("找不到输入文件");
            exit(0);
        }

        /*输入数组*/
        i=0;
        while (fscanf(infp, "%d", &item_array[i].id) != EOF)
        {
            fscanf(infp, "%d", &item_array[i].id);
            fscanf(infp, "%s", &item_array[i].category);
            fscanf(infp, "%s", &item_array[i].name);
            fscanf(infp, "%d", &item_array[i].in_prize);
            fscanf(infp, "%d", &item_array[i].out_prize);
            fscanf(infp, "%d", &item_array[i].stock_quantity);
            fscanf(infp, "%d", &item_array[i].purchase_quantity);
            fscanf(infp, "%d %d %d", &item_array[i].manufacture_date[0], &item_array[i].manufacture_date[1], &item_array[i].manufacture_date[2]);
            fscanf(infp, "%d %d %d", &item_array[i].in_date[0], &item_array[i].in_date[1], &item_array[i].in_date[2]);
            fscanf(infp, "%d %d %d", &item_array[i].expiry_date[0], &item_array[i].expiry_date[1], &item_array[i].expiry_date[2]);
            i++;
        }
        sum=i;
        fclose(infp);

        for (i = 0; i < sum; i++)
        {
            item_array[i].stock_quantity += item_array[i].purchase_quantity;
            item_array[i].purchase_quantity = 0;
        }
        /*成功录入数组提示*/
        printf("\n成功检测到如下%d件商品:\n",sum);
        for (i = 0; i < sum; i++)
        {
            printf("货号：%d \n", item_array[i].id);
            printf("类别：%s ", item_array[i].category);
            printf("名称：%s \n", item_array[i].name);
            printf("进价：%d ", item_array[i].in_prize);
            printf("售价：%d ", item_array[i].out_prize);
            printf("库存：%d ", item_array[i].stock_quantity);
            printf("\n生产日期:%d年%d月%d日 ", item_array[i].manufacture_date[0], item_array[i].manufacture_date[1], item_array[i].manufacture_date[2]);
            printf("\n进货日期:%d年%d月%d日 ", item_array[i].in_date[0], item_array[i].in_date[1], item_array[i].in_date[2]);
            printf("\n保质期至:%d年%d月%d日\n\n", item_array[i].expiry_date[0], item_array[i].expiry_date[1], item_array[i].expiry_date[2]);
        }
        if (sum == i)
            printf("全部商品录入完成!\n");

        /*输入数据库*/
        fprintf(fp, "\n");
        for (i = 0; i < sum; i++)
        {
            fprintf(fp, "%d ", item_array[i].id);
            fprintf(fp, "%s ", item_array[i].category);
            fprintf(fp, "%s ", item_array[i].name);
            fprintf(fp, "%d ", item_array[i].in_prize);
            fprintf(fp, "%d ", item_array[i].out_prize);
            fprintf(fp, "%d ", item_array[i].stock_quantity);
            fprintf(fp, "%d ", item_array[i].purchase_quantity);
            fprintf(fp, "%d %d %d ", item_array[i].manufacture_date[0], item_array[i].manufacture_date[1], item_array[i].manufacture_date[2]);
            fprintf(fp, "%d %d %d ", item_array[i].in_date[0], item_array[i].in_date[1], item_array[i].in_date[2]);
            fprintf(fp, "%d %d %d\n", item_array[i].expiry_date[0], item_array[i].expiry_date[1], item_array[i].expiry_date[2]);
        }

        /*输入成功提示*/
        printf("文件写入完成!\n");
        fclose(fp);
        sleep(2);
        break;
    }
}




//***4***退货函数定义***//
void back()
{
    /***变量定义***/
    int to_be_deleted, delete_num;
    int whether_continue = 1;

    /***检测数据库文件是否存在***/
    FILE *fp;
    if ((fp = fopen("database.txt", "r")) == NULL)
    {
        printf("找不到数据库文件");
        exit(0);
    }

    /***输入文件指针定义***/
    FILE *new_fp;

    /***退货***/
    system("clear");
    /**数据库导入数组**/
    i=0;
    while (fscanf(fp, "%d", &item_array[i].id) != EOF)
    {

        fscanf(fp, "%d", &item_array[i].id);
        fscanf(fp, "%s", &item_array[i].category);
        fscanf(fp, "%s", &item_array[i].name);
        fscanf(fp, "%d", &item_array[i].in_prize);
        fscanf(fp, "%d", &item_array[i].out_prize);
        fscanf(fp, "%d", &item_array[i].stock_quantity);
        fscanf(fp, "%d", &item_array[i].purchase_quantity);
        fscanf(fp, "%d %d %d", &item_array[i].manufacture_date[0], &item_array[i].manufacture_date[1], &item_array[i].manufacture_date[2]);
        fscanf(fp, "%d %d %d", &item_array[i].in_date[0], &item_array[i].in_date[1], &item_array[i].in_date[2]);
        fscanf(fp, "%d %d %d", &item_array[i].expiry_date[0], &item_array[i].expiry_date[1], &item_array[i].expiry_date[2]);
        i++;
    }
    sum=i;
    fclose(fp);

    /**展示数据库**/
    printf("\n数据库中有如下商品：\n");
    for (i = 0; i < sum; i++)
    {
        printf("货号：%d \n", item_array[i].id);
        printf("类别：%s ", item_array[i].category);
        printf("名称：%s \n", item_array[i].name);
        printf("进价：%d ", item_array[i].in_prize);
        printf("售价：%d ", item_array[i].out_prize);
        printf("库存：%d ", item_array[i].stock_quantity);
        printf("\n生产日期：%d年%d月%d日 ", item_array[i].manufacture_date[0], item_array[i].manufacture_date[1], item_array[i].manufacture_date[2]);
        printf("\n进货日期：%d年%d月%d日 ", item_array[i].in_date[0], item_array[i].in_date[1], item_array[i].in_date[2]);
        printf("\n保质期至：%d年%d月%d日\n\n", item_array[i].expiry_date[0], item_array[i].expiry_date[1], item_array[i].expiry_date[2]);
    }

    /**对数组修改**/
    while (whether_continue == 1)
    {
        /*获取想要删除商品的货号/数量*/
        printf("\n请输入想要退货的商品货号：\n");
        scanf("%d", &to_be_deleted);
        to_be_deleted -= 1;
        system("clear");
        printf("\n请输入想要退货的数量:\n");
        printf("(目前库存%d件)\n", item_array[to_be_deleted].stock_quantity);
        scanf("%d", &delete_num);

        /*删除操作*/
        item_array[to_be_deleted].stock_quantity -= delete_num;
        system("clear");
        printf("\n操作成功！\n");
        sleep(1);
        system("clear");

        /*继续操作*/
        printf("是否继续删除？\n");
        printf("1.继续删除\n");
        printf("2.停止删除\n");
        scanf("%d", &whether_continue);
        system("clear");
    }

    //***将数组写入新文件***//

    /*新建数据库*/
    if ((new_fp = fopen("database_new.txt", "w")) == NULL)
    {
        printf("已新建数据库文件");
        exit(0);
    }
    /*写入新database*/
    for (i = 0; i < sum; i++)
    {
        fprintf(new_fp, "%d ", item_array[i].id);
        fprintf(new_fp, "%s ", item_array[i].category);
        fprintf(new_fp, "%s ", item_array[i].name);
        fprintf(new_fp, "%d ", item_array[i].in_prize);
        fprintf(new_fp, "%d ", item_array[i].out_prize);
        fprintf(new_fp, "%d ", item_array[i].stock_quantity);
        fprintf(new_fp, "%d ", item_array[i].purchase_quantity);
        fprintf(new_fp, "%d %d %d ", item_array[i].manufacture_date[0], item_array[i].manufacture_date[1], item_array[i].manufacture_date[2]);
        fprintf(new_fp, "%d %d %d ", item_array[i].in_date[0], item_array[i].in_date[1], item_array[i].in_date[2]);
        fprintf(new_fp, "%d %d %d\n", item_array[i].expiry_date[0], item_array[i].expiry_date[1], item_array[i].expiry_date[2]);
    }
    fclose(new_fp);

    system("rm -rf database.txt");
    system("rename database_new.txt database.txt"); //第三次简报修改

    printf("\n数据库写入完成！\n");
}




//***5***显示库存功能***//
void disstore()
{
    /***检测数据库文件是否存在***/
    FILE *fp;
    if ((fp = fopen("database.txt", "r")) == NULL)
    {
        printf("找不到数据库文件");
        exit(0);
    }

    i = 0;
    while (fscanf(fp, "%d", &item_array[i].id) != EOF)
    {
        fscanf(fp, "%d", &item_array[i].id);
        fscanf(fp, "%s", &item_array[i].category);
        fscanf(fp, "%s", &item_array[i].name);
        fscanf(fp, "%d", &item_array[i].in_prize);
        fscanf(fp, "%d", &item_array[i].out_prize);
        fscanf(fp, "%d", &item_array[i].stock_quantity);
        fscanf(fp, "%d", &item_array[i].purchase_quantity);
        fscanf(fp, "%d %d %d", &item_array[i].manufacture_date[0], &item_array[i].manufacture_date[1], &item_array[i].manufacture_date[2]);
        fscanf(fp, "%d %d %d", &item_array[i].in_date[0], &item_array[i].in_date[1], &item_array[i].in_date[2]);
        fscanf(fp, "%d %d %d", &item_array[i].expiry_date[0], &item_array[i].expiry_date[1], &item_array[i].expiry_date[2]);
        i++;
    }
    sum=i;
    for (int j=0; j < sum; j++)
    {
        printf("货号：%d \n", item_array[j].id);
        printf("类别：%s ", item_array[j].category);
        printf("名称：%s \n", item_array[j].name);
        printf("进价：%d ", item_array[j].in_prize);
        printf("售价：%d ", item_array[j].out_prize);
        printf("库存：%d ", item_array[j].stock_quantity);
        printf("\n生产日期：%d年%d月%d日 ", item_array[j].manufacture_date[0], item_array[j].manufacture_date[1], item_array[j].manufacture_date[2]);
        printf("\n进货日期：%d年%d月%d日 ", item_array[j].in_date[0], item_array[j].in_date[1], item_array[j].in_date[2]);
        printf("\n保质期至：%d年%d月%d日\n\n", item_array[j].expiry_date[0], item_array[j].expiry_date[1], item_array[j].expiry_date[2]);
    }
    fclose(fp);
    printf("按任意键返回主菜单：\n");
    scanf("%d", &GoBack);   
}






//***6***购物车功能***//
void shop()
{
  while (1)
  {
    switch (shop_menu())
    {
    case 1:
      system("clear");
      disshop();
      system("clear");
      break; //***显示购物车商品

    case 2:
      system("clear");
      chanshop();
      system("clear");
      break; //***修改购物车商品

    case 3:
     return;
    }
  }
}




//***7***购物车菜单功能***//
int shop_menu()
{
  int select;
  printf("\n\t\t请选择操作\n");
  printf("\t-----------------------\n");
  printf("\t1.显示当前购物列表\n");
  printf("\t2.修改当前购物列表\n");
  printf("\t3.退出\n");
  printf("\t-----------------------\n\n");
  while (1)
  {
    fflush(stdin);
    scanf("%d",&select);
    if (select < 1 || select > 3)
      printf("输入错误，请重新输入:");
    else
      break;
  }
  return select;
}




//***8***显示购物车列表功能***//
void disshop()
{
  FILE *shopfp;
  if ((shopfp = fopen("shopping.txt", "r")) == NULL)
  {
    printf("找不到数据库文件");
    exit(0);
  }

  struct Goods //***购物车结构体定义***//
  {
    int code;
    char name[20];
    double price;
    double discount;     //折扣
    int number;          //数量
    double totalPayment; //总额
  };
  struct Goods goods[100];

  i = 0;
  while (fscanf(shopfp, "%d", &goods[i].code) != EOF)
  {
    fscanf(shopfp, "%s", &goods[i].name);
    fscanf(shopfp, "%lf", &goods[i].price);
    fscanf(shopfp, "%lf", &goods[i].discount);
    fscanf(shopfp, "%d", &goods[i].number);
    fscanf(shopfp, "%lf", &goods[i].totalPayment);
    i++;
  }
  sum=i;
  if(i==0)
  {
	  printf("购物车中没有商品！\n");
  }
  for (int j = 0; j < sum; j++)
  {
    printf("货号是：%d \n", goods[j].code);
    printf("货物名字是：%s \n", goods[j].name);
    printf("价格是：%lf \n", goods[j].price);
    printf("折扣是：%lf \n", goods[j].discount);
    printf("数量是：%d \n", goods[j].number);
    printf("总价是：%lf \n\n", goods[j].totalPayment);
  }

  fclose(shopfp);
  printf("按任意键继续...");
  scanf("%d",&GoBack);

}






//***9***修改购物车函数功能***//
void chanshop()
{
  /***检测数据库文件是否存在***/
  FILE *fp;
  if ((fp = fopen("database.txt", "r")) == NULL)
  {
    printf("找不到数据库文件");
    exit(0);
  }

  FILE *shopfp;
  if ((shopfp = fopen("shopping.txt", "a+")) == NULL)
  {
    printf("找不到数据库文件");
    exit(0);
  }

  i = 0;
  while (fscanf(fp, "%d ", &item_array[i].id) != EOF)
  {
    fscanf(fp, "%s ", &item_array[i].category);
    fscanf(fp, "%s ", &item_array[i].name);
    fscanf(fp, "%d ", &item_array[i].in_prize);
    fscanf(fp, "%d ", &item_array[i].out_prize);
    fscanf(fp, "%d ", &item_array[i].stock_quantity);
    fscanf(fp, "%d ", &item_array[i].purchase_quantity);
    fscanf(fp, "%d %d %d", &item_array[i].manufacture_date[0], &item_array[i].manufacture_date[1], &item_array[i].manufacture_date[2]);
    fscanf(fp, "%d %d %d", &item_array[i].in_date[0], &item_array[i].in_date[1], &item_array[i].in_date[2]);
    fscanf(fp, "%d %d %d\n", &item_array[i].expiry_date[0], &item_array[i].expiry_date[1], &item_array[i].expiry_date[2]);
    i++;
  }
  fclose(fp);
  sum=i;
  /**展示数据库**/
  printf("\n\t数据库中有如下商品：\n");
  for (i = 0; i < sum; i++)
  {
    printf("货号：%d \n", item_array[i].id);
    printf("类别：%s ", item_array[i].category);
    printf("名称：%s \n", item_array[i].name);
    printf("进价：%d ", item_array[i].in_prize);
    printf("售价：%d ", item_array[i].out_prize);
    printf("库存：%d ", item_array[i].stock_quantity);
    printf("\n生产日期：%d年%d月%d日 ", item_array[i].manufacture_date[0], item_array[i].manufacture_date[1], item_array[i].manufacture_date[2]);
    printf("\n进货日期：%d年%d月%d日 ", item_array[i].in_date[0], item_array[i].in_date[1], item_array[i].in_date[2]);
    printf("\n保质期至：%d年%d月%d日\n\n", item_array[i].expiry_date[0], item_array[i].expiry_date[1], item_array[i].expiry_date[2]);
  }

  struct Goods //***购物车结构体定义***//
  {
    int code;
    char name[30];
    float price;
    float discount;     //折扣
    int number;          //数量
    float totalPayment; //总额
  };
  struct Goods goods[100];
  int e;

  for (e = 0; e < 100; e++)
    goods[e].code = 0;
  printf("-----------------------------------------------\n");
  printf("请选择添加商品到购物车，或者从购物车中删除商品\n");
  printf("\t\t1.添加商品\n");
  printf("\t\t2.删除商品\n");
  scanf("%d", &input_method);
  system("clear");
  switch (input_method)
  {

  case 1:
  {

    //***添加商品***//
    char choicex[200];
    do
    {

      printf("\t请输入想要加入购物车的商品货号：\n");
      scanf("%d", &input_id);

      /**搜索商品**/
      int t;
      for (i = 0; i < sum; i++)
      {
        if (item_array[i].id == input_id)
        {
    
          system("clear");
          t = i;
          printf("\t库中有此商品，商品信息为：\n");
          printf("货号：%d \n", item_array[i].id);
          printf("类别：%s \n", item_array[i].category);
          printf("名称：%s \n", item_array[i].name);
          printf("进价：%d \n", item_array[i].in_prize);
          printf("售价：%d \n", item_array[i].out_prize);
          printf("库存：%d \n", item_array[i].stock_quantity);
          printf("生产日期：%d年%d月%d日\n", item_array[i].manufacture_date[0], item_array[i].manufacture_date[1], item_array[i].manufacture_date[2]);
          printf("进货日期：%d年%d月%d日\n", item_array[i].in_date[0], item_array[i].in_date[1], item_array[i].in_date[2]);
          printf("保质期至：%d年%d月%d日\n", item_array[i].expiry_date[0], item_array[i].expiry_date[1], item_array[i].expiry_date[2]);

          char choicey[200];
          printf("\n\t是否将此商品加入购物车？(是Y/否N）\n");
          fflush(stdin);
          choicey[200] = getchar();//***开始往购物车添加商品***//
          if (choicey[200] == 'Y' || choicey[200] == 'y')
          {
            printf("\t请问想要添加多少件该商品到购物车？\n");
            int k;
            scanf("%d", &k);
            if (k > item_array[t].stock_quantity)
            {
              printf("\t库存不足!\n");
              break;
            }
            else //***将商品信息添加至goods结构体数组中
            {
              int j = 0;
              while (goods[j].code != 0) //此处如果不等于0，则说明结构体数组的这一项已经有商品了，所以跳到下一个
              {
                j++;
              }

              goods[j].code = item_array[t].id;
              strcpy(goods[j].name,item_array[t].name);
              goods[j].number = k;
              goods[j].price = item_array[t].out_prize;
              item_array[j].stock_quantity = item_array[t].stock_quantity - k;
              goods[j].totalPayment = k * item_array[t].out_prize;
              printf("\n\t添加商品至购物车成功！\n");
              
              
              fprintf(shopfp, "%d ", goods[i].code);
              fprintf(shopfp, "%s ", goods[i].name);
              fprintf(shopfp, "%f ", goods[i].price);
              fprintf(shopfp, "%f ", goods[i].discount);
              fprintf(shopfp, "%d ", goods[i].number);
              fprintf(shopfp, "%f \n", goods[i].totalPayment);

              /*输入成功提示*/
              printf("\t文件写入完成!\n");

              fclose(shopfp);
               
            }
            break;
          }
        }
      }
       
       if(i==sum)
        {
          printf("\n\t查无此商品\n");
          break;
        }

      printf("\n\t是否继续购物?(是Y/否N)\n");
      fflush(stdin);
      choicex[200] = getchar();
    } while (choicex[200] == 'Y' || choicex[200] == 'y'); //***do-while函数判断***//
    break;
  }

  case 2:
  {

    //***删除商品***//
    char choicew[200];
    do
    {/***变量定义***/
    int to_be_deleted, delete_num;
    int whether_continue = 1;

    /***检测数据库文件是否存在***/
    FILE *oldfp;
    if ((oldfp = fopen("shopping.txt", "r")) == NULL)
    {
        printf("找不到数据库文件");
        exit(0);
    }

    /***输入文件指针定义***/
    FILE *new_fp;

    /***退货***/
    system("clear");
    /**数据库导入数组**/
    i=0;
    while (fscanf(oldfp, "%d", &goods[i].code) != EOF)
    {

        fscanf(oldfp, "%d", &goods[i].code);
        fscanf(oldfp, "%s", &goods[i].name);
        fscanf(oldfp, "%f", &goods[i].price);
        fscanf(oldfp, "%d", &goods[i].discount);
        fscanf(oldfp, "%d", &goods[i].number);
        fscanf(oldfp, "%f", &goods[i].totalPayment);
        i++;
    }
    sum=i;
    fclose(oldfp);


      printf("\t请输入想要删除的商品货号\n");
      int deleid;
      scanf("%d", &deleid);
      int i;
      for (i = 0; i < sum; i++)
      {
        if (deleid == goods[i].code)
        {
          printf("\t此商品在购物车中有，数量是%d", goods[i].number);
          printf("\t请问是否删除?(是Y/否N)\n");
          char choicez[200];
          choicez[200] = getchar();
          if (choicez[200] == 'Y' || choicez[200] == 'y')
          {
            printf("\t请输入删除数量\n");
            int delenum;
            scanf("%d", &delenum);
            goods[i].number = goods[i].number - delenum;
            break;
          }

          //***将数组写入新文件***//

            /*新建数据库*/
       
              if ((new_fp = fopen("shopping_new.txt", "w")) == NULL)
            {
                printf("已新建数据库文件");
                exit(0);
            }
     

                 for(i=0;i<sum;i++)
             {
                fprintf(new_fp, "%d ", goods[i].code);
                fprintf(new_fp, "%s ", goods[i].name);
                fprintf(new_fp, "%d ", goods[i].number);
                fprintf(new_fp, "%f ", goods[i].price);
                fprintf(new_fp, "%f ", goods[i].discount);
                fprintf(new_fp, "%f\n", goods[i].totalPayment);
             }

              fclose(new_fp);
              system("rm -rf shopping.txt");
              system("rename shopping_new.txt shopping.txt"); 
              printf("\n数据库写入完成！\n");

        }
      }
      


    } while (choicew[200] == 'Y' || choicew[200] == 'y'); //***do-while函数判断***//
    break;
  }
  }
}




//***10***计算功能***//
void calculate()
{
	int calculate_menu(),calculate_all(),fangkui_txt();
	while(1)
	{
		switch(calculate_menu())
		{
			case 1:system("clear");calculate_all();lijian=0;break;//***计算购物车内的商品总价 
			
			case 2:system("clear");calculate_all();lijian=0;break;
			
			case 3:system("clear");calculate_all();lijian=1;break;
			
			case 4:system("clear");calculate_all();lijian=0;break;
			
			case 5:system("clear");fangkui_txt();break;

			case 6:return;//***返回
		}
	}
}



//***11***计算购物车内的商品总价的菜单**//
int calculate_menu()
{
	char  import[5];
	int   select;
	printf("\n请选择操作\n");
	printf("-----------------------\n");
	printf("1.微信支付\n");
	printf("2.支付宝支付\n");
	printf("3.银行卡支付\n");
	printf("4.现金支付\n");
	printf("5.商品反馈\n");
	printf("6.退出\n");
	printf("-----------------------\n\n");
	
	while (1)
	{
		fflush(stdin);
		gets(import);
		select = atoi(import);
		if (select<1 || select>7)
			printf("\n输入错误，请重新输入:");
		else
			break;
	}
	return select;
} 



//***让顾客反映超市没有但需要的商品***//
int fangkui_txt()
{
	
	printf("请输入需要的商品，但是超市目前还没有的，我们将会马上准备，感谢您的谅解！\n") ;
    struct Need
	{
        char name[200];	 
	} ;
    struct Need need[100]={0};
    /**手动录入**/
	printf("请输入想要添加的商品数量\n");
	scanf("%d",&input_num);
	/*输入数组*/
	for(i=0;i<input_num;i++)
	{
		printf("正在录入第%d件商品：\n",i+1);
		printf("请输入所需商品信息：\n");
		fflush(stdin);
		gets(need[i].name);
	}
	/***检测需求文件是否存在***/
	FILE *rfp;
	if((rfp=fopen("require.txt","a+"))==NULL)
	{
		printf("\n找不到需求文件");
		exit(0);
	}//***录入文件***// 
	for(i=0;i<input_num;i++)
		{
            fprintf(rfp,"%s ",need[i].name);
        }

	/*输入成功提示*/
	printf("\n已成功提交您的需求，我们将会第一时间为你解决!");
	
	fclose(rfp);
} 


struct viper
{
    char name[30];    //会员姓名
    int id;           //会员卡号码
    int phone;        //会员电话
    int money;        //会员卡储值
    int integal;      //会员积分 
}vipers[1000];

//***12计算购物车内的商品总价***//
int calculate_all()
{
  time_t tmpcal_ptr;
  struct tm *tmp_ptr = NULL; //定义系统时间结构体
  struct Goods               //***购物车结构体定义***//
  {
    int code;
    char name[20];
    double price;
    double discount;         //折扣
    int number;              //数量
    double totalPayment;     //总额
    int manufacture_date[3]; //生产日期
    int in_date[3];          //进货日期
    int expiry_date[3];      //保质期
  };
  struct Goods goods[100] = {0};

  /***检测购物车文件是否存在***/
  FILE *profitfp, *pff;
  if ((profitfp = fopen("shopping.txt", "a+")) == NULL)
  {
    printf("找不到购物车文件\n");
    exit(0);
  }

  int i = 0;
  while (fscanf(profitfp, "%d", &goods[i].code) != EOF)
  {
    fscanf(profitfp, "%s", &goods[i].name);
    fscanf(profitfp, "%lf", &goods[i].price);
    fscanf(profitfp, "%lf", &goods[i].discount);
    fscanf(profitfp, "%d", &goods[i].number);
    fscanf(profitfp, "%lf", &goods[i].totalPayment);
    fscanf(profitfp, "\n生产日期：%d年%d月%d日  ", &goods[i].manufacture_date[0], &goods[i].manufacture_date[1], &goods[i].manufacture_date[2]);
    fscanf(profitfp, "\n进货日期：%d年%d月%d日  ", &goods[i].in_date[0], &goods[i].in_date[1], &goods[i].in_date[2]);
    fscanf(profitfp, "\n保质期至：%d年%d月%d日\n\n", &goods[i].expiry_date[0], &goods[i].expiry_date[1], &goods[i].expiry_date[2]);
    i++;
  }
  int sum = i;

  /***根据保质期给用户折扣***/
  int now_day, now_month, now_year;
  time_t timep;
  struct tm *p;
  char time1[28];
  time(&timep);
  p = gmtime(&timep);
  now_day = p->tm_mday;         /*获取当前月份日数,范围是1-31*/
  now_month = 1 + p->tm_mon;    /*获取当前月份,范围是0-11,所以要加1*/
  now_year = 1900 + p->tm_year; /*获取当前年份,从1900开始，所以要加1900*/

  double day1, day2;
  double date(int n, int m1, int d1, int m, int m2, int d2);
  int discount;
  for (i = 0; i < sum; i++)
  {
    day1 = date(now_year, now_month, now_day, goods[i].expiry_date[0], goods[i].expiry_date[1], goods[i].expiry_date[2]);

    if (day1 < 10.0)
    {
      goods[i].totalPayment = 0.8 * goods[i].totalPayment;
    }
    if (day1 < 20.0)
    {
      goods[i].totalPayment = 0.9 * goods[i].totalPayment;
    }
    if (day1 < 30.0)
    {
      goods[i].totalPayment = 0.95 * goods[i].totalPayment;
    }
  }

    double TotalPayment;
    

	for(i=0;i<sum;i++)
	{
		//***商品拆分 
		if(strcmp(goods[i].name,"milk")==0)
    {
        printf("您的购物车中现有一箱12瓶的牛奶，是否购买其中的几瓶牛奶？\n");
        printf("1.是\n");
        printf("2.否\n");
        int i=0,choice;
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            {
            
			printf("请输入要购买的数量：");
            double price=0;
            int count=0;
            scanf("%d",&count);
            double total=0;
            double one_price=8.0;//***一瓶牛奶的价格 
            total=count*one_price*1.0;
            goods[i].totalPayment=total; 
            printf("已购买%d瓶牛奶",count);
            
            }break;
			
            case 2:
			{
			TotalPayment=TotalPayment;
			break;	
		    }	
		} 
	    
		TotalPayment=TotalPayment+goods[i].totalPayment;//***计算购物车内商品总价 
    }
    }

	fclose(profitfp);
	
	
	
	//***捆绑销售 
    

    for(i=0;i<sum;i++)
{
		
        if(strcmp(goods[i].name,"toothpaste")==0)
    {
		printf("是否购买牙刷？和牙膏一起购买能够更优惠哦！\n");
        printf("1.是\n");
        printf("2.否\n");
        
        int i=0,choice;
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            {
            	
            /***检测数据库文件是否存在***/
            FILE *fp;
            if ((fp = fopen("database.txt", "a+")) == NULL)
            {
                printf("找不到数据库文件");
                exit(0);
            }
            int sum = 0;
            /**数据库导入数组**/
            int i = 0;
            
            
            while (fscanf(fp, "%d", &item_array[i].id) != EOF)
            {
                fscanf(fp, "%s", &item_array[i].category);
                fscanf(fp, "%s", &item_array[i].name);
                fscanf(fp, "%d", &item_array[i].in_prize);
                fscanf(fp, "%d", &item_array[i].out_prize);
                fscanf(fp, "%d", &item_array[i].stock_quantity);
                fscanf(fp, "%d", &item_array[i].purchase_quantity);
                fscanf(fp, "%d %d %d", &item_array[i].manufacture_date[0], &item_array[i].manufacture_date[1], &item_array[i].manufacture_date[2]);
                fscanf(fp, "%d %d %d", &item_array[i].in_date[0], &item_array[i].in_date[1], &item_array[i].in_date[2]);
                fscanf(fp, "%d %d %d", &item_array[i].expiry_date[0], &item_array[i].expiry_date[1], &item_array[i].expiry_date[2]);
                i++;
            }
            
            
            sum=i;
			printf("请输入要购买的数量：");
            double count,price=0;
            scanf("%lf",&count);
            
            for (i = 0; i < sum; i++)
            {
            	if(strcmp(goods[i].name,"toothbrush")==0)
            	{
            		item_array[i].stock_quantity=item_array[i].stock_quantity-count;
            		price=item_array[i].out_prize;
				}
            }
            
            
            double total;
            total=count*1.0*price;
			TotalPayment=25;
            break;
            }
            
            
			case 2:
			{
			TotalPayment=TotalPayment;
			break;	
			} 
	    }
    }
}

  double newPayment;
  if (lijian == 0)
  {
    newPayment = TotalPayment;
    printf("本店会根据保质日期给您相应折扣，根据此次购物，则总价为：%lf", newPayment);
  }

  /***进行随机立减功能***/
  /***随机数的取值***/
  //***srand()用来设置rand()产生随机数时的随机数种子。参数seed必须是个整数，通常可以利用geypid()或time(0)的返回值来当做seed
  if (lijian == 1)
  {
    srand(time(0));
    double newPayment;
    newPayment = TotalPayment - (rand() % 10) * 0.01 * TotalPayment;
    scanf("\n并且由于是使用银行卡支付，本店有随机立减的优惠，则最后的总价为：%f\n", newPayment);
  }

  //***记录本次购物的交易额

  //记录时间
  time(&tmpcal_ptr);
  tmp_ptr = localtime(&tmpcal_ptr);


  //记录流水
  void profit(double TotalPayment, \
  int  tm_year,int  tm_mon,int tm_mday,\
  int  tm_hour,int  tm_min,int tm_sec,\
  char name20,float price,float discount,int number,\
  int expiry_date0, int expiry_date1, int expiry_date2,\
  int manufacture_date0, int manufacture_date1, int manufacture_date2,\
  int in_date0, int in_date1,int in_date2);


  profit(newPayment, tmp_ptr->tm_year, (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday,\
  tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec,\
  goods[i].name[20],goods[i].price,goods[i].discount,goods[i].number,\
  goods[i].expiry_date[0],goods[i].expiry_date[1],goods[i].expiry_date[2],\
  goods[i].manufacture_date[0],goods[i].manufacture_date[1],goods[i].manufacture_date[2],\
  goods[i].in_date[0],goods[i].in_date[1],goods[i].in_date[2]);

  //***会员结算功能
  printf("请输入会员卡号：");
  int card;
  scanf("%d", &card);
  FILE *fps;
  if ((fps = fopen("vip_new.txt", "a+")) == NULL)
  {
    printf("找不到数据库文件");
    exit(0);
  }

  struct viper vipers[1000];
  while (fscanf(fps, "%d", &vipers[i].id) != EOF)
  {
    fscanf(fps, "%s", &vipers[i].name);
    fscanf(fps, "%d", &vipers[i].id);
    fscanf(fps, "%d", &vipers[i].phone);
    fscanf(fps, "%d", &vipers[i].money);
    i++;
  }

  if (card == vipers[i].id) /***将会员卡中的钱进行结算***/
  {
    printf("请输入要支付的金额：");
    int momey_income;
    scanf("%d", &momey_income);
    vipers[i].integal = momey_income; /***记录会员卡中的积分***/

    if (vipers[i].money >= momey_income)
    {
      vipers[i].money = vipers[i].money - momey_income;
    }
    else if (vipers[i].money < momey_income)
    {
      printf("很抱歉，余额不足，请充值！\n");
    }

    //***将新信息写进新文件
    for (i = 0; i < sum; i++)
    {
      fprintf(fps, "%s ", vipers[i].name);
      fprintf(fps, "%d ", vipers[i].id);
      fprintf(fps, "%d ", vipers[i].phone);
      fprintf(fps, "%d\n", vipers[i].money);
      fprintf(fps, "%d\n", vipers[i].integal);
      i++;
    }
    fclose(fps);
  }

  printf("\n谢谢惠顾，欢迎下次购物！");

  /***清空购物车文件中的内容***/
  pff = fopen("shopping.txt", "w");
  if (pff)
  {
    printf("\n购物车物品已清空");
    fclose(pff);
  }
}



//***12.5计算两个日期相差的天数***//
double date(int n, int m1, int d1, int m, int m2, int d2)  //为了主函数较简洁  函数体部分如下
{
	int i,j,k,t1,t2,q,y,sum = 0;
	int a[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };/*数组中第一个元素直接赋值为0，与月份相对应*/
	for (i = n; i <= m; i++)        /*外层循环，从开始年份开始自增循环+1年直到你输入的年份*/
	{
		if (i == n)
			t1 = m1;   //将起始月份赋值给变量t1
		else t1 = 1;   //当年份自增后  月份开始赋值为1（除起始年份和目标年份外 ）
		if (i == m)   
			t2 = m2;   //当i自增到目标月份时 将目标月份的值赋给t2
		else t2 = 12;    
		for (j = t1; j <= t2; j++)  //t1,t2用来计算相应的月份差
		{
			if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)//判断是否为闰年，若为闰年将二月份重新赋值为29天
				a[2] = 29;
			else a[2] = 28;    
			if (i == n && j == m1)    
				q = d1;
			else q = 1;
			if (i == n && j == m2)
				y = d2;
			else y = a[j];
			for (k =q; k <= y;k++)
			{
				sum++;        //算每个月份相差多少天
			}
		}
	}
	return sum;   //返回值就是两个日期之前相差的天数了
}




//***13***记录每次购物的交易额***/
void profit(double TotalPayment, int  tm_year,int  tm_mon,int tm_mday,int  tm_hour,int  tm_min,int tm_sec,\
  char name,float price,float discount,int number,\
  int expiry_date0, int expiry_date1, int expiry_date2,\
  int manufacture_date0, int manufacture_date1, int manufacture_date2,\
  int in_date0, int in_date1,int in_date2)
{
  /***检测交易额文件是否存在***/
  FILE *profitfp;
  if ((profitfp = fopen("profit.txt", "a+")) == NULL)
  {
    printf("\n找不到交易额文件");
    exit(0);
  }

  fscanf(profitfp, "%.2f ", &TotalPayment);
  fscanf(profitfp, "%d %d %d", tm_year, tm_mon, tm_mday);
  fscanf(profitfp, "%d %d %d ", tm_hour, tm_min, tm_sec);
  fscanf(profitfp, "%s ",name);
  fscanf(profitfp, "%.2f ",price);
  fscanf(profitfp, "%.2f ",discount);
  fscanf(profitfp, "%d",number);
  fscanf(profitfp, "%d %d %d ", expiry_date0, expiry_date1, expiry_date2);
  fscanf(profitfp, "%d %d %d ", manufacture_date0, manufacture_date1, manufacture_date2);
  fscanf(profitfp, "%d %d %d \n", in_date0, in_date1,in_date2);

  /*输入成功提示*/
  printf("\n\t\t(已成功录入流水）");

  fclose(profitfp);
}




//***14***查找函数定义***//
void search()
{

  /***检测数据库文件是否存在***/
  FILE *fp;
  if ((fp = fopen("database.txt", "a+")) == NULL)
  {
    printf("找不到数据库文件");
    exit(0);
  }

  /***查找***/
  printf("\t请输入想要查找商品的货号：\n");
  scanf("%d", &input_id);
  /**数据库导入数组**/
  int i = 0;
  while (fscanf(fp, "%d", &item_array[i].id) != EOF)
  {
    fscanf(fp, "%s", &item_array[i].category);
    fscanf(fp, "%s", &item_array[i].name);
    fscanf(fp, "%d", &item_array[i].in_prize);
    fscanf(fp, "%d", &item_array[i].out_prize);
    fscanf(fp, "%d", &item_array[i].stock_quantity);
    fscanf(fp, "%d", &item_array[i].purchase_quantity);
    fscanf(fp, "%d %d %d", &item_array[i].manufacture_date[0], &item_array[i].manufacture_date[1], &item_array[i].manufacture_date[2]);
    fscanf(fp, "%d %d %d", &item_array[i].in_date[0], &item_array[i].in_date[1], &item_array[i].in_date[2]);
    fscanf(fp, "%d %d %d", &item_array[i].expiry_date[0], &item_array[i].expiry_date[1], &item_array[i].expiry_date[2]);
    i++;
  }
  /**搜索商品**/
  i = i - 1;
  int j;
  for (j = i; j >= 0; j--)
  {
    if (item_array[j].id == input_id)
    {
      printf("\t库中仍有此商品，商品信息为：\n");
      printf("货号：%d \n", item_array[j].id);
      printf("类别：%s \n", item_array[j].category);
      printf("名称：%s \n", item_array[j].name);
      printf("进价：%d \n", item_array[j].in_prize);
      printf("售价：%d \n", item_array[j].out_prize);
      printf("库存：%d \n", item_array[j].stock_quantity);
      printf("生产日期：%d年%d月%d日\n", item_array[j].manufacture_date[0], item_array[j].manufacture_date[1], item_array[j].manufacture_date[2]);
      printf("进货日期：%d年%d月%d日\n", item_array[j].in_date[0], item_array[j].in_date[1], item_array[j].in_date[2]);
      printf("保质期至：%d年%d月%d日\n", item_array[j].expiry_date[0], item_array[j].expiry_date[1], item_array[j].expiry_date[2]);
      break;
    }
  }
  sleep(3);
  if (j < 0)
  {
    printf("\t查无此商品\n");
  }
  fclose(fp);
}





//***15***显示函数的菜单函数***//
void dismenu()
{
       while(1)
       {
        sleep(1);
        system("clear");
    printf("\n\t\t请选择数字进行操作\n");
    printf("\t\t1.显示所有商品信息\n");
    printf("\t\t2.按类别显示商品\n");
    printf("\t\t3.按货号大小排序商品进行显示\n");
    printf("\t\t4.退出\n");
        
        int input = 0;
        scanf("%d",&input);
        switch (input) //选择函数，选择功能
        {
        case 1:
            system("clear");
            disstore();
            break;

        case 2:
            system("clear");
            category();
            break;

        case 3:
            system("clear");
            rank();
            break;

        case 4:
            return;
            
        }
        
        }
    
}




//***创建一个结构体***//
typedef struct product
{
    int id;                  //货号
    char category[10];       //类型
    char name[30];           //名称
    int out_prize;           //售价
    int stock_quantity;      //总库存
    int manufacture_date[3]; //生产日期
    int expiry_date[3];      //保质期
}PRODUCT;




//***16-1***交换函数***//
void swap(PRODUCT *A, PRODUCT *B)
{
    PRODUCT temp;

    temp = *A;
    *A = *B;
    *B = temp;
}




//***16-2***降序函数***//
int down(int a, int b)
{
    if (a > b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



//***16-3***升序函数***//
int up(int a, int b)
{
    if (a < b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



//***16-4***输出一条功能函数***//
void output(PRODUCT user)
{
    printf("%d %s %d %d\n", user.id, user.category, user.out_prize, user.stock_quantity);
}




//***16-5***自定义函数输出所有条目***//
void output_all(PRODUCT *list, int length)
{
    printf("ID   UserName   Income   Expenses\n");

    for (int i = 0; i < length; i++)
    {
        output(list[i]);
    }
}





//***16-6***指针传参排序函数***//
void sortrank(PRODUCT *list, int length, int strategy)
{
    int (*p)(int, int); // 定义一个函数指针

    if (strategy == 1)
    {
        // 升序
        p = up;
    }
    else
    {
        // 降序
        p = down;
    }

    for (int i = 0; i < length - 1; i++)
    {
        for (int k = 0; k < length - 1 - i; k++)
        {
            if (p(list[k].id, list[k + 1].id))
            {
                swap(&(list[k]), &(list[k + 1]));
            }
        }
    }
}





//***16***排序输出函数***//
void rank()
{
 /***检测数据库文件是否存在***/
  FILE *fp;
  if ((fp = fopen("database.txt", "a+")) == NULL)
  {
    printf("找不到数据库文件");
    exit(0);
  }
 
 
  int sum = 0;
  /**数据库导入数组**/
  int i = 0;
  while (fscanf(fp, "%d", &item_array[i].id) != EOF)
  {
    fscanf(fp, "%s", &item_array[i].category);
    fscanf(fp, "%s", &item_array[i].name);
    fscanf(fp, "%d", &item_array[i].in_prize);
    fscanf(fp, "%d", &item_array[i].out_prize);
    fscanf(fp, "%d", &item_array[i].stock_quantity);
    fscanf(fp, "%d", &item_array[i].purchase_quantity);
    fscanf(fp, "%d %d %d", &item_array[i].manufacture_date[0], &item_array[i].manufacture_date[1], &item_array[i].manufacture_date[2]);
    fscanf(fp, "%d %d %d", &item_array[i].in_date[0], &item_array[i].in_date[1], &item_array[i].in_date[2]);
    fscanf(fp, "%d %d %d", &item_array[i].expiry_date[0], &item_array[i].expiry_date[1], &item_array[i].expiry_date[2]);
    i++;
  }
   sum=i;
   PRODUCT item_list[100];//***给PRODUCT结构体定义
   
   for(i=0;i<sum;i++)//***循环赋值给item_list[100]
   {
      item_list[i].id=item_array[i].id;
      strcpy(item_list[i].name,item_array[i].name);
      strcpy(item_list[i].category,item_array[i].category);
      item_list[i].out_prize=item_array[i].out_prize;
      item_list[i].expiry_date[0]=item_array[i].expiry_date[0];
      item_list[i].expiry_date[1]=item_array[i].expiry_date[1];
      item_list[i].expiry_date[2]=item_array[i].expiry_date[2];
      item_list[i].stock_quantity=item_array[i].stock_quantity;
      item_list[i].manufacture_date[0]=item_array[i].manufacture_date[0];
      item_list[i].manufacture_date[1]=item_array[i].manufacture_date[1];
      item_list[i].manufacture_date[2]=item_array[i].manufacture_date[2];
   }

   printf("请输入升序还是降序排列：升序1/降序0\n");
   int p;
   scanf("%d",&p);

   sortrank(item_list,sum,p);//***调用冒泡排序函数进行排序
   output_all(item_list,sum);//***调用输出函数全部输出
 sleep(100);
}





//***17***分类查找函数***//
void category()
{
  /***检测数据库文件是否存在***/
  FILE *fp;
  if ((fp = fopen("database.txt", "a+")) == NULL)
  {
    printf("找不到数据库文件");
    exit(0);
  }
 


 
  int sum = 0;
  /**数据库导入数组**/
  int i = 0;
  while (fscanf(fp, "%d", &item_array[i].id) != EOF)
  {
    fscanf(fp, "%s", &item_array[i].category);
    fscanf(fp, "%s", &item_array[i].name);
    fscanf(fp, "%d", &item_array[i].in_prize);
    fscanf(fp, "%d", &item_array[i].out_prize);
    fscanf(fp, "%d", &item_array[i].stock_quantity);
    fscanf(fp, "%d", &item_array[i].purchase_quantity);
    fscanf(fp, "%d %d %d", &item_array[i].manufacture_date[0], &item_array[i].manufacture_date[1], &item_array[i].manufacture_date[2]);
    fscanf(fp, "%d %d %d", &item_array[i].in_date[0], &item_array[i].in_date[1], &item_array[i].in_date[2]);
    fscanf(fp, "%d %d %d", &item_array[i].expiry_date[0], &item_array[i].expiry_date[1], &item_array[i].expiry_date[2]);
    i++;
  }
   sum=i;
   
   
   for (int j=0; j < sum; j++)
    {
        if(strcmp(item_array[j].category,"food")==0)
        {
          printf("--------------------------------------------\n");
          printf("类别为food的商品有：");
			    printf("货号       品名           单价    数量\n");
          printf("%s       %s            %d      %d\n",item_array[j].category,item_array[j].name,item_array[j].out_prize,item_array[j].stock_quantity);
        }
    }



}



struct worker
{
    char name[30];    //员工名字
    int number;       //工号
    int workday;      //签到次数
}workers[1000];



//***会员管理函数
void vip()
{
  
  FILE *fp;
  if ((fp = fopen("vip.txt", "a+")) == NULL)
  {
    printf("找不到数据库文件");
    exit(0);
  }

  printf("请选择:\n");
  printf("1.会员注册\n");
  printf("2.会员卡充值\n");
  
  
  int choice;
  scanf("%d",&choice);
  switch(choice)
  {
    case 1:                    //***会员注册信息录入
    {
      printf("请输入会员姓名：\n");
      scanf("%s",&vipers[0].name);

      printf("请输入会员卡卡号：\n");
      scanf("%d",&vipers[0].id);

      printf("请输入会员电话号码：\n");
      scanf("%d",&vipers[0].phone);

      printf("请输入储值金额：\n");
      scanf("%d",&vipers[0].money);


      fprintf(fp,"%s ",vipers[0].name);
      fprintf(fp,"%d ",vipers[0].id);
      fprintf(fp,"%d ",vipers[0].phone);
      fprintf(fp,"%d\n",vipers[0].money);
      printf("会员注册完成！");

      fclose(fp);

      break;

    }

    case 2:                    //***会员卡充值
    {
        
        FILE *fps;
      if ((fps = fopen("vip.txt", "a+")) == NULL)
      {
        printf("找不到数据库文件");
        exit(0);
      }

      int i = 0;
      int sum = 0;
      while (fscanf(fps, "%d", &vipers[i].id) != EOF)   //录入文件内的会员信息
      {
        fscanf(fps, "%s", &vipers[i].name);
        fscanf(fps, "%d", &vipers[i].id);
        fscanf(fps, "%d", &vipers[i].phone);
        fscanf(fps, "%d\n", &vipers[i].money);
        i++;
      }

      sum = i;

      fclose(fps);

    
       FILE *fps_new;
      if ((fps_new = fopen("vip_new.txt", "a+")) == NULL)
      {
        printf("找不到数据库文件");
        exit(0);
      }


      printf("请输入会员卡号：");
      int card;
      scanf("%d",&card);

      
      
      for(i=0;i<sum;i++)
      {
        if(card == vipers[i].id)    //***进行充值，修改money的值
        {
          printf("请输入充值金额：");
          int momey_income;
          scanf("%d",&momey_income);
          vipers[i].money = vipers[i].money + momey_income;
        }
      }

      for(i=0;i<sum;i++)           //***将新信息写进新文件
      {
        fprintf(fps_new, "%s ", vipers[i].name);
        fprintf(fps_new, "%d ", vipers[i].id);
        fprintf(fps_new, "%d ", vipers[i].phone);
        fprintf(fps_new, "%d\n", vipers[i].money);
      }


     system("rm -rf vip.txt");//****这里有问题,删除旧文件无法删除
     system("rename vip_new.txt vip.txt");//***修改新文件名

     break;



    }
  }


}        



//***员工签到函数
void sign_in()
{
  
  FILE *fp;
  if ((fp = fopen("workers.txt", "a+")) == NULL)
  {
    printf("找不到数据库文件");
    exit(0);
  }

  printf("请选择：\n");
  printf("1.员工注册\n");
  printf("2.员工考勤\n");
  
  int i=0;
  int choice;
  scanf("%d",&choice);
  
  switch(choice)
  {
    case 1:         //***员工信息录入
    {

    system("clear");
    printf("请输入员工姓名：\n");
    scanf("%s",&workers[i].name);
    
    printf("请输入员工工号：\n");
    scanf("%d",&workers[i].number);

    workers[i].workday = 0;

    fprintf(fp, "%s ", workers[i].name);
    fprintf(fp, "%d ", workers[i].number);
    fprintf(fp, "%d\n", workers[i].workday);
    printf("员工注册完成！");
    
    fclose(fp);
    
    break;

    }

    case 2:              //***员工考勤打卡
    {
        FILE *fps;
      if ((fps = fopen("workers.txt", "a+")) == NULL)
      {
        printf("找不到数据库文件");
        exit(0);
      }
      
      
      int i = 0;
      int sum = 0;
      while (fscanf(fps, "%d", &workers[i].number) != EOF)
      {
        fscanf(fps, "%s", &workers[i].name);
        fscanf(fps, "%d", &workers[i].number);
        fscanf(fps, "%d", &workers[i].workday);
        i++;
      }
      sum = i;
      
      fclose(fps);
    

      
      
      int sign_number;
      printf("请输入你的工号：\n");
      scanf("%d",&sign_number);

      for(i=0;i<sum;i++)              //***员工考勤天数加1,打卡成功
      {
        if(sign_number == workers[i].number)
        {
          workers[i].workday = workers[i].workday + 1;
        }
      }

      
      
      FILE *fps_new;
      if ((fps_new = fopen("workers_new.txt", "a+")) == NULL)
      {
        printf("已新建数据库文件");
        exit(0);
      }
      


      
      for(i=0;i<sum;i++)
      {
        fprintf(fps_new, "%s ", workers[i].name);
        fprintf(fps_new, "%d ", workers[i].number);
        fprintf(fps_new, "%d\n", workers[i].workday);
      }
      printf("打卡成功！\n");
      sleep(5);
      fclose(fps_new);


    system("rm -rf workers.txt");//****这里有问题,删除旧文件无法删除
    system("rename workers_new.txt workers.txt");//***修改新文件名
     
    break;

    }

  }

}  




//***缺货提醒函数
void shortage()
{
	/***检测数据库文件是否存在***/
    
    
	FILE *fp;
    if ((fp = fopen("database.txt", "a+")) == NULL)
    {
        printf("找不到数据库文件");
        exit(0);
    }
    
    
    struct item item_array[100];
    i = 0;
    while (fscanf(fp, "%d ", &item_array[i].id) != EOF)
    {
        fscanf(fp, "%d", &item_array[i].id);
        fscanf(fp, "%s", &item_array[i].category);
        fscanf(fp, "%s", &item_array[i].name);
        fscanf(fp, "%d", &item_array[i].in_prize);
        fscanf(fp, "%d", &item_array[i].out_prize);
        fscanf(fp, "%d", &item_array[i].stock_quantity);
        fscanf(fp, "%d", &item_array[i].purchase_quantity);
        fscanf(fp, "%d %d %d", &item_array[i].manufacture_date[0], &item_array[i].manufacture_date[1], &item_array[i].manufacture_date[2]);
        fscanf(fp, "%d %d %d", &item_array[i].in_date[0], &item_array[i].in_date[1], &item_array[i].in_date[2]);
        fscanf(fp, "%d %d %d", &item_array[i].expiry_date[0], &item_array[i].expiry_date[1], &item_array[i].expiry_date[2]);
        i++;
    }
    fclose(fp);
    
	
	sum=i;
    int count=0;//计算缺货的商品个数 
    for (i = 0; i < sum; i++)
    {
  	    if(item_array[i].stock_quantity<=10)//***此处可以修改缺货的阈值 
		{
			printf("%s库存低于10，请及时补货\n",item_array[i].name);
			count++;
	    }
	    else if(item_array[i].stock_quantity>10)
	    {
	    	printf("%s库存为%d,货源充足\n",item_array[i].name,item_array[i].stock_quantity);
		}
		if(count==0)
		{
			printf("所有商品的库存充足!\n");
			count=0; 
		}
    }sleep(5); 
}

//绘图函数
void plot()
{
  
	int i=0,sum=0,j=0,k=0;
	struct forPlot
	{
		int year;
		int month;
		int day;
		int hour;
		int min;
		int sec;
		char name[20];
		float price;
		float discount;
		int number;
	}forPlotArr[100];
  //文件扫入数组
	FILE *profp;
	if ((profp = fopen("profit.txt", "r")) == NULL)
	{
		printf("找不到数据库文件");
		exit(0);
	}

	while (fscanf(profp, "%d ", &forPlotArr[i].year) != EOF)
	{
		fscanf(profp, "%d", &forPlotArr[i].month);
		fscanf(profp, "%d", &forPlotArr[i].day);
		fscanf(profp, "%d", &forPlotArr[i].hour);
		fscanf(profp, "%d", &forPlotArr[i].min);
		fscanf(profp, "%d", &forPlotArr[i].sec);
		fscanf(profp, "%s", &forPlotArr[i].name);
		fscanf(profp, "%f", &forPlotArr[i].price);
		fscanf(profp, "%f", &forPlotArr[i].discount);
		fscanf(profp, "%d", &forPlotArr[i].number);
		i++;
	}
	sum=i;

 //获取现在时间
  time_t tmpcal_ptr;
  struct tm *tmp_ptr = NULL;
  time(&tmpcal_ptr);
  tmp_ptr = localtime(&tmpcal_ptr);
  int nowYear=tmp_ptr->tm_year+1900;
  int nowMon=(1+tmp_ptr->tm_mon);
  int numMonToScanf=nowMon-6;
  char nameToFind[20];
  printf("请输入想要绘图的商品名称：");
  scanf("%s",&nameToFind);
  
	//数据处理
	int salesNumber[6][100];
  int count[6];
  j=0;
  k=0;
	for (i=0;i<sum;i++)
	{
		if(forPlotArr[i].year==2022 && forPlotArr[i].month>=7)
    {
      
      if(strcmp(forPlotArr[i].name,nameToFind)==0)
      {
        salesNumber[j][k]=forPlotArr[i].number;
        if(forPlotArr[i+1].month==forPlotArr[i].month)
        k++;
        if(forPlotArr[i+1].month!=forPlotArr[i].month)
        {
          count[j]=k;
          j++;
          k=0;
        }
      }
    }
	}
	fclose(profp);
  int value[6];
  for(i=0;i<6;i++)
  value[i]=0;

  for(i=0;i<6;i++)
  {
    for(int l=0;l<count[i]+1;l++)
    {
      value[i]=value[i]+salesNumber[i][l];
    }
  }

  //画图
  system("clear");
  for(i=0;i<6;i++)
  {
    printf("%d月",i+6);
    for(j=0;j<value[i];j++)
    {
    printf("■");
    }
    printf("  %d件\n\n",value[i]);
  }
  printf("按任意键返回主菜单：\n");
  scanf("%d", &GoBack); 
}
