#include<stdio.h>
#include <stdlib.h>
#include<string.h>

struct product
{
    int no;
    char name[20];
    float price;
} p;

void insert();
void viewlist();
void search();
void modify();
void delet();
void bill();

int main()
{
    int n;
    printf("\n\n                                         Product Management System\n                                       *****************************");

    while(n!=8)
    {
        printf("\n\n\n\n                   --------------------------------------------------------------------\n\n                   1.Insert a product.\t\t\t2.View product list.\n\n\
                   3.Search a product.\t\t\t4.Modify a product details.\n\n                   5.Delete a product.\t\t\t6.Bill of the chosen products.\n\n                   7.Exit\n\n                   --------------------------------------------------------------------\n\n");

        printf("\n\n                   Enter an option: ");
        scanf("%d",&n);

        switch(n)
        {
        case 1:
            insert();
            break;
        case 2:
            viewlist();
            break;
        case 3:
            search();
            break;
        case 4:
            modify();
            break;
        case 5:
            delet();
            break;

        case 6:
            bill();
            break;
        case 7:
        {
            printf("\n\n\n                   The program is closed.\n\n                   Thanks for using this program :)\n\n\n\n\n");
        }
        }
    }
}
void insert()
{
    FILE *information;
    int n,i;

    information=fopen("data.txt","a");

    if(information==NULL)
    {
        printf("file doesn't exist");
    }
    else
    {
        printf("\n                   Enter the number of product you want to add: ");
        scanf("%d",&n);
        printf("\n\n                   Enter Product Information \n");

        for(i=0; i<n; i++)
        {
            printf("\n                   Product No: ");
            scanf("%d",&p.no);
            printf("                   Product Name: ");
            scanf("%s",&p.name);
            printf("                   Product Price: ");
            scanf("%f",&p.price);

            fwrite(&p,sizeof(p),1,information);
        }
    }

    printf("\n\n                   Informations have been added successfully. \n\n\n\n");

    fclose(information);
}
void viewlist()
{
    FILE *information;
    information= fopen("data.txt","r");
    printf("\n\n\n\n                   ---------------List of all the Products with details---------------\n\n");


    printf("\t\t\tProduct No\t\t");
    printf("Product Name\t\t");
    printf("Product Price\t");
    printf("\n\n");


    while(fread(&p,sizeof(p),1,information)==1)

    {
        printf("\t\t\t%d\t\t",p.no);
        printf("\t%s\t\t",p.name);
        printf("\t%f\t",p.price);
        printf("\n\n");

    }
    printf("\n\n\n");
    fclose(information);
}
void search()
{
    int i;
    char product_name[20];
    int found=0;

    FILE *information;
    information=fopen("data.txt","r");

    printf("\n                   Enter Product name: ");
    scanf("%s",&product_name);

    while(fread(&p,sizeof(p),1,information)==1)
    {
        if(strcmp(product_name,p.name)==0)
        {
            found=1;
            break;
        }
    }
    if(found==1)
    {
        printf("\n\n                   Product details Found!!\n\n\n");
        printf("                   Product No: %d",p.no);
        printf("\n                   Product Name: %s",p.name);
        printf("\n                   Product Price: %f",p.price);
    }
    else
        printf("\n\n                   Sorry....Product doesn't found!!!");

    printf("\n\n\n\n");


    fclose(information);
}

void modify()
{
    int product_no;
    int found=0;
    printf("                   Enter Product No to modify: ");
    scanf("%d",&product_no);
    FILE *information;
    information=fopen("data.txt","rb+");

    while(fread(&p,sizeof(p),1,information)==1)
    {
        if(product_no==p.no)
        {
            printf("                   Product No: ");
            scanf("%d",&p.no);
            printf("                   Product Name: ");
            scanf("%s",&p.name);
            printf("                   Product Price: ");
            scanf("%f",&p.price);

            fseek(information,-sizeof(p), SEEK_CUR);
            fwrite(&p,sizeof(p),1,information);
            printf("                   Product details have been modified.");
            break;
        }

    }
    fclose(information);
}
void delet()
{
    int product_no;
    printf("\n\n                   Enter Product No to delete: ");
    scanf("%d",&product_no);
    FILE *information,*temp;
    information=fopen("data.txt","rb");
    temp=fopen("temp.txt","wb");
    while(fread(&p,sizeof(p),1,information)==1)
    {
        if(product_no!=p.no)
        {
            fwrite(&p,sizeof(p),1,temp);
        }
    }
    fclose(information);
    fclose(temp);
    remove("data.txt");
    rename("temp.txt","data.txt");
    printf("\n\n                   The record is successfully deleted\n\n");
}

void bill()
{
    int quan;
    float bill;
    char product_name[20];
    int found=0;

    FILE *information;
    information=fopen("data.txt","r");

    printf("\n                   Enter Product name: ");
    scanf("%s",&product_name);
    printf("\n                   Enter Product quantity: ");
    scanf("%d",&quan);

    while(fread(&p,sizeof(p),1,information)==1)
    {
        if(strcmp(product_name,p.name)==0)
        {
            found=1;
            break;
        }
    }
    if(found==1)
    {
        printf("\n                   Product Price: %f",p.price);
        bill = (p.price)*quan;
        printf("\n                   Total Bill: %f",bill);
    }
    else
        printf("\n\n                   Sorry....Product doesn't available!!!");


    printf("\n\n\n\n");


    fclose(information);
}


