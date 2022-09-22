#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/****������Ʒ�ṹ��****/
typedef struct item
{
	int id;//���� 
	char category[10]; //����
	char name[30];//����
	int in_prize;//����
	int out_prize;//�ۼ�
	int stock_quantity;//�ܿ��
	int purchase_quantity;//������
	int manufacture_date[3];//��������
	int in_date[3];//��������
	int expiry_date[3];//������
};



//***�Զ��庯������***//
void establish();//��������
int menu();//���˵�����
void back();//�˻�����
void disstore();//��ʾ��溯��
void shop();//���ﳵ����
void calculate();//���㹦��



//***ȫ�ֱ�������***//
int input_method;
int input_num;
int mode;
int i;
int to_be_deleted,delete_num;
int whether_continue=1;
struct item item_array[100];


//***����������***//
void main()
{
    printf("***********************************\n");
	printf("     ��ӭ���볬�й���ϵͳ\n");
	printf("***********************************\n");
	
	
	while(1)
    {
        switch(menu())//***ѡ������ѡ����***//
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
			printf("��лʹ�ã��ټ�!\n");
			exit(0);
        }
    }
			
}

//***�˵�ѡ��������***//
int menu()
{
    char str[5];
	int  select;
	printf("\n\n��ѡ�����ֽ��в���\n");
	printf("1.����\n");
	printf("2.�˻�\n");
	printf("3.��ʾ������Ϣ\n");
	printf("4.���ﳵ\n");
	printf("5.����\n");
    printf("6.�˳�����\n");
	printf("��ѡ���Ӧ����1--6:\n");

	while (1)
	{
		fflush(stdin);//***������뻺����***//
		gets(str);
		select = atoi(str);
		if (select<1 || select>5)
			printf("�����������������:");
		else
			break;

	}
	return select;
}


//***�����������***//
void establish()
{

 /***������ݿ��ļ��Ƿ����***/
	FILE *fp;
	if((fp=fopen("database.txt","a+"))==NULL)
	{
		printf("�Ҳ������ݿ��ļ�");
		exit(0);
	}
	
	   /***�����ļ�ָ�붨��***/
	   FILE *infp;
	   FILE *new_fp;



       /***����***/
		printf("��ѡ��¼�뷽ʽ��\n");
		printf("1.�ֶ�¼��\n");
		printf("2.�ļ�¼��\n");
		scanf("%d",&input_method);
		switch (input_method) 
	    {
		    case 1:
		    /**�ֶ�¼��**/
			printf("��������Ҫ��ӵ���Ʒ����\n");
			scanf("%d",&input_num);
			/*��������*/
			for(i=0;i<input_num;i++)
			{
				printf("����¼���%d����Ʒ��\n",i+1);
				printf("���������Ʒ��Ϣ��\n");
				
				printf("���ţ�\n");
				scanf("%d",&item_array[i].id);
				
				printf("���\n");
				fflush(stdin);
				gets(item_array[i].category);
				printf("���ƣ�\n");
				fflush(stdin);
				gets(item_array[i].name);
				
				printf("���ۣ�\n");
				scanf("%d",&item_array[i].in_prize);
				printf("�ۼۣ�\n");
				scanf("%d",&item_array[i].out_prize);
				printf("��棺����Ϊ���������롰0����\n");
				scanf("%d",&item_array[i].stock_quantity);
				printf("��������\n");
				scanf("%d",&item_array[i].purchase_quantity);
				printf("*�������������Ϊ yyyy mm dd ��ʽ*\n");
				printf("�������ڣ�\n");
				scanf("%d %d %d",&item_array[i].manufacture_date[0],&item_array[i].manufacture_date[1],&item_array[i].manufacture_date[2]);
				printf("�������ڣ�\n");
				scanf("%d %d %d",&item_array[i].in_date[0],&item_array[i].in_date[1],&item_array[i].in_date[2]);
				printf("�����ڣ�\n");
				scanf("%d %d %d",&item_array[i].expiry_date[0],&item_array[i].expiry_date[1],&item_array[i].expiry_date[2]);
				printf("\n��%d����Ʒ¼����ɣ�\n\n",i+1);
			}
			if(input_num>1)
				printf("ȫ����Ʒ¼�����!\n");
			for(i=0;i<input_num;i++)
			{
				item_array[i].stock_quantity+=item_array[i].purchase_quantity;
				item_array[i].purchase_quantity=0;
			}
			/*�����ļ�*/
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
			
			printf("�ļ�д�����!");
			fclose(fp);
			break;
			
			
			

		case 2:
		/**�ļ�¼��**/
			printf("��������Ҫ��ӵ���Ʒ����\n");
			scanf("%d",&input_num);
			/*��������ļ��Ƿ����*/
			if((infp=fopen("input.txt","r"))==NULL)
			{
				printf("�Ҳ��������ļ�");
				exit(0);
			}

			/*��������*/
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
			/*�ɹ�¼��������ʾ*/
			printf("�ɹ���⵽������Ŀ��\n");
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
				printf("ȫ����Ʒ¼�����!\n");
			
			
			/*�������ݿ�*/
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
			
			/*����ɹ���ʾ*/
			printf("�ļ�д�����!");
			
			fclose(fp);
			break;
        }
}



//***�˻���������***//
void back()
{

    /***������ݿ��ļ��Ƿ����***/
	FILE *fp;
	if((fp=fopen("database.txt","a+"))==NULL)
	{
		printf("�Ҳ������ݿ��ļ�");
		exit(0);
	}
	
	/***�����ļ�ָ�붨��***/
	FILE *infp;
	FILE *new_fp;


    /***�˻�***/
		printf("��������Ҫ��ȡ�ͱ༭��Ʒ������\n");
		scanf("%d",&input_num);
		/**���ݿ⵼������**/
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
		/**չʾ���ݿ�**/
		printf("���ݿ�����������Ʒ��\n");
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
		
		/**�������޸�**/
		while(whether_continue==1)
		{
			/*��ȡ��Ҫɾ����Ʒ�Ļ���/����*/
			printf("\n��������Ҫ�˻�����Ʒ���ţ�\n");
			scanf("%d",&to_be_deleted);
			to_be_deleted-=1;
			printf("\n��������Ҫ�˻�������:\n");
			printf("(Ŀǰ���%d��)\n",item_array[to_be_deleted].stock_quantity);
			scanf("%d",&delete_num);
			
			/*ɾ������*/
			item_array[to_be_deleted].stock_quantity-=delete_num;
			printf("\n�����ɹ���\n");
			
			/*��������*/
			printf("�Ƿ����ɾ����\n");
			printf("1.����ɾ��\n");
			printf("2.ֹͣɾ��\n");
			scanf("%d",&whether_continue);
		}
		
		/**������д�����ļ�**/
		
		/*�½����ݿ�*/
		if((new_fp=fopen("database_new.txt","w"))==NULL)
		{
			printf("���½����ݿ��ļ�");
			exit(0);
		}
		/*д��*/
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
		printf("�����ݿ�д����ɣ�");
}

void disstore()//***��ʾ��湦�ܣ�δ��ɿ�����
{
    printf("\n���ܴ�������лл֧�֣� ���ţ�3�����Ũq?��\n");
}

void shop()//***���ﳵ���ܣ�δ��ɿ�����
{
    printf("\n���ܴ�������лл֧�֣� ���ţ�3�����Ũq?��\n");
}

void calculate()//***���㹦�ܣ�δ��ɿ�����
{
    printf("\n���ܴ�������лл֧�֣� ���ţ�3�����Ũq?��\n");
}