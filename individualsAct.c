#include <stdio.h>
#include <stdlib.h>

struct PRODUCT
{
    char prodCode[8];
    char prodDescription[30];
    float unitPrice;
    int quantity;
};

struct CUSTOMER
{
    char customerName[30];
    char cust_addres[20];
    struct PRODUCT productDetail[3];
};
struct CUSTOMER customerDetail;

void RECORD()
{
    printf("Enter Customer Name: ");
    scanf(" %[^\n]", customerDetail.customerName);
    printf("Enter Customer Address: ");
    scanf(" %[^\n]", customerDetail.cust_addres);
    for (int i = 0; i < 3; i++)
    {
        printf("Enter Product code: ");
        scanf(" %[^\n]", customerDetail.productDetail[i].prodCode);
        printf("Enter Product Description: ");
        scanf(" %[^\n]", customerDetail.productDetail[i].prodDescription);
        printf("Enter Unit Price: ");
        scanf(" %f", &customerDetail.productDetail[i].unitPrice);
        printf("Enter Number of Quantity: ");
        scanf(" %d", &customerDetail.productDetail[i].quantity);
        printf("\n");
    }
}

void KOMPUTE(float sum[])
{
    for (int i = 0; i < 3; i++)
    {
        sum[i] = customerDetail.productDetail[i].unitPrice * customerDetail.productDetail[i].quantity;
    }
}

int main()
{
    float sum[3];
    RECORD();
    KOMPUTE(sum);
    float totalAmount = sum[0] + sum[1] + sum[2];

    printf("\n%45s", "ABC HARDWARE COMPANY");
    printf("\n--------------------------------------------------------------------------");
    printf("\nCustomer: %s", customerDetail.customerName);
    printf("\nAddress:  %s", customerDetail.cust_addres);
    printf("\n--------------------------------------------------------------------------\n");

    printf("%-12s %-25s %10s %10s %12s\n", 
           "CODE", "DESCRIPTION", "PRICE", "QTY", "SUBTOTAL");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < 3; i++)
    {
        printf("%-12s %-25s %10.2f %10d %12.2f\n",
               customerDetail.productDetail[i].prodCode,
               customerDetail.productDetail[i].prodDescription,
               customerDetail.productDetail[i].unitPrice,
               customerDetail.productDetail[i].quantity,
               sum[i]);
    }
    printf("--------------------------------------------------------------------------\n");
    printf("%-60s %12.2f\n", "TOTAL AMOUNT DUE:", totalAmount);
    printf("--------------------------------------------------------------------------\n");
    return 0;
}