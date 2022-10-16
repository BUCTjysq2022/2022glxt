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
void establish(); //进货功能
int menu();       //主菜单功能
void back();      //退货函数
void disstore();  //显示库存函数
void shop();      //购物车功能
void calculate(); //计算功能
void search();    //查找功能
void disshop();   //***提前声明函数
void chanshop();  //***提前声明函数
int shop_menu();  //***提前声明函数




//***全局变量定义***//
int input_method;
int input_num;
int input_id;
int mode;
int i,sum;//sum记录文件中有几行，用i进行遍历
struct item item_array[100];
int GoBack;
int lijian=0; 




//***1***主函数整体***//
int main()
{   
    while (1)
    {
        system("cls");
        printf("\t***********************************\n");
        printf("\t\t欢迎进入超市管理系统\n");
        printf("\t***********************************\n");
        switch (menu()) //选择函数，选择功能
        {
        case 1:
            system("cls");
            establish();
            break;

        case 2:
            system("cls");
            back();
            break;

        case 3:
            system("cls");
            disstore();
            break;

        case 4:
            system("cls");
            shop();
            break;

        case 5:
            system("cls");
            calculate();
            break;

        case 6:
            system("cls");
            search();
            break;

        case 7:
            system("cls");
            printf("感谢使用，再见!\n");
            exit(0);
        }
    }
}




//***2***菜单选择函数定义***//
int menu()
{
    int select;
    printf("\n\t\t请选择数字进行操作\n");
    printf("\t\t1.进货\n");
    printf("\t\t2.退货\n");
    printf("\t\t3.显示所有信息\n");
    printf("\t\t4.购物车\n");
    printf("\t\t5.结算\n");
    printf("\t\t6.查找\n");
    printf("\t\t7.退出程序\n");
    printf("\t\t请选择对应数字1--7:\n");

    while (1)
    {
        fflush(stdin); //清空输入缓存流
        scanf("%d",&select);
        if (select < 1 || select > 7)
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
    system("cls");
    switch (input_method)
    {
    case 1:
        /**手动录入**/
        printf("请输入想要添加的商品数量\n");
        scanf("%d", &input_num);
        system("cls");
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
            system("cls");
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
        system("cls");
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
    system("cls");
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
        system("cls");
        printf("\n请输入想要退货的数量:\n");
        printf("(目前库存%d件)\n", item_array[to_be_deleted].stock_quantity);
        scanf("%d", &delete_num);

        /*删除操作*/
        item_array[to_be_deleted].stock_quantity -= delete_num;
        system("cls");
        printf("\n操作成功！\n");
        sleep(1);
        system("cls");

        /*继续操作*/
        printf("是否继续删除？\n");
        printf("1.继续删除\n");
        printf("2.停止删除\n");
        scanf("%d", &whether_continue);
        system("cls");
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

    system("del database.txt");
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
      system("cls");
      disshop();
      system("cls");
      break; //***显示购物车商品

    case 2:
      system("cls");
      chanshop();
      system("cls");
      break; //***修改购物车商品

    case 3:
      system("cls");
      return; //***返回
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
  if(i=0)
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
    int manufacture_date[3];//生产日期
	int in_date[3];//进货日期
	int expiry_date[3];//保质期
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
  system("cls");
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
    
          system("cls");
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
              goods[j].manufacture_date[0]=item_array[t].manufacture_date[0]; 
			  goods[j].manufacture_date[1]=item_array[t].manufacture_date[1];
				goods[j].manufacture_date[2]=item_array[t].manufacture_date[2];
				goods[j].in_date[0]=item_array[t].in_date[0]; 
				goods[j].in_date[1]=item_array[t].in_date[1];
				goods[j].in_date[2]=item_array[t].in_date[2];
				goods[j].expiry_date[0]=item_array[t].expiry_date[0]; 
				goods[j].expiry_date[1]=item_array[t].expiry_date[1];
				goods[j].expiry_date[2]=item_array[t].expiry_date[2];
              printf("\n\t添加商品至购物车成功！\n");
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
    {
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
        }
      }
    } while (choicew[200] == 'Y' || choicew[200] == 'y'); //***do-while函数判断***//
    break;
  }
  }

  fprintf(shopfp, "%d ", goods[i].code);
  fprintf(shopfp, "%s ", goods[i].name);
  fprintf(shopfp, "%f ", goods[i].price);
  fprintf(shopfp, "%f ", goods[i].discount);
  fprintf(shopfp, "%d ", goods[i].number);
  fprintf(shopfp, "%f \n", goods[i].totalPayment);
  fprintf(shopfp,"%d %d %d  ",goods[i].manufacture_date[0],goods[i].manufacture_date[1],goods[i].manufacture_date[2]);
  fprintf(shopfp,"%d %d %d ",goods[i].in_date[0],goods[i].in_date[1],goods[i].in_date[2]);
  fprintf(shopfp,"%d %d %d\n\n",goods[i].expiry_date[0],goods[i].expiry_date[1],goods[i].expiry_date[2]);

  /*输入成功提示*/
  printf("\t文件写入完成!\n");

  fclose(shopfp);
}



//***10***计算功能***//
void calculate()
{
	int calculate_menu(),calculate_all(),fangkui_txt();
	while(1)
	{
		switch(calculate_menu())
		{
			case 1:calculate_all();lijian=0;break;//***计算购物车内的商品总价 
			
			case 2:calculate_all();lijian=0;break;
			
			case 3:calculate_all();lijian=1;break;
			
			case 4:calculate_all();lijian=0;break;
			
			case 5:fangkui_txt();break;

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



//***12计算购物车内的商品总价***//
int calculate_all()
{
	struct Goods//***购物车结构体定义***//
    {
        int code;
        char name[20];
        double price;
        double discount;//折扣
        int number;//数量
        double totalPayment;//总额
        int manufacture_date[3];//生产日期
	    int in_date[3];//进货日期
     	int expiry_date[3];//保质期
    };
    struct Goods goods[100]={0};
     /***检测购物车文件是否存在***/
	FILE *shoppfp,*pff;
	if((shoppfp=fopen("shopping.txt","a+"))==NULL)
	{
		printf("找不到购物车文件\n");
		exit(0);
	}
	
	printf("请输入要读取的购物车内物品数量：\n");
	scanf("%d",&input_num);
	
	int i;
	for(i=0;i<input_num;i++)
	{
        fscanf(shoppfp,"%d",&goods[i].code);
		fscanf(shoppfp,"%s",&goods[i].name);
		fscanf(shoppfp,"%lf",&goods[i].price);
		fscanf(shoppfp,"%lf",&goods[i].discount);
		fscanf(shoppfp,"%d",&goods[i].number);
		fscanf(shoppfp,"%lf",&goods[i].totalPayment);
		fscanf(shoppfp,"\n生产日期：%d年%d月%d日  ",&goods[i].manufacture_date[0],&goods[i].manufacture_date[1],&goods[i].manufacture_date[2]);
		fscanf(shoppfp,"\n进货日期：%d年%d月%d日  ",&goods[i].in_date[0],&goods[i].in_date[1],&goods[i].in_date[2]);
		fscanf(shoppfp,"\n保质期至：%d年%d月%d日\n\n",&goods[i].expiry_date[0],&goods[i].expiry_date[1],&goods[i].expiry_date[2]);
		
	}
    
    /***根据保质期给用户折扣***/
    int now_day,now_month,now_year;
    time_t timep;
    struct tm *p;
    char time1[28];
    time (&timep);
    p=gmtime(&timep);
	now_day=p->tm_mday;/*获取当前月份日数,范围是1-31*/
    now_month=1+p->tm_mon;/*获取当前月份,范围是0-11,所以要加1*/
    now_year=1900+p->tm_year;/*获取当前年份,从1900开始，所以要加1900*/
	
	double day1,day2;
	double date(int n, int m1, int d1, int m, int m2, int d2);
	int discount; 
	for(i=0;i<input_num;i++)
	{
		day1=date(now_year,now_month,now_day,goods[i].expiry_date[0],goods[i].expiry_date[1],goods[i].expiry_date[2]);
	
		if(day1<10.0)
		{
			goods[i].totalPayment=0.8*goods[i].totalPayment;
		}
		if(day1<20.0)
		{
			goods[i].totalPayment=0.9*goods[i].totalPayment;
		}
		if(day1<30.0)
		{
			goods[i].totalPayment=0.95*goods[i].totalPayment;
		}
	}
    double TotalPayment;
	for(i=0;i<input_num;i++)
	{
		TotalPayment=TotalPayment+goods[i].totalPayment;//***计算购物车内商品总价 
    }
	printf("本店会根据保质日期给您相应折扣，根据此次购物，则总价为：%lf",TotalPayment);
	int Profit(double TotalPayment);
	Profit(TotalPayment);//***记录本次购物的交易额 
    fclose(shoppfp);
	/***进行随机立减功能***/
	/***随机数的取值***/
	//***srand()用来设置rand()产生随机数时的随机数种子。参数seed必须是个整数，通常可以利用geypid()或time(0)的返回值来当做seed
    if(lijian==1)
	{
	    srand(time(0));
     	double newPayment;
	    newPayment=TotalPayment-(rand()%10)*0.01*TotalPayment;
	    printf("\n并且由于是使用银行卡支付，本店有随机立减的优惠，则最后的总价为：%f\n",newPayment);
	} 

	
	printf("\n谢谢惠顾，欢迎下次购物！");
	
	/***清空购物车文件中的内容***/
	pff=fopen("shopping.txt","w");
	if(pff)
	{
		printf("\n购物车物品已清空");
		fclose(pff);
	} 
}


//***计算两个日期相差的天数***//
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
void Profit(double TotalPayment)
{
  /***检测交易额文件是否存在***/
  FILE *profitfp;
  if ((profitfp = fopen("profit.txt", "a+")) == NULL)
  {
    printf("\n找不到交易额文件");
    exit(0);
  }
  fprintf(profitfp, "%lf", &TotalPayment);

  /*输入成功提示*/
  printf("\n\t\t(已录入交易额）");

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

