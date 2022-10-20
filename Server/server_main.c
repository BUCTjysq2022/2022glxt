#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
//****������Ʒ�ṹ��****//
struct item
{
	int id;                  //����
	char category[10];       //����
	char name[30];           //����
	int in_prize;            //����
	int out_prize;           //�ۼ�
	int stock_quantity;      //�ܿ��
	int purchase_quantity;   //������
	int manufacture_date[3]; //��������
	int in_date[3];          //��������
	int expiry_date[3];      //������
};




//***�Զ��庯������***//
void establish(); //��������
int menu();       //���˵�����
void back();      //�˻�����
void disstore();  //��ʾ��溯��
void shop();      //���ﳵ����
void calculate(); //���㹦��
void search();    //���ҹ���
void disshop();   //***��ǰ��������
void chanshop();  //***��ǰ��������
int shop_menu();  //***��ǰ��������
void rank();//***�����ܺ���
void category();//***�������Һ���
void dismenu();//***��ʾ�����Ĳ˵�����







//***ȫ�ֱ�������***//
int input_method;
int input_num;
int input_id;
int mode;
int i,sum;//sum��¼�ļ����м��У���i���б���
struct item item_array[100];
int GoBack;




//***1***����������***//
int main()
{   
	while (1)
	{
		system("cls");
		printf("\t***********************************\n");
		printf("\t\t��ӭ���볬�й���ϵͳ\n");
		printf("\t***********************************\n");
		switch (menu()) //ѡ������ѡ����
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
			dismenu();
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
			printf("��лʹ�ã��ټ�!\n");
			exit(0);
		}
	}
}




//***2***�˵�ѡ��������***//
int menu()
{
	int select;
	printf("\n\t\t��ѡ�����ֽ��в���\n");
	printf("\t\t1.����\n");
	printf("\t\t2.�˻�\n");
	printf("\t\t3.��ʾ������Ϣ\n");
	printf("\t\t4.���ﳵ\n");
	printf("\t\t5.����\n");
	printf("\t\t6.����\n");
	printf("\t\t7.�˳�����\n");
	printf("\t\t��ѡ���Ӧ����1--7:\n");
	
	while (1)
	{
		fflush(stdin); //������뻺����
		scanf("%d",&select);
		if (select < 1 || select > 7)
			printf("�����������������:");
		else
			break;
	}
	return select;
}





//***3***�����������***//
void establish()
{
	
	/***������ݿ��ļ��Ƿ����***/
	FILE *fp;
	if ((fp = fopen("database.txt", "a+")) == NULL)
	{
		printf("�Ҳ������ݿ��ļ�");
		exit(0);
	}
	
	/***�����ļ�ָ�붨��***/
	FILE *infp;
	
	/***����***/
	printf("��ѡ��¼�뷽ʽ��\n");
	printf("1.�ֶ�¼��\n");
	printf("2.�ļ�¼��\n");
	scanf("%d", &input_method);
	system("cls");
	switch (input_method)
	{
	case 1:
		/**�ֶ�¼��**/
		printf("��������Ҫ��ӵ���Ʒ����\n");
		scanf("%d", &input_num);
		system("cls");
		/*��������*/
		for (i = 0; i < input_num; i++)
		{
			printf("����¼���%d����Ʒ��\n", i + 1);
			printf("���������Ʒ��Ϣ��\n");
			
			printf("���ţ�\n");
			scanf("%d", &item_array[i].id);
			
			printf("���\n");
			fflush(stdin);
			scanf("%s",&item_array[i].category);
			printf("���ƣ�\n");
			fflush(stdin);
			scanf("%s",&item_array[i].name);
			
			printf("���ۣ�\n");
			scanf("%d", &item_array[i].in_prize);
			printf("�ۼۣ�\n");
			scanf("%d", &item_array[i].out_prize);
			printf("���:(��Ϊ���������롰0��)\n");
			scanf("%d", &item_array[i].stock_quantity);
			printf("��������\n");
			scanf("%d", &item_array[i].purchase_quantity);
			printf("*�������������Ϊ yyyy mm dd ��ʽ*\n");
			printf("�������ڣ�\n");
			scanf("%d %d %d", &item_array[i].manufacture_date[0], &item_array[i].manufacture_date[1], &item_array[i].manufacture_date[2]);
			printf("�������ڣ�\n");
			scanf("%d %d %d", &item_array[i].in_date[0], &item_array[i].in_date[1], &item_array[i].in_date[2]);
			printf("����������\n");
			scanf("%d %d %d", &item_array[i].expiry_date[0], &item_array[i].expiry_date[1], &item_array[i].expiry_date[2]);
			system("cls");
			printf("��%d����Ʒ¼����ɣ�\n", i + 1);
		}
		if (input_num == i && input_num!=1)
			printf("ȫ����Ʒ¼�����!\n");
		//�����ӵ����
		for (i = 0; i < input_num; i++)
		{
			item_array[i].stock_quantity += item_array[i].purchase_quantity;
			item_array[i].purchase_quantity = 0;
		}
		/*�����ļ�*/
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
		
		printf("�ļ�д�����!\n");
		fclose(fp);
		sleep(2);
		break;
		
	case 2:
		/**�ļ�¼��**/
		system("cls");
		/*��������ļ��Ƿ����*/
		if ((infp = fopen("input.txt", "r")) == NULL)
		{
			printf("�Ҳ��������ļ�");
			exit(0);
		}
		
		/*��������*/
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
		/*�ɹ�¼��������ʾ*/
		printf("\n�ɹ���⵽����%d����Ʒ:\n",sum);
		for (i = 0; i < sum; i++)
		{
			printf("���ţ�%d \n", item_array[i].id);
			printf("���%s ", item_array[i].category);
			printf("���ƣ�%s \n", item_array[i].name);
			printf("���ۣ�%d ", item_array[i].in_prize);
			printf("�ۼۣ�%d ", item_array[i].out_prize);
			printf("��棺%d ", item_array[i].stock_quantity);
			printf("\n��������:%d��%d��%d�� ", item_array[i].manufacture_date[0], item_array[i].manufacture_date[1], item_array[i].manufacture_date[2]);
			printf("\n��������:%d��%d��%d�� ", item_array[i].in_date[0], item_array[i].in_date[1], item_array[i].in_date[2]);
			printf("\n��������:%d��%d��%d��\n\n", item_array[i].expiry_date[0], item_array[i].expiry_date[1], item_array[i].expiry_date[2]);
		}
		if (sum == i)
			printf("ȫ����Ʒ¼�����!\n");
		
		/*�������ݿ�*/
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
		
		/*����ɹ���ʾ*/
		printf("�ļ�д�����!\n");
		fclose(fp);
		sleep(2);
		break;
	}
}




//***4***�˻���������***//
void back()
{
	/***��������***/
	int to_be_deleted, delete_num;
	int whether_continue = 1;
	
	/***������ݿ��ļ��Ƿ����***/
	FILE *fp;
	if ((fp = fopen("database.txt", "r")) == NULL)
	{
		printf("�Ҳ������ݿ��ļ�");
		exit(0);
	}
	
	/***�����ļ�ָ�붨��***/
	FILE *new_fp;
	
	/***�˻�***/
	system("cls");
	/**���ݿ⵼������**/
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
	
	/**չʾ���ݿ�**/
	printf("\n���ݿ�����������Ʒ��\n");
	for (i = 0; i < sum; i++)
	{
		printf("���ţ�%d \n", item_array[i].id);
		printf("���%s ", item_array[i].category);
		printf("���ƣ�%s \n", item_array[i].name);
		printf("���ۣ�%d ", item_array[i].in_prize);
		printf("�ۼۣ�%d ", item_array[i].out_prize);
		printf("��棺%d ", item_array[i].stock_quantity);
		printf("\n�������ڣ�%d��%d��%d�� ", item_array[i].manufacture_date[0], item_array[i].manufacture_date[1], item_array[i].manufacture_date[2]);
		printf("\n�������ڣ�%d��%d��%d�� ", item_array[i].in_date[0], item_array[i].in_date[1], item_array[i].in_date[2]);
		printf("\n����������%d��%d��%d��\n\n", item_array[i].expiry_date[0], item_array[i].expiry_date[1], item_array[i].expiry_date[2]);
	}
	
	/**�������޸�**/
	while (whether_continue == 1)
	{
		/*��ȡ��Ҫɾ����Ʒ�Ļ���/����*/
		printf("\n��������Ҫ�˻�����Ʒ���ţ�\n");
		scanf("%d", &to_be_deleted);
		to_be_deleted -= 1;
		system("cls");
		printf("\n��������Ҫ�˻�������:\n");
		printf("(Ŀǰ���%d��)\n", item_array[to_be_deleted].stock_quantity);
		scanf("%d", &delete_num);
		
		/*ɾ������*/
		item_array[to_be_deleted].stock_quantity -= delete_num;
		system("cls");
		printf("\n�����ɹ���\n");
		sleep(1);
		system("cls");
		
		/*��������*/
		printf("�Ƿ����ɾ����\n");
		printf("1.����ɾ��\n");
		printf("2.ֹͣɾ��\n");
		scanf("%d", &whether_continue);
		system("cls");
	}
	
	//***������д�����ļ�***//
	
	/*�½����ݿ�*/
	if ((new_fp = fopen("database_new.txt", "w")) == NULL)
	{
		printf("���½����ݿ��ļ�");
		exit(0);
	}
	/*д����database*/
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
	system("rename database_new.txt database.txt"); //�����μ��޸�
	
	printf("\n���ݿ�д����ɣ�\n");
}




//***5***��ʾ��湦��***//
void disstore()
{
	/***������ݿ��ļ��Ƿ����***/
	FILE *fp;
	if ((fp = fopen("database.txt", "r")) == NULL)
	{
		printf("�Ҳ������ݿ��ļ�");
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
		printf("���ţ�%d \n", item_array[j].id);
		printf("���%s ", item_array[j].category);
		printf("���ƣ�%s \n", item_array[j].name);
		printf("���ۣ�%d ", item_array[j].in_prize);
		printf("�ۼۣ�%d ", item_array[j].out_prize);
		printf("��棺%d ", item_array[j].stock_quantity);
		printf("\n�������ڣ�%d��%d��%d�� ", item_array[j].manufacture_date[0], item_array[j].manufacture_date[1], item_array[j].manufacture_date[2]);
		printf("\n�������ڣ�%d��%d��%d�� ", item_array[j].in_date[0], item_array[j].in_date[1], item_array[j].in_date[2]);
		printf("\n����������%d��%d��%d��\n\n", item_array[j].expiry_date[0], item_array[j].expiry_date[1], item_array[j].expiry_date[2]);
	}
	fclose(fp);
	printf("��������������˵���\n");
	scanf("%d", &GoBack);   
}




//***6***���ﳵ����***//
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
			break; //***��ʾ���ﳵ��Ʒ
			
		case 2:
			system("cls");
			chanshop();
			system("cls");
			break; //***�޸Ĺ��ﳵ��Ʒ
			
		case 3:
			system("cls");
			return; //***����
		}
	}
}




//***7***���ﳵ�˵�����***//
int shop_menu()
{
	int select;
	printf("\n\t\t��ѡ�����\n");
	printf("\t-----------------------\n");
	printf("\t1.��ʾ��ǰ�����б�\n");
	printf("\t2.�޸ĵ�ǰ�����б�\n");
	printf("\t3.�˳�\n");
	printf("\t-----------------------\n\n");
	while (1)
	{
		fflush(stdin);
		scanf("%d",&select);
		if (select < 1 || select > 3)
			printf("�����������������:");
		else
			break;
	}
	return select;
}




//***8***��ʾ���ﳵ�б���***//
void disshop()
{
	FILE *shopfp;
	if ((shopfp = fopen("shopping.txt", "r")) == NULL)
	{
		printf("�Ҳ������ݿ��ļ�");
		exit(0);
	}
	
	struct Goods //***���ﳵ�ṹ�嶨��***//
	{
		int code;
		char name[20];
		double price;
		double discount;     //�ۿ�
		int number;          //����
		double totalPayment; //�ܶ�
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
		printf("���ﳵ��û����Ʒ��\n");
	}
	for (int j = 0; j < sum; j++)
	{
		printf("�����ǣ�%d \n", goods[j].code);
		printf("���������ǣ�%s \n", goods[j].name);
		printf("�۸��ǣ�%lf \n", goods[j].price);
		printf("�ۿ��ǣ�%lf \n", goods[j].discount);
		printf("�����ǣ�%d \n", goods[j].number);
		printf("�ܼ��ǣ�%lf \n\n", goods[j].totalPayment);
	}
	
	fclose(shopfp);
	printf("�����������...");
	scanf("%d",&GoBack);
}




//***9***�޸Ĺ��ﳵ��������***//
void chanshop()
{
	/***������ݿ��ļ��Ƿ����***/
	FILE *fp;
	if ((fp = fopen("database.txt", "r")) == NULL)
	{
		printf("�Ҳ������ݿ��ļ�");
		exit(0);
	}
	
	FILE *shopfp;
	if ((shopfp = fopen("shopping.txt", "a+")) == NULL)
	{
		printf("�Ҳ������ݿ��ļ�");
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
	/**չʾ���ݿ�**/
	printf("\n\t���ݿ�����������Ʒ��\n");
	for (i = 0; i < sum; i++)
	{
		printf("���ţ�%d \n", item_array[i].id);
		printf("���%s ", item_array[i].category);
		printf("���ƣ�%s \n", item_array[i].name);
		printf("���ۣ�%d ", item_array[i].in_prize);
		printf("�ۼۣ�%d ", item_array[i].out_prize);
		printf("��棺%d ", item_array[i].stock_quantity);
		printf("\n�������ڣ�%d��%d��%d�� ", item_array[i].manufacture_date[0], item_array[i].manufacture_date[1], item_array[i].manufacture_date[2]);
		printf("\n�������ڣ�%d��%d��%d�� ", item_array[i].in_date[0], item_array[i].in_date[1], item_array[i].in_date[2]);
		printf("\n����������%d��%d��%d��\n\n", item_array[i].expiry_date[0], item_array[i].expiry_date[1], item_array[i].expiry_date[2]);
	}
	
	struct Goods //***���ﳵ�ṹ�嶨��***//
	{
		int code;
		char name[30];
		float price;
		float discount;     //�ۿ�
		int number;          //����
		float totalPayment; //�ܶ�
	};
	struct Goods goods[100];
	int e;
	
	for (e = 0; e < 100; e++)
		goods[e].code = 0;
	printf("-----------------------------------------------\n");
	printf("��ѡ�������Ʒ�����ﳵ�����ߴӹ��ﳵ��ɾ����Ʒ\n");
	printf("\t\t1.�����Ʒ\n");
	printf("\t\t2.ɾ����Ʒ\n");
	scanf("%d", &input_method);
	system("cls");
	switch (input_method)
	{
		
	case 1:
		{
			
			//***�����Ʒ***//
			char choicex[200];
			do
			{
				
				printf("\t��������Ҫ���빺�ﳵ����Ʒ���ţ�\n");
				scanf("%d", &input_id);
				
				/**������Ʒ**/
				int t;
				for (i = 0; i < sum; i++)
				{
					if (item_array[i].id == input_id)
					{
						
						system("cls");
						t = i;
						printf("\t�����д���Ʒ����Ʒ��ϢΪ��\n");
						printf("���ţ�%d \n", item_array[i].id);
						printf("���%s \n", item_array[i].category);
						printf("���ƣ�%s \n", item_array[i].name);
						printf("���ۣ�%d \n", item_array[i].in_prize);
						printf("�ۼۣ�%d \n", item_array[i].out_prize);
						printf("��棺%d \n", item_array[i].stock_quantity);
						printf("�������ڣ�%d��%d��%d��\n", item_array[i].manufacture_date[0], item_array[i].manufacture_date[1], item_array[i].manufacture_date[2]);
						printf("�������ڣ�%d��%d��%d��\n", item_array[i].in_date[0], item_array[i].in_date[1], item_array[i].in_date[2]);
						printf("����������%d��%d��%d��\n", item_array[i].expiry_date[0], item_array[i].expiry_date[1], item_array[i].expiry_date[2]);
						
						char choicey[200];
						printf("\n\t�Ƿ񽫴���Ʒ���빺�ﳵ��(��Y/��N��\n");
						fflush(stdin);
						choicey[200] = getchar();//***��ʼ�����ﳵ�����Ʒ***//
						if (choicey[200] == 'Y' || choicey[200] == 'y')
						{
							printf("\t������Ҫ��Ӷ��ټ�����Ʒ�����ﳵ��\n");
							int k;
							scanf("%d", &k);
							if (k > item_array[t].stock_quantity)
							{
								printf("\t��治��!\n");
								break;
							}
							else //***����Ʒ��Ϣ�����goods�ṹ��������
							{
								int j = 0;
								while (goods[j].code != 0) //�˴����������0����˵���ṹ���������һ���Ѿ�����Ʒ�ˣ�����������һ��
								{
									j++;
								}
								
								goods[j].code = item_array[t].id;
								strcpy(goods[j].name,item_array[t].name);
								goods[j].number = k;
								goods[j].price = item_array[t].out_prize;
								item_array[j].stock_quantity = item_array[t].stock_quantity - k;
								goods[j].totalPayment = k * item_array[t].out_prize;
								printf("\n\t�����Ʒ�����ﳵ�ɹ���\n");
								
								
								fprintf(shopfp, "%d ", goods[i].code);
								fprintf(shopfp, "%s ", goods[i].name);
								fprintf(shopfp, "%f ", goods[i].price);
								fprintf(shopfp, "%f ", goods[i].discount);
								fprintf(shopfp, "%d ", goods[i].number);
								fprintf(shopfp, "%f \n", goods[i].totalPayment);
								
								/*����ɹ���ʾ*/
								printf("\t�ļ�д�����!\n");
								
								fclose(shopfp);
								
							}
							break;
						}
					}
				}
				
				if(i==sum)
				{
					printf("\n\t���޴���Ʒ\n");
					break;
				}
				
				printf("\n\t�Ƿ��������?(��Y/��N)\n");
				fflush(stdin);
				choicex[200] = getchar();
			} while (choicex[200] == 'Y' || choicex[200] == 'y'); //***do-while�����ж�***//
			fclose(fp);
			break;
		}
		
	case 2:
		{
			
			//***ɾ����Ʒ***//
			char choicew[200];
			do
			{/***��������***/
				int to_be_deleted, delete_num;
				int whether_continue = 1;
				
				/***������ݿ��ļ��Ƿ����***/
				FILE *oldfp;
				if ((oldfp = fopen("shopping.txt", "r")) == NULL)
				{
					printf("�Ҳ������ݿ��ļ�");
					exit(0);
				}
				
				/***�����ļ�ָ�붨��***/
				FILE *new_fp;
				
				/***�˻�***/
				system("cls");
				/**���ݿ⵼������**/
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
				
				
				printf("\t��������Ҫɾ������Ʒ����\n");
				int deleid;
				scanf("%d", &deleid);
				int i;
				for (i = 0; i < sum; i++)
				{
					if (deleid == goods[i].code)
					{
						printf("\t����Ʒ�ڹ��ﳵ���У�������%d", goods[i].number);
						printf("\t�����Ƿ�ɾ��?(��Y/��N)\n");
						char choicez[200];
						choicez[200] = getchar();
						if (choicez[200] == 'Y' || choicez[200] == 'y')
						{
							printf("\t������ɾ������\n");
							int delenum;
							scanf("%d", &delenum);
							goods[i].number = goods[i].number - delenum;
							break;
						}
						
						//***������д�����ļ�***//
						
						/*�½����ݿ�*/
						
						if ((new_fp = fopen("shopping_new.txt", "w")) == NULL)
						{
							printf("���½����ݿ��ļ�");
							exit(0);
						}
						
						
						for(i=0;i<sum;i++)
						{
							fprintf(new_fp, "%d ", goods[i].code);
							fprintf(new_fp, "%s ", goods[i].name);
							fprintf(new_fp, "%d ", goods[i].number);
							fprintf(new_fp, "%f ", goods[i].price);
							fprintf(new_fp, "%f ", goods[i].discount);
							fprintf(new_fp, "%f ", goods[i].totalPayment);
						}
						
						fclose(new_fp);
						system("del shopping.txt");
						system("rename shopping_new.txt shopping.txt"); 
						printf("\n���ݿ�д����ɣ�\n");
						
					}
				}
				
				
				
			} while (choicew[200] == 'Y' || choicew[200] == 'y'); //***do-while�����ж�***//
			break;
		}
	}
}



//***10***���㹦��***//
void calculate()
{
	int calculate_menu(), calculate_all();
	while (1)
	{
		switch (calculate_menu())
		{
		case 1:
			calculate_all();
			break; //***���㹺�ﳵ�ڵ���Ʒ�ܼ�
			
		case 2:
			return; //***����
		}
	}
}




//***11***���㹺�ﳵ�ڵ���Ʒ�ܼ۵Ĳ˵�**//
int calculate_menu()
{
	char import[5];
	int select;
	printf("\n\t\t��ѡ�����\n");
	printf("\t-----------------------------\n");
	printf("\t1.���㵱ǰ���ﳵ�ڵ���Ʒ�ܼ�\n");
	printf("\t2.�˳�\n");
	printf("\t-----------------------------\n\n");
	
	while (1)
	{
		fflush(stdin);
		scanf("%d",&select);
		if (select < 1 || select > 3)
			printf("\n\t�����������������:");
		else
			system("cls");
		break;
	}
	return select;
}




//***12***���㹺�ﳵ�ڵ���Ʒ�ܼ�***//
int calculate_all()
{
	struct Goods //***���ﳵ�ṹ�嶨��***//
	{
		int code;
		char name[20];
		double price;
		double discount;     //�ۿ�
		int number;          //����
		double totalPayment; //�ܶ�
	};
	struct Goods goods[100];
	/***��⹺�ﳵ�ļ��Ƿ����***/
	FILE *shoppfp, *pff;
	if ((shoppfp = fopen("shopping.txt", "a+")) == NULL)
	{
		printf("\t�Ҳ������ﳵ�ļ�\n");
		exit(0);
	}
	
	i=0;
	while (fscanf(shoppfp, "%d", &item_array[i].id) != EOF)
	{
		fscanf(shoppfp, "%d", &goods[i].code);
		fscanf(shoppfp, "%s", &goods[i].name);
		fscanf(shoppfp, "%lf", &goods[i].price);
		fscanf(shoppfp, "%lf", &goods[i].discount);
		fscanf(shoppfp, "%d", &goods[i].number);
		fscanf(shoppfp, "%lf", &goods[i].totalPayment);
		i++;
	}
	sum=i;
	
	double TotalPayment;
	for (i = 0; i < sum; i++)
	{
		TotalPayment = TotalPayment + goods[i].totalPayment; //***���㹺�ﳵ����Ʒ�ܼ�
	}
	printf("\n\t��Ʒ�ܼۣ�%0.2f", TotalPayment);
	
	fclose(shoppfp);
	
	void Profit(double TotalPayment);
	Profit(TotalPayment); //***��¼���ι���Ľ��׶�
	
	/***���������������***/
	/***�������ȡֵ***/
	
	
	srand(time(0));//***srand()��������rand()���������ʱ����������ӡ�����seed�����Ǹ�������ͨ����������geypid()��time(0)�ķ���ֵ������seed
	double newPayment;
	newPayment = TotalPayment - (rand() % 10 + 1) * 0.01 * TotalPayment;
	printf("\n\n\n\t���ڱ���������������Żݣ��������ܼ�Ϊ��%0.2f\n", newPayment);
	printf("\n\n\n\tлл�ݹˣ���ӭ�´ι��");
	
	
	
	/***��չ��ﳵ�ļ��е�����***/
	pff = fopen("shopping.txt", "w");
	if (pff)
	{
		printf("\n\t\t\t(���ﳵ��Ʒ�����)");
		fclose(pff);
	}
	printf("\n\n\t�����������...");
	scanf("%d",&GoBack);
	system("cls");
}




//***13***��¼ÿ�ι���Ľ��׶�***/
void Profit(double TotalPayment)
{
	/***��⽻�׶��ļ��Ƿ����***/
	FILE *profitfp;
	if ((profitfp = fopen("profit.txt", "a+")) == NULL)
	{
		printf("\n�Ҳ������׶��ļ�");
		exit(0);
	}
	fprintf(profitfp, "%lf", &TotalPayment);
	
	/*����ɹ���ʾ*/
	printf("\n\t\t(��¼�뽻�׶");
	
	fclose(profitfp);
}




//***14***���Һ�������***//
void search()
{
	
	/***������ݿ��ļ��Ƿ����***/
	FILE *fp;
	if ((fp = fopen("database.txt", "a+")) == NULL)
	{
		printf("�Ҳ������ݿ��ļ�");
		exit(0);
	}
	
	/***����***/
	printf("\t��������Ҫ������Ʒ�Ļ��ţ�\n");
	scanf("%d", &input_id);
	/**���ݿ⵼������**/
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
	/**������Ʒ**/
	i = i - 1;
	int j;
	for (j = i; j >= 0; j--)
	{
		if (item_array[j].id == input_id)
		{
			printf("\t�������д���Ʒ����Ʒ��ϢΪ��\n");
			printf("���ţ�%d \n", item_array[j].id);
			printf("���%s \n", item_array[j].category);
			printf("���ƣ�%s \n", item_array[j].name);
			printf("���ۣ�%d \n", item_array[j].in_prize);
			printf("�ۼۣ�%d \n", item_array[j].out_prize);
			printf("��棺%d \n", item_array[j].stock_quantity);
			printf("�������ڣ�%d��%d��%d��\n", item_array[j].manufacture_date[0], item_array[j].manufacture_date[1], item_array[j].manufacture_date[2]);
			printf("�������ڣ�%d��%d��%d��\n", item_array[j].in_date[0], item_array[j].in_date[1], item_array[j].in_date[2]);
			printf("����������%d��%d��%d��\n", item_array[j].expiry_date[0], item_array[j].expiry_date[1], item_array[j].expiry_date[2]);
			break;
		}
	}
	sleep(3);
	if (j < 0)
	{
		printf("\t���޴���Ʒ\n");
	}
	fclose(fp);
}


void dismenu()//***��ʾ�����Ĳ˵�����
{
	while(1)
	{
		sleep(1);
		system("cls");
		printf("\n\t\t��ѡ�����ֽ��в���\n");
		printf("\t\t1.��ʾ������Ʒ��Ϣ\n");
		printf("\t\t2.�������ʾ��Ʒ\n");
		printf("\t\t3.�����Ŵ�С������Ʒ������ʾ\n");
		printf("\t\t4.�˳�\n");
		
		int input = 0;
		scanf("%d",&input);
		switch (input) //ѡ������ѡ����
		{
		case 1:
			system("cls");
			disstore();
			break;
			
		case 2:
			system("cls");
			category();
			break;
			
		case 3:
			system("cls");
			rank();
			break;
			
		case 4:
			system("cls");
			exit(0);
			break;
		}
		
	}
	
}


typedef struct product//***����һ���ṹ��
{
	int id;                  //����
	char category[10];       //����
	char name[30];           //����
	int out_prize;           //�ۼ�
	int stock_quantity;      //�ܿ��
	int manufacture_date[3]; //��������
	int expiry_date[3];      //������
}PRODUCT;


void swap(PRODUCT *A, PRODUCT *B)
{
	PRODUCT temp;
	
	temp = *A;
	*A = *B;
	*B = temp;
}


//***������
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


//***������
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


// ���һ��
void output(PRODUCT user)
{
	printf("%d %s %d %d\n", user.id, user.category, user.out_prize, user.stock_quantity);
}


void output_all(PRODUCT *list, int length)//***�Զ��庯�����������Ŀ
{
	printf("ID   UserName   Income   Expenses\n");
	
	for (int i = 0; i < length; i++)
	{
		output(list[i]);
	}
}


void sortrank(PRODUCT *list, int length, int strategy)//***ָ�봫��
{
	int (*p)(int, int); // ����һ������ָ��
	
	if (strategy == 1)
	{
		// ����
		p = up;
	}
	else
	{
		// ����
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


void rank()//***������
{
	/***������ݿ��ļ��Ƿ����***/
	FILE *fp;
	if ((fp = fopen("database.txt", "a+")) == NULL)
	{
		printf("�Ҳ������ݿ��ļ�");
		exit(0);
	}
	
	
	int sum = 0;
	/**���ݿ⵼������**/
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
	PRODUCT item_list[100];//***��PRODUCT�ṹ�嶨��
	
	for(i=0;i<sum;i++)//***ѭ����ֵ��item_list[100]
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
	
	printf("�����������ǽ������У�����1/����0");
	int p;
	scanf("%d",&p);
	
	sortrank(item_list,sum,p);//***����ð����������������
	output_all(item_list,sum);//***�����������ȫ�����
	
}


void category()//***������Һ���
{
	/***������ݿ��ļ��Ƿ����***/
	FILE *fp;
	if ((fp = fopen("database.txt", "r")) == NULL)
	{
		printf("�Ҳ������ݿ��ļ�");
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
	fclose(fp);
	sum=i;
	
	for (int j=0; j < sum; j++)
	{    
		if(strcmp(item_array[j].category,"food")==0)
		{
			printf("--------------------------------------------\n");
			printf("���Ϊfood����Ʒ�У�");
			printf("����       Ʒ��           ����    ����\n");
			printf("%s       %s            %d      %d\n",item_array[j].category,item_array[j].name,item_array[j].out_prize,item_array[j].stock_quantity);
		}
	}
	
	
	
}

