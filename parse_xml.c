#include "parse_xml.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nps_utils.h"
//#include <libxml/parser.h>

/**************************************************************
 * Return idx of field *key inside struct pResponse
 * ************************************************************/
int GetRespFieldIdxByDesc(char *key, int type, char* pResponse) {
  char **ptr=NULL;
  int i, max_fields;
  char **structFieldsDesc;
  size_t *structFieldsOffset;
  int envField = getEnvironment();
  
  if (type > 0) {
    structFieldsDesc=methodsRespFields[type-1].structFieldsDesc;
    structFieldsOffset=methodsRespFields[type-1].structFieldsOffset;
    max_fields=methodsRespFields[type-1].max_fields;
  }
  else {
    structFieldsDesc=((struct nps_generics *)pResponse)->structFieldsDesc;
    structFieldsOffset=((struct nps_generics *)pResponse)->structFieldsOffset;
    max_fields=((struct nps_generics *)pResponse)->max_fields;
  }
  
  Log(DEBUG,"\tGetRespFieldIdxByDesc max_fields [%d]",max_fields);
  
  for (i = 0; i < max_fields; i++)  {
    
    ptr=(char*) pResponse + structFieldsOffset[(i*ARR_OFFSET_COUNT)];
    
    if ( strcmp(*structFieldsDesc, key)==0) {
      if ((int)structFieldsOffset[(i*ARR_OFFSET_COUNT)+envField]<0) {
        Log(ERROR,"\tstructFieldsDesc[%s] not exist in [%s]",*structFieldsDesc, npsEnvDesc[envField]);
        return -1;
      }    

      Log(DEBUG, "\tGetRespFieldIdxByDesc [%s] idx[%d]\n",key,i);
      return i;
    }
    *structFieldsDesc++;
  }
  return -1;
}

xmlNodePtr GetRespuestaPtr(xmlDoc *doc, xmlNode * a_node)
{
  xmlNodePtr cur = NULL;
  cur = a_node;
  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      Log(DEBUG, "node type: Element, name: %s, VALUE %s",cur->name, xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

      if (strcmp(cur->name,"Respuesta")==0) {
	cur = cur->children;
	break;
      }
    }
        cur = cur->children;
   }
   return cur;
}

void SetResponseValue(char **varPtr, char *varValue) {
  int needSize;
  char *aux;
  
  needSize=strlen(varValue)+1;
  aux=(char*)calloc(needSize, sizeof(char));
  strcpy(aux,varValue);
  *varPtr=aux;
  
}

void parse_TaxesResponseStruct(TAXES_RESPONSE_STRUCT **pPtr, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_TaxesResponseStruct Init");
  cur = a_node->children;
  if (cur)
    *pPtr=(char*)calloc(sizeof(TAXES_RESPONSE_STRUCT), sizeof(TAXES_RESPONSE_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s\n",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, TYPEID_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->TYPEID_FIELD);
        if (strcmp(cur->name, TYPEDESCRIPTION_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->TYPEDESCRIPTION_FIELD);
        if (strcmp(cur->name, AMOUNT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->AMOUNT_FIELD);
        if (strcmp(cur->name, RATE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->RATE_FIELD);
        if (strcmp(cur->name, BASEAMOUNT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->BASEAMOUNT_FIELD);
        if (strcmp(cur->name, APPLIEDAMOUNT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->APPLIEDAMOUNT_FIELD);
        if (strcmp(cur->name, REMARKS_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->REMARKS_FIELD);
	
        SetResponseValue(varPtr, varValue);
      }
    }
    cur = cur->next;
   }
   Log(DEBUG, "parse_TaxesResponseStruct done");
   return ;
}
  
void parse_ArrayOf_TaxesResponseStruct(ARRAYOF_TAXESRESPONSESTRUCT **pTaxes, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  TAXES_RESPONSE_STRUCT *pPtr;
  int i=0, needSize;
  
  Log(DEBUG, "parse_ArrayOf_TaxesResponseStruct Init");
  cur = a_node->children;
  if (cur)
    *pTaxes=(char*)calloc(sizeof(ARRAYOF_TAXESRESPONSESTRUCT), sizeof(ARRAYOF_TAXESRESPONSESTRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      
      if (strcmp(cur->name, "item")==0) {
	
	needSize=sizeof(TAXES_RESPONSE_STRUCT *)*(i+1);
	
        if (i==0)
          (*pTaxes)->__ptr=(TAXES_RESPONSE_STRUCT *)malloc(needSize);
        else
          (*pTaxes)->__ptr=realloc((*pTaxes)->__ptr,needSize);
	
	Log(DEBUG, "parse_TaxesResponseStruct %d",i);
        parse_TaxesResponseStruct(&((*pTaxes)->__ptr[i]), doc, cur);
	Log(DEBUG, "parse_TaxesResponseStruct %d done",i);
	i++;
      }
    }
    cur = cur->next;
   }
   Log(DEBUG, "parse_ArrayOf_TaxesResponseStruct while done");
   
   if (i>0)
     (*pTaxes)->__size=i;
   
   return ;
  
}

void parse_AmountAdditionalDetailsResponseStruct(AMOUNT_ADDITIONAL_DETAILS_RESPONSE_STRUCT **pAmountAdditionalDetails, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  int i;
  
  Log(DEBUG, "parse_AmountAdditionalDetailsResponseStruct Init");
  cur = a_node->children;
  if (cur)
    *pAmountAdditionalDetails=(char*)calloc(sizeof(AMOUNT_ADDITIONAL_DETAILS_RESPONSE_STRUCT), sizeof(AMOUNT_ADDITIONAL_DETAILS_RESPONSE_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   parse_AmountAdditionalDetailsResponseStruct node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {

        if (strcmp(cur->name, TIP_FIELD_DESC)==0)
          varPtr=(char**)&((*pAmountAdditionalDetails)->TIP_FIELD);
        if (strcmp(cur->name, DISCOUNT_FIELD_DESC)==0)
          varPtr=(char**)&((*pAmountAdditionalDetails)->DISCOUNT_FIELD);
	
        SetResponseValue(varPtr, varValue);
        
      }
      else {
        if (strcmp(cur->name, "Taxes")==0)
          parse_ArrayOf_TaxesResponseStruct(&((*pAmountAdditionalDetails)->Taxes), doc, cur);
      }      
    }
    cur = cur->next;
   }
   return ;
}


void parse_PersonStruct(PERSON_STRUCT **pPerson, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_PersonStruct Init");
  cur = a_node->children;
  if (cur)
    *pPerson=(char*)calloc(sizeof(PERSON_STRUCT), sizeof(PERSON_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, FIRSTNAME_FIELD_DESC)==0)
          varPtr=(char**)&((*pPerson)->FIRSTNAME_FIELD);
        if (strcmp(cur->name, LASTNAME_FIELD_DESC)==0)
          varPtr=(char**)&((*pPerson)->LASTNAME_FIELD);
        if (strcmp(cur->name, MIDDLENAME_FIELD_DESC)==0)
          varPtr=(char**)&((*pPerson)->MIDDLENAME_FIELD);
        if (strcmp(cur->name, PHONENUMBER1_FIELD_DESC)==0)
          varPtr=(char**)&((*pPerson)->PHONENUMBER1_FIELD);
        if (strcmp(cur->name, PHONENUMBER2_FIELD_DESC)==0)
          varPtr=(char**)&((*pPerson)->PHONENUMBER2_FIELD);
        if (strcmp(cur->name, GENDER_FIELD_DESC)==0)
          varPtr=(char**)&((*pPerson)->GENDER_FIELD);
        if (strcmp(cur->name, DATEOFBIRTH_FIELD_DESC)==0)
          varPtr=(char**)&((*pPerson)->DATEOFBIRTH_FIELD);
        if (strcmp(cur->name, NATIONALITY_FIELD_DESC)==0)
          varPtr=(char**)&((*pPerson)->NATIONALITY_FIELD);
        if (strcmp(cur->name, IDNUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pPerson)->IDNUMBER_FIELD);
        if (strcmp(cur->name, IDTYPE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPerson)->IDTYPE_FIELD);
	
        SetResponseValue(varPtr, varValue);
      }
    }
    cur = cur->next;
   }
   return ;
}

void parse_AddressStruct(ADDRESS_STRUCT **pAddress, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_AddressStruct Init");
  cur = a_node->children;
  if (cur)
    *pAddress=(char*)calloc(sizeof(ADDRESS_STRUCT), sizeof(ADDRESS_STRUCT));
  
  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, STREET_FIELD_DESC)==0)
          varPtr=(char**)&((*pAddress)->STREET_FIELD);
        if (strcmp(cur->name, HOUSENUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pAddress)->HOUSENUMBER_FIELD);
        if (strcmp(cur->name, ADDITIONALINFO_FIELD_DESC)==0)
          varPtr=(char**)&((*pAddress)->ADDITIONALINFO_FIELD);
        if (strcmp(cur->name, CITY_FIELD_DESC)==0)
          varPtr=(char**)&((*pAddress)->CITY_FIELD);
        if (strcmp(cur->name, STATEPROVINCE_FIELD_DESC)==0)
          varPtr=(char**)&((*pAddress)->STATEPROVINCE_FIELD);
        if (strcmp(cur->name, COUNTRY_FIELD_DESC)==0)
          varPtr=(char**)&((*pAddress)->COUNTRY_FIELD);
        if (strcmp(cur->name, ZIPCODE_FIELD_DESC)==0)
          varPtr=(char**)&((*pAddress)->ZIPCODE_FIELD);
	
        SetResponseValue(varPtr, varValue);
      }
    }
    cur = cur->next;
   }
   return ;
}

void parse_CardOutputDetailsStruct(CARD_OUTPUT_DETAILS_STRUCT **pCardOutputDetails, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_CardOutputDetailsStruct Init");
  cur = a_node->children;
  if (cur)
    *pCardOutputDetails=(char*)calloc(sizeof(CARD_OUTPUT_DETAILS_STRUCT), sizeof(CARD_OUTPUT_DETAILS_STRUCT));
  
  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, NUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pCardOutputDetails)->NUMBER_FIELD);
        if (strcmp(cur->name, EXPIRATIONDATE_FIELD_DESC)==0)
          varPtr=(char**)&((*pCardOutputDetails)->EXPIRATIONDATE_FIELD);
        if (strcmp(cur->name, EXPIRATIONYEAR_FIELD_DESC)==0)
          varPtr=(char**)&((*pCardOutputDetails)->EXPIRATIONYEAR_FIELD);
        if (strcmp(cur->name, EXPIRATIONMONTH_FIELD_DESC)==0)
          varPtr=(char**)&((*pCardOutputDetails)->EXPIRATIONMONTH_FIELD);
        if (strcmp(cur->name, HOLDERNAME_FIELD_DESC)==0)
          varPtr=(char**)&((*pCardOutputDetails)->HOLDERNAME_FIELD);
        if (strcmp(cur->name, IIN_FIELD_DESC)==0)
          varPtr=(char**)&((*pCardOutputDetails)->IIN_FIELD);
        if (strcmp(cur->name, LAST4_FIELD_DESC)==0)
          varPtr=(char**)&((*pCardOutputDetails)->LAST4_FIELD);
        if (strcmp(cur->name, NUMBERLENGTH_FIELD_DESC)==0)
          varPtr=(char**)&((*pCardOutputDetails)->NUMBERLENGTH_FIELD);
        if (strcmp(cur->name, MASKEDNUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pCardOutputDetails)->MASKEDNUMBER_FIELD);
        if (strcmp(cur->name, MASKEDNUMBERALTERNATIVE_FIELD_DESC)==0)
          varPtr=(char**)&((*pCardOutputDetails)->MASKEDNUMBERALTERNATIVE_FIELD);
	
        SetResponseValue(varPtr, varValue);
      }
    }
    cur = cur->next;
   }
   return ;
}


void parse_PaymentMethodOutputDetailsStruct(PAYMENT_METHOD_OUTPUT_DETAILS_STRUCT **pPaymentMethod, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_PaymentMethodOutputDetailsStruct Init");
  cur = a_node->children;
  if (cur)
    *pPaymentMethod=(char*)calloc(sizeof(PAYMENT_METHOD_OUTPUT_DETAILS_STRUCT), sizeof(PAYMENT_METHOD_OUTPUT_DETAILS_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, PAYMENTMETHODID_FIELD_DESC)==0)
          varPtr=(char**)&((*pPaymentMethod)->PAYMENTMETHODID_FIELD);
        if (strcmp(cur->name, PAYMENTMETHODTAG_FIELD_DESC)==0)
          varPtr=(char**)&((*pPaymentMethod)->PAYMENTMETHODTAG_FIELD);
        if (strcmp(cur->name, PRODUCT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPaymentMethod)->PRODUCT_FIELD);
        if (strcmp(cur->name, FINGERPRINT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPaymentMethod)->FINGERPRINT_FIELD);
        if (strcmp(cur->name, CREATEDAT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPaymentMethod)->CREATEDAT_FIELD);
        if (strcmp(cur->name, UPDATEDAT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPaymentMethod)->UPDATEDAT_FIELD);
	
        SetResponseValue(varPtr, varValue);
      }
      else {
        if (strcmp(cur->name, "CardOutputDetails")==0)
          parse_CardOutputDetailsStruct(&((*pPaymentMethod)->CardOutputDetails), doc, cur);
        if (strcmp(cur->name, "Person")==0)
          parse_PersonStruct(&((*pPaymentMethod)->Person), doc, cur);
        if (strcmp(cur->name, "Address")==0)
          parse_AddressStruct(&((*pPaymentMethod)->Address), doc, cur);
      }      
    }
    cur = cur->next;
   }
   return ;
}

void parse_FraudScreeningResultStruct(FRAUD_SCREENING_RESULT_STRUCT **pFraudScreeningResult, xmlDoc *doc, xmlNode * a_node){
  xmlNodePtr cur = NULL;
  char *varValue, **varPtr;
  
  Log(DEBUG, "parse_FraudScreeningResultStruct Init");
  cur = a_node->children;
  if (cur)
    *pFraudScreeningResult=(char*)calloc(sizeof(FRAUD_SCREENING_RESULT_STRUCT), sizeof(FRAUD_SCREENING_RESULT_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, RESULTCODE_FIELD_DESC)==0)
          varPtr=(char**)&((*pFraudScreeningResult)->RESULTCODE_FIELD);
        if (strcmp(cur->name, RESULTDESCRIPTION_FIELD_DESC)==0)
          varPtr=(char**)&((*pFraudScreeningResult)->RESULTDESCRIPTION_FIELD);
        if (strcmp(cur->name, ADDITIONALINFO_FIELD_DESC)==0)
          varPtr=(char**)&((*pFraudScreeningResult)->ADDITIONALINFO_FIELD);
	
        SetResponseValue(varPtr, varValue);
      }
    }
    cur = cur->next;
   }
   return ;
  
}

void parse_VerificationServicesResultStruct(VERIFICATION_SERVICES_RESULT_STRUCT **pVerificationServicesResult, xmlDoc *doc, xmlNode * a_node){
  xmlNodePtr cur = NULL;
  char *varValue, **varPtr;
  
  Log(DEBUG, "parse_VerificationServicesResultStruct Init");
  cur = a_node->children;
  if (cur)
    *pVerificationServicesResult=(char*)calloc(sizeof(VERIFICATION_SERVICES_RESULT_STRUCT), sizeof(VERIFICATION_SERVICES_RESULT_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, RESULTCODECARDSECURITYCODE_FIELD_DESC)==0)
          varPtr=(char**)&((*pVerificationServicesResult)->RESULTCODECARDSECURITYCODE_FIELD);
        if (strcmp(cur->name, RESULTCODEBILLINGADDRESS_FIELD_DESC)==0)
          varPtr=(char**)&((*pVerificationServicesResult)->RESULTCODEBILLINGADDRESS_FIELD);
        if (strcmp(cur->name, RESULTCODEBILLINGADDRESSZIPCODE_FIELD_DESC)==0)
          varPtr=(char**)&((*pVerificationServicesResult)->RESULTCODEBILLINGADDRESSZIPCODE_FIELD);
        if (strcmp(cur->name, RESULTCODEBILLINGPERSONIDTYPE_FIELD_DESC)==0)
          varPtr=(char**)&((*pVerificationServicesResult)->RESULTCODEBILLINGPERSONIDTYPE_FIELD);
        if (strcmp(cur->name, RESULTCODEBILLINGPERSONIDNUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pVerificationServicesResult)->RESULTCODEBILLINGPERSONIDNUMBER_FIELD);
        if (strcmp(cur->name, RESULTCODEBILLINGPERSONDATEOFBIRTH_FIELD_DESC)==0)
          varPtr=(char**)&((*pVerificationServicesResult)->RESULTCODEBILLINGPERSONDATEOFBIRTH_FIELD);
        if (strcmp(cur->name, RESULTCODEBILLINGPERSONNAME_FIELD_DESC)==0)
          varPtr=(char**)&((*pVerificationServicesResult)->RESULTCODEBILLINGPERSONNAME_FIELD);
        if (strcmp(cur->name, RESULTCODEBILLINGPERSONPHONENUMBER1_FIELD_DESC)==0)
          varPtr=(char**)&((*pVerificationServicesResult)->RESULTCODEBILLINGPERSONPHONENUMBER1_FIELD);
        if (strcmp(cur->name, RESULTCODECUSTOMEREMAILADDRESS_FIELD_DESC)==0)
          varPtr=(char**)&((*pVerificationServicesResult)->RESULTCODECUSTOMEREMAILADDRESS_FIELD);
	
        SetResponseValue(varPtr, varValue);
      }
    }
    cur = cur->next;
   }
   return ;
}

void parse_RespuestaStruct_SplitPayOnLine_2p_Transactions(RESPUESTASTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS **pPtr, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_RespuestaStruct_SplitPayOnLine_2p_Transactions Init");
  cur = a_node->children;
  if (cur)
    *pPtr=(char*)calloc(sizeof(RESPUESTASTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS), sizeof(RESPUESTASTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, PSP_TRANSACTIONID_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_TRANSACTIONID_FIELD);
        if (strcmp(cur->name, PSP_MERCHANTID_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_MERCHANTID_FIELD);
        if (strcmp(cur->name, PSP_MERCHTXREF_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_MERCHTXREF_FIELD);
        if (strcmp(cur->name, PSP_MERCHADDITIONALREF_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_MERCHADDITIONALREF_FIELD);
        if (strcmp(cur->name, PSP_AMOUNT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_AMOUNT_FIELD);
        if (strcmp(cur->name, PSP_NUMPAYMENTS_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_NUMPAYMENTS_FIELD);
        if (strcmp(cur->name, PSP_PAYMENTAMOUNT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_PAYMENTAMOUNT_FIELD);
        if (strcmp(cur->name, PSP_PRODUCT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_PRODUCT_FIELD);
        if (strcmp(cur->name, PSP_CARDNUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CARDNUMBER_FIELD);
        if (strcmp(cur->name, PSP_CARDEXPDATE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CARDEXPDATE_FIELD);
        if (strcmp(cur->name, PSP_AUTHORIZATIONCODE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_AUTHORIZATIONCODE_FIELD);
        if (strcmp(cur->name, PSP_BATCHNRO_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_BATCHNRO_FIELD);
        if (strcmp(cur->name, PSP_TICKETNUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_TICKETNUMBER_FIELD);
        if (strcmp(cur->name, PSP_SEQUENCENUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_SEQUENCENUMBER_FIELD);
        if (strcmp(cur->name, PSP_CLTRNID_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CLTRNID_FIELD);
        if (strcmp(cur->name, PSP_CLEXTERNALMERCHANT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CLEXTERNALMERCHANT_FIELD);
        if (strcmp(cur->name, PSP_CLEXTERNALTERMINAL_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CLEXTERNALTERMINAL_FIELD);
        if (strcmp(cur->name, PSP_CLRESPONSECOD_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CLRESPONSECOD_FIELD);
        if (strcmp(cur->name, PSP_CLRESPONSEMSG_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CLRESPONSEMSG_FIELD);
        if (strcmp(cur->name, PSP_PLAN_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_PLAN_FIELD);
        if (strcmp(cur->name, PSP_PROMOTIONCODE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_PROMOTIONCODE_FIELD);
        if (strcmp(cur->name, PSP_PRESETCARDIIN_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_PRESETCARDIIN_FIELD);
        if (strcmp(cur->name, PSP_CREATEDAT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CREATEDAT_FIELD);
	
        SetResponseValue(varPtr, varValue);
      }
      else {
        if (strcmp(cur->name, "psp_AmountAdditionalDetails")==0)
          parse_AmountAdditionalDetailsResponseStruct(&((*pPtr)->psp_AmountAdditionalDetails), doc, cur);
        if (strcmp(cur->name, PSP_FRAUDSCREENINGRESULT_FIELD_DESC)==0)
          parse_FraudScreeningResultStruct(&((*pPtr)->psp_FraudScreeningResult), doc, cur);
        if (strcmp(cur->name, PSP_VERIFICATIONSERVICESRESULT_FIELD_DESC)==0)
          parse_VerificationServicesResultStruct(&((*pPtr)->psp_VerificationServicesResult), doc, cur);
      }      
	
    }
    cur = cur->next;
   }
   return ;
}

void parse_ArrayOf_RespuestaStruct_SplitPayOnLine_2p_Transactions(ARRAYOF_RESPUESTASTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS **pTransactions, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  RESPUESTASTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS *pPtr;
  int i=0, needSize;
  
  Log(DEBUG, "parse_ArrayOf_RespuestaStruct_SplitPayOnLine_2p_Transactions Init");
  cur = a_node->children;
  if (cur)
    *pTransactions=(char*)calloc(sizeof(ARRAYOF_RESPUESTASTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS), sizeof(ARRAYOF_RESPUESTASTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      
      if (strcmp(cur->name, "item")==0) {
	
	needSize=sizeof(RESPUESTASTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS *)*(i+1);
	
        if (i==0)
          (*pTransactions)->__ptr=(RESPUESTASTRUCT_SPLITPAYONLINE_2P_TRANSACTIONS *)malloc(needSize);
        else
          (*pTransactions)->__ptr=realloc((*pTransactions)->__ptr,needSize);
	
        parse_RespuestaStruct_SplitPayOnLine_2p_Transactions(&((*pTransactions)->__ptr[i]), doc, cur);
	i++;
      }
    }
    cur = cur->next;
   }
   
   if (i>0)
     (*pTransactions)->__size=i;
   
   return ;
  
}

void parse_PaymentMethodsOutputDetailsStruct(PAYMENT_METHODS_OUTPUT_DETAILS_STRUCT **pPtr, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_PaymentMethodsOutputDetailsStruct Init");
  cur = a_node->children;
  if (cur)
    *pPtr=(char*)calloc(sizeof(PAYMENT_METHODS_OUTPUT_DETAILS_STRUCT), sizeof(PAYMENT_METHODS_OUTPUT_DETAILS_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
	
        if (strcmp(cur->name, PAYMENTMETHODID_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PAYMENTMETHODID_FIELD);
        if (strcmp(cur->name, PAYMENTMETHODTAG_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PAYMENTMETHODTAG_FIELD);
        if (strcmp(cur->name, PRODUCT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PRODUCT_FIELD);
        if (strcmp(cur->name, FINGERPRINT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->FINGERPRINT_FIELD);
        if (strcmp(cur->name, CREATEDAT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->CREATEDAT_FIELD);
        if (strcmp(cur->name, UPDATEDAT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->UPDATEDAT_FIELD);
	
        SetResponseValue(varPtr, varValue);
      }
      else {
        if (strcmp(cur->name, CARDOUTPUTDETAILS_FIELD_DESC)==0)
          parse_CardOutputDetailsStruct(&((*pPtr)->CARDOUTPUTDETAILS_FIELD), doc, cur);
        if (strcmp(cur->name, PERSON_FIELD_DESC)==0)
          parse_PersonStruct(&((*pPtr)->PERSON_FIELD), doc, cur);
        if (strcmp(cur->name, ADDRESS_FIELD_DESC)==0)
          parse_AddressStruct(&((*pPtr)->ADDRESS_FIELD), doc, cur);
      }      
	
    }
    cur = cur->next;
   }
   return ;
}

void parse_ArrayOf_PaymentMethodsOutputDetailsStruct(ARRAYOF_PAYMENTMETHODSOUTPUTDETAILSSTRUCT **pPaymentMethods, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  PAYMENT_METHODS_OUTPUT_DETAILS_STRUCT *pPtr;
  int i=0, needSize;
  
  Log(DEBUG, "parse_ArrayOf_PaymentMethodsOutputDetailsStruct Init");
  cur = a_node->children;
  if (cur)
    *pPaymentMethods=(char*)calloc(sizeof(ARRAYOF_PAYMENTMETHODSOUTPUTDETAILSSTRUCT), sizeof(ARRAYOF_PAYMENTMETHODSOUTPUTDETAILSSTRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      
      if (strcmp(cur->name, "item")==0) {
	
	needSize=sizeof(PAYMENT_METHODS_OUTPUT_DETAILS_STRUCT *)*(i+1);
	
        if (i==0)
          (*pPaymentMethods)->__ptr=(PAYMENT_METHODS_OUTPUT_DETAILS_STRUCT *)malloc(needSize);
        else
          (*pPaymentMethods)->__ptr=realloc((*pPaymentMethods)->__ptr,needSize);
	
        parse_PaymentMethodsOutputDetailsStruct(&((*pPaymentMethods)->__ptr[i]), doc, cur);
	i++;
      }
    }
    cur = cur->next;
   }
   
   if (i>0)
     (*pPaymentMethods)->__size=i;
   
   return ;
  
}

void parse_SellerDetailsStruct(SELLER_DETAILS_STRUCT **pSellerDetails, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_SellerDetailsStruct Init");
  cur = a_node->children;
  if (cur)
    *pSellerDetails=(char*)calloc(sizeof(SELLER_DETAILS_STRUCT), sizeof(SELLER_DETAILS_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, IDNUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pSellerDetails)->IDNUMBER_FIELD);
        if (strcmp(cur->name, IDTYPE_FIELD_DESC)==0)
          varPtr=(char**)&((*pSellerDetails)->IDTYPE_FIELD);
        if (strcmp(cur->name, NAME_FIELD_DESC)==0)
          varPtr=(char**)&((*pSellerDetails)->NAME_FIELD);
        if (strcmp(cur->name, INVOICE_FIELD_DESC)==0)
          varPtr=(char**)&((*pSellerDetails)->INVOICE_FIELD);
        if (strcmp(cur->name, PURCHASEDESCRIPTION_FIELD_DESC)==0)
          varPtr=(char**)&((*pSellerDetails)->PURCHASEDESCRIPTION_FIELD);
        if (strcmp(cur->name, MCC_FIELD_DESC)==0)
          varPtr=(char**)&((*pSellerDetails)->MCC_FIELD);
        if (strcmp(cur->name, CHANNELCODE_FIELD_DESC)==0)
          varPtr=(char**)&((*pSellerDetails)->CHANNELCODE_FIELD);
        if (strcmp(cur->name, GEOCODE_FIELD_DESC)==0)
          varPtr=(char**)&((*pSellerDetails)->GEOCODE_FIELD);
          
        SetResponseValue(varPtr, varValue);
      }
      else {
        if (strcmp(cur->name, ADDRESS_FIELD_DESC)==0)
          parse_AddressStruct(&((*pSellerDetails)->ADDRESS_FIELD), doc, cur);
      }      
    }
    cur = cur->next;
   }
   return ;
}

void parse_MerchantAdditionalDetailsStruct(MERCHANT_ADDITIONAL_DETAILS_STRUCT **pMerchantAdditionalDetails, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_MerchantAdditionalDetailsStruct Init");
  cur = a_node->children;
  if (cur)
    *pMerchantAdditionalDetails=(char*)calloc(sizeof(MERCHANT_ADDITIONAL_DETAILS_STRUCT), sizeof(MERCHANT_ADDITIONAL_DETAILS_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, TYPE_FIELD_DESC)==0)
          varPtr=(char**)&((*pMerchantAdditionalDetails)->TYPE_FIELD);
        if (strcmp(cur->name, SDKINFO_FIELD_DESC)==0)
          varPtr=(char**)&((*pMerchantAdditionalDetails)->SDKINFO_FIELD);
        if (strcmp(cur->name, SHOPPINGCARTINFO_FIELD_DESC)==0)
          varPtr=(char**)&((*pMerchantAdditionalDetails)->SHOPPINGCARTINFO_FIELD);
        if (strcmp(cur->name, SHOPPINGCARTPLUGININFO_FIELD_DESC)==0)
          varPtr=(char**)&((*pMerchantAdditionalDetails)->SHOPPINGCARTPLUGININFO_FIELD);
	
        SetResponseValue(varPtr, varValue);
      }
      else {
        if (strcmp(cur->name, SELLERDETAILS_FIELD_DESC)==0)
          parse_SellerDetailsStruct(&((*pMerchantAdditionalDetails)->SELLERDETAILS_FIELD), doc, cur);
      }      
    }
    cur = cur->next;
   }
   return ;
}

void parse_CustomerAdditionalDetailsStruct(CUSTOMER_ADDITIONAL_DETAILS_STRUCT **pCustomerAdditionalDetails, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_CustomerAdditionalDetailsStruct Init");
  cur = a_node->children;
  if (cur)
    *pCustomerAdditionalDetails=(char*)calloc(sizeof(CUSTOMER_ADDITIONAL_DETAILS_STRUCT), sizeof(CUSTOMER_ADDITIONAL_DETAILS_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, EMAILADDRESS_FIELD_DESC)==0)
          varPtr=(char**)&((*pCustomerAdditionalDetails)->EMAILADDRESS_FIELD);
        if (strcmp(cur->name, ALTERNATIVEEMAILADDRESS_FIELD_DESC)==0)
          varPtr=(char**)&((*pCustomerAdditionalDetails)->ALTERNATIVEEMAILADDRESS_FIELD);
        if (strcmp(cur->name, IPADDRESS_FIELD_DESC)==0)
          varPtr=(char**)&((*pCustomerAdditionalDetails)->IPADDRESS_FIELD);
        if (strcmp(cur->name, ACCOUNTID_FIELD_DESC)==0)
          varPtr=(char**)&((*pCustomerAdditionalDetails)->ACCOUNTID_FIELD);
        if (strcmp(cur->name, ACCOUNTCREATEDAT_FIELD_DESC)==0)
          varPtr=(char**)&((*pCustomerAdditionalDetails)->ACCOUNTCREATEDAT_FIELD);
        if (strcmp(cur->name, ACCOUNTPREVIOUSACTIVITY_FIELD_DESC)==0)
          varPtr=(char**)&((*pCustomerAdditionalDetails)->ACCOUNTPREVIOUSACTIVITY_FIELD);
        if (strcmp(cur->name, ACCOUNTHASCREDENTIALS_FIELD_DESC)==0)
          varPtr=(char**)&((*pCustomerAdditionalDetails)->ACCOUNTHASCREDENTIALS_FIELD);
        if (strcmp(cur->name, DEVICETYPE_FIELD_DESC)==0)
          varPtr=(char**)&((*pCustomerAdditionalDetails)->DEVICETYPE_FIELD);
        if (strcmp(cur->name, DEVICEFINGERPRINT_FIELD_DESC)==0)
          varPtr=(char**)&((*pCustomerAdditionalDetails)->DEVICEFINGERPRINT_FIELD);
        if (strcmp(cur->name, BROWSERLANGUAGE_FIELD_DESC)==0)
          varPtr=(char**)&((*pCustomerAdditionalDetails)->BROWSERLANGUAGE_FIELD);
        if (strcmp(cur->name, HTTPUSERAGENT_FIELD_DESC)==0)
          varPtr=(char**)&((*pCustomerAdditionalDetails)->HTTPUSERAGENT_FIELD);
	
        SetResponseValue(varPtr, varValue);
      }
    }
    cur = cur->next;
   }
   return ;
}

void parse_BillingDetailsStruct(BILLING_DETAILS_STRUCT **pBillingDetails, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_BillingDetailsStruct Init");
  cur = a_node->children;
  if (cur)
    *pBillingDetails=(char*)calloc(sizeof(BILLING_DETAILS_STRUCT), sizeof(BILLING_DETAILS_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, INVOICE_FIELD_DESC)==0)
          varPtr=(char**)&((*pBillingDetails)->INVOICE_FIELD);
        if (strcmp(cur->name,INVOICEDATE_FIELD_DESC)==0)
          varPtr=(char**)&((*pBillingDetails)->INVOICEDATE_FIELD);
        if (strcmp(cur->name, INVOICEAMOUNT_FIELD_DESC)==0)
          varPtr=(char**)&((*pBillingDetails)->INVOICEAMOUNT_FIELD);
        if (strcmp(cur->name, INVOICECURRENCY_FIELD_DESC)==0)
          varPtr=(char**)&((*pBillingDetails)->INVOICECURRENCY_FIELD);
	
        SetResponseValue(varPtr, varValue);
      }
      else {
        if (strcmp(cur->name, PERSON_FIELD_DESC)==0)
          parse_PersonStruct(&((*pBillingDetails)->PERSON_FIELD), doc, cur);
        if (strcmp(cur->name, ADDRESS_FIELD_DESC)==0)
          parse_AddressStruct(&((*pBillingDetails)->ADDRESS_FIELD), doc, cur);
      }      
      
    }
    cur = cur->next;
   }
   return ;
}

void parse_ShippingDetailsStruct(SHIPPING_DETAILS_STRUCT **pShippingDetails, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_ShippingDetailsStruct Init");
  cur = a_node->children;
  if (cur)
    *pShippingDetails=(char*)calloc(sizeof(SHIPPING_DETAILS_STRUCT), sizeof(SHIPPING_DETAILS_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, TRACKINGNUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pShippingDetails)->TRACKINGNUMBER_FIELD);
        if (strcmp(cur->name, METHOD_FIELD_DESC)==0)
          varPtr=(char**)&((*pShippingDetails)->METHOD_FIELD);
        if (strcmp(cur->name, CARRIER_FIELD_DESC)==0)
          varPtr=(char**)&((*pShippingDetails)->CARRIER_FIELD);
        if (strcmp(cur->name, DELIVERYDATE_FIELD_DESC)==0)
          varPtr=(char**)&((*pShippingDetails)->DELIVERYDATE_FIELD);
        if (strcmp(cur->name, FREIGHTAMOUNT_FIELD_DESC)==0)
          varPtr=(char**)&((*pShippingDetails)->FREIGHTAMOUNT_FIELD);
        if (strcmp(cur->name, GIFTMESSAGE_FIELD_DESC)==0)
          varPtr=(char**)&((*pShippingDetails)->GIFTMESSAGE_FIELD);
        if (strcmp(cur->name, GIFTWRAPPING_FIELD_DESC)==0)
          varPtr=(char**)&((*pShippingDetails)->GIFTWRAPPING_FIELD);

	SetResponseValue(varPtr, varValue);
      }
      else {
        if (strcmp(cur->name, PRIMARYRECIPIENT_FIELD_DESC)==0)
          parse_PersonStruct(&((*pShippingDetails)->PRIMARYRECIPIENT_FIELD), doc, cur);
        if (strcmp(cur->name, SECONDARYRECIPIENT_FIELD_DESC)==0)
          parse_PersonStruct(&((*pShippingDetails)->SECONDARYRECIPIENT_FIELD), doc, cur);
        if (strcmp(cur->name, ADDRESS_FIELD_DESC)==0)
          parse_AddressStruct(&((*pShippingDetails)->ADDRESS_FIELD), doc, cur);
      }      
      
    }
    cur = cur->next;
   }
   return ;
}


void parse_OrderItemStruct(ORDER_ITEM_STRUCT **pPtr, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_OrderItemStruct Init");
  cur = a_node->children;
  if (cur)
    *pPtr=(char*)calloc(sizeof(ORDER_ITEM_STRUCT), sizeof(ORDER_ITEM_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, QUANTITY_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->QUANTITY_FIELD);
        if (strcmp(cur->name, UNITPRICE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->UNITPRICE_FIELD);
        if (strcmp(cur->name, DESCRIPTION_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->DESCRIPTION_FIELD);
        if (strcmp(cur->name, TYPE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->TYPE_FIELD);
        if (strcmp(cur->name,SKUCODE_FIELD_DESC)==0) 
          varPtr=(char**)&((*pPtr)->SKUCODE_FIELD);
        if (strcmp(cur->name, MANUFACTURERPARTNUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->MANUFACTURERPARTNUMBER_FIELD);
        if (strcmp(cur->name,RISK_FIELD_DESC)==0) 
          varPtr=(char**)&((*pPtr)->RISK_FIELD);
	
        SetResponseValue(varPtr, varValue);
      }
    }
    cur = cur->next;
   }
   return ;
}

void parse_ArrayOf_OrderItemStruct(ARRAYOF_ORDERITEMSTRUCT **pOrderItems, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  ORDER_ITEM_STRUCT *pPtr;
  int i=0, needSize;
  
  Log(DEBUG, "parse_ArrayOf_OrderItemStruct Init");
  cur = a_node->children;
  if (cur)
    *pOrderItems=(char*)calloc(sizeof(ARRAYOF_ORDERITEMSTRUCT), sizeof(ARRAYOF_ORDERITEMSTRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      
      if (strcmp(cur->name, "item")==0) {
	
	needSize=sizeof(ORDER_ITEM_STRUCT *)*(i+1);
	
        if (i==0)
          (*pOrderItems)->__ptr=(ORDER_ITEM_STRUCT *)malloc(needSize);
        else
          (*pOrderItems)->__ptr=realloc((*pOrderItems)->__ptr,needSize);
	
        parse_OrderItemStruct(&((*pOrderItems)->__ptr[i]), doc, cur);
	i++;
      }
    }
    cur = cur->next;
   }
   
   if (i>0)
     (*pOrderItems)->__size=i;
   
   return ;
  
}

void parse_OrderDetailsStruct(ORDER_DETAILS_STRUCT **pOrderDetails, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_OrderDetailsStruct Init");
  cur = a_node->children;
  if (cur)
    *pOrderDetails=(char*)calloc(sizeof(ORDER_DETAILS_STRUCT), sizeof(ORDER_DETAILS_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (!varValue) {
        if (strcmp(cur->name, ORDERITEMS_FIELD_DESC)==0)
          parse_ArrayOf_OrderItemStruct(&((*pOrderDetails)->ORDERITEMS_FIELD), doc, cur);
      }      
    }
    cur = cur->next;
   }
   return ;
}

void parse_LegStruct(LEG_STRUCT **pPtr, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_LegStruct Init");
  cur = a_node->children;
  if (cur)
    *pPtr=(char*)calloc(sizeof(LEG_STRUCT), sizeof(LEG_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, DEPARTUREAIRPORT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->DEPARTUREAIRPORT_FIELD);
        if (strcmp(cur->name, DEPARTUREDATETIME_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->DEPARTUREDATETIME_FIELD);
        if (strcmp(cur->name, DEPARTUREAIRPORTTIMEZONE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->DEPARTUREAIRPORTTIMEZONE_FIELD);
        if (strcmp(cur->name, ARRIVALAIRPORT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->ARRIVALAIRPORT_FIELD);
        if (strcmp(cur->name, CARRIERCODE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->CARRIERCODE_FIELD);
        if (strcmp(cur->name, FLIGHTNUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->FLIGHTNUMBER_FIELD);
        if (strcmp(cur->name, FAREBASISCODE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->FAREBASISCODE_FIELD);
        if (strcmp(cur->name, FARECLASSCODE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->FARECLASSCODE_FIELD);
        if (strcmp(cur->name, BASEFARE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->BASEFARE_FIELD);
        if (strcmp(cur->name, BASEFARECURRENCY_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->BASEFARECURRENCY_FIELD);

        SetResponseValue(varPtr, varValue);
      }
    }
    cur = cur->next;
   }
   return ;
}


void parse_ArrayOf_LegStruct(ARRAYOF_LEGSTRUCT **pLegs, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  LEG_STRUCT *pPtr;
  int i=0, needSize;
  
  Log(DEBUG, "parse_ArrayOf_LegStruct Init");
  cur = a_node->children;
  if (cur)
    *pLegs=(char*)calloc(sizeof(ARRAYOF_LEGSTRUCT), sizeof(ARRAYOF_LEGSTRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      
      if (strcmp(cur->name, "item")==0) {
	
	needSize=sizeof(LEG_STRUCT *)*(i+1);
	
        if (i==0)
          (*pLegs)->__ptr=(LEG_STRUCT *)malloc(needSize);
        else
          (*pLegs)->__ptr=realloc((*pLegs)->__ptr,needSize);
	
        parse_LegStruct(&((*pLegs)->__ptr[i]), doc, cur);
	i++;
      }
    }
    cur = cur->next;
   }
   
   if (i>0)
     (*pLegs)->__size=i;
   
   return ;
  
}

void parse_PassengerStruct(PASSENGER_STRUCT **pPtr, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_PassengerStruct Init");
  cur = a_node->children;
  if (cur)
    *pPtr=(char*)calloc(sizeof(PASSENGER_STRUCT), sizeof(PASSENGER_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, FIRSTNAME_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->FIRSTNAME_FIELD);
        if (strcmp(cur->name, LASTNAME_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->LASTNAME_FIELD);
        if (strcmp(cur->name, MIDDLENAME_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->MIDDLENAME_FIELD);
        if (strcmp(cur->name, TYPE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->TYPE_FIELD);
        if (strcmp(cur->name, DATEOFBIRTH_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->DATEOFBIRTH_FIELD);
        if (strcmp(cur->name, NATIONALITY_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->NATIONALITY_FIELD);
        if (strcmp(cur->name, IDNUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->IDNUMBER_FIELD);
        if (strcmp(cur->name, IDTYPE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->IDTYPE_FIELD);
        if (strcmp(cur->name, IDCOUNTRY_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->IDCOUNTRY_FIELD);
        if (strcmp(cur->name, LOYALTYNUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->LOYALTYNUMBER_FIELD);

        SetResponseValue(varPtr, varValue);
      }
    }
    cur = cur->next;
   }
   return ;
}

void parse_ArrayOf_PassengerStruct(ARRAYOF_PASSENGERSTRUCT **pPassengers, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  PASSENGER_STRUCT *pPtr;
  int i=0, needSize;
  
  Log(DEBUG, "parse_ArrayOf_PassengerStruct Init");
  cur = a_node->children;
  if (cur)
    *pPassengers=(char*)calloc(sizeof(ARRAYOF_PASSENGERSTRUCT), sizeof(ARRAYOF_PASSENGERSTRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      
      if (strcmp(cur->name, "item")==0) {
	
	needSize=sizeof(PASSENGER_STRUCT *)*(i+1);
	
        if (i==0)
          (*pPassengers)->__ptr=(PASSENGER_STRUCT *)malloc(needSize);
        else
          (*pPassengers)->__ptr=realloc((*pPassengers)->__ptr,needSize);
	
        parse_PassengerStruct(&((*pPassengers)->__ptr[i]), doc, cur);
	i++;
      }
    }
    cur = cur->next;
   }
   
   if (i>0)
     (*pPassengers)->__size=i;
   
   return ;
  
}

void parse_AirlineTicketIssueStruct(AIRLINE_TICKET_ISSUE_STRUCT **pPtr, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_AirlineTicketIssueStruct Init");
  cur = a_node->children;
  if (cur)
    *pPtr=(char*)calloc(sizeof(AIRLINE_TICKET_ISSUE_STRUCT), sizeof(AIRLINE_TICKET_ISSUE_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, CARRIERPREFIXCODE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->CARRIERPREFIXCODE_FIELD);
        if (strcmp(cur->name, TRAVELAGENTCODE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->TRAVELAGENTCODE_FIELD);
        if (strcmp(cur->name, TRAVELAGENTNAME_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->TRAVELAGENTNAME_FIELD);
        if (strcmp(cur->name, DATE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->DATE_FIELD);
        if (strcmp(cur->name, COUNTRY_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->COUNTRY_FIELD);
        if (strcmp(cur->name, CITY_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->CITY_FIELD);
        if (strcmp(cur->name, ADDRESS_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->ADDRESS_FIELD);

        SetResponseValue(varPtr, varValue);
      }
    }
    cur = cur->next;
   }
   return ;
}


void parse_AirlineTicketStruct(AIRLINE_TICKET_STRUCT **pPtr, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_AirlineTicketStruct Init");
  cur = a_node->children;
  if (cur)
    *pPtr=(char*)calloc(sizeof(AIRLINE_TICKET_STRUCT), sizeof(AIRLINE_TICKET_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, TICKETNUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->TICKETNUMBER_FIELD);
        if (strcmp(cur->name, ETICKET_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->ETICKET_FIELD);
        if (strcmp(cur->name, RESTRICTED_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->RESTRICTED_FIELD);
        if (strcmp(cur->name, TOTALFAREAMOUNT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->TOTALFAREAMOUNT_FIELD);
        if (strcmp(cur->name, TOTALTAXAMOUNT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->TOTALTAXAMOUNT_FIELD);
        if (strcmp(cur->name, TOTALFEEAMOUNT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->TOTALFEEAMOUNT_FIELD);

        SetResponseValue(varPtr, varValue);
      }
      else {
        if (strcmp(cur->name, ISSUE_FIELD_DESC)==0)
          parse_AirlineTicketIssueStruct(&((*pPtr)->ISSUE_FIELD), doc, cur);
      }      
      
    }
    cur = cur->next;
   }
   return ;
}

void parse_AirlineDetailsStruct(AIRLINE_DETAILS_STRUCT **pAirlineDetails, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_AirlineDetailsStruct Init");
  cur = a_node->children;
  if (cur)
    *pAirlineDetails=(char*)calloc(sizeof(AIRLINE_DETAILS_STRUCT), sizeof(AIRLINE_DETAILS_STRUCT));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, PNR_FIELD_DESC)==0)
          varPtr=(char**)&((*pAirlineDetails)->PNR_FIELD);

	SetResponseValue(varPtr, varValue);
      }
      else {
        if (strcmp(cur->name, LEGS_FIELD_DESC)==0)
          parse_ArrayOf_LegStruct(&((*pAirlineDetails)->LEGS_FIELD), doc, cur);	
        if (strcmp(cur->name, PASSENGERS_FIELD_DESC)==0)
          parse_ArrayOf_PassengerStruct(&((*pAirlineDetails)->PASSENGERS_FIELD), doc, cur);	
        if (strcmp(cur->name, TICKET_FIELD_DESC)==0)
          parse_AirlineTicketStruct(&((*pAirlineDetails)->TICKET_FIELD), doc, cur);	
      }      
    }
    cur = cur->next;
   }
   return ;
}

void parse_RespuestaStruct_SimpleQueryTx_Transactions(RESPUESTASTRUCT_SIMPLEQUERYTX_TRANSACTIONS **pPtr, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_RespuestaStruct_SimpleQueryTx_Transactions Init");
  cur = a_node->children;
  if (cur)
    *pPtr=(char*)calloc(sizeof(RESPUESTASTRUCT_SIMPLEQUERYTX_TRANSACTIONS), sizeof(RESPUESTASTRUCT_SIMPLEQUERYTX_TRANSACTIONS));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, PSP_RESPONSECOD_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_RESPONSECOD_FIELD);
        if (strcmp(cur->name, PSP_RESPONSEMSG_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_RESPONSEMSG_FIELD);
        if (strcmp(cur->name, PSP_RESPONSEEXTENDED_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_RESPONSEEXTENDED_FIELD);
        if (strcmp(cur->name,PSP_TRANSACTIONID_FIELD_DESC )==0)
          varPtr=(char**)&((*pPtr)->PSP_TRANSACTIONID_FIELD);
        if (strcmp(cur->name, PSP_MERCHANTID_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_MERCHANTID_FIELD);
        if (strcmp(cur->name, PSP_TXSOURCE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_TXSOURCE_FIELD);
        if (strcmp(cur->name, PSP_OPERATION_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_OPERATION_FIELD);
        if (strcmp(cur->name, PSP_MERCHTXREF_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_MERCHTXREF_FIELD);
        if (strcmp(cur->name, PSP_MERCHORDERID_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_MERCHORDERID_FIELD);
        if (strcmp(cur->name, PSP_MERCHADDITIONALREF_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_MERCHADDITIONALREF_FIELD);
        if (strcmp(cur->name, PSP_AMOUNT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_AMOUNT_FIELD);
        if (strcmp(cur->name, PSP_NUMPAYMENTS_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_NUMPAYMENTS_FIELD);
        if (strcmp(cur->name, PSP_PAYMENTAMOUNT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_PAYMENTAMOUNT_FIELD);
        if (strcmp(cur->name, PSP_FIRSTPAYMENTDEFERRAL_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_FIRSTPAYMENTDEFERRAL_FIELD);
        if (strcmp(cur->name, PSP_CURRENCY_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CURRENCY_FIELD);
        if (strcmp(cur->name,PSP_COUNTRY_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_COUNTRY_FIELD);
        if (strcmp(cur->name, PSP_PRODUCT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_PRODUCT_FIELD);
        if (strcmp(cur->name,PSP_AUTHORIZATIONCODE_FIELD_DESC)==0) 
          varPtr=(char**)&((*pPtr)->PSP_AUTHORIZATIONCODE_FIELD);
        if (strcmp(cur->name, PSP_BATCHNRO_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_BATCHNRO_FIELD);
        if (strcmp(cur->name, PSP_SEQUENCENUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_SEQUENCENUMBER_FIELD);
        if (strcmp(cur->name, PSP_TICKETNUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_TICKETNUMBER_FIELD);
        if (strcmp(cur->name, PSP_CARDNUMBER_FSD_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CARDNUMBER_FSD_FIELD);
        if (strcmp(cur->name, PSP_CARDNUMBER_LFD_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CARDNUMBER_LFD_FIELD);
        if (strcmp(cur->name, PSP_CARDMASK_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CARDMASK_FIELD);
        if (strcmp(cur->name, PSP_CARDHOLDERNAME_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CARDHOLDERNAME_FIELD);
        if (strcmp(cur->name, PSP_CUSTOMERMAIL_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CUSTOMERMAIL_FIELD);
        if (strcmp(cur->name, PSP_CUSTOMERID_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CUSTOMERID_FIELD);
        if (strcmp(cur->name, PSP_CUSTOMERIPADDRESS_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CUSTOMERIPADDRESS_FIELD);
        if (strcmp(cur->name, PSP_CUSTOMERHTTPUSERAGENT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CUSTOMERHTTPUSERAGENT_FIELD);
        if (strcmp(cur->name, PSP_MERCHANTMAIL_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_MERCHANTMAIL_FIELD);
        if (strcmp(cur->name, PSP_CLTRNID_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CLTRNID_FIELD);
        if (strcmp(cur->name, PSP_CLEXTERNALMERCHANT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CLEXTERNALMERCHANT_FIELD);
        if (strcmp(cur->name, PSP_CLEXTERNALTERMINAL_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CLEXTERNALTERMINAL_FIELD);
        if (strcmp(cur->name, PSP_CLRESPONSECOD_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CLRESPONSECOD_FIELD);
        if (strcmp(cur->name, PSP_CLRESPONSEMSG_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CLRESPONSEMSG_FIELD);
        if (strcmp(cur->name, PSP_POSDATETIME_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_POSDATETIME_FIELD);
        if (strcmp(cur->name, PSP_PURCHASEDESCRIPTION_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_PURCHASEDESCRIPTION_FIELD);
        if (strcmp(cur->name, PSP_SOFTDESCRIPTOR_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_SOFTDESCRIPTOR_FIELD);
        if (strcmp(cur->name, PSP_PLAN_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_PLAN_FIELD);
        if (strcmp(cur->name, PSP_VISAARG_VBV_SECURED_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_VISAARG_VBV_SECURED_FIELD);
        if (strcmp(cur->name, PSP_3DSECURE_XID_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_3DSECURE_XID_FIELD);
        if (strcmp(cur->name, PSP_3DSECURE_CAVV_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_3DSECURE_CAVV_FIELD);
        if (strcmp(cur->name, PSP_3DSECURE_Eci_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_3DSECURE_Eci_FIELD);
        if (strcmp(cur->name, PSP_3DSECURE_ECIMSG_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_3DSECURE_ECIMSG_FIELD);
        if (strcmp(cur->name, PSP_3DSECURE_SECURED_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_3DSECURE_SECURED_FIELD);
        if (strcmp(cur->name, PSP_VISAARG_DA_RESULT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_VISAARG_DA_RESULT_FIELD);
        if (strcmp(cur->name, PSP_AMEXARG_AVS_RESULT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_AMEXARG_AVS_RESULT_FIELD);
        if (strcmp(cur->name, PSP_MASTERARG_AVS_RESULT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_MASTERARG_AVS_RESULT_FIELD);
        if (strcmp(cur->name, PSP_CREATEDAT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CREATEDAT_FIELD);
        SetResponseValue(varPtr, varValue);
      }
      else {
        if (strcmp(cur->name, PSP_AMOUNTADDITIONALDETAILS_FIELD_DESC)==0)
          parse_AmountAdditionalDetailsResponseStruct(&((*pPtr)->PSP_AMOUNTADDITIONALDETAILS_FIELD), doc, cur);
        if (strcmp(cur->name, PSP_FRAUDSCREENINGRESULT_FIELD_DESC)==0)
          parse_FraudScreeningResultStruct(&((*pPtr)->PSP_FRAUDSCREENINGRESULT_FIELD), doc, cur);
        if (strcmp(cur->name, PSP_VERIFICATIONSERVICESRESULT_FIELD_DESC)==0)
          parse_VerificationServicesResultStruct(&((*pPtr)->PSP_VERIFICATIONSERVICESRESULT_FIELD), doc, cur);
        if (strcmp(cur->name, PSP_MERCHANTADDITIONALDETAILS_FIELD_DESC)==0)
          parse_MerchantAdditionalDetailsStruct(&((*pPtr)->PSP_MERCHANTADDITIONALDETAILS_FIELD), doc, cur);
        if (strcmp(cur->name, PSP_CUSTOMERADDITIONALDETAILS_FIELD_DESC)==0)
          parse_CustomerAdditionalDetailsStruct(&((*pPtr)->PSP_CUSTOMERADDITIONALDETAILS_FIELD), doc, cur);
        if (strcmp(cur->name, PSP_BILLINGDETAILS_FIELD_DESC)==0)
          parse_BillingDetailsStruct(&((*pPtr)->PSP_BILLINGDETAILS_FIELD), doc, cur);
        if (strcmp(cur->name, PSP_SHIPPINGDETAILS_FIELD_DESC)==0)
          parse_ShippingDetailsStruct(&((*pPtr)->PSP_SHIPPINGDETAILS_FIELD), doc, cur);
        if (strcmp(cur->name, PSP_ORDERDETAILS_FIELD_DESC)==0)
          parse_OrderDetailsStruct(&((*pPtr)->PSP_ORDERDETAILS_FIELD), doc, cur);
        if (strcmp(cur->name, PSP_AIRLINEDETAILS_FIELD_DESC)==0)
          parse_AirlineDetailsStruct(&((*pPtr)->PSP_AIRLINEDETAILS_FIELD), doc, cur);
      }      
	
    }
    cur = cur->next;
   }
   return ;
}
void parse_RespuestaStruct_QueryTxs_Transactions(RESPUESTASTRUCT_QUERYTXS_TRANSACTIONS **pPtr, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  
  Log(DEBUG, "parse_RespuestaStruct_QueryTxs_Transactions Init");
  cur = a_node->children;
  if (cur)
    *pPtr=(char*)calloc(sizeof(RESPUESTASTRUCT_QUERYTXS_TRANSACTIONS), sizeof(RESPUESTASTRUCT_QUERYTXS_TRANSACTIONS));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      if (varValue) {
        if (strcmp(cur->name, PSP_RESPONSECOD_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_RESPONSECOD_FIELD);
        if (strcmp(cur->name, PSP_RESPONSEMSG_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_RESPONSEMSG_FIELD);
        if (strcmp(cur->name, PSP_RESPONSEEXTENDED_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_RESPONSEEXTENDED_FIELD);
        if (strcmp(cur->name,PSP_TRANSACTIONID_FIELD_DESC )==0)
          varPtr=(char**)&((*pPtr)->PSP_TRANSACTIONID_FIELD);
        if (strcmp(cur->name, PSP_MERCHANTID_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_MERCHANTID_FIELD);
        if (strcmp(cur->name, PSP_TXSOURCE_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_TXSOURCE_FIELD);
        if (strcmp(cur->name, PSP_OPERATION_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_OPERATION_FIELD);
        if (strcmp(cur->name, PSP_MERCHTXREF_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_MERCHTXREF_FIELD);
        if (strcmp(cur->name, PSP_MERCHORDERID_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_MERCHORDERID_FIELD);
        if (strcmp(cur->name, PSP_MERCHADDITIONALREF_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_MERCHADDITIONALREF_FIELD);
        if (strcmp(cur->name, PSP_AMOUNT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_AMOUNT_FIELD);
        if (strcmp(cur->name, PSP_NUMPAYMENTS_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_NUMPAYMENTS_FIELD);
        if (strcmp(cur->name, PSP_PAYMENTAMOUNT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_PAYMENTAMOUNT_FIELD);
        if (strcmp(cur->name, PSP_FIRSTPAYMENTDEFERRAL_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_FIRSTPAYMENTDEFERRAL_FIELD);
        if (strcmp(cur->name, PSP_CURRENCY_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CURRENCY_FIELD);
        if (strcmp(cur->name,PSP_COUNTRY_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_COUNTRY_FIELD);
        if (strcmp(cur->name, PSP_PRODUCT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_PRODUCT_FIELD);
        if (strcmp(cur->name,PSP_AUTHORIZATIONCODE_FIELD_DESC)==0) 
          varPtr=(char**)&((*pPtr)->PSP_AUTHORIZATIONCODE_FIELD);
        if (strcmp(cur->name, PSP_BATCHNRO_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_BATCHNRO_FIELD);
        if (strcmp(cur->name, PSP_SEQUENCENUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_SEQUENCENUMBER_FIELD);
        if (strcmp(cur->name, PSP_TICKETNUMBER_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_TICKETNUMBER_FIELD);
        if (strcmp(cur->name, PSP_CARDNUMBER_FSD_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CARDNUMBER_FSD_FIELD);
        if (strcmp(cur->name, PSP_CARDNUMBER_LFD_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CARDNUMBER_LFD_FIELD);
        if (strcmp(cur->name, PSP_CARDMASK_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CARDMASK_FIELD);
        if (strcmp(cur->name, PSP_CARDHOLDERNAME_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CARDHOLDERNAME_FIELD);
        if (strcmp(cur->name, PSP_CUSTOMERMAIL_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CUSTOMERMAIL_FIELD);
        if (strcmp(cur->name, PSP_CUSTOMERID_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CUSTOMERID_FIELD);
        if (strcmp(cur->name, PSP_CUSTOMERIPADDRESS_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CUSTOMERIPADDRESS_FIELD);
        if (strcmp(cur->name, PSP_CUSTOMERHTTPUSERAGENT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CUSTOMERHTTPUSERAGENT_FIELD);
        if (strcmp(cur->name, PSP_MERCHANTMAIL_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_MERCHANTMAIL_FIELD);
        if (strcmp(cur->name, PSP_CLTRNID_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CLTRNID_FIELD);
        if (strcmp(cur->name, PSP_CLEXTERNALMERCHANT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CLEXTERNALMERCHANT_FIELD);
        if (strcmp(cur->name, PSP_CLEXTERNALTERMINAL_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CLEXTERNALTERMINAL_FIELD);
        if (strcmp(cur->name, PSP_CLRESPONSECOD_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CLRESPONSECOD_FIELD);
        if (strcmp(cur->name, PSP_CLRESPONSEMSG_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CLRESPONSEMSG_FIELD);
        if (strcmp(cur->name, PSP_POSDATETIME_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_POSDATETIME_FIELD);
        if (strcmp(cur->name, PSP_PURCHASEDESCRIPTION_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_PURCHASEDESCRIPTION_FIELD);
        if (strcmp(cur->name, PSP_SOFTDESCRIPTOR_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_SOFTDESCRIPTOR_FIELD);
        if (strcmp(cur->name, PSP_PLAN_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_PLAN_FIELD);
        if (strcmp(cur->name, PSP_VISAARG_VBV_SECURED_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_VISAARG_VBV_SECURED_FIELD);
        if (strcmp(cur->name, PSP_3DSECURE_XID_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_3DSECURE_XID_FIELD);
        if (strcmp(cur->name, PSP_3DSECURE_CAVV_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_3DSECURE_CAVV_FIELD);
        if (strcmp(cur->name, PSP_3DSECURE_Eci_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_3DSECURE_Eci_FIELD);
        if (strcmp(cur->name, PSP_3DSECURE_ECIMSG_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_3DSECURE_ECIMSG_FIELD);
        if (strcmp(cur->name, PSP_3DSECURE_SECURED_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_3DSECURE_SECURED_FIELD);
        if (strcmp(cur->name, PSP_VISAARG_DA_RESULT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_VISAARG_DA_RESULT_FIELD);
        if (strcmp(cur->name, PSP_AMEXARG_AVS_RESULT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_AMEXARG_AVS_RESULT_FIELD);
        if (strcmp(cur->name, PSP_MASTERARG_AVS_RESULT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_MASTERARG_AVS_RESULT_FIELD);
        if (strcmp(cur->name, PSP_CREATEDAT_FIELD_DESC)==0)
          varPtr=(char**)&((*pPtr)->PSP_CREATEDAT_FIELD);
        SetResponseValue(varPtr, varValue);
      }
      else {
        if (strcmp(cur->name, PSP_AMOUNTADDITIONALDETAILS_FIELD_DESC)==0)
          parse_AmountAdditionalDetailsResponseStruct(&((*pPtr)->PSP_AMOUNTADDITIONALDETAILS_FIELD), doc, cur);
        if (strcmp(cur->name, PSP_FRAUDSCREENINGRESULT_FIELD_DESC)==0)
          parse_FraudScreeningResultStruct(&((*pPtr)->PSP_FRAUDSCREENINGRESULT_FIELD), doc, cur);
        if (strcmp(cur->name, PSP_VERIFICATIONSERVICESRESULT_FIELD_DESC)==0)
          parse_VerificationServicesResultStruct(&((*pPtr)->PSP_VERIFICATIONSERVICESRESULT_FIELD), doc, cur);
        if (strcmp(cur->name, PSP_MERCHANTADDITIONALDETAILS_FIELD_DESC)==0)
          parse_MerchantAdditionalDetailsStruct(&((*pPtr)->PSP_MERCHANTADDITIONALDETAILS_FIELD), doc, cur);
        if (strcmp(cur->name, PSP_CUSTOMERADDITIONALDETAILS_FIELD_DESC)==0)
          parse_CustomerAdditionalDetailsStruct(&((*pPtr)->PSP_CUSTOMERADDITIONALDETAILS_FIELD), doc, cur);
        if (strcmp(cur->name, PSP_BILLINGDETAILS_FIELD_DESC)==0)
          parse_BillingDetailsStruct(&((*pPtr)->PSP_BILLINGDETAILS_FIELD), doc, cur);
        if (strcmp(cur->name, PSP_SHIPPINGDETAILS_FIELD_DESC)==0)
          parse_ShippingDetailsStruct(&((*pPtr)->PSP_SHIPPINGDETAILS_FIELD), doc, cur);
        if (strcmp(cur->name, PSP_ORDERDETAILS_FIELD_DESC)==0)
          parse_OrderDetailsStruct(&((*pPtr)->PSP_ORDERDETAILS_FIELD), doc, cur);
        if (strcmp(cur->name, PSP_AIRLINEDETAILS_FIELD_DESC)==0)
          parse_AirlineDetailsStruct(&((*pPtr)->PSP_AIRLINEDETAILS_FIELD), doc, cur);
      }      
	
    }
    cur = cur->next;
   }
   return ;
}

void parse_ArrayOf_RespuestaStruct_QueryTxs_Transactions(ARRAYOF_RESPUESTASTRUCT_QUERYTXS_TRANSACTIONS **pTransactions, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  RESPUESTASTRUCT_QUERYTXS_TRANSACTIONS *pPtr;
  int i=0, needSize;
  
  Log(DEBUG, "parse_ArrayOf_RespuestaStruct_QueryTxs_Transactions Init");
  cur = a_node->children;
  if (cur)
    *pTransactions=(char*)calloc(sizeof(ARRAYOF_RESPUESTASTRUCT_QUERYTXS_TRANSACTIONS), sizeof(ARRAYOF_RESPUESTASTRUCT_QUERYTXS_TRANSACTIONS));

  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   node type: Element, name: %s, VALUE %s",cur->name, varValue);
      
      if (strcmp(cur->name, "item")==0) {
	
	needSize=sizeof(RESPUESTASTRUCT_QUERYTXS_TRANSACTIONS *)*(i+1);
	
        if (i==0)
          (*pTransactions)->__ptr=(RESPUESTASTRUCT_QUERYTXS_TRANSACTIONS *)malloc(needSize);
        else
          (*pTransactions)->__ptr=realloc((*pTransactions)->__ptr,needSize);
	
        parse_RespuestaStruct_QueryTxs_Transactions(&((*pTransactions)->__ptr[i]), doc, cur);
	i++;
      }
    }
    cur = cur->next;
   }
   
   if (i>0)
     (*pTransactions)->__size=i;
   
   return ;
  
}

void parseResponse(int type, char *pResponse, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  int i, respFound=0, needSize;
  int envField = getEnvironment();
  Log(DEBUG, "parseResponse type %s", GET_SOAP_ACTION(type), npsEnvDesc[envField]);
  
  memset(pResponse, 0, methodsRespFields[type-1].structSize);
  
  cur=GetRespuestaPtr(doc, a_node);
  
  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "node type: Element, name: %s, VALUE %s",cur->name, varValue);
      
      if (varValue) {
        i=GetRespFieldIdxByDesc(cur->name, type, pResponse);
        if (i>=0) {
          varPtr=(char*) pResponse + methodsRespFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
	
	  *varPtr=(char *)calloc(strlen(varValue)+1, sizeof(char));
	  strcpy(*varPtr, varValue);
	}
      }
      else {
        if (strcmp(cur->name, PSP_AMOUNTADDITIONALDETAILS_FIELD_DESC)==0) {
          i=GetRespFieldIdxByDesc(cur->name, type, pResponse);
          if (i>=0) {
            varPtr=(char*) pResponse + methodsRespFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
            parse_AmountAdditionalDetailsResponseStruct(varPtr, doc, cur);
          }
        }
	
        if (strcmp(cur->name, PSP_FRAUDSCREENINGRESULT_FIELD_DESC)==0) {
          i=GetRespFieldIdxByDesc(cur->name, type, pResponse);
          if (i>=0) {
            varPtr=(char*) pResponse + methodsRespFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
            parse_FraudScreeningResultStruct(varPtr, doc, cur);
          }
	}
        if (strcmp(cur->name, PSP_VERIFICATIONSERVICESRESULT_FIELD_DESC)==0) {
          i=GetRespFieldIdxByDesc(cur->name, type, pResponse);
          if (i>=0) {
            varPtr=(char*) pResponse + methodsRespFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
            parse_VerificationServicesResultStruct(varPtr, doc, cur);
          }
	}
        if (strcmp(cur->name, PSP_TRANSACTIONS_FIELD_DESC)==0) {
          i=GetRespFieldIdxByDesc(cur->name, type, pResponse);
          if (i>=0) {
            varPtr=(char*) pResponse + methodsRespFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
            parse_ArrayOf_RespuestaStruct_SplitPayOnLine_2p_Transactions(varPtr, doc, cur);
          }
	}
        if (strcmp(cur->name, PSP_PAYMENTMETHOD_FIELD_DESC)==0) {
          i=GetRespFieldIdxByDesc(cur->name, type, pResponse);
          if (i>=0) {
            varPtr=(char*) pResponse + methodsRespFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
            parse_PaymentMethodOutputDetailsStruct(varPtr, doc, cur);
          }
	}
        if (strcmp(cur->name, PSP_CARDOUTPUTDETAILS_FIELD_DESC)==0) {
          i=GetRespFieldIdxByDesc(cur->name, type, pResponse);
          if (i>=0) {
            varPtr=(char*) pResponse + methodsRespFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
	    parse_CardOutputDetailsStruct(varPtr, doc, cur);
          }
	}
        if (strcmp(cur->name, PSP_PERSON_FIELD_DESC)==0) {
          i=GetRespFieldIdxByDesc(cur->name, type, pResponse);
          if (i>=0) {
            varPtr=(char*) pResponse + methodsRespFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
	    parse_PersonStruct(varPtr, doc, cur);
          }
	}
        if (strcmp(cur->name, PSP_ADDRESS_FIELD_DESC)==0) {
          i=GetRespFieldIdxByDesc(cur->name, type, pResponse);
          if (i>=0) {
            varPtr=(char*) pResponse + methodsRespFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
	    parse_AddressStruct(varPtr, doc, cur);
          }
	}
        if (strcmp(cur->name, PSP_PAYMENTMETHODS_FIELD_DESC)==0) {
          i=GetRespFieldIdxByDesc(cur->name, type, pResponse);
          if (i>=0) {
            varPtr=(char*) pResponse + methodsRespFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
	    parse_ArrayOf_PaymentMethodsOutputDetailsStruct(varPtr, doc, cur);
          }
	}
        if (strcmp(cur->name, PSP_TRANSACTION_FIELD_DESC)==0) {
          i=GetRespFieldIdxByDesc(cur->name, type, pResponse);
          if (i>=0) {
            varPtr=(char*) pResponse + methodsRespFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
	    parse_RespuestaStruct_SimpleQueryTx_Transactions(varPtr, doc, cur);
          }
	}
        if (strcmp(cur->name, PSP_TRANSACTIONS_FIELD_DESC)==0) {
          i=GetRespFieldIdxByDesc(cur->name, type, pResponse);
          if (i>=0) {
            varPtr=(char*) pResponse + methodsRespFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
	    parse_ArrayOf_RespuestaStruct_QueryTxs_Transactions(varPtr, doc, cur);
          }
	}
      }

    }
   
        cur = cur->next;
   }
    
}
    
