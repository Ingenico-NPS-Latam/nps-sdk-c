#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <stddef.h> /* offsetof */
//#include "NpsMethods.h"

#include "npsSdk.h"

char *psp_ClientSession = "iYgdiXyl56vszeEpCRGmS1JiNYg1xSnYXzQuiFWP4Q2nTwbPiWwZruUzXmqrXYR9";
char *psp_TransactionId_Orig = "158611";
char *psp_Currency = "032";
char *psp_Product = "14";
char *psp_Amount = "15050";
char *psp_Country = "ARG";
char *psp_CardNumber =  "4507990000000010";
char *psp_MerchantId="psp_test";
char *npsUrl= "https://psp.localhost:443/ws.php";
//char *npsUrl= "https://sandbox.nps.com.ar:443/ws.php";
char *apiKey="IeShlZMDk8mp8VA6vy41mLnVggnj1yqHcJyNqIYaRINZnXdiTfhF0Ule9WNAUCR6";

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
    
    pCustomerAdditionalDetails->EmailAddress=malloc(strlen("JUAN@juan.com")+1);
    strcpy(pCustomerAdditionalDetails->EmailAddress,"JUAN@juan.com");
    
    pCustomerAdditionalDetails->AlternativeEmailAddress=malloc(strlen("PEPE@pepe.com")+1);
    strcpy(pCustomerAdditionalDetails->AlternativeEmailAddress,"PEPE@pepe.com");
    
    pCustomerAdditionalDetails->IPAddress=malloc(strlen("222.222.222.222")+1);
    strcpy(pCustomerAdditionalDetails->IPAddress,"222.222.222.222");
    
    pCustomerAdditionalDetails->AccountID=malloc(strlen("2")+1);
    strcpy(pCustomerAdditionalDetails->AccountID,"2");
    
    pCustomerAdditionalDetails->AccountCreatedAt=malloc(strlen("2014-01-01")+1);
    strcpy(pCustomerAdditionalDetails->AccountCreatedAt,"2014-01-01");
    
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
    
    pCustomerAdditionalDetails->HttpUserAgent=malloc(strlen("User Agent TEST, filled by merchant")+1);
    strcpy(pCustomerAdditionalDetails->HttpUserAgent,"User Agent TEST, filled by merchant");
}

void FillPersonStruct(PERSON_STRUCT *pPerson) {
    memset(pPerson, 0, sizeof(PERSON_STRUCT));
    
    pPerson->FirstName=malloc(strlen("Silvina")+1);
    strcpy(pPerson->FirstName, "Silvina");
    
    pPerson->LastName=malloc(strlen("Falconi")+1);
    strcpy(pPerson->LastName, "Falconi");
    
    pPerson->MiddleName=malloc(strlen("Fernanda")+1);
    strcpy(pPerson->MiddleName, "Fernanda");
    
    pPerson->PhoneNumber1=malloc(strlen("52520960")+1);
    strcpy(pPerson->PhoneNumber1, "52520960");
    
    pPerson->PhoneNumber2=malloc(strlen("52520960")+1);
    strcpy(pPerson->PhoneNumber2, "52520960");
    
    pPerson->Gender=malloc(strlen("F")+1);
    strcpy(pPerson->Gender,"F");
    
    //pPerson->DateOfBirth=malloc(strlen(
    //pPerson->Nationality=malloc(strlen(
    pPerson->IDNumber=malloc(strlen("11111111")+1);
    strcpy(pPerson->IDNumber,"11111111");
    
    pPerson->IDType=malloc(strlen("100")+1);
    strcpy(pPerson->IDType,"100");
  
}

void FillAddressStruct(ADDRESS_STRUCT *pAddress) {
    memset(pAddress, 0, sizeof(ADDRESS_STRUCT));
    
    pAddress->Street=malloc(strlen("Calle falsa")+1);
    strcpy(pAddress->Street,"Calle falsa");
    
    pAddress->HouseNumber=malloc(strlen("456")+1);
    strcpy(pAddress->HouseNumber,"456");
    
    pAddress->AdditionalInfo=malloc(strlen("28")+1);
    strcpy(pAddress->AdditionalInfo,"28");
    
    pAddress->City=malloc(strlen("Capital Feedral")+1);
    strcpy(pAddress->City, "Capital Feedral");
    
    pAddress->StateProvince=malloc(strlen("Buenos Aires")+1);
    strcpy(pAddress->StateProvince, "Buenos Aires");
    
    pAddress->Country=malloc(strlen("032")+1);
    strcpy(pAddress->Country, "032");
    
    pAddress->ZipCode=malloc(strlen("1414")+1);
    strcpy(pAddress->ZipCode, "1414");
  
}

void FillSellerDetails(SELLER_DETAILS_STRUCT *pSellerDetails) {
    memset(pSellerDetails, 0, sizeof(SELLER_DETAILS_STRUCT));

    pSellerDetails->IDNumber=malloc(strlen("27087764-0")+1);
    strcpy(pSellerDetails->IDNumber,"27087764-0");
    
    pSellerDetails->IDType=malloc(strlen("200")+1);
    strcpy(pSellerDetails->IDType,"200");
    
    pSellerDetails->Name=malloc(strlen("Seller Name")+1);
    strcpy(pSellerDetails->Name,"Seller Name");
    
    pSellerDetails->Invoice=malloc(strlen("125447")+1);
    strcpy(pSellerDetails->Invoice,"125447");
    
    pSellerDetails->PurchaseDescription=malloc(strlen("Descripcion")+1);
    strcpy(pSellerDetails->PurchaseDescription,"Descripcion");

    //pSellerDetails->MCC;
    //pSellerDetails->ChannelCode;
    //pSellerDetails->GeoCode;
}

void FillBillingDetails(BILLING_DETAILS_STRUCT *pBillingDetails) {
    memset(pBillingDetails, 0, sizeof(BILLING_DETAILS_STRUCT));
    
    pBillingDetails->Invoice = malloc(strlen("100001234")+1);
    strcpy(pBillingDetails->Invoice,"100001234");
    
    //pBillingDetails->InvoiceDate = malloc(strlen("20170601")+1);
    //strcpy(pBillingDetails->InvoiceDate, "20170601");
    
    pBillingDetails->InvoiceAmount = malloc(strlen("990")+1);
    strcpy(pBillingDetails->InvoiceAmount, "990");
    
    pBillingDetails->InvoiceCurrency = malloc(strlen("032")+1);
    strcpy(pBillingDetails->InvoiceCurrency, "032");
    
    //PERSON_STRUCT*            Person                         ;
    //ADDRESS_STRUCT*           Address                        ;
};    
    
void FillMerchantAdditionalDetails(MERCHANT_ADDITIONAL_DETAILS_STRUCT *pMerchantAdditionalDetails) {
  memset(pMerchantAdditionalDetails, 0, sizeof(MERCHANT_ADDITIONAL_DETAILS_STRUCT));
  
  pMerchantAdditionalDetails->ShoppingCartInfo = malloc(strlen("ShoppingCartInfo")+1);
  strcpy(pMerchantAdditionalDetails->ShoppingCartInfo,"ShoppingCartInfo");
  
  pMerchantAdditionalDetails->SdkInfo = malloc(strlen("SdkInfo")+1);
  strcpy(pMerchantAdditionalDetails->SdkInfo, "SdkInfo");

  pMerchantAdditionalDetails->ShoppingCartPluginInfo = malloc(strlen("ShoppingCartPluginInfo")+1);
  strcpy(pMerchantAdditionalDetails->ShoppingCartPluginInfo,"ShoppingCartPluginInfo");
  
}

void FillTaxesRequestStruct(TAXES_REQUEST_STRUCT *ptr, char *typeId, char *Amount) {
    memset(ptr, 0, sizeof(TAXES_REQUEST_STRUCT));
    
    ptr->TypeId = malloc(strlen(typeId)+1);
    strcpy(ptr->TypeId, typeId);
    
    ptr->Amount = malloc(strlen(Amount)+1);
    strcpy(ptr->Amount,Amount);
    
    /*ptr->Rate = malloc(strlen("rate")+1);
    strcpy(ptr->Rate, "rate");
    */
    
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

void FillRequestAuthorize_2p(AUTHORIZE_2P_REQ_STRUCT *pRequest) {

    char psp_MerchTxRef[30];
    memset(pRequest, 0, sizeof(AUTHORIZE_2P_REQ_STRUCT));
    pRequest->psp_Version =  malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_SecureHash =  malloc(strlen("160162873179c18ade301b86d1ccf7a5")+1);
    strcpy(pRequest->psp_SecureHash, "160162873179c18ade301b86d1ccf7a5");

    pRequest->psp_Recurrent =  malloc(strlen("0")+1);
    strcpy(pRequest->psp_Recurrent, "0");

    pRequest->psp_NumPayments =  malloc(strlen("1")+1);
    strcpy(pRequest->psp_NumPayments, "1");
    
    pRequest->psp_Currency =  malloc(strlen(psp_Currency)+1);
    strcpy(pRequest->psp_Currency, psp_Currency);

    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_CardExpDate =  malloc(strlen("1812")+1);
    strcpy(pRequest->psp_CardExpDate, "1812");
    
    pRequest->psp_MerchOrderId =  malloc(strlen("000000223500001076720000100001")+1);
    strcpy(pRequest->psp_MerchOrderId, "000000223500001076720000100001");
    
    pRequest->psp_Product =  malloc(strlen(psp_Product)+1);
    strcpy(pRequest->psp_Product, psp_Product);

    pRequest->psp_Amount =  malloc(strlen(psp_Amount)+1);
    strcpy(pRequest->psp_Amount, psp_Amount);
    
    pRequest->psp_SoftDescriptor =  malloc(strlen("000000223500001")+1);
    strcpy(pRequest->psp_SoftDescriptor, "000000223500001");

    pRequest->psp_PosDateTime =  malloc(strlen("2017-03-23 04:13:37")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-03-23 04:13:37");
    
    pRequest->psp_PurchaseDescription =  malloc(strlen("00000022350000107672")+1);
    strcpy(pRequest->psp_PurchaseDescription, "00000022350000107672");
    
    pRequest->psp_TxSource =  malloc(strlen("WEB")+1);
    strcpy(pRequest->psp_TxSource, "WEB");

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
    
    //pRequest->psp_SecureHash =  malloc(strlen("160162873179c18ade301b86d1ccf7a5")+1);
    //strcpy(pRequest->psp_SecureHash, "160162873179c18ade301b86d1ccf7a5");
    
    pRequest->psp_Recurrent =  malloc(strlen("0")+1);
    strcpy(pRequest->psp_Recurrent, "0");
    
    pRequest->psp_NumPayments =  malloc(strlen("1")+1);
    strcpy(pRequest->psp_NumPayments, "1");
    
    pRequest->psp_Currency =  malloc(strlen(psp_Currency)+1);
    strcpy(pRequest->psp_Currency, psp_Currency);
    
    pRequest->psp_CardExpDate =  malloc(strlen("1812")+1);
    strcpy(pRequest->psp_CardExpDate, "1812");
    
    pRequest->psp_MerchOrderId =  malloc(strlen("000000223500001076720000100001")+1);
    strcpy(pRequest->psp_MerchOrderId, "000000223500001076720000100001");
    
    pRequest->psp_Product =  malloc(strlen(psp_Product)+1);
    strcpy(pRequest->psp_Product, psp_Product);
    
    pRequest->psp_Amount =  malloc(strlen(psp_Amount)+1);
    strcpy(pRequest->psp_Amount, psp_Amount);
    
    pRequest->psp_SoftDescriptor =  malloc(strlen("000000223500001")+1);
    strcpy(pRequest->psp_SoftDescriptor, "000000223500001");
    
    pRequest->psp_PosDateTime =  malloc(strlen("2017-03-23 04:13:37")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-03-23 04:13:37");
    
    pRequest->psp_PurchaseDescription =  malloc(strlen("00000022350000107672")+1);
    strcpy(pRequest->psp_PurchaseDescription, "00000022350000107672");

    //pRequest->psp_UserId =  malloc(strlen("useridSil")+1);
    //strcpy(pRequest->psp_UserId, "useridSil");
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(psp_MerchTxRef,"ANSIC-CLIENT-%4d%02d%02d%02d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);    

    pRequest->psp_MerchTxRef =  malloc(strlen(psp_MerchTxRef)+1);
    strcpy(pRequest->psp_MerchTxRef, psp_MerchTxRef);
    
    pRequest->psp_CardNumber =  malloc(strlen(psp_CardNumber)+1);
    strcpy(pRequest->psp_CardNumber, psp_CardNumber);

    //pRequest->psp_Plan =  malloc(strlen("plan")+1);
    //strcpy(pRequest->psp_Plan, "plan");
    
    pRequest->psp_MerchantMail =  malloc(strlen("systemtest@globalcollect.nl")+1);
    strcpy(pRequest->psp_MerchantMail, "systemtest@globalcollect.nl");
    
    pRequest->psp_Country =  malloc(strlen(psp_Country)+1);
    strcpy(pRequest->psp_Country, psp_Country);

}

void FillRequestRefund(REFUND_REQ_STRUCT *pRequest) {
    char psp_MerchTxRef[30];  
    memset(pRequest, 0, sizeof(REFUND_REQ_STRUCT));
    pRequest->psp_Version =  malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");

    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);

    pRequest->psp_TxSource =  malloc(strlen("WEB")+1);
    strcpy(pRequest->psp_TxSource, "WEB");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(psp_MerchTxRef,"ANSIC-CLIENT-%4d%02d%02d%02d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);    
    pRequest->psp_MerchTxRef =  malloc(strlen(psp_MerchTxRef)+1);
    strcpy(pRequest->psp_MerchTxRef, psp_MerchTxRef);

    pRequest->psp_TransactionId_Orig =  malloc(strlen(psp_TransactionId_Orig)+1);
    strcpy(pRequest->psp_TransactionId_Orig, psp_TransactionId_Orig);
    
    pRequest->psp_AmountToRefund =  malloc(strlen(psp_Amount)+1);
    strcpy(pRequest->psp_AmountToRefund, psp_Amount);

    pRequest->psp_CardNumber =  malloc(strlen(psp_CardNumber)+1);
    strcpy(pRequest->psp_CardNumber, psp_CardNumber);
    
    pRequest->psp_CardExpDate =  malloc(strlen("1812")+1);
    strcpy(pRequest->psp_CardExpDate, "1812");

    pRequest->psp_PosDateTime =  malloc(strlen("2017-03-23 04:13:37")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-03-23 04:13:37");

}

void FillRequestCapture(CAPTURE_REQ_STRUCT *pRequest) {
    char psp_MerchTxRef[30];  
    memset(pRequest, 0, sizeof(CAPTURE_REQ_STRUCT));
    pRequest->psp_Version =  malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");

    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);

    pRequest->psp_TxSource =  malloc(strlen("WEB")+1);
    strcpy(pRequest->psp_TxSource, "WEB");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(psp_MerchTxRef,"ANSIC-CLIENT-%4d%02d%02d%02d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);    
    pRequest->psp_MerchTxRef =  malloc(strlen(psp_MerchTxRef)+1);
    strcpy(pRequest->psp_MerchTxRef, psp_MerchTxRef);

    pRequest->psp_TransactionId_Orig =  malloc(strlen(psp_TransactionId_Orig)+1);
    strcpy(pRequest->psp_TransactionId_Orig, psp_TransactionId_Orig);
    
    pRequest->psp_AmountToCapture =  malloc(strlen(psp_Amount)+1);
    strcpy(pRequest->psp_AmountToCapture, psp_Amount);

    pRequest->psp_PosDateTime =  malloc(strlen("2017-03-23 04:13:37")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-03-23 04:13:37");
}

void FillRequestBankPayment_2p(BANK_PAYMENT_2P_REQ_STRUCT *pRequest) {
    char psp_MerchTxRef[30];
    memset(pRequest, 0, sizeof(BANK_PAYMENT_2P_REQ_STRUCT));
    pRequest->psp_Version =  malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_TxSource =  malloc(strlen("WEB")+1);
    strcpy(pRequest->psp_TxSource, "WEB");
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(psp_MerchTxRef,"ANSIC-CLIENT-%4d%02d%02d%02d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);    

    pRequest->psp_MerchTxRef =  malloc(strlen(psp_MerchTxRef)+1);
    strcpy(pRequest->psp_MerchTxRef, psp_MerchTxRef);
    
    pRequest->psp_MerchOrderId =  malloc(strlen("000000223500001076720000100001")+1);
    strcpy(pRequest->psp_MerchOrderId, "000000223500001076720000100001");

    pRequest->psp_Currency =  malloc(strlen(psp_Currency)+1);
    strcpy(pRequest->psp_Currency, psp_Currency);
    
    pRequest->psp_Product =  malloc(strlen("320")+1);
    strcpy(pRequest->psp_Product, "320");
    
    pRequest->psp_Country =  malloc(strlen(psp_Country)+1);
    strcpy(pRequest->psp_Country, psp_Country);
    
    pRequest->psp_ScreenDescription =  malloc(strlen("SCR DESC")+1);
    strcpy(pRequest->psp_ScreenDescription, "SCR DESC");
    
    pRequest->psp_TicketDescription =  malloc(strlen("ticket desc")+1);
    strcpy(pRequest->psp_TicketDescription, "ticket desc");
    
    pRequest->psp_Amount1 =  malloc(strlen("10000")+1);
    strcpy(pRequest->psp_Amount1, "10000");
    
    //pRequest->psp_ExpDate1 =  malloc(strlen(
    
    pRequest->psp_Amount2 =  malloc(strlen("20000")+1);
    strcpy(pRequest->psp_Amount2, "20000");
    
    //pRequest->psp_ExpDate2 =  malloc(strlen(
    
    pRequest->psp_Amount3 =  malloc(strlen("30000")+1);
    strcpy(pRequest->psp_Amount3, "30000");
    
    //pRequest->psp_ExpDate3 =  malloc(strlen(
    //pRequest->psp_MinAmount =  malloc(strlen(
    //pRequest->psp_ExpTime =  malloc(strlen(
    //pRequest->psp_ExpMark =  malloc(strlen(
    pRequest->psp_CustomerBankId =  malloc(strlen("HSBC")+1);
    strcpy(pRequest->psp_CustomerBankId, "HSBC");
    
    //pRequest->psp_CustomerMail =  malloc(strlen(
    //pRequest->psp_CustomerId =  malloc(strlen(
      
    pRequest->psp_MerchantMail =  malloc(strlen("systemtest@globalcollect.nl")+1);
    strcpy(pRequest->psp_MerchantMail, "systemtest@globalcollect.nl");
    
    pRequest->psp_PosDateTime =  malloc(strlen("2017-03-23 04:13:37")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-03-23 04:13:37");
    
}
void FillRequestSplitPayOnLine_2p(SPLIT_PAY_ONLINE_2P_REQ_STRUCT *pRequest) {
  
    char psp_MerchTxRef[30];
    memset(pRequest, 0, sizeof(SPLIT_PAY_ONLINE_2P_REQ_STRUCT));
    
    pRequest->psp_Version =  malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_TxSource =  malloc(strlen("WEB")+1);
    strcpy(pRequest->psp_TxSource, "WEB");
    
    pRequest->psp_MerchOrderId =  malloc(strlen("000000223500001076720000100001")+1);
    strcpy(pRequest->psp_MerchOrderId, "000000223500001076720000100001");
    
    pRequest->psp_Amount =  malloc(strlen(psp_Amount)+1);
    strcpy(pRequest->psp_Amount, psp_Amount);
    
    pRequest->psp_Currency =  malloc(strlen(psp_Currency)+1);
    strcpy(pRequest->psp_Currency, psp_Currency);
    
    pRequest->psp_Country =  malloc(strlen(psp_Country)+1);
    strcpy(pRequest->psp_Country, psp_Country);
    
    pRequest->psp_Recurrent =  malloc(strlen("0")+1);
    strcpy(pRequest->psp_Recurrent, "0");
    
    //char*                                psp_UseMultipleProducts  ;
    
    pRequest->psp_Product =  malloc(strlen(psp_Product)+1);
    strcpy(pRequest->psp_Product, psp_Product);
    
    pRequest->psp_CardNumber =  malloc(strlen(psp_CardNumber)+1);
    strcpy(pRequest->psp_CardNumber, psp_CardNumber);
    
    pRequest->psp_CardExpDate =  malloc(strlen("1812")+1);
    strcpy(pRequest->psp_CardExpDate, "1812");

    pRequest->psp_CardSecurityCode =  malloc(strlen("123")+1);
    strcpy(pRequest->psp_CardSecurityCode, "123");
    
    pRequest->psp_CardHolderName =  malloc(strlen("Holder Name")+1);
    strcpy(pRequest->psp_CardHolderName, "Holder Name");
    
    pRequest->psp_PurchaseDescription =  malloc(strlen("00000022350000107672")+1);
    strcpy(pRequest->psp_PurchaseDescription, "00000022350000107672");
    
    pRequest->psp_SoftDescriptor =  malloc(strlen("000000223500001")+1);
    strcpy(pRequest->psp_SoftDescriptor, "000000223500001");
//    char*                                psp_ForceProcessingMethod ;
    
    pRequest->psp_PosDateTime =  malloc(strlen("2017-03-23 04:13:37")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-03-23 04:13:37");
    /*char*                                psp_3dSecure_XID   ;
    char*                                psp_3dSecure_CAVV  ;
    char*                                psp_3dSecure_ECI   ;
    char*                                psp_3dSecure_Secured ;
    char*                                psp_SecureHash           ;
    */
}
void FillRequestPayOnLine_3p(PAY_ONLINE_3P_REQ_STRUCT *pRequest) {
  
    char psp_MerchTxRef[30];
    memset(pRequest, 0, sizeof(PAY_ONLINE_3P_REQ_STRUCT));
    pRequest->psp_Version =  malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_TxSource =  malloc(strlen("WEB")+1);
    strcpy(pRequest->psp_TxSource, "WEB");
    
    pRequest->psp_SecureHash =  malloc(strlen("160162873179c18ade301b86d1ccf7a5")+1);
    strcpy(pRequest->psp_SecureHash, "160162873179c18ade301b86d1ccf7a5");
    
    pRequest->psp_NumPayments =  malloc(strlen("1")+1);
    strcpy(pRequest->psp_NumPayments, "1");
    
    pRequest->psp_Currency =  malloc(strlen(psp_Currency)+1);
    strcpy(pRequest->psp_Currency, psp_Currency);
    
    pRequest->psp_MerchOrderId =  malloc(strlen("000000223500001076720000100001")+1);
    strcpy(pRequest->psp_MerchOrderId, "000000223500001076720000100001");
    
    pRequest->psp_Product =  malloc(strlen(psp_Product)+1);
    strcpy(pRequest->psp_Product, psp_Product);
    
    pRequest->psp_Amount =  malloc(strlen(psp_Amount)+1);
    strcpy(pRequest->psp_Amount, psp_Amount);
    
    pRequest->psp_SoftDescriptor =  malloc(strlen("000000223500001")+1);
    strcpy(pRequest->psp_SoftDescriptor, "000000223500001");
    
    pRequest->psp_PosDateTime =  malloc(strlen("2017-03-23 04:13:37")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-03-23 04:13:37");
    
    pRequest->psp_PurchaseDescription =  malloc(strlen("00000022350000107672")+1);
    strcpy(pRequest->psp_PurchaseDescription, "00000022350000107672");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(psp_MerchTxRef,"ANSIC-CLIENT-%4d%02d%02d%02d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);    

    pRequest->psp_MerchTxRef =  malloc(strlen(psp_MerchTxRef)+1);
    strcpy(pRequest->psp_MerchTxRef, psp_MerchTxRef);
    
    pRequest->psp_MerchantMail =  malloc(strlen("systemtest@globalcollect.nl")+1);
    strcpy(pRequest->psp_MerchantMail, "systemtest@globalcollect.nl");
    
    pRequest->psp_Country =  malloc(strlen(psp_Country)+1);
    strcpy(pRequest->psp_Country, psp_Country);

    pRequest->psp_ReturnURL =  malloc(strlen("'http://psp-client.localhost/simple_query_tx.php'")+1);
    strcpy(pRequest->psp_ReturnURL, "http://psp-client.localhost/simple_query_tx.php");

    pRequest->psp_FrmLanguage =  malloc(strlen("en_US")+1);
    strcpy(pRequest->psp_FrmLanguage, "en_US");
    
}

void FillRequestSplitPayOnLine_3p(SPLIT_PAY_ONLINE_3P_REQ_STRUCT *pRequest) {
/*    
    char*                                psp_PromotionCode        ;
    char*                                psp_PresetCardIIN        ;
    char*                                psp_3dSecureAction       ;
    char*                                psp_VisaArg_DA_DocType ;
    char*                                psp_VisaArg_DA_DocNum ;
    char*                                psp_VisaArg_DA_DoorNum ;
    char*                                psp_VisaArg_DA_BirthDay ;
    char*                                psp_VisaArg_DA_Name ;
    char*                                psp_AmexArg_AVS_Address ;
    char*                                psp_AmexArg_AVS_PostCode ;
    char*                                psp_MasterArg_AVS_BirthDay ;
    char*                                psp_MasterArg_AVS_AdditionalsQtty ;
    char*                                psp_MasterArg_AVS_PostalCode ;
    char*                                psp_MasterArg_AVS_BranchEntity ;
    char*                                psp_SecureHash           ;
    struct VaultReference3pStruct*  psp_VaultReference       ;
    MERCHANT_ADDITIONAL_DETAILS_STRUCT*  psp_MerchantAdditionalDetails ;
    CUSTOMER_ADDITIONAL_DETAILS_STRUCT*  psp_CustomerAdditionalDetails ;
    BILLING_DETAILS_STRUCT*    psp_BillingDetails       ;
    struct ShippingDetailsStruct*   psp_ShippingDetails      ;
    ORDER_DETAILS_STRUCT*      psp_OrderDetails         ;
    struct AirlineDetailsStruct*    psp_AirlineDetails       ;
    ARRAYOF_REQUERIMIENTOSTRUCT_SPLITPAYONLINE_3P_TRANSACTIONS*  psp_Transactions         ;*/
    
    char psp_MerchTxRef[30];
    memset(pRequest, 0, sizeof(SPLIT_PAY_ONLINE_3P_REQ_STRUCT));
    
    pRequest->psp_Version =  malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_TxSource =  malloc(strlen("WEB")+1);
    strcpy(pRequest->psp_TxSource, "WEB");
    
    pRequest->psp_MerchOrderId =  malloc(strlen("000000223500001076720000100001")+1);
    strcpy(pRequest->psp_MerchOrderId, "000000223500001076720000100001");

    pRequest->psp_ReturnURL =  malloc(strlen("'http://psp-client.localhost/simple_query_tx.php'")+1);
    strcpy(pRequest->psp_ReturnURL, "http://psp-client.localhost/simple_query_tx.php");

    pRequest->psp_FrmLanguage =  malloc(strlen("en_US")+1);
    strcpy(pRequest->psp_FrmLanguage, "en_US");
    //char*                                psp_FrmBackButtonURL     ;
    //char*                                psp_FrmTimeout           ;
    
    pRequest->psp_Amount =  malloc(strlen(psp_Amount)+1);
    strcpy(pRequest->psp_Amount, psp_Amount);
    
    pRequest->psp_Currency =  malloc(strlen(psp_Currency)+1);
    strcpy(pRequest->psp_Currency, psp_Currency);
    
    pRequest->psp_Country =  malloc(strlen(psp_Country)+1);
    strcpy(pRequest->psp_Country, psp_Country);
    
    //char*                                psp_UseMultipleProducts  ;
    
    pRequest->psp_Product =  malloc(strlen(psp_Product)+1);
    strcpy(pRequest->psp_Product, psp_Product);
    
    pRequest->psp_MerchantMail =  malloc(strlen("systemtest@globalcollect.nl")+1);
    strcpy(pRequest->psp_MerchantMail, "systemtest@globalcollect.nl");
    //char*                                psp_CustomerId           ;
    
    pRequest->psp_PurchaseDescription =  malloc(strlen("00000022350000107672")+1);
    strcpy(pRequest->psp_PurchaseDescription, "00000022350000107672");
    
    pRequest->psp_SoftDescriptor =  malloc(strlen("000000223500001")+1);
    strcpy(pRequest->psp_SoftDescriptor, "000000223500001");
//    char*                                psp_ForceProcessingMethod ;
    
    pRequest->psp_PosDateTime =  malloc(strlen("2017-03-23 04:13:37")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-03-23 04:13:37");
    /*char*                                psp_3dSecure_XID   ;
    char*                                psp_3dSecure_CAVV  ;
    char*                                psp_3dSecure_ECI   ;
    char*                                psp_3dSecure_Secured ;
    char*                                psp_SecureHash           ;
    */
    
}
void FillRequestAuthorize_3p(AUTHORIZE_3P_REQ_STRUCT *pRequest) {
  
    char psp_MerchTxRef[30];
    memset(pRequest, 0, sizeof(AUTHORIZE_3P_REQ_STRUCT));
    pRequest->psp_Version =  malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_TxSource =  malloc(strlen("WEB")+1);
    strcpy(pRequest->psp_TxSource, "WEB");
    
    pRequest->psp_SecureHash =  malloc(strlen("160162873179c18ade301b86d1ccf7a5")+1);
    strcpy(pRequest->psp_SecureHash, "160162873179c18ade301b86d1ccf7a5");
    
    pRequest->psp_NumPayments =  malloc(strlen("1")+1);
    strcpy(pRequest->psp_NumPayments, "1");
    
    pRequest->psp_Currency =  malloc(strlen(psp_Currency)+1);
    strcpy(pRequest->psp_Currency, psp_Currency);
    
    pRequest->psp_MerchOrderId =  malloc(strlen("000000223500001076720000100001")+1);
    strcpy(pRequest->psp_MerchOrderId, "000000223500001076720000100001");
    
    pRequest->psp_Product =  malloc(strlen(psp_Product)+1);
    strcpy(pRequest->psp_Product, psp_Product);
    
    pRequest->psp_Amount =  malloc(strlen(psp_Amount)+1);
    strcpy(pRequest->psp_Amount, psp_Amount);
    
    pRequest->psp_SoftDescriptor =  malloc(strlen("000000223500001")+1);
    strcpy(pRequest->psp_SoftDescriptor, "000000223500001");
    
    pRequest->psp_PosDateTime =  malloc(strlen("2017-03-23 04:13:37")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-03-23 04:13:37");
    
    pRequest->psp_PurchaseDescription =  malloc(strlen("00000022350000107672")+1);
    strcpy(pRequest->psp_PurchaseDescription, "00000022350000107672");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(psp_MerchTxRef,"ANSIC-CLIENT-%4d%02d%02d%02d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);    

    pRequest->psp_MerchTxRef =  malloc(strlen(psp_MerchTxRef)+1);
    strcpy(pRequest->psp_MerchTxRef, psp_MerchTxRef);
    
    pRequest->psp_MerchantMail =  malloc(strlen("systemtest@globalcollect.nl")+1);
    strcpy(pRequest->psp_MerchantMail, "systemtest@globalcollect.nl");
    
    pRequest->psp_Country =  malloc(strlen(psp_Country)+1);
    strcpy(pRequest->psp_Country, psp_Country);

    pRequest->psp_ReturnURL =  malloc(strlen("'http://psp-client.localhost/simple_query_tx.php'")+1);
    strcpy(pRequest->psp_ReturnURL, "http://psp-client.localhost/simple_query_tx.php");

    pRequest->psp_FrmLanguage =  malloc(strlen("en_US")+1);
    strcpy(pRequest->psp_FrmLanguage, "en_US");
}
void FillRequestBankPayment_3p(BANK_PAYMENT_3P_REQ_STRUCT *pRequest) {
    char psp_MerchTxRef[30];
    memset(pRequest, 0, sizeof(BANK_PAYMENT_3P_REQ_STRUCT));
    pRequest->psp_Version =  malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_TxSource =  malloc(strlen("WEB")+1);
    strcpy(pRequest->psp_TxSource, "WEB");
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(psp_MerchTxRef,"ANSIC-CLIENT-%4d%02d%02d%02d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);    

    pRequest->psp_MerchTxRef =  malloc(strlen(psp_MerchTxRef)+1);
    strcpy(pRequest->psp_MerchTxRef, psp_MerchTxRef);
    
    pRequest->psp_MerchOrderId =  malloc(strlen("000000223500001076720000100001")+1);
    strcpy(pRequest->psp_MerchOrderId, "000000223500001076720000100001");

    pRequest->psp_Currency =  malloc(strlen(psp_Currency)+1);
    strcpy(pRequest->psp_Currency, psp_Currency);
    
    pRequest->psp_Product =  malloc(strlen("320")+1);
    strcpy(pRequest->psp_Product, "320");
    
    pRequest->psp_Country =  malloc(strlen(psp_Country)+1);
    strcpy(pRequest->psp_Country, psp_Country);
    
    pRequest->psp_ScreenDescription =  malloc(strlen("SCR DESC")+1);
    strcpy(pRequest->psp_ScreenDescription, "SCR DESC");
    
    pRequest->psp_TicketDescription =  malloc(strlen("ticket desc")+1);
    strcpy(pRequest->psp_TicketDescription, "ticket desc");
    
    pRequest->psp_Amount1 =  malloc(strlen("10000")+1);
    strcpy(pRequest->psp_Amount1, "10000");
    
    //pRequest->psp_ExpDate1 =  malloc(strlen(
    
    pRequest->psp_Amount2 =  malloc(strlen("20000")+1);
    strcpy(pRequest->psp_Amount2, "20000");
    
    //pRequest->psp_ExpDate2 =  malloc(strlen(
    
    pRequest->psp_Amount3 =  malloc(strlen("30000")+1);
    strcpy(pRequest->psp_Amount3, "30000");
    
    //pRequest->psp_ExpDate3 =  malloc(strlen(
    //pRequest->psp_MinAmount =  malloc(strlen(
    //pRequest->psp_ExpTime =  malloc(strlen(
    //pRequest->psp_ExpMark =  malloc(strlen(
    
    //pRequest->psp_CustomerMail =  malloc(strlen(
    //pRequest->psp_CustomerId =  malloc(strlen(
      
    pRequest->psp_MerchantMail =  malloc(strlen("systemtest@globalcollect.nl")+1);
    strcpy(pRequest->psp_MerchantMail, "systemtest@globalcollect.nl");
    
    pRequest->psp_PosDateTime =  malloc(strlen("2017-03-23 04:13:37")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-03-23 04:13:37");
}

void FillRequestCashPayment_3p(CASH_PAYMENT_3P_REQ_STRUCT *pRequest) {
    char psp_MerchTxRef[30];
    memset(pRequest, 0, sizeof(CASH_PAYMENT_3P_REQ_STRUCT));
    pRequest->psp_Version =  malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_TxSource =  malloc(strlen("WEB")+1);
    strcpy(pRequest->psp_TxSource, "WEB");
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(psp_MerchTxRef,"ANSIC-CLIENT-%4d%02d%02d%02d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);    

    pRequest->psp_MerchTxRef =  malloc(strlen(psp_MerchTxRef)+1);
    strcpy(pRequest->psp_MerchTxRef, psp_MerchTxRef);
    
    pRequest->psp_MerchOrderId =  malloc(strlen("000000223500001076720000100001")+1);
    strcpy(pRequest->psp_MerchOrderId, "000000223500001076720000100001");

    pRequest->psp_Currency =  malloc(strlen(psp_Currency)+1);
    strcpy(pRequest->psp_Currency, psp_Currency);
    
    pRequest->psp_Product =  malloc(strlen("320")+1);
    strcpy(pRequest->psp_Product, "320");
    
    pRequest->psp_Country =  malloc(strlen(psp_Country)+1);
    strcpy(pRequest->psp_Country, psp_Country);
    
    
    //pRequest->psp_ExpDate3 =  malloc(strlen(
    //pRequest->psp_MinAmount =  malloc(strlen(
    //pRequest->psp_ExpTime =  malloc(strlen(
    //pRequest->psp_ExpMark =  malloc(strlen(
    
    //pRequest->psp_CustomerMail =  malloc(strlen(
    //pRequest->psp_CustomerId =  malloc(strlen(
      
    pRequest->psp_MerchantMail =  malloc(strlen("systemtest@globalcollect.nl")+1);
    strcpy(pRequest->psp_MerchantMail, "systemtest@globalcollect.nl");
    
    pRequest->psp_PosDateTime =  malloc(strlen("2017-03-23 04:13:37")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-03-23 04:13:37");
}

void FillCardInputDetailsStruct(CARD_INPUT_DETAILS_STRUCT *ptr)
{
  memset(ptr, 0, sizeof(CARD_INPUT_DETAILS_STRUCT));

  ptr->HolderName = malloc(strlen("tester")+1);
  strcpy(ptr->HolderName,"tester");

  ptr->ExpirationDate = malloc(strlen("1812")+1);
  strcpy(ptr->ExpirationDate,"1812");

  ptr->Number = malloc(strlen("4507990000000010")+1);
  strcpy(ptr->Number,"4507990000000010");

  ptr->SecurityCode = malloc(strlen("123")+1);
  strcpy(ptr->SecurityCode,"123");
  
}

void FillPaymentMethodInputDetailsStruct(PAYMENT_METHOD_INPUT_DETAILS_STRUCT *ptr)
{
  CARD_INPUT_DETAILS_STRUCT *pCardInputDetails;
  PERSON_STRUCT *pPerson;
  ADDRESS_STRUCT *pAddress;
  
  memset(ptr, 0, sizeof(PAYMENT_METHOD_INPUT_DETAILS_STRUCT));
  
  pCardInputDetails=(CARD_INPUT_DETAILS_STRUCT *)malloc(sizeof(CARD_INPUT_DETAILS_STRUCT));
  FillCardInputDetailsStruct(pCardInputDetails);
  ptr->CardInputDetails=pCardInputDetails;
  
  pPerson=(PERSON_STRUCT *)malloc(sizeof(PERSON_STRUCT));
  FillPersonStruct(pPerson);
  ptr->Person=pPerson;
  
  pAddress=(ADDRESS_STRUCT *)malloc(sizeof(ADDRESS_STRUCT));
  FillAddressStruct(pAddress);
  ptr->Address=pAddress;
  
}

void FillRequestCreatePaymentMethod(CREATE_PAYMENT_METHOD_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(CREATE_PAYMENT_METHOD_REQ_STRUCT));
    
    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    //pRequest->psp_CustomerId= malloc(strlen("customer id")+1);
    //strcpy(pRequest->psp_CustomerId, "customer id");
    //pRequest->psp_SetAsCustomerDefault ;
    
    pRequest->psp_PosDateTime= malloc(strlen("2017-03-23 04:13:37")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-03-23 04:13:37");

}

void FillRequestCreatePaymentMethodToken(CREATE_PAYMENT_METHOD_TOKEN_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(CREATE_PAYMENT_METHOD_TOKEN_REQ_STRUCT));
    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_ClientSession = malloc(strlen(psp_ClientSession)+1);
    strcpy(pRequest->psp_ClientSession, psp_ClientSession);
}
void FillRequestRetrievePaymentMethodToken(RETRIEVE_PAYMENT_METHOD_TOKEN_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(RETRIEVE_PAYMENT_METHOD_TOKEN_REQ_STRUCT));
    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_PaymentMethodToken = malloc(strlen("FG2WE0mVhoOm4U2a1R8qsBe307mtiVy0")+1);
    strcpy(pRequest->psp_PaymentMethodToken, "FG2WE0mVhoOm4U2a1R8qsBe307mtiVy0");
    
    pRequest->psp_ClientSession = malloc(strlen(psp_ClientSession)+1);
    strcpy(pRequest->psp_ClientSession, psp_ClientSession);
}

void FillRequestCreatePaymentMethodFromPayment(CREATE_PAYMENT_METHOD_FROM_PAYMENT_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(CREATE_PAYMENT_METHOD_FROM_PAYMENT_REQ_STRUCT));
    
    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_TransactionId = malloc(strlen("1868712") +1);
    strcpy(pRequest->psp_TransactionId,"1868712");
    
    pRequest->psp_PosDateTime = malloc(strlen("2018-03-21 12:00:00")+1);
    strcpy(pRequest->psp_PosDateTime, "2018-03-21 12:00:00");
    pRequest->psp_SecureHash =  malloc(strlen("160162873179c18ade301b86d1ccf7a5")+1);
    strcpy(pRequest->psp_SecureHash, "160162873179c18ade301b86d1ccf7a5");
}

void FillRequestRetrievePaymentMethod(RETRIEVE_PAYMENT_METHOD_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(RETRIEVE_PAYMENT_METHOD_TOKEN_REQ_STRUCT));
    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_PaymentMethodId = malloc(strlen("ZSUjUAEcb5uQ3qtNSS7N7gyDMPtODkjt")+1);
    strcpy(pRequest->psp_PaymentMethodId, "ZSUjUAEcb5uQ3qtNSS7N7gyDMPtODkjt");
    
    pRequest->psp_PosDateTime = malloc(strlen("2018-03-21 12:00:00")+1);
    strcpy(pRequest->psp_PosDateTime, "2018-03-21 12:00:00");
}

void FillRequestUpdatePaymentMethod(UPDATE_PAYMENT_METHOD_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(UPDATE_PAYMENT_METHOD_REQ_STRUCT));
    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_PaymentMethodId = malloc(strlen("ZSUjUAEcb5uQ3qtNSS7N7gyDMPtODkjt")+1);
    strcpy(pRequest->psp_PaymentMethodId, "ZSUjUAEcb5uQ3qtNSS7N7gyDMPtODkjt");

    pRequest->psp_PosDateTime = malloc(strlen("2018-03-21 12:00:00")+1);
    strcpy(pRequest->psp_PosDateTime, "2018-03-21 12:00:00");
}

void FillRequestDeletePaymentMethod(DELETE_PAYMENT_METHOD_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(DELETE_PAYMENT_METHOD_REQ_STRUCT));
    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_PaymentMethodId = malloc(strlen("ZSUjUAEcb5uQ3qtNSS7N7gyDMPtODkjt")+1);
    strcpy(pRequest->psp_PaymentMethodId, "ZSUjUAEcb5uQ3qtNSS7N7gyDMPtODkjt");
    
    pRequest->psp_PosDateTime = malloc(strlen("2018-03-21 12:00:00")+1);
    strcpy(pRequest->psp_PosDateTime, "2018-03-21 12:00:00");
}
/*
    char*                                psp_PaymentMethodId      ;
    char*                                psp_CardSecurityCode     ;
    PERSON_STRUCT*            psp_Person               ;
    ADDRESS_STRUCT*           psp_Address              ;
    char*                                psp_ClientSession        ;  
*/
void FillRequestRecachePaymentMethodToken(RECACHE_PAYMENT_METHOD_TOKEN_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(RECACHE_PAYMENT_METHOD_TOKEN_REQ_STRUCT));
    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_PaymentMethodId = malloc(strlen("ZSUjUAEcb5uQ3qtNSS7N7gyDMPtODkjt")+1);
    strcpy(pRequest->psp_PaymentMethodId, "ZSUjUAEcb5uQ3qtNSS7N7gyDMPtODkjt");
    
    pRequest->psp_ClientSession = malloc(strlen(psp_ClientSession)+1);
    strcpy(pRequest->psp_ClientSession, psp_ClientSession);
    
    pRequest->psp_CardSecurityCode = malloc(strlen("123")+1);
    strcpy(pRequest->psp_CardSecurityCode, "123");
}

void FillRequestCreateCustomer(CREATE_CUSTOMER_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(CREATE_CUSTOMER_REQ_STRUCT));
    
    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_PosDateTime = malloc(strlen("2017-06-19 12:00:00")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-06-19 12:00:00");
    
    pRequest->psp_EmailAddress = malloc(strlen("CustomerEmail@email.com.ar")+1);
    strcpy(pRequest->psp_EmailAddress, "CustomerEmail@email.com.ar");
/*    char*                                psp_AlternativeEmailAddress ;
    char*                                psp_AccountID            ;
    char*                                psp_AccountCreatedAt     ;
*/
  
}

void FillRequestRetrieveCustomer(RETRIEVE_CUSTOMER_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(RETRIEVE_CUSTOMER_REQ_STRUCT));
    
    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);

    pRequest->psp_CustomerId = malloc(strlen("6zovJd3916kc4syXxGYtr6iINotYhUFN")+1);
    strcpy(pRequest->psp_CustomerId, "6zovJd3916kc4syXxGYtr6iINotYhUFN");

    pRequest->psp_PosDateTime = malloc(strlen("2017-06-19 12:00:00")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-06-19 12:00:00");
    
}

void FillRequestUpdateCustomer(UPDATE_CUSTOMER_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(UPDATE_CUSTOMER_REQ_STRUCT));
    
    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);

    pRequest->psp_CustomerId = malloc(strlen("6zovJd3916kc4syXxGYtr6iINotYhUFN")+1);
    strcpy(pRequest->psp_CustomerId, "6zovJd3916kc4syXxGYtr6iINotYhUFN");
    
    pRequest->psp_PosDateTime = malloc(strlen("2017-06-19 12:00:00")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-06-19 12:00:00");
    
    pRequest->psp_EmailAddress = malloc(strlen("CustomerEmail@email.com.ar")+1);
    strcpy(pRequest->psp_EmailAddress, "CustomerEmail@email.com.ar");
    
}

void FillRequestDeleteCustomer(DELETE_CUSTOMER_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(DELETE_CUSTOMER_REQ_STRUCT));

    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);

    pRequest->psp_CustomerId = malloc(strlen("6zovJd3916kc4syXxGYtr6iINotYhUFN")+1);
    strcpy(pRequest->psp_CustomerId, "6zovJd3916kc4syXxGYtr6iINotYhUFN");

    pRequest->psp_PosDateTime = malloc(strlen("2017-06-19 12:00:00")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-06-19 12:00:00");
    
}

void FillRequestSimpleQueryTx(SIMPLE_QUERY_TX_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(SIMPLE_QUERY_TX_REQ_STRUCT));

    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_QueryCriteria = malloc(strlen("T")+1);
    strcpy(pRequest->psp_QueryCriteria, "T");
    
    pRequest->psp_QueryCriteriaId = malloc(strlen("2299459")+1);
    strcpy(pRequest->psp_QueryCriteriaId,"2299459");

    pRequest->psp_PosDateTime = malloc(strlen("2017-06-19 12:00:00")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-06-19 12:00:00");
    
}

void FillRequestQueryCardNumber(QUERY_CARD_NUMBER_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(QUERY_CARD_NUMBER_REQ_STRUCT));

    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_QueryCriteria = malloc(strlen("T")+1);
    strcpy(pRequest->psp_QueryCriteria, "T");
    
    pRequest->psp_QueryCriteriaId = malloc(strlen("76577")+1);
    strcpy(pRequest->psp_QueryCriteriaId,"76577");

    pRequest->psp_PosDateTime = malloc(strlen("2017-06-19 12:00:00")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-06-19 12:00:00");
    
}

void FillRequestQueryCardDetails(QUERY_CARD_DETAILS_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(QUERY_CARD_DETAILS_REQ_STRUCT));

    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_QueryCriteria = malloc(strlen("T")+1);
    strcpy(pRequest->psp_QueryCriteria, "T");
    
    pRequest->psp_QueryCriteriaId = malloc(strlen("76577")+1);
    strcpy(pRequest->psp_QueryCriteriaId,"76577");

    pRequest->psp_PosDateTime = malloc(strlen("2017-06-19 12:00:00")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-06-19 12:00:00");
    
}
void FillRequestQueryTxs(QUERY_TXS_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(QUERY_TXS_REQ_STRUCT));

    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_QueryCriteria = malloc(strlen("T")+1);
    strcpy(pRequest->psp_QueryCriteria, "T");
    
    pRequest->psp_QueryCriteriaId = malloc(strlen("1868712")+1);
    strcpy(pRequest->psp_QueryCriteriaId,"1868712");

    pRequest->psp_PosDateTime = malloc(strlen("2017-06-19 12:00:00")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-06-19 12:00:00");
    
}

void FillRequestGetIINDetails(GET_IIN_DETAILS_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(GET_IIN_DETAILS_REQ_STRUCT));

    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_IIN = malloc(strlen("450799")+1);
    strcpy(pRequest->psp_IIN, "450799");

    pRequest->psp_PosDateTime = malloc(strlen("2017-06-19 12:00:00")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-06-19 12:00:00");
    
}

void FillRequestChangeSecretKey(CHANGE_SECRET_KEY_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(CHANGE_SECRET_KEY_REQ_STRUCT));

    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);
    
    pRequest->psp_PosDateTime = malloc(strlen("2017-06-19 12:00:00")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-06-19 12:00:00");
    
}

void FillRequestFraudScreening(FRAUD_SCREENING_REQ_STRUCT *pRequest)
{
  char psp_MerchTxRef[30];
   memset(pRequest, 0, sizeof(FRAUD_SCREENING_REQ_STRUCT));  
   
    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");

    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);

    pRequest->psp_TxSource =  malloc(strlen("WEB")+1);
    strcpy(pRequest->psp_TxSource, "WEB");
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(psp_MerchTxRef,"ANSIC-CLIENT-%4d%02d%02d%02d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);    

    pRequest->psp_MerchTxRef =  malloc(strlen(psp_MerchTxRef)+1);
    strcpy(pRequest->psp_MerchTxRef, psp_MerchTxRef);
    
    pRequest->psp_MerchOrderId =  malloc(strlen("000000223500001076720000100001")+1);
    strcpy(pRequest->psp_MerchOrderId, "000000223500001076720000100001");

    pRequest->psp_Currency =  malloc(strlen(psp_Currency)+1);
    strcpy(pRequest->psp_Currency, psp_Currency);
    
    pRequest->psp_Product =  malloc(strlen("320")+1);
    strcpy(pRequest->psp_Product, "320");

//    char*                                psp_MerchAdditionalRef   ;	
    
    pRequest->psp_Amount =  malloc(strlen(psp_Amount)+1);
    strcpy(pRequest->psp_Amount, psp_Amount);

    pRequest->psp_NumPayments =  malloc(strlen("1")+1);
    strcpy(pRequest->psp_NumPayments, "1");

    //char*                                psp_FirstPaymentDeferral ;	
    //char*                                psp_Recurrent            ;	
    pRequest->psp_Country =  malloc(strlen(psp_Country)+1);
    strcpy(pRequest->psp_Country, psp_Country);

    pRequest->psp_CardNumber =  malloc(strlen(psp_CardNumber)+1);
    strcpy(pRequest->psp_CardNumber, psp_CardNumber);
    
    pRequest->psp_CardExpDate =  malloc(strlen("1812")+1);
    strcpy(pRequest->psp_CardExpDate, "1812");

    pRequest->psp_CardHolderName =  malloc(strlen("Holder Name")+1);
    strcpy(pRequest->psp_CardHolderName, "Holder Name");

    pRequest->psp_PosDateTime =  malloc(strlen("2017-03-23 04:13:37")+1);
    strcpy(pRequest->psp_PosDateTime, "2017-03-23 04:13:37");
    
    pRequest->psp_PurchaseDescription =  malloc(strlen("00000022350000107672")+1);
    strcpy(pRequest->psp_PurchaseDescription, "00000022350000107672");
}


void FillRequesCreateClientSession(CREATE_CLIENT_SESSION_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(CREATE_CLIENT_SESSION_REQ_STRUCT));

    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");
    
    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);

    pRequest->psp_CustomerId = malloc(strlen("6zovJd3916kc4syXxGYtr6iINotYhUFN")+1);
    strcpy(pRequest->psp_CustomerId, "6zovJd3916kc4syXxGYtr6iINotYhUFN");

    pRequest->psp_PosDateTime = malloc(strlen("2017-06-19 12:00:00")+1);
    strcpy(pRequest->psp_PosDateTime, "2018-05-20 12:00:00");

}
void FillGetInstallmentsOptions(GET_INSTALLMENTS_OPTIONS_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(GET_INSTALLMENTS_OPTIONS_REQ_STRUCT));
    pRequest->psp_SecureHash =  malloc(strlen("160162873179c18ade301b86d1ccf7a5")+1);
    strcpy(pRequest->psp_SecureHash, "160162873179c18ade301b86d1ccf7a5");

    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");

    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);

    pRequest->psp_Amount =  malloc(strlen(psp_Amount)+1);
    strcpy(pRequest->psp_Amount, psp_Amount);

    pRequest->psp_Product =  malloc(strlen("320")+1);
    strcpy(pRequest->psp_Product, "320");

    pRequest->psp_Currency =  malloc(strlen(psp_Currency)+1);
    strcpy(pRequest->psp_Currency, psp_Currency);
    
    pRequest->psp_Country =  malloc(strlen(psp_Country)+1);
    strcpy(pRequest->psp_Country, psp_Country);

    pRequest->psp_NumPayments =  malloc(strlen("1")+1);
    strcpy(pRequest->psp_NumPayments, "1");

    pRequest->psp_PaymentMethodToken = malloc(strlen("FG2WE0mVhoOm4U2a1R8qsBe307mtiVy0")+1);
    strcpy(pRequest->psp_PaymentMethodToken, "FG2WE0mVhoOm4U2a1R8qsBe307mtiVy0");

    pRequest->psp_ClientSession = malloc(strlen(psp_ClientSession)+1);
    strcpy(pRequest->psp_ClientSession, psp_ClientSession);
}

void FillNotifyFraudScreeningReview(NOTIFY_FRAUD_SCREENING_REVIEW_REQ_STRUCT *pRequest)
{
    memset(pRequest, 0, sizeof(NOTIFY_FRAUD_SCREENING_REVIEW_REQ_STRUCT));
    
    pRequest->psp_Version = malloc(strlen("2.2")+1);
    strcpy(pRequest->psp_Version, "2.2");

    pRequest->psp_MerchantId =  malloc(strlen(psp_MerchantId)+1);
    strcpy(pRequest->psp_MerchantId, psp_MerchantId);

    /*char*                                psp_Criteria             ;	
    char*                                psp_CriteriaId           ;	
    char*                                psp_ReviewResult         ;	*/
    pRequest->psp_UserId =  malloc(strlen("useridSil")+1);
    strcpy(pRequest->psp_UserId, "useridSil");

    pRequest->psp_PosDateTime = malloc(strlen("2017-06-19 12:00:00")+1);
    strcpy(pRequest->psp_PosDateTime, "2018-05-20 12:00:00");

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
    //sendRequest(npsUrl, PAY_ONLINE_2P_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(PAY_ONLINE_2P_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(PAY_ONLINE_2P_TYPE,(char *)pResponse);
    
  return 0;
}

int SendAuthorize_2p(void) {
  int i;
  ORDER_DETAILS_STRUCT OrderDetails, *pOrderDetails;
  CUSTOMER_ADDITIONAL_DETAILS_STRUCT CustomerAdditionalDetails, *pCustomerAdditionalDetails;
  ADDRESS_STRUCT Address, *pAddress;
  SELLER_DETAILS_STRUCT SellerDetails, *pSellerDetails;
  MERCHANT_ADDITIONAL_DETAILS_STRUCT MerchantAdditionalDetails, *pMerchantAdditionalDetails;
  AMOUNT_ADDITIONAL_DETAILS_REQUEST_STRUCT AmountAdditionalDetailsRequest, *pAmountAdditionalDetailsRequest;
  AUTHORIZE_2P_REQ_STRUCT Request, *pRequest;
  AUTHORIZE_2P_RESP_STRUCT Response, *pResponse;
  
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
    FillRequestAuthorize_2p(pRequest);
    
    pRequest->psp_AmountAdditionalDetails = pAmountAdditionalDetailsRequest;
    pRequest->psp_MerchantAdditionalDetails = pMerchantAdditionalDetails;
    pRequest->psp_CustomerAdditionalDetails = pCustomerAdditionalDetails;
    pRequest->psp_OrderDetails = pOrderDetails;

    pResponse = &Response;
    showRequest(AUTHORIZE_2P_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, AUTHORIZE_2P_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(AUTHORIZE_2P_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(AUTHORIZE_2P_TYPE,(char *)pResponse);
  
  return 0;
}

int SendRefund(void) {
  int i;
  REFUND_REQ_STRUCT Request, *pRequest;
  REFUND_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;

    FillRequestRefund(pRequest);
    
    pResponse = &Response;
    showRequest(REFUND_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, REFUND_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    sendRequest(REFUND_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(REFUND_TYPE,(char *)pResponse);
  
  return 0;
}

int SendCapture(void) {
  int i;
  CAPTURE_REQ_STRUCT Request, *pRequest;
  CAPTURE_RESP_STRUCT Response, *pResponse;
  AMOUNT_ADDITIONAL_DETAILS_REQUEST_STRUCT AmountAdditionalDetailsRequest, *pAmountAdditionalDetailsRequest;

    pAmountAdditionalDetailsRequest = &AmountAdditionalDetailsRequest;    
    pRequest = &Request;
    
    FillAmountAdditionalDetails(pAmountAdditionalDetailsRequest);  
    FillRequestCapture(pRequest);
    pRequest->psp_AmountAdditionalDetails=pAmountAdditionalDetailsRequest;
    
    pResponse = &Response;
    showRequest(CAPTURE_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, CAPTURE_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    sendRequest(CAPTURE_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(CAPTURE_TYPE,(char *)pResponse);
  
  return 0;
}

int SendBankPayment_2p(void) {
  int i;
  PERSON_STRUCT Person, *pPerson;
  ORDER_DETAILS_STRUCT OrderDetails, *pOrderDetails;
  CUSTOMER_ADDITIONAL_DETAILS_STRUCT CustomerAdditionalDetails, *pCustomerAdditionalDetails;
  ADDRESS_STRUCT Address, *pAddress;
  SELLER_DETAILS_STRUCT SellerDetails, *pSellerDetails;
  MERCHANT_ADDITIONAL_DETAILS_STRUCT MerchantAdditionalDetails, *pMerchantAdditionalDetails;
  BILLING_DETAILS_STRUCT BillingDetails, *pBillingDetails;
  AMOUNT_ADDITIONAL_DETAILS_REQUEST_STRUCT AmountAdditionalDetailsRequest, *pAmountAdditionalDetailsRequest;
  BANK_PAYMENT_2P_REQ_STRUCT Request, *pRequest;
  BANK_PAYMENT_2P_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;

    pAmountAdditionalDetailsRequest = &AmountAdditionalDetailsRequest;
    pBillingDetails = &BillingDetails;
    pMerchantAdditionalDetails = &MerchantAdditionalDetails;
    pSellerDetails = &SellerDetails;
    pAddress = &Address;
    pPerson = &Person;
    pCustomerAdditionalDetails = &CustomerAdditionalDetails;
    pOrderDetails = &OrderDetails;
    
    FillOrderDetailsStruct(pOrderDetails);
    
    FillCustomerAdditionalDetailsStruct(pCustomerAdditionalDetails);
        
    FillMerchantAdditionalDetails(pMerchantAdditionalDetails);
    FillSellerDetails(pSellerDetails);
    pMerchantAdditionalDetails->SellerDetails = pSellerDetails;
    
    FillAmountAdditionalDetails(pAmountAdditionalDetailsRequest);
    
    FillBillingDetails(pBillingDetails);
    FillPersonStruct(pPerson);
    FillAddressStruct(pAddress);
    pBillingDetails->Address=pAddress;
    pBillingDetails->Person=pPerson;
    
    FillRequestBankPayment_2p(pRequest);
    
    pRequest->psp_AmountAdditionalDetails = pAmountAdditionalDetailsRequest;
    pRequest->psp_BillingDetails = pBillingDetails;
    pRequest->psp_MerchantAdditionalDetails = pMerchantAdditionalDetails;
    pRequest->psp_CustomerAdditionalDetails = pCustomerAdditionalDetails;
    pRequest->psp_OrderDetails = pOrderDetails;
 
    pResponse = &Response;
    showRequest(BANK_PAYMENT_2P_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, BANK_PAYMENT_2P_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(BANK_PAYMENT_2P_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(BANK_PAYMENT_2P_TYPE,(char *)pResponse);
    
  return 0;
}

int SendSplitPayOnLine_2p(void) {
  int i, count;
  MERCHANT_ADDITIONAL_DETAILS_STRUCT MerchantAdditionalDetails, *pMerchantAdditionalDetails;
  CUSTOMER_ADDITIONAL_DETAILS_STRUCT CustomerAdditionalDetails, *pCustomerAdditionalDetails;
  BILLING_DETAILS_STRUCT BillingDetails, *pBillingDetails;
  ORDER_DETAILS_STRUCT OrderDetails, *pOrderDetails;
  ARRAYOF_REQUERIMIENTOSTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS *pTransactions;
  REQUERIMIENTO_STRUCT_SPLIT_PAYONLINE_2P_TRANSACTIONS *ptr;
  
  SPLIT_PAY_ONLINE_2P_REQ_STRUCT Request, *pRequest;
  SPLIT_PAY_ONLINE_2P_RESP_STRUCT Response, *pResponse;
  
    pMerchantAdditionalDetails = &MerchantAdditionalDetails;
    pCustomerAdditionalDetails = &CustomerAdditionalDetails;
    pBillingDetails = &BillingDetails;
    pOrderDetails = &OrderDetails;
    
    pRequest = &Request;

    FillMerchantAdditionalDetails(pMerchantAdditionalDetails);
    FillCustomerAdditionalDetailsStruct(pCustomerAdditionalDetails);    
    FillBillingDetails(pBillingDetails); 
    FillOrderDetailsStruct(pOrderDetails);
    FillRequestSplitPayOnLine_2p(pRequest);
    
    pRequest->psp_MerchantAdditionalDetails=pMerchantAdditionalDetails;
    pRequest->psp_CustomerAdditionalDetails=pCustomerAdditionalDetails;
    pRequest->psp_BillingDetails=pBillingDetails;
    pRequest->psp_OrderDetails=pOrderDetails;

    pTransactions=(ARRAYOF_REQUERIMIENTOSTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS *) malloc(sizeof(ARRAYOF_REQUERIMIENTOSTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS));
    memset(pTransactions,0,sizeof(ARRAYOF_REQUERIMIENTOSTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS));
    count=2;
    pTransactions->__size=count;
    pTransactions->__ptr=(REQUERIMIENTO_STRUCT_SPLIT_PAYONLINE_2P_TRANSACTIONS *)malloc(sizeof(REQUERIMIENTO_STRUCT_SPLIT_PAYONLINE_2P_TRANSACTIONS*)*count);
  
    for (i = 0; i < pTransactions->__size; ++i){
      ptr=(REQUERIMIENTO_STRUCT_SPLIT_PAYONLINE_2P_TRANSACTIONS *)malloc(sizeof(REQUERIMIENTO_STRUCT_SPLIT_PAYONLINE_2P_TRANSACTIONS));
      memset(ptr, 0, sizeof(REQUERIMIENTO_STRUCT_SPLIT_PAYONLINE_2P_TRANSACTIONS));
      
      ptr->psp_MerchantId = malloc(strlen("psp_test")+1);
      strcpy(ptr->psp_MerchantId,"psp_test");
      
      ptr->psp_MerchTxRef = malloc(strlen("ORDER66666-5")+1);
      sprintf(ptr->psp_MerchTxRef, "ORDER6666%d-5",i+1);
      
      ptr->psp_Product = malloc(strlen("14")+1);
      strcpy(ptr->psp_Product, "14");
      
      ptr->psp_Amount = malloc(strlen("10000")+1);
      strcpy(ptr->psp_Amount,"10000");
      
      ptr->psp_NumPayments = malloc(strlen("1")+1);
      strcpy(ptr->psp_NumPayments,"1");
      
      //ptr->Psp_VaultReference = VaultReference
      
      pTransactions->__ptr[i]=ptr;
    }

    pRequest->psp_Transactions=pTransactions;
    
    pResponse = &Response;
    showRequest(SPLIT_PAY_ONLINE_2P_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, SPLIT_PAY_ONLINE_2P_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(SPLIT_PAY_ONLINE_2P_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(SPLIT_PAY_ONLINE_2P_TYPE,(char *)pResponse);
    
  return 0;
}
int SendSplitAuthorize_2p(void) {
  int i, count;
  MERCHANT_ADDITIONAL_DETAILS_STRUCT MerchantAdditionalDetails, *pMerchantAdditionalDetails;
  CUSTOMER_ADDITIONAL_DETAILS_STRUCT CustomerAdditionalDetails, *pCustomerAdditionalDetails;
  BILLING_DETAILS_STRUCT BillingDetails, *pBillingDetails;
  ORDER_DETAILS_STRUCT OrderDetails, *pOrderDetails;
  ARRAYOF_REQUERIMIENTOSTRUCT_SPLITAUTHORIZE_2P_TRANSACTIONS *pTransactions;
  REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_2P_TRANSACTIONS *ptr;
  
  SPLIT_AUTHORIZE_2P_REQ_STRUCT Request, *pRequest;
  SPLIT_AUTHORIZE_2P_RESP_STRUCT Response, *pResponse;
  
    pMerchantAdditionalDetails = &MerchantAdditionalDetails;
    pCustomerAdditionalDetails = &CustomerAdditionalDetails;
    pBillingDetails = &BillingDetails;
    pOrderDetails = &OrderDetails;
    
    pRequest = &Request;

    FillMerchantAdditionalDetails(pMerchantAdditionalDetails);
    FillCustomerAdditionalDetailsStruct(pCustomerAdditionalDetails);    
    FillBillingDetails(pBillingDetails); 
    FillOrderDetailsStruct(pOrderDetails);
    FillRequestSplitPayOnLine_2p(pRequest);
    
    pRequest->psp_MerchantAdditionalDetails=pMerchantAdditionalDetails;
    pRequest->psp_CustomerAdditionalDetails=pCustomerAdditionalDetails;
    pRequest->psp_BillingDetails=pBillingDetails;
    pRequest->psp_OrderDetails=pOrderDetails;

    pTransactions=(ARRAYOF_REQUERIMIENTOSTRUCT_SPLITAUTHORIZE_2P_TRANSACTIONS *) malloc(sizeof(ARRAYOF_REQUERIMIENTOSTRUCT_SPLITAUTHORIZE_2P_TRANSACTIONS));
    memset(pTransactions,0,sizeof(ARRAYOF_REQUERIMIENTOSTRUCT_SPLITAUTHORIZE_2P_TRANSACTIONS));
    count=2;
    pTransactions->__size=count;
    pTransactions->__ptr=(REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_2P_TRANSACTIONS *)malloc(sizeof(REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_2P_TRANSACTIONS*)*count);
  
    for (i = 0; i < pTransactions->__size; ++i){
      ptr=(REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_2P_TRANSACTIONS *)malloc(sizeof(REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_2P_TRANSACTIONS));
      memset(ptr, 0, sizeof(REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_2P_TRANSACTIONS));
      
      ptr->psp_MerchantId = malloc(strlen("psp_test")+1);
      strcpy(ptr->psp_MerchantId,"psp_test");
      
      ptr->psp_MerchTxRef = malloc(strlen("ORDER66666-5")+1);
      sprintf(ptr->psp_MerchTxRef, "ORDER6666%d-5",i+1);
      
      ptr->psp_Product = malloc(strlen("14")+1);
      strcpy(ptr->psp_Product, "14");
      
      ptr->psp_Amount = malloc(strlen("10000")+1);
      strcpy(ptr->psp_Amount,"10000");
      
      ptr->psp_NumPayments = malloc(strlen("1")+1);
      strcpy(ptr->psp_NumPayments,"1");
      
      //ptr->Psp_VaultReference = VaultReference
      
      pTransactions->__ptr[i]=ptr;
    }

    pRequest->psp_Transactions=pTransactions;
    
    pResponse = &Response;
    showRequest(SPLIT_AUTHORIZE_2P_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, SPLIT_AUTHORIZE_2P_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    sendRequest(SPLIT_AUTHORIZE_2P_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(SPLIT_AUTHORIZE_2P_TYPE,(char *)pResponse);
    
  return 0;
}
int SendPayOnLine_3p(void) {

  int i;
  ORDER_DETAILS_STRUCT OrderDetails, *pOrderDetails;
  CUSTOMER_ADDITIONAL_DETAILS_STRUCT CustomerAdditionalDetails, *pCustomerAdditionalDetails;
  ADDRESS_STRUCT Address, *pAddress;
  SELLER_DETAILS_STRUCT SellerDetails, *pSellerDetails;
  MERCHANT_ADDITIONAL_DETAILS_STRUCT MerchantAdditionalDetails, *pMerchantAdditionalDetails;
  AMOUNT_ADDITIONAL_DETAILS_REQUEST_STRUCT AmountAdditionalDetailsRequest, *pAmountAdditionalDetailsRequest;
  PAY_ONLINE_3P_REQ_STRUCT Request, *pRequest;
  PAY_ONLINE_3P_RESP_STRUCT Response, *pResponse;
  
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
    FillRequestPayOnLine_3p(pRequest);
    
    pRequest->psp_AmountAdditionalDetails = pAmountAdditionalDetailsRequest;
    pRequest->psp_MerchantAdditionalDetails = pMerchantAdditionalDetails;
    pRequest->psp_CustomerAdditionalDetails = pCustomerAdditionalDetails;
    pRequest->psp_OrderDetails = pOrderDetails;
 
    pResponse = &Response;
    showRequest(PAY_ONLINE_3P_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, PAY_ONLINE_3P_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(PAY_ONLINE_3P_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(PAY_ONLINE_3P_TYPE,(char *)pResponse);
    
  return 0;
}

int SendSplitPayOnLine_3p(void) {
  int i, count;
  MERCHANT_ADDITIONAL_DETAILS_STRUCT MerchantAdditionalDetails, *pMerchantAdditionalDetails;
  CUSTOMER_ADDITIONAL_DETAILS_STRUCT CustomerAdditionalDetails, *pCustomerAdditionalDetails;
  BILLING_DETAILS_STRUCT BillingDetails, *pBillingDetails;
  ORDER_DETAILS_STRUCT OrderDetails, *pOrderDetails;
  ARRAYOF_REQUERIMIENTOSTRUCT_SPLITPAYONLINE_3P_TRANSACTIONS *pTransactions;
  REQUERIMIENTO_STRUCT_SPLITPAYONLINE_3P_TRANSACTIONS *ptr;
  
  SPLIT_PAY_ONLINE_3P_REQ_STRUCT Request, *pRequest;
  SPLIT_PAY_ONLINE_3P_RESP_STRUCT Response, *pResponse;
  
    pMerchantAdditionalDetails = &MerchantAdditionalDetails;
    pCustomerAdditionalDetails = &CustomerAdditionalDetails;
    pBillingDetails = &BillingDetails;
    pOrderDetails = &OrderDetails;
    
    pRequest = &Request;

    FillMerchantAdditionalDetails(pMerchantAdditionalDetails);
    FillCustomerAdditionalDetailsStruct(pCustomerAdditionalDetails);    
    FillBillingDetails(pBillingDetails); 
    FillOrderDetailsStruct(pOrderDetails);
    FillRequestSplitPayOnLine_3p(pRequest);
    
    pRequest->psp_MerchantAdditionalDetails=pMerchantAdditionalDetails;
    pRequest->psp_CustomerAdditionalDetails=pCustomerAdditionalDetails;
    pRequest->psp_BillingDetails=pBillingDetails;
    pRequest->psp_OrderDetails=pOrderDetails;

    pTransactions=(ARRAYOF_REQUERIMIENTOSTRUCT_SPLITPAYONLINE_3P_TRANSACTIONS *) malloc(sizeof(ARRAYOF_REQUERIMIENTOSTRUCT_SPLITPAYONLINE_3P_TRANSACTIONS));
    memset(pTransactions,0,sizeof(ARRAYOF_REQUERIMIENTOSTRUCT_SPLITPAYONLINE_3P_TRANSACTIONS));
    count=2;
    pTransactions->__size=count;
    pTransactions->__ptr=(REQUERIMIENTO_STRUCT_SPLITPAYONLINE_3P_TRANSACTIONS *)malloc(sizeof(REQUERIMIENTO_STRUCT_SPLITPAYONLINE_3P_TRANSACTIONS*)*count);
  
    for (i = 0; i < pTransactions->__size; ++i){
      ptr=(REQUERIMIENTO_STRUCT_SPLITPAYONLINE_3P_TRANSACTIONS *)malloc(sizeof(REQUERIMIENTO_STRUCT_SPLITPAYONLINE_3P_TRANSACTIONS));
      memset(ptr, 0, sizeof(REQUERIMIENTO_STRUCT_SPLITPAYONLINE_3P_TRANSACTIONS));
      
      ptr->psp_MerchantId = malloc(strlen("psp_test")+1);
      strcpy(ptr->psp_MerchantId,"psp_test");
      
      ptr->psp_MerchTxRef = malloc(strlen("ORDER66666-5")+1);
      sprintf(ptr->psp_MerchTxRef, "ORDER6666%d-5",i+1);
      
      ptr->psp_Product = malloc(strlen("14")+1);
      strcpy(ptr->psp_Product, "14");
      
      ptr->psp_Amount = malloc(strlen("10000")+1);
      strcpy(ptr->psp_Amount,"10000");
      
      ptr->psp_NumPayments = malloc(strlen("1")+1);
      strcpy(ptr->psp_NumPayments,"1");
      
      //ptr->Psp_VaultReference = VaultReference
      
      pTransactions->__ptr[i]=ptr;
    }

    pRequest->psp_Transactions=pTransactions;
    
    pResponse = &Response;
    showRequest(SPLIT_PAY_ONLINE_3P_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, SPLIT_PAY_ONLINE_3P_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(SPLIT_PAY_ONLINE_3P_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(SPLIT_PAY_ONLINE_3P_TYPE,(char *)pResponse);
    
  return 0;
}

int SendAuthorize_3p(void) {

  int i;
  ORDER_DETAILS_STRUCT OrderDetails, *pOrderDetails;
  CUSTOMER_ADDITIONAL_DETAILS_STRUCT CustomerAdditionalDetails, *pCustomerAdditionalDetails;
  ADDRESS_STRUCT Address, *pAddress;
  SELLER_DETAILS_STRUCT SellerDetails, *pSellerDetails;
  MERCHANT_ADDITIONAL_DETAILS_STRUCT MerchantAdditionalDetails, *pMerchantAdditionalDetails;
  AMOUNT_ADDITIONAL_DETAILS_REQUEST_STRUCT AmountAdditionalDetailsRequest, *pAmountAdditionalDetailsRequest;
  AUTHORIZE_3P_REQ_STRUCT Request, *pRequest;
  AUTHORIZE_3P_RESP_STRUCT Response, *pResponse;
  
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
    FillRequestAuthorize_3p(pRequest);
    
    pRequest->psp_AmountAdditionalDetails = pAmountAdditionalDetailsRequest;
    pRequest->psp_MerchantAdditionalDetails = pMerchantAdditionalDetails;
    pRequest->psp_CustomerAdditionalDetails = pCustomerAdditionalDetails;
    pRequest->psp_OrderDetails = pOrderDetails;
 
    pResponse = &Response;
    showRequest(AUTHORIZE_3P_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, AUTHORIZE_3P_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    sendRequest(AUTHORIZE_3P_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(AUTHORIZE_3P_TYPE,(char *)pResponse);
    
  return 0;
}

int SendSplitAuthorize_3p(void) {
  int i, count;
  MERCHANT_ADDITIONAL_DETAILS_STRUCT MerchantAdditionalDetails, *pMerchantAdditionalDetails;
  CUSTOMER_ADDITIONAL_DETAILS_STRUCT CustomerAdditionalDetails, *pCustomerAdditionalDetails;
  BILLING_DETAILS_STRUCT BillingDetails, *pBillingDetails;
  ORDER_DETAILS_STRUCT OrderDetails, *pOrderDetails;
  ARRAYOF_REQUERIMIENTOSTRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS *pTransactions;
  REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS *ptr;
  
  SPLIT_AUTHORIZE_3P_REQ_STRUCT Request, *pRequest;
  SPLIT_AUTHORIZE_3P_RESP_STRUCT Response, *pResponse;
  
    pMerchantAdditionalDetails = &MerchantAdditionalDetails;
    pCustomerAdditionalDetails = &CustomerAdditionalDetails;
    pBillingDetails = &BillingDetails;
    pOrderDetails = &OrderDetails;
    
    pRequest = &Request;

    FillMerchantAdditionalDetails(pMerchantAdditionalDetails);
    FillCustomerAdditionalDetailsStruct(pCustomerAdditionalDetails);    
    FillBillingDetails(pBillingDetails); 
    FillOrderDetailsStruct(pOrderDetails);
    FillRequestSplitPayOnLine_3p(pRequest);
    
    pRequest->psp_MerchantAdditionalDetails=pMerchantAdditionalDetails;
    pRequest->psp_CustomerAdditionalDetails=pCustomerAdditionalDetails;
    pRequest->psp_BillingDetails=pBillingDetails;
    pRequest->psp_OrderDetails=pOrderDetails;

    pTransactions=(ARRAYOF_REQUERIMIENTOSTRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS *) malloc(sizeof(ARRAYOF_REQUERIMIENTOSTRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS));
    memset(pTransactions,0,sizeof(ARRAYOF_REQUERIMIENTOSTRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS));
    count=2;
    pTransactions->__size=count;
    pTransactions->__ptr=(REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS *)malloc(sizeof(REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS*)*count);
  
    for (i = 0; i < pTransactions->__size; ++i){
      ptr=(REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS *)malloc(sizeof(REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS));
      memset(ptr, 0, sizeof(REQUERIMIENTO_STRUCT_SPLITAUTHORIZE_3P_TRANSACTIONS));
      
      ptr->psp_MerchantId = malloc(strlen("psp_test")+1);
      strcpy(ptr->psp_MerchantId,"psp_test");
      
      ptr->psp_MerchTxRef = malloc(strlen("ORDER66666-5")+1);
      sprintf(ptr->psp_MerchTxRef, "ORDER6666%d-5",i+1);
      
      ptr->psp_Product = malloc(strlen("14")+1);
      strcpy(ptr->psp_Product, "14");
      
      ptr->psp_Amount = malloc(strlen("10000")+1);
      strcpy(ptr->psp_Amount,"10000");
      
      ptr->psp_NumPayments = malloc(strlen("1")+1);
      strcpy(ptr->psp_NumPayments,"1");
      
      //ptr->Psp_VaultReference = VaultReference
      
      pTransactions->__ptr[i]=ptr;
    }

    pRequest->psp_Transactions=pTransactions;
    
    pResponse = &Response;
    showRequest(SPLIT_AUTHORIZE_3P_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, SPLIT_AUTHORIZE_3P_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(SPLIT_AUTHORIZE_3P_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(SPLIT_AUTHORIZE_3P_TYPE,(char *)pResponse);
    
  return 0;
}

int SendBankPayment_3p(void) {
  int i;
  PERSON_STRUCT Person, *pPerson;
  ORDER_DETAILS_STRUCT OrderDetails, *pOrderDetails;
  CUSTOMER_ADDITIONAL_DETAILS_STRUCT CustomerAdditionalDetails, *pCustomerAdditionalDetails;
  ADDRESS_STRUCT Address, *pAddress;
  SELLER_DETAILS_STRUCT SellerDetails, *pSellerDetails;
  MERCHANT_ADDITIONAL_DETAILS_STRUCT MerchantAdditionalDetails, *pMerchantAdditionalDetails;
  BILLING_DETAILS_STRUCT BillingDetails, *pBillingDetails;
  AMOUNT_ADDITIONAL_DETAILS_REQUEST_STRUCT AmountAdditionalDetailsRequest, *pAmountAdditionalDetailsRequest;
  BANK_PAYMENT_3P_REQ_STRUCT Request, *pRequest;
  BANK_PAYMENT_3P_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;

    pAmountAdditionalDetailsRequest = &AmountAdditionalDetailsRequest;
    pBillingDetails = &BillingDetails;
    pMerchantAdditionalDetails = &MerchantAdditionalDetails;
    pSellerDetails = &SellerDetails;
    pAddress = &Address;
    pPerson = &Person;
    pCustomerAdditionalDetails = &CustomerAdditionalDetails;
    pOrderDetails = &OrderDetails;
    
    FillOrderDetailsStruct(pOrderDetails);
    
    FillCustomerAdditionalDetailsStruct(pCustomerAdditionalDetails);
        
    FillMerchantAdditionalDetails(pMerchantAdditionalDetails);
    FillSellerDetails(pSellerDetails);
    pMerchantAdditionalDetails->SellerDetails = pSellerDetails;
    
    FillAmountAdditionalDetails(pAmountAdditionalDetailsRequest);
    
    FillBillingDetails(pBillingDetails);
    FillPersonStruct(pPerson);
    FillAddressStruct(pAddress);
    pBillingDetails->Address=pAddress;
    pBillingDetails->Person=pPerson;
    
    FillRequestBankPayment_3p(pRequest);
    
    pRequest->psp_AmountAdditionalDetails = pAmountAdditionalDetailsRequest;
    pRequest->psp_BillingDetails = pBillingDetails;
    pRequest->psp_MerchantAdditionalDetails = pMerchantAdditionalDetails;
    pRequest->psp_CustomerAdditionalDetails = pCustomerAdditionalDetails;
    pRequest->psp_OrderDetails = pOrderDetails;
 
    pResponse = &Response;
    showRequest(BANK_PAYMENT_3P_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, BANK_PAYMENT_3P_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(BANK_PAYMENT_3P_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(BANK_PAYMENT_3P_TYPE,(char *)pResponse);
    
  return 0;
}

int SendCashPayment_3p(void) {
  int i;
  PERSON_STRUCT Person, *pPerson;
  ORDER_DETAILS_STRUCT OrderDetails, *pOrderDetails;
  CUSTOMER_ADDITIONAL_DETAILS_STRUCT CustomerAdditionalDetails, *pCustomerAdditionalDetails;
  ADDRESS_STRUCT Address, *pAddress;
  SELLER_DETAILS_STRUCT SellerDetails, *pSellerDetails;
  MERCHANT_ADDITIONAL_DETAILS_STRUCT MerchantAdditionalDetails, *pMerchantAdditionalDetails;
  BILLING_DETAILS_STRUCT BillingDetails, *pBillingDetails;
  AMOUNT_ADDITIONAL_DETAILS_REQUEST_STRUCT AmountAdditionalDetailsRequest, *pAmountAdditionalDetailsRequest;
  CASH_PAYMENT_3P_REQ_STRUCT Request, *pRequest;
  CASH_PAYMENT_3P_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;

    pAmountAdditionalDetailsRequest = &AmountAdditionalDetailsRequest;
    pBillingDetails = &BillingDetails;
    pMerchantAdditionalDetails = &MerchantAdditionalDetails;
    pSellerDetails = &SellerDetails;
    pAddress = &Address;
    pPerson = &Person;
    pCustomerAdditionalDetails = &CustomerAdditionalDetails;
    pOrderDetails = &OrderDetails;
    
    FillOrderDetailsStruct(pOrderDetails);
    
    FillCustomerAdditionalDetailsStruct(pCustomerAdditionalDetails);
        
    FillMerchantAdditionalDetails(pMerchantAdditionalDetails);
    FillSellerDetails(pSellerDetails);
    pMerchantAdditionalDetails->SellerDetails = pSellerDetails;
    
    FillAmountAdditionalDetails(pAmountAdditionalDetailsRequest);
    
    FillBillingDetails(pBillingDetails);
    FillPersonStruct(pPerson);
    FillAddressStruct(pAddress);
    pBillingDetails->Address=pAddress;
    pBillingDetails->Person=pPerson;
    
    FillRequestCashPayment_3p(pRequest);
    
    pRequest->psp_AmountAdditionalDetails = pAmountAdditionalDetailsRequest;
    pRequest->psp_BillingDetails = pBillingDetails;
    pRequest->psp_MerchantAdditionalDetails = pMerchantAdditionalDetails;
    pRequest->psp_CustomerAdditionalDetails = pCustomerAdditionalDetails;
    pRequest->psp_OrderDetails = pOrderDetails;
 
    pResponse = &Response;
    showRequest(CASH_PAYMENT_3P_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, CASH_PAYMENT_3P_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(CASH_PAYMENT_3P_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(CASH_PAYMENT_3P_TYPE,(char *)pResponse);
    
  return 0;
}

int SendCreatePaymentMethod(void) {
  int i;
  PAYMENT_METHOD_INPUT_DETAILS_STRUCT PaymentMethod, *pPaymentMethod;
  CREATE_PAYMENT_METHOD_REQ_STRUCT Request, *pRequest;
  CREATE_PAYMENT_METHOD_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;

    pPaymentMethod = &PaymentMethod;
    
    FillPaymentMethodInputDetailsStruct(pPaymentMethod);
    FillRequestCreatePaymentMethod(pRequest);
    
    pRequest->psp_PaymentMethod = pPaymentMethod;
 
    pResponse = &Response;
    showRequest(CREATE_PAYMENT_METHOD_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, CREATE_PAYMENT_METHOD_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(CREATE_PAYMENT_METHOD_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(CREATE_PAYMENT_METHOD_TYPE,(char *)pResponse);
    
  return 0;
}

int SendCreatePaymentMethodToken(void) {
  int i;
  CARD_INPUT_DETAILS_STRUCT CardInputDetails, *pCardInputDetails;
  PERSON_STRUCT Person, *pPerson;
  ADDRESS_STRUCT Address, *pAddress;
  CREATE_PAYMENT_METHOD_TOKEN_REQ_STRUCT Request, *pRequest;
  CREATE_PAYMENT_METHOD_TOKEN_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;
    pCardInputDetails=&CardInputDetails;
    pPerson=&Person;
    pAddress=&Address;


    FillCardInputDetailsStruct(pCardInputDetails);
    FillPersonStruct(pPerson);
    FillAddressStruct(pAddress);
    FillRequestCreatePaymentMethodToken(pRequest);
    
    pRequest->psp_CardInputDetails=pCardInputDetails;
    pRequest->psp_Person=pPerson;
    pRequest->psp_Address = pAddress;
 
    pResponse = &Response;
    showRequest(CREATE_PAYMENT_METHOD_TOKEN_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, CREATE_PAYMENT_METHOD_TOKEN_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    sendRequest(CREATE_PAYMENT_METHOD_TOKEN_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(CREATE_PAYMENT_METHOD_TOKEN_TYPE,(char *)pResponse);
    
  return 0;
}

int SendRetrievePaymentMethodToken(void) {
  int i;
  RETRIEVE_PAYMENT_METHOD_TOKEN_REQ_STRUCT Request, *pRequest;
  RETRIEVE_PAYMENT_METHOD_TOKEN_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;
    FillRequestRetrievePaymentMethodToken(pRequest);
    
    pResponse = &Response;
    showRequest(RETRIEVE_PAYMENT_METHOD_TOKEN_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, RETRIEVE_PAYMENT_METHOD_TOKEN_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    sendRequest(RETRIEVE_PAYMENT_METHOD_TOKEN_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(RETRIEVE_PAYMENT_METHOD_TOKEN_TYPE,(char *)pResponse);
    
  return 0;
}

int SendCreatePaymentMethodFromPayment(void) {
  int i;
  CREATE_PAYMENT_METHOD_FROM_PAYMENT_REQ_STRUCT Request, *pRequest;
  CREATE_PAYMENT_METHOD_FROM_PAYMENT_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;
    FillRequestCreatePaymentMethodFromPayment(pRequest);
    
    pResponse = &Response;
    showRequest(CREATE_PAYMENT_METHOD_FROM_PAYMENT_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, CREATE_PAYMENT_METHOD_FROM_PAYMENT_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(CREATE_PAYMENT_METHOD_FROM_PAYMENT_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(CREATE_PAYMENT_METHOD_FROM_PAYMENT_TYPE,(char *)pResponse);
    
  return 0;
}

int SendRetrievePaymentMethod(void) {
  int i;
  RETRIEVE_PAYMENT_METHOD_REQ_STRUCT Request, *pRequest;
  RETRIEVE_PAYMENT_METHOD_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;
    FillRequestRetrievePaymentMethod(pRequest);
    
    pResponse = &Response;
    showRequest(RETRIEVE_PAYMENT_METHOD_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, RETRIEVE_PAYMENT_METHOD_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(RETRIEVE_PAYMENT_METHOD_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(RETRIEVE_PAYMENT_METHOD_TYPE,(char *)pResponse);
    
  return 0;
}

int SendUpdatePaymentMethod(void) {
  int i;
  CARD_INPUT_DETAILS_STRUCT CardInputDetails, *pCardInputDetails;
  PERSON_STRUCT Person, *pPerson;
  ADDRESS_STRUCT Address, *pAddress;
  UPDATE_PAYMENT_METHOD_REQ_STRUCT Request, *pRequest;
  UPDATE_PAYMENT_METHOD_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;
    pCardInputDetails=&CardInputDetails;
    pPerson=&Person;
    pAddress=&Address;


    FillCardInputDetailsStruct(pCardInputDetails);
    FillPersonStruct(pPerson);
    FillAddressStruct(pAddress);
    FillRequestUpdatePaymentMethod(pRequest);
    
    pRequest->psp_CardInputDetails=pCardInputDetails;
    pRequest->psp_Person=pPerson;
    pRequest->psp_Address = pAddress;
 
    pResponse = &Response;
    showRequest(UPDATE_PAYMENT_METHOD_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, UPDATE_PAYMENT_METHOD_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(UPDATE_PAYMENT_METHOD_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(UPDATE_PAYMENT_METHOD_TYPE,(char *)pResponse);
    
  return 0;
}

int SendDeletePaymentMethod(void) {
  int i;
  DELETE_PAYMENT_METHOD_REQ_STRUCT Request, *pRequest;
  DELETE_PAYMENT_METHOD_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;
    FillRequestDeletePaymentMethod(pRequest);
    
    pResponse = &Response;
    showRequest(DELETE_PAYMENT_METHOD_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, DELETE_PAYMENT_METHOD_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(DELETE_PAYMENT_METHOD_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(DELETE_PAYMENT_METHOD_TYPE,(char *)pResponse);
    
  return 0;
}

int SendRecachePaymentMethodToken(void) {
  int i;
  PERSON_STRUCT Person, *pPerson;
  ADDRESS_STRUCT Address, *pAddress;
  RECACHE_PAYMENT_METHOD_TOKEN_REQ_STRUCT Request, *pRequest;
  RECACHE_PAYMENT_METHOD_TOKEN_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;
    pPerson=&Person;
    pAddress=&Address;

    FillPersonStruct(pPerson);
    FillAddressStruct(pAddress);
    FillRequestRecachePaymentMethodToken(pRequest);
    
    pRequest->psp_Person=pPerson;
    pRequest->psp_Address = pAddress;
 
    pResponse = &Response;
    showRequest(RECACHE_PAYMENT_METHOD_TOKEN_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, RECACHE_PAYMENT_METHOD_TOKEN_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(RECACHE_PAYMENT_METHOD_TOKEN_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(RECACHE_PAYMENT_METHOD_TOKEN_TYPE,(char *)pResponse);
    
  return 0;
}

int SendCreateCustomer(void) {
  int i;
  PERSON_STRUCT Person, *pPerson;
  ADDRESS_STRUCT Address, *pAddress;
  PAYMENT_METHOD_INPUT_DETAILS_STRUCT PaymentMethod, *pPaymentMethod;
  CREATE_CUSTOMER_REQ_STRUCT Request, *pRequest;
  CREATE_CUSTOMER_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;
    pPerson=&Person;
    pAddress=&Address;
    pPaymentMethod=&PaymentMethod;

    FillPersonStruct(pPerson);
    FillAddressStruct(pAddress);
    FillPaymentMethodInputDetailsStruct(pPaymentMethod);
    
    FillRequestCreateCustomer(pRequest);
    
    pRequest->psp_Person=pPerson;
    pRequest->psp_Address = pAddress;
    pRequest->psp_PaymentMethod=pPaymentMethod;
 
    pResponse = &Response;
    showRequest(CREATE_CUSTOMER_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, CREATE_CUSTOMER_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(CREATE_CUSTOMER_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(CREATE_CUSTOMER_TYPE,(char *)pResponse);
    
  return 0;
}

int SendRetrieveCustomer(void) {
  int i;
  RETRIEVE_CUSTOMER_REQ_STRUCT Request, *pRequest;
  RETRIEVE_CUSTOMER_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;
    
    FillRequestRetrieveCustomer(pRequest);
    
    pResponse = &Response;
    showRequest(RETRIEVE_CUSTOMER_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, RETRIEVE_CUSTOMER_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(RETRIEVE_CUSTOMER_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(RETRIEVE_CUSTOMER_TYPE,(char *)pResponse);
    
  return 0;
}

int SendUpdateCustomer(void) {
  int i;
  PERSON_STRUCT Person, *pPerson;
  ADDRESS_STRUCT Address, *pAddress;
  PAYMENT_METHOD_INPUT_DETAILS_STRUCT PaymentMethod, *pPaymentMethod;
  UPDATE_CUSTOMER_REQ_STRUCT Request, *pRequest;
  UPDATE_CUSTOMER_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;
    pPerson=&Person;
    pAddress=&Address;
    pPaymentMethod=&PaymentMethod;

    FillPersonStruct(pPerson);
    FillAddressStruct(pAddress);
    FillPaymentMethodInputDetailsStruct(pPaymentMethod);
    
    FillRequestUpdateCustomer(pRequest);
    
    pRequest->psp_Person=pPerson;
    pRequest->psp_Address = pAddress;
    pRequest->psp_PaymentMethod=pPaymentMethod;
 
    pResponse = &Response;
    showRequest(UPDATE_CUSTOMER_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, UPDATE_CUSTOMER_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(UPDATE_CUSTOMER_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(UPDATE_CUSTOMER_TYPE,(char *)pResponse);
    
  return 0;
}

int SendDeleteCustomer(void) {
  int i;
  DELETE_CUSTOMER_REQ_STRUCT Request, *pRequest;
  DELETE_CUSTOMER_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;
    
    FillRequestDeleteCustomer(pRequest);
    
    pResponse = &Response;
    showRequest(DELETE_CUSTOMER_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, DELETE_CUSTOMER_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(DELETE_CUSTOMER_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(DELETE_CUSTOMER_TYPE,(char *)pResponse);
    
  return 0;
}

int SendSimpleQueryTx(void) {
  int i;
  SIMPLE_QUERY_TX_REQ_STRUCT Request, *pRequest;
  SIMPLE_QUERY_TX_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;
    FillRequestSimpleQueryTx(pRequest);
    
    pResponse = &Response;
    showRequest(SIMPLE_QUERY_TX_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, SIMPLE_QUERY_TX_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(SIMPLE_QUERY_TX_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(SIMPLE_QUERY_TX_TYPE,(char *)pResponse);
    
  return 0;
}

int SendQueryCardNumber(void) {
  int i;
  QUERY_CARD_NUMBER_REQ_STRUCT Request, *pRequest;
  QUERY_CARD_NUMBER_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;
    FillRequestQueryCardNumber(pRequest);
    
    pResponse = &Response;
    showRequest(QUERY_CARD_NUMBER_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, QUERY_CARD_NUMBER_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(QUERY_CARD_NUMBER_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(QUERY_CARD_NUMBER_TYPE,(char *)pResponse);
    
  return 0;
}

int SendQueryCardDetails(void) {
  int i;
  QUERY_CARD_DETAILS_REQ_STRUCT Request, *pRequest;
  QUERY_CARD_DETAILS_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;
    FillRequestQueryCardDetails(pRequest);
    
    pResponse = &Response;
    showRequest(QUERY_CARD_DETAILS_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, QUERY_CARD_DETAILS_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(QUERY_CARD_DETAILS_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(QUERY_CARD_DETAILS_TYPE,(char *)pResponse);
    
  return 0;
}

int SendQueryTxs(void) {
  int i;
  QUERY_TXS_REQ_STRUCT Request, *pRequest;
  QUERY_TXS_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;
    FillRequestQueryTxs(pRequest);
    
    pResponse = &Response;
    showRequest(QUERY_TXS_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, QUERY_TXS_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(QUERY_TXS_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(QUERY_TXS_TYPE,(char *)pResponse);
    
  return 0;
}

int SendGetIINDetails(void) {
  int i;
  GET_IIN_DETAILS_REQ_STRUCT Request, *pRequest;
  GET_IIN_DETAILS_RESP_STRUCT Response, *pResponse;
  
    pRequest = &Request;
    FillRequestGetIINDetails(pRequest);
    
    pResponse = &Response;
    showRequest(GET_IIN_DETAILS_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, GET_IIN_DETAILS_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(GET_IIN_DETAILS_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(GET_IIN_DETAILS_TYPE,(char *)pResponse);
    
  return 0;
}

int SendChangeSecretKey(void) {
  int i;
  CHANGE_SECRET_KEY_REQ_STRUCT Request, *pRequest;
  CHANGE_SECRET_KEY_RESP_STRUCT Response, *pResponse;
 
    pRequest = &Request;
    FillRequestChangeSecretKey(pRequest);
    
    pResponse = &Response;
    showRequest(CHANGE_SECRET_KEY_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, CHANGE_SECRET_KEY_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(CHANGE_SECRET_KEY_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(CHANGE_SECRET_KEY_TYPE,(char *)pResponse);
    
  return 0;
}

int SendFraudScreening(void) {
  int i;
  FRAUD_SCREENING_REQ_STRUCT Request, *pRequest;
  FRAUD_SCREENING_RESP_STRUCT Response, *pResponse;
  MERCHANT_ADDITIONAL_DETAILS_STRUCT MerchantAdditionalDetails, *pMerchantAdditionalDetails;
  CUSTOMER_ADDITIONAL_DETAILS_STRUCT CustomerAdditionalDetails, *pCustomerAdditionalDetails;
  SELLER_DETAILS_STRUCT SellerDetails, *pSellerDetails;
  ADDRESS_STRUCT Address, *pAddress;
  ORDER_DETAILS_STRUCT OrderDetails, *pOrderDetails;
  
   printf("\n******************SendFraudScreening************************************\n");
    pRequest=&Request;

    pSellerDetails=&SellerDetails;
    pMerchantAdditionalDetails=&MerchantAdditionalDetails;
    pCustomerAdditionalDetails=&CustomerAdditionalDetails;
    pOrderDetails=&OrderDetails;
    pAddress=&Address;

    FillOrderDetailsStruct(pOrderDetails);
    FillCustomerAdditionalDetailsStruct(pCustomerAdditionalDetails);
    FillAddressStruct(pAddress);
    FillSellerDetails(pSellerDetails);
    pSellerDetails->Address = pAddress;
    FillMerchantAdditionalDetails(pMerchantAdditionalDetails);
    pMerchantAdditionalDetails->SellerDetails = pSellerDetails;

    FillRequestFraudScreening(pRequest);
    pRequest->psp_MerchantAdditionalDetails = pMerchantAdditionalDetails;
    pRequest->psp_CustomerAdditionalDetails = pCustomerAdditionalDetails;
    pRequest->psp_OrderDetails = pOrderDetails;
   
    pResponse = &Response;
    showRequest(FRAUD_SCREENING_TYPE,(char *)pRequest);
    sendRequest(FRAUD_SCREENING_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(FRAUD_SCREENING_TYPE,(char *)pResponse);
  return 0;
}


int SendCreateClientSession(void) {
  int i;
  CREATE_CLIENT_SESSION_REQ_STRUCT Request, *pRequest;
  CREATE_CLIENT_SESSION_RESP_STRUCT Response, *pResponse;
   
   printf("\n******************SendCreateClientSession************************************\n");

    pRequest = &Request;
    FillRequesCreateClientSession(pRequest);
   
    pResponse = &Response;
    showRequest(CREATE_CLIENT_SESSION_TYPE,(char *)pRequest);
    sendRequest(CREATE_CLIENT_SESSION_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(CREATE_CLIENT_SESSION_TYPE,(char *)pResponse);
    
  return 0;
}

int SendGetInstallmentsOptions(void) {
  int i;
  GET_INSTALLMENTS_OPTIONS_REQ_STRUCT Request, *pRequest;
  GET_INSTALLMENTS_OPTIONS_RESP_STRUCT Response, *pResponse;
  
    printf("\n******************SendGetInstallmentsOptions************************************\n");  
    pRequest = &Request;
    FillGetInstallmentsOptions(pRequest);
    
    pResponse = &Response;
    showRequest(GET_INSTALLMENTS_OPTIONS_TYPE,(char *)pRequest);
    //sendRequest(npsUrl, QUERY_TXS_TYPE, apiKey, (char *)pRequest, pResponse) ;
    sendRequest(GET_INSTALLMENTS_OPTIONS_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(GET_INSTALLMENTS_OPTIONS_TYPE,(char *)pResponse);
    
  return 0;
}

int SendNotifyFraudScreeningReview(void) {
  int i;
  NOTIFY_FRAUD_SCREENING_REVIEW_REQ_STRUCT Request, *pRequest;
  NOTIFY_FRAUD_SCREENING_REVIEW_RESP_STRUCT Response, *pResponse;
  
    printf("\n******************SendNotifyFraudScreeningReview************************************\n");  
    pRequest = &Request;
    FillNotifyFraudScreeningReview(pRequest);
    
    pResponse = &Response;
    showRequest(NOTIFY_FRAUD_SCREENING_REVIEW_TYPE,(char *)pRequest);
    sendRequest(NOTIFY_FRAUD_SCREENING_REVIEW_TYPE, apiKey, (char *)pRequest, pResponse) ;    
    printf("\n******************************************************\n");
    showResponse(NOTIFY_FRAUD_SCREENING_REVIEW_TYPE,(char *)pResponse);
    
  return 0;
}

int main( int argc, char **argv)
{
 
  int logLevel=0;
  int env=SANBOX_ENV;
  int type = 0;
  int i,index;
  int c;

  FILE * auxFd = fopen ( "log_de_mi_app.log", "a" ) ;
  fprintf( auxFd, "**********************Comienza prueba\n");
  logLevel=getLogLevel();

  if (setLog( INFO, NULL, NULL)<0) {
    printf ("-1\n");
    return;
  }
  
  if (setEnvironment(env)<0)
    return;  

  
  printf ("argc [%d]\n", argc);
  while ((c = getopt (argc, argv, "a:t:u:m:c:p:i:e:s:")) != -1)
    switch (c)  {
      case 'a':
        psp_Amount = optarg;
        break;
      case 'e':
	env = getEnvironment();
        env = atoi(optarg);
	if (setEnvironment(env)<0)
	  return;
	//fprintf( auxFd, "********************** env [%d]\n", env);
	env = getEnvironment();
        break;
      case 't':
        type = atoi(optarg);
        break;
      case 'u':
        npsUrl = optarg;
        break;
      case 'm':
        psp_MerchantId = optarg;
        break;
      case 'i':
        psp_TransactionId_Orig = optarg;
        break;
      case 'c':
        psp_CardNumber = optarg;
        break;
      case 'p':
        psp_Product = optarg;
        break;
      case 's':
        psp_ClientSession = optarg;
        break;
      case '?':
        if (optopt == 't') {
	  printf ("Option -%c requires an integer (1..35).\n", optopt);
         for (index = PAY_ONLINE_2P_TYPE; index < TOTAL_METHODS; index++)
           printf ("\t[%02d] = %s\n", index, GET_SOAP_ACTION(index));
	}
        else if (optopt == 'a') {
	  printf ("Option -%c requires an amount argument example: 1000 ($10.00)\n", optopt);
	}
        else if (optopt == 'u') {
	  printf ("Option -%c requires an url argument example: 'https://psp.localhost:443/ws.php'\n", optopt);
	}
        else if (optopt == 'm') {
	  printf ("Option -%c requires a merchant argument example: 'psp_test'\n", optopt);
	}
        else if (optopt == 'i') {
	  printf ("Option -%c requires a TransactionId_orig argument example: '158611'\n", optopt);
	}
        else if (optopt == 'p') {
	  printf ("Option -%c requires a product argument example: 14\n", optopt);
	}
        else if (optopt == 'c') {
	  printf ("Option -%c requires a cardNumber argument example: '4507990000000010'\n", optopt);
	}
        else if (optopt == 's') {
	  printf ("Option -%c requires a clientSession: example 'iYgdiXyl56vszeEpCRGmS1JiNYg1xSnYXzQuiFWP4Q2nTwbPiWwZruUzXmqrXYR9'\n", optopt);
	}
        else if (isprint (optopt))
          printf ("Unknown option `-%c'.\n", optopt);
        else
          printf ("Unknown option character `\\x%x'.\n", optopt);
        return 1;
      default:
        abort ();
      }

  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);
  
  printf ("\turl = %s\n", npsUrl);
  printf ("\ttype=[%02d](%s)\n", type, GET_SOAP_ACTION(type));
  printf ("\tmerchant= %s\n",psp_MerchantId);
  printf ("\tcardNumber= %s\n", psp_CardNumber);
  printf ("\tcurrency = %s\n", psp_Currency);
  printf ("\tProduct = %s\n", psp_Product);
  printf ("\tAmount = %s\n", psp_Amount);
  printf ("\tCountry = %s\n",psp_Country);
  printf ("\tTransactionId_orig = %s\n",psp_TransactionId_Orig);

  switch (type) {
    case PAY_ONLINE_2P_TYPE: SendPayOnLine_2p(); break;
    case AUTHORIZE_2P_TYPE : SendAuthorize_2p(); break;
    case REFUND_TYPE: SendRefund(); break;
    case CAPTURE_TYPE: SendCapture(); break;
    case BANK_PAYMENT_2P_TYPE: SendBankPayment_2p(); break;
    case SPLIT_PAY_ONLINE_2P_TYPE: SendSplitPayOnLine_2p(); break;
    case SPLIT_AUTHORIZE_2P_TYPE: SendSplitAuthorize_2p(); break;    
    case PAY_ONLINE_3P_TYPE: SendPayOnLine_3p(); break;
    case SPLIT_PAY_ONLINE_3P_TYPE: SendSplitPayOnLine_3p(); break;
    case AUTHORIZE_3P_TYPE: SendAuthorize_3p(); break;
    case SPLIT_AUTHORIZE_3P_TYPE: SendSplitAuthorize_3p(); break;
    case BANK_PAYMENT_3P_TYPE: SendBankPayment_3p(); break;
    case CASH_PAYMENT_3P_TYPE: SendCashPayment_3p(); break;
    case CREATE_PAYMENT_METHOD_TYPE: SendCreatePaymentMethod(); break;
    case CREATE_PAYMENT_METHOD_TOKEN_TYPE: SendCreatePaymentMethodToken(); break;   
    case RETRIEVE_PAYMENT_METHOD_TOKEN_TYPE:  SendRetrievePaymentMethodToken(); break;   
    case CREATE_PAYMENT_METHOD_FROM_PAYMENT_TYPE:  SendCreatePaymentMethodFromPayment(); break;
    case RETRIEVE_PAYMENT_METHOD_TYPE: SendRetrievePaymentMethod(); break;      
    case UPDATE_PAYMENT_METHOD_TYPE: SendUpdatePaymentMethod(); break;      
    case DELETE_PAYMENT_METHOD_TYPE: SendDeletePaymentMethod(); break;      
    case RECACHE_PAYMENT_METHOD_TOKEN_TYPE: SendRecachePaymentMethodToken(); break;
    case CREATE_CUSTOMER_TYPE: SendCreateCustomer(); break;
    case RETRIEVE_CUSTOMER_TYPE: SendRetrieveCustomer(); break;
    case UPDATE_CUSTOMER_TYPE: SendUpdateCustomer(); break;
    case DELETE_CUSTOMER_TYPE: SendDeleteCustomer(); break;
    case SIMPLE_QUERY_TX_TYPE: SendSimpleQueryTx(); break;   
    case QUERY_CARD_NUMBER_TYPE: SendQueryCardNumber(); break;   
    case QUERY_CARD_DETAILS_TYPE: SendQueryCardDetails(); break;   
    case QUERY_TXS_TYPE: SendQueryTxs(); break;   
    case GET_IIN_DETAILS_TYPE: SendGetIINDetails(); break;
    case CHANGE_SECRET_KEY_TYPE: SendChangeSecretKey(); break;
    case FRAUD_SCREENING_TYPE: SendFraudScreening(); break;
    case CREATE_CLIENT_SESSION_TYPE: SendCreateClientSession(); break;
    case GET_INSTALLMENTS_OPTIONS_TYPE: SendGetInstallmentsOptions(); break;
    case NOTIFY_FRAUD_SCREENING_REVIEW_TYPE: SendNotifyFraudScreeningReview(); break;
    default: printf("Invalid type[%d]\n", type); break;

  }
  //fprintf( auxFd, "********************** listo \n");
  //LogClose();

}
/*
int main( int argc, char **argv)
{
 
  int env=SANBOX_ENV; /*PROD_ENV | SANBOX_ENV | STAGING_ENV*//*

  FILE * auxFd = fopen ( "test.log", "a" ) ;

  if (setLog( DEBUG, NULL, auxFd)<0)
    return;

  if (setEnvironment(env)<0)
    return;

  SendPayOnLine_2p();

  LogClose();

}*/