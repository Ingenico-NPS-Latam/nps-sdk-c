#  C SDK (Beta Under Development)

##  Pre Requesites
sudo apt-get install libcurl4-openssl-dev
sudo apt-get install libxml2-dev libxml2-doc

##  How to use it

* Download and build locally: `go get github.com/Ingenico-NPS-Latam/nps-sdk-c/npsSdk`
* test.c it's just an example of how to use the sdk

##  How to Build

cc -o test test.c  npsSdk.c xml_save.c nps_utils.c parse_xml.c -I/usr/include/curl -I/usr/include/libxml2 -I/usr/include/openssl -lcurl -lxml2 -lcrypto 2>err.log

##  Configuration

It's a basic configuration of the SDK

```test.c
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <stddef.h> 

int main( int argc, char **argv)
{
 
  int env=SANBOX_ENV; /*PROD_ENV | SANBOX_ENV | STAGING_ENV*/

  FILE * auxFd = fopen ( "test.log", "a" ) ;

  if (setLog( DEBUG, NULL, auxFd)<0)
    return;

  if (setEnvironment(env)<0)
    return;
}

```
Here is an simple example request:

```test.c
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <stddef.h> /* offsetof */

#include "npsSdk.h"

FillOrderItemStruct(ORDER_ITEM_STRUCT *ptr, char *qty, char *unitPrice, char *descrip,char *type, char *skuCode, char *manFactPartNum, char *risk){
    memset(ptr, 0, sizeof(ORDER_ITEM_STRUCT));
    
    ptr->Quantity = malloc(strlen(qty)+1);
    strcpy(ptr->Quantity, qty);
    
    ptr->UnitPrice = malloc(strlen(unitPrice)+1);
    strcpy(ptr->UnitPrice, unitPrice);
    
    ptr->Description = malloc(strlen(descrip)+1);
    strcpy(ptr->Description, descrip);
    
    ptr->Type = malloc(strlen(type)+1);
    strcpy(ptr->Type, type);
    
    ptr->SkuCode = malloc(strlen(skuCode)+1);
    strcpy(ptr->SkuCode, skuCode);
    
    ptr->ManufacturerPartNumber = malloc(strlen(manFactPartNum)+1);
    strcpy(ptr->ManufacturerPartNumber, manFactPartNum);
    
    ptr->Risk = malloc(strlen(risk)+1);
    strcpy(ptr->Risk, risk);
    
}

void FillOrderItems(ARRAYOF_ORDERITEMSTRUCT *pOrderItems, int count) {
  int i;
  char qty[20];
  char unitPrice[20];
  char descrip[20];
  char type[20];
  char skuCode[20];
  char manFactPartNum[20];
  char risk[20];
  
  ORDER_ITEM_STRUCT *ptr;
  
  memset(pOrderItems, 0, sizeof(ARRAYOF_ORDERITEMSTRUCT));
  
  pOrderItems->__size = count;
  
  pOrderItems->__ptr=(ORDER_ITEM_STRUCT *)malloc(sizeof(ORDER_ITEM_STRUCT *)*count);
  for (i = 0; i < pOrderItems->__size; ++i){
    ptr=(ORDER_ITEM_STRUCT *)malloc(sizeof(ORDER_ITEM_STRUCT));
    sprintf(qty, "%d", i+1);
    sprintf(unitPrice, "%d", i+100);
    sprintf(descrip, "descrip%d", i+1);
    sprintf(type, "type%d", i+1);
    sprintf(skuCode, "skucode%d", i+1);
    sprintf(manFactPartNum, "manFactPartNum%d", i+1);
    sprintf(risk, "L");

    FillOrderItemStruct(ptr, qty, unitPrice, descrip,type, skuCode, manFactPartNum, risk);
    
    pOrderItems->__ptr[i]=ptr;
  }
  
}

void FillOrderDetailsStruct(ORDER_DETAILS_STRUCT *pOrderDetails){
    ARRAYOF_ORDERITEMSTRUCT *pOrderItems;
    int i;
    
    pOrderItems=(ARRAYOF_ORDERITEMSTRUCT *)malloc(sizeof(ARRAYOF_ORDERITEMSTRUCT));
    memset(pOrderItems, 0, sizeof(ARRAYOF_ORDERITEMSTRUCT));
    
    pOrderItems->__size=2;
    FillOrderItems(pOrderItems, 2);
    
    pOrderDetails->OrderItems=pOrderItems;
}

void FillCustomerAdditionalDetailsStruct(CUSTOMER_ADDITIONAL_DETAILS_STRUCT *pCustomerAdditionalDetails) {
    memset(pCustomerAdditionalDetails, 0, sizeof(CUSTOMER_ADDITIONAL_DETAILS_STRUCT));
    
    pCustomerAdditionalDetails->EmailAddress=malloc(strlen("jdoe@email.com")+1);
    strcpy(pCustomerAdditionalDetails->EmailAddress,"jdoe@email.com");
    
    pCustomerAdditionalDetails->AlternativeEmailAddress=malloc(strlen("Jdoe79@email.com")+1);
    strcpy(pCustomerAdditionalDetails->AlternativeEmailAddress,"Jdoe79@email.com");
    
    pCustomerAdditionalDetails->IPAddress=malloc(strlen("192.168.158.190")+1);
    strcpy(pCustomerAdditionalDetails->IPAddress,"192.168.158.190");
    
    pCustomerAdditionalDetails->AccountID=malloc(strlen("2")+1);
    strcpy(pCustomerAdditionalDetails->AccountID,"2");
    
    pCustomerAdditionalDetails->AccountCreatedAt=malloc(strlen("2010-10-23")+1);
    strcpy(pCustomerAdditionalDetails->AccountCreatedAt,"2010-10-23");
    
    pCustomerAdditionalDetails->AccountPreviousActivity=malloc(strlen("0")+1);
    strcpy(pCustomerAdditionalDetails->AccountPreviousActivity,"0");
    
    pCustomerAdditionalDetails->AccountHasCredentials=malloc(strlen("0")+1);
    strcpy(pCustomerAdditionalDetails->AccountHasCredentials,"0");
    
    pCustomerAdditionalDetails->DeviceType=malloc(strlen("2")+1);
    strcpy(pCustomerAdditionalDetails->DeviceType,"2");
    
    pCustomerAdditionalDetails->DeviceFingerPrint=malloc(strlen("22")+1);
    strcpy(pCustomerAdditionalDetails->DeviceFingerPrint,"22");
    
    pCustomerAdditionalDetails->BrowserLanguage=malloc(strlen("ES")+1);
    strcpy(pCustomerAdditionalDetails->BrowserLanguage,"ES");
    
    pCustomerAdditionalDetails->HttpUserAgent=malloc(strlen("Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:21.0) Gecko/20100101 Firefox/21.0")+1);
    strcpy(pCustomerAdditionalDetails->HttpUserAgent,"Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:21.0) Gecko/20100101 Firefox/21.0");
}

void FillPersonStruct(PERSON_STRUCT *pPerson) {
    memset(pPerson, 0, sizeof(PERSON_STRUCT));
    
    pPerson->FirstName=malloc(strlen("John")+1);
    strcpy(pPerson->FirstName, "John");
    
    pPerson->LastName=malloc(strlen("Doe")+1);
    strcpy(pPerson->LastName, "Doe");
    
    pPerson->MiddleName=malloc(strlen("Michael")+1);
    strcpy(pPerson->MiddleName, "Michael");
    
    pPerson->PhoneNumber1=malloc(strlen("+1 011 11111111")+1);
    strcpy(pPerson->PhoneNumber1, "+1 011 11111111");
    
    pPerson->PhoneNumber2=malloc(strlen("+1 011 22222222")+1);
    strcpy(pPerson->PhoneNumber2, "+1 011 22222222");
    
    pPerson->Gender=malloc(strlen("F")+1);
    strcpy(pPerson->Gender,"F");
    
    pPerson->IDNumber=malloc(strlen("54111111")+1);
    strcpy(pPerson->IDNumber,"54111111");
    
    pPerson->IDType=malloc(strlen("200")+1);
    strcpy(pPerson->IDType,"200");
  
}

void FillAddressStruct(ADDRESS_STRUCT *pAddress) {
    memset(pAddress, 0, sizeof(ADDRESS_STRUCT));
    
    pAddress->Street=malloc(strlen("Av. Collins")+1);
    strcpy(pAddress->Street,"Av. Collins");
    
    pAddress->HouseNumber=malloc(strlen("1245")+1);
    strcpy(pAddress->HouseNumber,"1245");
    
    pAddress->AdditionalInfo=malloc(strlen("2 A")+1);
    strcpy(pAddress->AdditionalInfo,"2 A");
    
    pAddress->City=malloc(strlen("Miami")+1);
    strcpy(pAddress->City, "Miami");
    
    pAddress->StateProvince=malloc(strlen("Florida")+1);
    strcpy(pAddress->StateProvince, "Florida");
    
    pAddress->Country=malloc(strlen("USA")+1);
    strcpy(pAddress->Country, "USA");
    
    pAddress->ZipCode=malloc(strlen("33140")+1);
    strcpy(pAddress->ZipCode, "33140");
  
}

void FillSellerDetails(SELLER_DETAILS_STRUCT *pSellerDetails) {
    memset(pSellerDetails, 0, sizeof(SELLER_DETAILS_STRUCT));

    pSellerDetails->IDNumber=malloc(strlen("27087764-0")+1);
    strcpy(pSellerDetails->IDNumber,"27087764-0");
    
    pSellerDetails->IDType=malloc(strlen("200")+1);
    strcpy(pSellerDetails->IDType,"200");
    
    pSellerDetails->Name=malloc(strlen("John Doe")+1);
    strcpy(pSellerDetails->Name,"John Doe");
    
    pSellerDetails->Invoice=malloc(strlen("54877555")+1);
    strcpy(pSellerDetails->Invoice,"54877555");
    
    pSellerDetails->PurchaseDescription=malloc(strlen("Descripcion")+1);
    strcpy(pSellerDetails->PurchaseDescription,"Descripcion");

}

void FillBillingDetails(BILLING_DETAILS_STRUCT *pBillingDetails) {
    memset(pBillingDetails, 0, sizeof(BILLING_DETAILS_STRUCT));
    
    pBillingDetails->Invoice = malloc(strlen("54877555")+1);
    strcpy(pBillingDetails->Invoice,"54877555");
    
   
    pBillingDetails->InvoiceAmount = malloc(strlen("15050")+1);
    strcpy(pBillingDetails->InvoiceAmount, "15050");
    
    pBillingDetails->InvoiceCurrency = malloc(strlen("032")+1);
    strcpy(pBillingDetails->InvoiceCurrency, "032");
    
};    
    
void FillMerchantAdditionalDetails(MERCHANT_ADDITIONAL_DETAILS_STRUCT *pMerchantAdditionalDetails) {
  memset(pMerchantAdditionalDetails, 0, sizeof(MERCHANT_ADDITIONAL_DETAILS_STRUCT));
  
  pMerchantAdditionalDetails->ShoppingCartInfo = malloc(strlen("ShoppingCartInfo")+1);
  strcpy(pMerchantAdditionalDetails->ShoppingCartInfo,"ShoppingCartInfo");
  
  pMerchantAdditionalDetails->ShoppingCartPluginInfo = malloc(strlen("ShoppingCartPluginInfo")+1);
  strcpy(pMerchantAdditionalDetails->ShoppingCartPluginInfo,"ShoppingCartPluginInfo");
  
}

void FillTaxesRequestStruct(TAXES_REQUEST_STRUCT *ptr, char *typeId, char *Amount) {
    memset(ptr, 0, sizeof(TAXES_REQUEST_STRUCT));
    
    ptr->TypeId = malloc(strlen(typeId)+1);
    strcpy(ptr->TypeId, typeId);
    
    ptr->Amount = malloc(strlen(Amount)+1);
    strcpy(ptr->Amount,Amount);
    
    ptr->BaseAmount = malloc(strlen("11111")+1);
    strcpy(ptr->BaseAmount,"11111");
};

void FillTaxes(ARRAYOF_TAXESREQUESTSTRUCT *pTaxes, int count) {
  int i;
  char typeId[10];
  char amount[10];
  
  TAXES_REQUEST_STRUCT *ptr;
  
  memset(pTaxes, 0, sizeof(ARRAYOF_TAXESREQUESTSTRUCT));
  
  pTaxes->__size = count;
  
  pTaxes->__ptr=(TAXES_REQUEST_STRUCT *)malloc(sizeof(TAXES_REQUEST_STRUCT *)*count);
  
  for (i = 0; i < pTaxes->__size; ++i){
    ptr=(TAXES_REQUEST_STRUCT *)malloc(sizeof(TAXES_REQUEST_STRUCT));
    sprintf(typeId, "%d", i+500);
    sprintf(amount, "%d", i+1500);
    FillTaxesRequestStruct(ptr, typeId, amount);
    pTaxes->__ptr[i]=ptr;
  }
}

void FillAmountAdditionalDetails(AMOUNT_ADDITIONAL_DETAILS_REQUEST_STRUCT *pAmountAddic) {
    ARRAYOF_TAXESREQUESTSTRUCT *pTaxes;
    
    memset(pAmountAddic, 0, sizeof(AMOUNT_ADDITIONAL_DETAILS_REQUEST_STRUCT));
    
    pAmountAddic->Tip = malloc(strlen("1111")+1);
    strcpy(pAmountAddic->Tip, "1111");
    
    pAmountAddic->Discount = malloc(strlen("22")+1);
    strcpy(pAmountAddic->Discount, "22");
    
    pTaxes=(ARRAYOF_TAXESREQUESTSTRUCT *)malloc(sizeof(ARRAYOF_TAXESREQUESTSTRUCT));
    memset(pTaxes, 0, sizeof(ARRAYOF_TAXESREQUESTSTRUCT));
    
    pTaxes->__size=2;
    FillTaxes(pTaxes, 2);
    pAmountAddic->Taxes=pTaxes;
    
}

void FillRequestPayOnLine_2p(PAY_ONLINE_2P_REQ_STRUCT *pRequest) {
  
    char psp_MerchTxRef[30];
    memset(pRequest, 0, sizeof(PAY_ONLINE_2P_REQ_STRUCT));
    pRequest->psp_Version =  malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    printf("pRequest->psp_Version [%s]\n", pRequest->psp_Version);
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    printf("pRequest->psp_MerchantId [%s]\n", pRequest->psp_MerchantId);
    
    pRequest->psp_TxSource =  malloc(strlen("WEB")+1);
    strcpy(pRequest->psp_TxSource, "WEB");
    
    pRequest->psp_Recurrent =  malloc(strlen("0")+1);
    strcpy(pRequest->psp_Recurrent, "0");
    
    pRequest->psp_NumPayments =  malloc(strlen("1")+1);
    strcpy(pRequest->psp_NumPayments, "1");
    
    pRequest->psp_Currency =  malloc(strlen(psp_Currency)+1);
    strcpy(pRequest->psp_Currency, psp_Currency);
    
    pRequest->psp_CardExpDate =  malloc(strlen("1912")+1);
    strcpy(pRequest->psp_CardExpDate, "1912");
    
    pRequest->psp_MerchOrderId =  malloc(strlen("ORDERX1466Xz")+1);
    strcpy(pRequest->psp_MerchOrderId, "ORDERX1466Xz");
    
    pRequest->psp_Product =  malloc(strlen(psp_Product)+1);
    strcpy(pRequest->psp_Product, psp_Product);
    
    pRequest->psp_Amount =  malloc(strlen(psp_Amount)+1);
    strcpy(pRequest->psp_Amount, psp_Amount);
    
    pRequest->psp_SoftDescriptor =  malloc(strlen("000000223500001")+1);
    strcpy(pRequest->psp_SoftDescriptor, "000000223500001");
    
    pRequest->psp_PosDateTime =  malloc(strlen("2017-03-23 04:13:37")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-03-23 04:13:37");
    
    pRequest->psp_PurchaseDescription =  malloc(strlen("My Items")+1);
    strcpy(pRequest->psp_PurchaseDescription, "My Items");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(psp_MerchTxRef,"ANSIC-CLIENT-%4d%02d%02d%02d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);    

    pRequest->psp_MerchTxRef =  malloc(strlen(psp_MerchTxRef)+1);
    strcpy(pRequest->psp_MerchTxRef, psp_MerchTxRef);
    
    pRequest->psp_CardNumber =  malloc(strlen(psp_CardNumber)+1);
    strcpy(pRequest->psp_CardNumber, psp_CardNumber);

    pRequest->psp_MerchantMail =  malloc(strlen("systemtest@globalcollect.nl")+1);
    strcpy(pRequest->psp_MerchantMail, "systemtest@globalcollect.nl");
    
    pRequest->psp_Country =  malloc(strlen(psp_Country)+1);
    strcpy(pRequest->psp_Country, psp_Country);

}

int SendPayOnLine_2p(void) {

  int i;
  ORDER_DETAILS_STRUCT OrderDetails, *pOrderDetails;
  CUSTOMER_ADDITIONAL_DETAILS_STRUCT CustomerAdditionalDetails, *pCustomerAdditionalDetails;
  ADDRESS_STRUCT Address, *pAddress;
  SELLER_DETAILS_STRUCT SellerDetails, *pSellerDetails;
  MERCHANT_ADDITIONAL_DETAILS_STRUCT MerchantAdditionalDetails, *pMerchantAdditionalDetails;
  AMOUNT_ADDITIONAL_DETAILS_REQUEST_STRUCT AmountAdditionalDetailsRequest, *pAmountAdditionalDetailsRequest;
  
  PAY_ONLINE_2P_REQ_STRUCT Request, *pRequest;
  PAY_ONLINE_2P_RESP_STRUCT Response, *pResponse;
  
  printf("\n******************SendPayOnLine_2p************************************\n");
    pRequest = &Request;

    pAmountAdditionalDetailsRequest = &AmountAdditionalDetailsRequest;
    pMerchantAdditionalDetails = &MerchantAdditionalDetails;
    pSellerDetails = &SellerDetails;
    pAddress = &Address;
    pCustomerAdditionalDetails = &CustomerAdditionalDetails;
    pOrderDetails = &OrderDetails;
    
    FillOrderDetailsStruct(pOrderDetails);
    
    FillCustomerAdditionalDetailsStruct(pCustomerAdditionalDetails);
    FillAddressStruct(pAddress);
    
    FillSellerDetails(pSellerDetails);
    pSellerDetails->Address = pAddress;
    
    FillMerchantAdditionalDetails(pMerchantAdditionalDetails);
    pMerchantAdditionalDetails->SellerDetails = pSellerDetails;
    
    FillAmountAdditionalDetails(pAmountAdditionalDetailsRequest);
    
    FillRequestPayOnLine_2p(pRequest);
    
    pRequest->psp_AmountAdditionalDetails = pAmountAdditionalDetailsRequest;
    pRequest->psp_MerchantAdditionalDetails = pMerchantAdditionalDetails;
    pRequest->psp_CustomerAdditionalDetails = pCustomerAdditionalDetails;
    pRequest->psp_OrderDetails = pOrderDetails;
 
    pResponse = &Response;
    showRequest(PAY_ONLINE_2P_TYPE,(char *)pRequest);
    if (sendRequest(PAY_ONLINE_2P_TYPE, apiKey, (char *)pRequest, pResponse) < 0) {
      printf("%s\n", getNpsErrDesc());
    }
    else {
      if (pResponse->psp_ResponseCod && pResponse->psp_ResponseMsg) {
        printf("psp_ResponseCod [%s]\n", pResponse->psp_ResponseCod);
        printf("psp_ResponseMsg [%s]\n", pResponse->psp_ResponseMsg);
      }

      showResponse(PAY_ONLINE_2P_TYPE,(char *)pResponse);
    }
    
  return 0;
}


int main( int argc, char **argv)
{
 
  int env=SANBOX_ENV; /*PROD_ENV | SANBOX_ENV | STAGING_ENV*/

  FILE * auxFd = fopen ( "test.log", "a" ) ;

  if (setLog( DEBUG, NULL, auxFd)<0)
    return;

  if (setEnvironment(env)<0)
    return;

  SendPayOnLine_2p();

  LogClose();

}

```

##  Environments

```test.c
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <stddef.h> /* offsetof */

#include "npsSdk.h"
int main( int argc, char **argv)
{
 
  if (setEnvironment(PROD_ENV)<0) {
    printf("%s\n", getNpsErrDesc());
    return;
  }

  if (setEnvironment(SANBOX_ENV)<0) {
    printf("%s\n", getNpsErrDesc());
    return;
  }

  if (setEnvironment(STAGING_ENV)<0) {
    printf("%s\n", getNpsErrDesc());
    return;
  }

}

```
##  Error handling

All exceptions than can occur will be detailed inside of the response provided by NPS .

```test.c 

   if (sendRequest(PAY_ONLINE_2P_TYPE, apiKey, (char *)pRequest, pResponse) < 0) {
     printf("ERROR: %s\n", getNpsErrDesc());
   }
   else {
     showResponse(PAY_ONLINE_2P_TYPE,(char *)pResponse);
   }

```
##  Advanced configurations

Nps SDK allows you to log what’s happening with you request inside of our SDK, it logs by default to stout.
The SDK uses the custom logger that you use for your project.

An example using your project logger.

```test.c
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <stddef.h> /* offsetof */

#include "npsSdk.h"

/*Using an already opened Fd*/
int main( int argc, char **argv)
{
 
  FILE * auxFd = fopen ( "test.log", "a" ) ;

  if (setLog( DEBUG, NULL, auxFd)<0) {
    printf(auxFd, "ERROR: %s", getNpsErrDesc());
    return;
  }

}

/*Opening a file and log*/
int main( int argc, char **argv)
{
 
  if (setLog( DEBUG, test.log, NULL)<0) {
    printf(auxFd, "ERROR: %s", getNpsErrDesc());
    return;
  }

}

/*Logging to stdout*/
int main( int argc, char **argv)
{
 
  if (setLog( DEBUG, NULL, NULL)<0) {
    printf(auxFd, "ERROR: %s", getNpsErrDesc());
    return;
  }

}

```

The "INFO" level will write concise information of the request and will mask sensitive data of the request. 
The "DEBUG" level will write information about the request to let developers debug it in a more detailed way.

```
you can change the timeout of the request.

ExecutionTimeout(Default=60 seconds): you can change the execution timeout of the request.

ConnectionTimeout(Default=10 seconds): you can change the connection timeout of the request.

```test.c
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <stddef.h> /* offsetof */

#include "npsSdk.h"

int main( int argc, char **argv)
{

  if (setConnTimeout(5) <0) {
    printf("ERROR: %s", getNpsErrDesc());
    return;
  }

  if (setExecTimeout(30) <0) {
    printf("ERROR: %s", getNpsErrDesc());
    return;
  }

}

```



