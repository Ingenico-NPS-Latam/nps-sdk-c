#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <md5.h>
#include <openssl/hmac.h>
#include <time.h>
#include <assert.h>
#include <stdarg.h>            /* var...                */
#include "nps_utils.h"

struct hashItem{
  char *varName;
  char *varValue;
};

struct table2HashStruct{
  int count;
  struct hashItem **info;
};

struct table2HashStruct table2Hash, *ptable2Hash;

void LogInit( enum log_level type, char * LogFileName , FILE  * logFd)
{
    char   MISC_LogFileName [ 512 ] ;
    int    i;
    
    debug=1;
    
    if ( logFd != NULL ) {
      LogFd = logFd;
    }
    else {
      if ( LogFileName != NULL && LogFileName [ 0 ] != '\0' ) {

        strncpy ( MISC_LogFileName, LogFileName, sizeof ( MISC_LogFileName ) ) ;
        if ( MISC_LogFileName [ 0 ] != '\0' ) {
            if ( LogFd != stdout && LogFd != NULL ) {
                fclose ( LogFd ) ;
	    }

            LogFd= fopen ( MISC_LogFileName, "a" ) ;
	    if (LogFd)
              strncpy ( MISC_LoggerFileName, LogFileName, sizeof ( MISC_LogFileName ) ) ;

	}

      }
    }

    if ( LogFd == NULL ) {
        LogFd = stdout;
    }
}



void LogClose ( void )
{

    if ( LogFd != stdout && LogFd != NULL ) {
        fclose ( LogFd ) ;
    }

    LogFd = NULL ;

   return ;

}

void writeLog( enum log_level type,  const char *Format, ... )
{
  char         stext [ MAX_LEN_LINE ] ;
  time_t       Moment;
  va_list      ArgList;
  char         MomentStr[ 18 ];
  
    if ( Format != NULL && *Format != '\0' ) {
      va_start( ArgList,   Format );
      vsprintf(stext, Format, ArgList);
      va_end(   ArgList );
    }
    
    if ( Format != NULL && *Format != '\0' ) {
          if ( LogFd == NULL ) {
            LogFd = stdout;
          }
            va_start( ArgList,   Format );
            Moment = time( NULL );
            strftime( MomentStr, sizeof( MomentStr ), "%y/%m/%d %H:%M:%S", localtime( &Moment ) );
            fprintf( LogFd, "%s ",  MomentStr );
            vfprintf( LogFd, Format, ArgList );
            fprintf( LogFd, "\n" );
            fflush(  LogFd );
            va_end(   ArgList );
    }  
}

void MaskCardNumber(char *buffer, char *tagFrom, char *tagTo)
{
  char * sch=buffer;
  char * ech=buffer+strlen(buffer);
  char * ptr=buffer;
  int i=0;
  int j=0;
  int cardNumberLen=0;
  int maskLen=0;

  while (i< strlen(buffer)) {
    
    if(!(sch = strstr(buffer+i, tagFrom)))
      return;
    
    if (tagTo != NULL) {
      if(!(ech = strstr(buffer+i+strlen(tagFrom), tagTo)))
        return;
    }
    
    cardNumberLen=ech-(sch+strlen(tagFrom));
    maskLen=cardNumberLen-8;
    
    ptr=sch + strlen(tagFrom) + 4;
    
    for (j=0;j<maskLen;j++) {
      ptr[j]='#';
    }
    
    if (tagFrom != NULL) {
      i=(ech+strlen(tagFrom))-buffer;
    } else {
      i=strlen(buffer);
    }
    
  }
  buffer[strlen(buffer)]='\0';
}

void MaskExpDate(char *buffer, char *tagFrom, char *tagTo)
{
  char * sch=buffer;
  char * ech=buffer+strlen(buffer);
  char * ptr=buffer;
  int i=0;
  int j=0;
  int expDateLen=0;
  int maskLen=0;
  while (i< strlen(buffer)) {
    if(!(sch = strstr(buffer+i, tagFrom)))
      return;
    
    if (tagTo != NULL) {
      if(!(ech = strstr(buffer+i+strlen(tagFrom), tagTo)))
        return;
    }
    
    expDateLen=ech-(sch+strlen(tagFrom));
    maskLen=expDateLen;
    
    ptr=sch + strlen(tagFrom);
    for (j=0;j<maskLen;j++) {
      ptr[j]='#';
    }
    i=(ech+strlen(tagFrom))-buffer;
    
  }
  buffer[strlen(buffer)]='\0';
  
  return;
}
void MaskCvc(char *buffer, char *tagFrom, char *tagTo)
{
  char * sch=buffer;
  char * ech=buffer+strlen(buffer);
  char * ptr=buffer;
  int i=0;
  int j=0;
  int cvcLen=0;
  int maskLen=0;
  while (i< strlen(buffer)) {
    if(!(sch = strstr(buffer+i, tagFrom)))
      return;
    
    if (tagTo != NULL) {
      if(!(ech = strstr(buffer+i+strlen(tagFrom), tagTo)))
        return;
    }
    
    cvcLen=ech-(sch+strlen(tagFrom));
    maskLen=cvcLen;
    
    ptr=sch + strlen(tagFrom);
    for (j=0;j<maskLen;j++) {
      ptr[j]='#';
    }
    i=(ech+strlen(tagFrom))-buffer;
    
  }
  buffer[strlen(buffer)]='\0';
  
  return;
}
void MaskTokenCardNumber(char *buffer, char *tagFrom, char *tagTo)
{
  char * sch=buffer;
  char * ech=buffer+strlen(buffer);
  char * ptr=buffer;
  int i=0;
  int j=0;
  int TokenCardNumberLen=0;
  int maskLen=0;
  while (i< strlen(buffer)) {
    if(!(sch = strstr(buffer+i, tagFrom)))
      return;
    
    if (tagTo != NULL) {
      if(!(ech = strstr(buffer+i+strlen(tagFrom), tagTo)))
        return;
    }
    
    TokenCardNumberLen=ech-(sch+strlen(tagFrom));
    maskLen=TokenCardNumberLen-strlen(tagFrom);
    
    ptr=sch + strlen(tagFrom);
    for (j=0;j<maskLen;j++) {
      ptr[j]='#';
    }
    i=(ech+strlen(tagFrom))-buffer;
    
  }
  buffer[strlen(buffer)]='\0';
  
  
  return;
}
void MaskTokenExpDate(char *buffer, char *tagFrom, char *tagTo)
{
  char * sch=buffer;
  char * ech=buffer+strlen(buffer);
  char * ptr=buffer;
  int i=0;
  int j=0;
  int expDateLen=0;
  int maskLen=0;
  
  while (i< strlen(buffer)) {
    if(!(sch = strstr(buffer+i, tagFrom)))
      return;
    
    if (tagTo != NULL) {
      if(!(ech = strstr(buffer+i+strlen(tagFrom), tagTo)))
        return;
    }
    
    expDateLen=ech-(sch+strlen(tagFrom));
    maskLen=expDateLen;
    
    ptr=sch + strlen(tagFrom);
    for (j=0;j<maskLen;j++) {
      ptr[j]='#';
    }
    i=(ech+strlen(tagFrom))-buffer;
    
  }
  buffer[strlen(buffer)]='\0';
  
  return;
}
void MaskTokenCvc(char *buffer, char *tagFrom, char *tagTo)
{
  char * sch=buffer;
  char * ech=buffer+strlen(buffer);
  char * ptr=buffer;
  int i=0;
  int j=0;
  int cvcLen=0;
  int maskLen=0;
  
  while (i< strlen(buffer)) {
    if(!(sch = strstr(buffer+i, tagFrom)))
      return;
    
    if (tagTo != NULL) {  
      if(!(ech = strstr(buffer+i+strlen(tagFrom), tagTo)))
        return;
    }
    
    cvcLen=ech-(sch+strlen(tagFrom));
    maskLen=cvcLen;
    
    ptr=sch + strlen(tagFrom);
    for (j=0;j<maskLen;j++) {
      ptr[j]='#';
    }
    i=(ech+strlen(tagFrom))-buffer;
    
  }
  buffer[strlen(buffer)]='\0';
  
  return;
}

int MaskData(char *dest, char *orig)
{
   
   sprintf(dest,"%s", orig);
   MaskCardNumber(dest, "<psp_CardNumber>", "</psp_CardNumber>");
   MaskCardNumber(dest, "psp_CardNumber = ", NULL);
   
   MaskExpDate(dest, "<psp_CardExpDate>", "</psp_CardExpDate>");
   MaskExpDate(dest, "psp_CardExpDate = ", NULL);
   
   MaskCvc(dest, "<psp_CardSecurityCode>","</psp_CardSecurityCode>" );
   MaskCvc(dest, "psp_CardSecurityCode = ",NULL );
   
   MaskTokenCardNumber(dest, "<Number>", "</Number>");
   MaskTokenCardNumber(dest, " Number = ", NULL);
   
   MaskTokenExpDate(dest, "<ExpirationDate>", "</ExpirationDate>");
   MaskTokenExpDate(dest, " ExpirationDate = ", NULL);
   
   MaskTokenCvc(dest, "<SecurityCode>", "</SecurityCode>");
   MaskTokenCvc(dest, " SecurityCode = ", NULL);
   
   return 0;
}

void Log(enum log_level type,  const char *Format, ... )
{ 
  int rc=0;
  char buffer[MAX_LEN_LINE];
  char stext[ MAX_LEN_LINE ] ;
  int logLevel;
  va_list args;
  va_start(args, Format);
    
  if (debug) {
    rc = vsnprintf( stext, MAX_LEN_LINE, Format, args );

    logLevel=getLogLevel();
    if (logLevel == DEBUG) {
      writeLog(type, stext);
    } else {
      if (logLevel ==  INFO && type != DEBUG) {
	MaskData(buffer, stext);
	writeLog(type, buffer);
	
      } else {
	
        if (type == ERROR) {
          MaskData(buffer, stext);
          writeLog(type, buffer);
        }
      }
    }
  }
	
  va_end(args);	
}

int compare(const void *s1, const void *s2)
{
    struct hashItem **a = (struct hashItem **)s1;
    struct hashItem **b = (struct hashItem **)s2;
    return(strcmp((*a)->varName, (*b)->varName));
}

   
void compute_md5(char *str, char *psp_SecureHash) {
  unsigned char digest[16];
  int i;
  
  Log(DEBUG,"compute_md5 Init");

  MD5_CTX ctx;
  MD5_Init(&ctx);
  MD5_Update(&ctx, str, strlen(str));
  MD5_Final(digest, &ctx);
  for(i = 0; i < 16; ++i)
     sprintf(&psp_SecureHash[i*2], "%02x", (unsigned int)digest[i]);    
}

void compute_hmac256(char *data, char *key, char *psp_SecureHash) {
  char res_hexstring[64];
  unsigned char *result;

  Log(DEBUG,"compute256_hmac Init");

  result = HMAC(EVP_sha256(), key, strlen(key), data, strlen(data), NULL, NULL);

  for (int i = 0; i < 32; i++) {
    sprintf(&psp_SecureHash[i*2], "%02x", result[i]);
  }
}

void compute_hmac512(char *data, char *key, char *psp_SecureHash) {
  char res_hexstring[128];
  unsigned char *result;

    Log(DEBUG,"compute512_hmac Init");

  result = HMAC(EVP_sha512(), key, strlen(key), data, strlen(data), NULL, NULL);

  for (int i = 0; i < 64; i++) {
    sprintf(&psp_SecureHash[i*2], "%02x", result[i]);
  }
}

int ConcatOrderValues(char *apiKey, char *pRequest, char **sortValues) {
  int i, valuesLen=0;

  Log(DEBUG,"ConcatOrderValues Init");
  for (i = 0; i < ptable2Hash->count; ++i){
    valuesLen+=strlen(ptable2Hash->info[i]->varValue);
  }

  *sortValues=(char*)calloc(valuesLen+1, sizeof(char));

  for (i = 0; i < ptable2Hash->count; ++i){
    sprintf(*sortValues, "%s%s",*sortValues,ptable2Hash->info[i]->varValue);
  }
  
  *sortValues=(char*)realloc(*sortValues, valuesLen+1+strlen(apiKey));
  sprintf(*sortValues, "%s%s",*sortValues,apiKey);

}

int GetFieldIdxByDesc(char *key, int type, char* pRequest, struct nps_generics *ptrFieldsType ) {
  char **ptr=NULL;
  int i, max_fields;
  char **structFieldsDesc;
  size_t *structFieldsOffset;
  
  int envField= getEnvironment();
  
  if (ptrFieldsType) {
    structFieldsDesc  = ptrFieldsType->structFieldsDesc;
    structFieldsOffset= ptrFieldsType->structFieldsOffset;
    max_fields        = ptrFieldsType->max_fields;
    
  } else {
    structFieldsDesc=methodsFields[type-1].structFieldsDesc;
    structFieldsOffset=methodsFields[type-1].structFieldsOffset;
    max_fields=methodsFields[type-1].max_fields;
  }
  
  for (i = 0; i < max_fields; i++)  {

    if ((int)structFieldsOffset[(i*ARR_OFFSET_COUNT)]<0) {
      break;
    }
    
    ptr=(char*) pRequest + structFieldsOffset[(i*ARR_OFFSET_COUNT)];
    if (structFieldsDesc[i]) {
      if ( strcmp(structFieldsDesc[i], key)==0) {
        return i;
      }
    }
    else {
      break;
    }
  }
  return -1;
}

int FillSortTable(int type, char *pRequest){
  
  char **ptr=NULL;
  int i, max_fields;
  char **structFieldsDesc;
  size_t *structFieldsOffset;
  int *structFieldsIdx; 
  struct nps_generics **structFieldsType;  
  struct hashItem **info=NULL;
  int envField=getEnvironment();
  
  structFieldsDesc=methodsFields[type-1].structFieldsDesc;
  structFieldsOffset=methodsFields[type-1].structFieldsOffset;
  structFieldsIdx=methodsFields[type-1].structFieldsIdx;
  structFieldsType=methodsFields[type-1].structFieldsType;
  max_fields=methodsFields[type-1].max_fields;
  Log(DEBUG,"FillSortTable Init max_fields [%d]",max_fields);

  ptable2Hash=&table2Hash;
  ptable2Hash->count=0;
  
  for (i = 0; i < max_fields; i++)  {
    
    if (!structFieldsDesc[i])
      break;
    
    if ((int)structFieldsOffset[(i*ARR_OFFSET_COUNT)+envField] < 0) {
      Log(ERROR, "structFieldsDesc[%s] not exist in [%s]",structFieldsDesc[i], npsEnvDesc[envField]);
      continue;
    }
    
    Log(DEBUG,"structFieldsDesc[%s]",structFieldsDesc[i]);
    if (!structFieldsType[i]) {
      //break;
    if (strcmp(structFieldsDesc[i],PSP_SECUREHASH_FIELD_DESC)!=0) {
      ptr=(char*) pRequest + structFieldsOffset[(i*ARR_OFFSET_COUNT)];
      if (*ptr) {
        info = (struct hashItem **)realloc(info, (ptable2Hash->count + 1) * sizeof(struct hashItem *));    
        info[ptable2Hash->count]=(struct hashItem *)malloc(sizeof(struct hashItem));
        info[ptable2Hash->count]->varName=(char*)malloc(strlen(structFieldsDesc[i])+1);
        strcpy(info[ptable2Hash->count]->varName, structFieldsDesc[i]);
        info[ptable2Hash->count]->varValue=(char*)malloc(strlen((char*)(*ptr))+1);
        strcpy(info[ptable2Hash->count]->varValue, (char*)(*ptr));
        ptable2Hash->count++;
      }
    }
    }
  }
    
  qsort(info, ptable2Hash->count, sizeof(struct hashItem*), compare);

  ptable2Hash->info=info;
  Log(DEBUG, "FillSortTable Exit");
  
}

int setSecureHash(int type,char *apiKey, char *pRequest) {
  int i;
  char *concatvalues=NULL;
  char *p=pRequest;
  char **secureHash=NULL;
  struct hashItem *info=NULL;
  size_t *structFieldsOffset;

  Log(DEBUG, "setSecureHash Init");
  
  i=GetFieldIdxByDesc(PSP_SECUREHASH_FIELD_DESC, type, pRequest, NULL);
  if (i<0) 
    return;

  FillSortTable(type, pRequest);
  
  ConcatOrderValues("", pRequest, &concatvalues);
  
  structFieldsOffset=methodsFields[type-1].structFieldsOffset;

  if (i>=0)
    secureHash=(char*) pRequest + structFieldsOffset[(i*ARR_OFFSET_COUNT)];
    
  if (!*secureHash) {
    *secureHash=(char *)calloc(65, sizeof(char));
  }

  compute_hmac256(concatvalues, apiKey, *secureHash);
  Log(DEBUG, "secureHash %s",*secureHash);
  
  if (!*secureHash) 
    Log(DEBUG, "secureHash NULL");
  else
    Log(DEBUG, "secureHash %s", *secureHash);
  
  for (i = 0; i < ptable2Hash->count; ++i){
    info=ptable2Hash->info[i];
    free(info->varName);
    free(info->varValue);
    free(info);
  }

  free(concatvalues);

}

int AddExtraInf(int type, char *pRequest) {
  char **structFieldsDesc;
  size_t *structFieldsOffset;
  struct nps_generics **structFieldsType;  
  struct nps_generics *ptrAux;
  char **ptr=NULL;
  int i;
  char **sdkInfo=NULL;
  
  structFieldsDesc=methodsFields[type-1].structFieldsDesc;
  structFieldsOffset=methodsFields[type-1].structFieldsOffset;
  structFieldsType=methodsFields[type-1].structFieldsType;
  
  Log(DEBUG, "AddExtraInf Init");
  i=GetFieldIdxByDesc(PSP_MERCHANTADDITIONALDETAILS_FIELD_DESC, type, pRequest, NULL);
  if (i<0) {
    Log(ERROR, "AddExtraInf [%s] not in request", PSP_MERCHANTADDITIONALDETAILS_FIELD_DESC);
    return;
  }

  //BORRAR
  Log(INFO, "AddExtraInf [%s] found at [%d]", PSP_MERCHANTADDITIONALDETAILS_FIELD_DESC, i);
  ptr=(char*) pRequest + methodsFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
  
  if (!*ptr) {
     Log(ERROR, "AddExtraInf [%s] not in request", PSP_MERCHANTADDITIONALDETAILS_FIELD_DESC);
    return;
  }
  ptrAux=structFieldsType[i];  
  structFieldsType=structFieldsType[i];  

  structFieldsOffset= ptrAux->structFieldsOffset;
  
  i=GetFieldIdxByDesc(SDKINFO_FIELD_DESC, type, *ptr, structFieldsType);
  if (i<0) {
    Log(ERROR, "AddExtraInf [%s] not in request.%s", SDKINFO_FIELD_DESC, PSP_MERCHANTADDITIONALDETAILS_FIELD_DESC);
    return;
  }
  
  if (i>=0)
    sdkInfo=(char*) *ptr + structFieldsOffset[(i*ARR_OFFSET_COUNT)];
  
  if (!*sdkInfo) {
    *sdkInfo=(char *)calloc(strlen(SDK_VERSION) + strlen(" Version: ") + strlen(SDK_NAME) + 1, sizeof(char));
    if (!*sdkInfo) {
      return;
    }
    memset(*sdkInfo, 0, sizeof(strlen(SDK_VERSION) + strlen(" Version: ") + strlen(SDK_NAME)));
  } else {
    if (strlen(*sdkInfo) < (strlen(SDK_VERSION) + strlen(SDK_NAME)+1)) {
      *sdkInfo=(char *)realloc(*sdkInfo,strlen(SDK_VERSION) + strlen(SDK_NAME) + 1);
    }
  }
  
  sprintf(*sdkInfo, "%s Version: %s", SDK_NAME, SDK_VERSION);
  
  if (!*sdkInfo) 
    Log(DEBUG, "sdkInfo done (NULL)");
  else
    Log(DEBUG, "sdkInfo done (%s)",*sdkInfo);
  
}

void CheckSanitizeTable(char *key, char **pValue) {
  sanitizeItemStruct *ptrSanitizeItem;
  int i=0;

  ptrSanitizeItem = &sanitizeTable[i];

  while (ptrSanitizeItem->key) {
    if (strcmp(key, ptrSanitizeItem->key)==0)
    {
      if (strlen(*pValue) > ptrSanitizeItem->max_size){
	Log(DEBUG, "\t\t%s=[%s] debe contener [%d]",ptrSanitizeItem->key, *pValue, ptrSanitizeItem->max_size);
	sprintf(*pValue,"%.*s",ptrSanitizeItem->max_size,*pValue);
	return;
      }
    }
    i++;
    ptrSanitizeItem = &sanitizeTable[i];
  }
}

void sanitizeStruct(char *pRequest, struct nps_generics *ptrFieldsType, char *key) {
  char **ptr, **sizeArr, **ptrArr;
  int i, j,max_fields;
  char **structFieldsDesc;
  size_t *structFieldsOffset;
  int *structFieldsIdx;
  char keyAux[MAX_SANITIZE_ITEM_KEY_LEN];
  struct nps_generics **structFieldsType;
  
  int envField = getEnvironment();
  
  if (!pRequest) {
    return;
  }
  
  Log(DEBUG, "sanitizeStruct key [%s]", key);
  if (ptrFieldsType) {
    structFieldsDesc  = ptrFieldsType->structFieldsDesc;
    structFieldsOffset= ptrFieldsType->structFieldsOffset;
    structFieldsIdx   = ptrFieldsType->structFieldsIdx;
    structFieldsType  = ptrFieldsType->structFieldsType;
    max_fields        = ptrFieldsType->max_fields;

    for (i = 0; i < max_fields; i++)  {
      if ((int)structFieldsOffset[(i*ARR_OFFSET_COUNT)+envField]<0) {
        Log(ERROR, "structFieldsDesc[%s] not exist in [%s]\n",structFieldsDesc[i], npsEnvDesc[envField]);
	continue;
      }
      
      ptr=pRequest + structFieldsOffset[(i*ARR_OFFSET_COUNT)];
      if (structFieldsType[i]) {
	if (strcmp(structFieldsDesc[i], ARRAY_PTR_FIELD_DESC)==0) {
	  sizeArr=pRequest + structFieldsOffset[i+1];
	  for (j = 0; j < (int *)(*sizeArr); j++)  {
	    ptrArr=*ptr + (structFieldsType[i]->structSize * j);
	    sanitizeStruct((char*)(*ptrArr), structFieldsType[i], key);
	  }
	}
	else
          sanitizeStruct((char *)(*ptr), structFieldsType[i], structFieldsDesc[i]);
	  //sanitizeStruct(ptr, structFieldsType[i], structFieldsDesc[i]);
      }
      else {
	if (strcmp(structFieldsDesc[i], ARRAY_SIZE_FIELD_DESC)!=0){
/*	  Log(DEBUG, "\t[%d] offset [%d] idx [%d] >> %s items %d", i, structFieldsOffset[(i*ARR_OFFSET_COUNT)], structFieldsIdx[i], structFieldsDesc[i], (int *)(*sizeArr) );
	}
	else {
         Log(DEBUG, "\t[%d] offset [%d] idx [%d] >> %s = %s (%d)",i, 
           structFieldsOffset[(i*ARR_OFFSET_COUNT)], 
           structFieldsIdx[i], 
           structFieldsDesc[i], 
           (char *)(*ptr)? (char *)(*ptr):"NULL", 
           (char *)(*ptr)? strlen((char *)(*ptr)):0);*/
         Log(DEBUG, "\t%s = %s", structFieldsDesc[i], (char *)(*ptr)? (char *)(*ptr):"NULL");
	 if ((char *)(*ptr)) {
	   sprintf(keyAux, "%s.%s", key, structFieldsDesc[i]);
	   CheckSanitizeTable(keyAux, ptr);
	 }
	}
      }
    }
  }
}

void sanitize(int type,char *pRequest) {
  char **ptr=NULL;
  int i, max_fields;
  char **structFieldsDesc;
  size_t *structFieldsOffset;
  int *structFieldsIdx;
  struct nps_generics **structFieldsType;
  int envField = getEnvironment();

  Log(DEBUG, "sanitize Init");
  structFieldsDesc=methodsFields[type-1].structFieldsDesc;
  structFieldsOffset=methodsFields[type-1].structFieldsOffset;
  structFieldsIdx=methodsFields[type-1].structFieldsIdx;
  structFieldsType=methodsFields[type-1].structFieldsType;
  max_fields=methodsFields[type-1].max_fields;
  
  if (structFieldsType) {
    Log(DEBUG,"structFieldsType NOT NULL maxfields[%d]", max_fields);
  }
  
  for (i = 0; i < max_fields; i++)  {

      if ((int)structFieldsOffset[(i*ARR_OFFSET_COUNT)+envField]<0) {
	continue;
      }
    
      ptr=(char*) pRequest + methodsFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
      if (structFieldsIdx[i]<0) 
	break;
      
      if (structFieldsType[i]) {
	sanitizeStruct((char *)(*ptr), structFieldsType[i], structFieldsDesc[i]);
      }
      else {
        /*Log(DEBUG, "[%d] offset [%d %d] idx [%d %d] >> %s %s = %s", i, 
	        methodsFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)],structFieldsOffset[(i*ARR_OFFSET_COUNT)], 
	        methodsFields[type-1].structFieldsIdx[i],structFieldsIdx[i], 
	        methodsFields[type-1].structFieldsDesc[i], structFieldsDesc[i], 
	        (char *)(*ptr));
	        */
	Log(DEBUG, "%s = %s", structFieldsDesc[i], (char *)(*ptr));
	CheckSanitizeTable( structFieldsDesc[i],(char *)(*ptr)); 
      }
  }
  Log(DEBUG, "sanitize Exit");
}

char *MaskFieldData(char *fieldValue, char *fieldName)
{
  char *ch;
  if (strcmp(fieldName, "psp_CardNumber") == 0) {
    printf("MaskCardNumber [%s]\n",fieldValue);
   MaskCardNumber(fieldValue, NULL, NULL);
   printf("MaskCardNumber [%s]\n",fieldValue);
  }
   ch=fieldValue;
   return ch;
}

void showRequestStruct(char *pStruct, struct nps_generics *ptrFieldsType, char *key, char *arrTab) {
  char **ptr, **sizeArr, **ptrArr;
  int i, j,max_fields, iSize;
  char **structFieldsDesc;
  size_t *structFieldsOffset;
  int *structFieldsIdx;
  char keyAux[MAX_SANITIZE_ITEM_KEY_LEN];
  int envField=getEnvironment();
  char fieldValue[1024];
  char tabAux[100];
  
  sprintf(tabAux, "%s  ",arrTab);
  
  struct nps_generics **structFieldsType;
  
  if (!pStruct) {
    return;
  }
  
  Log(INFO,"%s%s",arrTab,key);
  if (ptrFieldsType) {
    structFieldsDesc  = ptrFieldsType->structFieldsDesc;
    structFieldsOffset= ptrFieldsType->structFieldsOffset;
    structFieldsIdx   = ptrFieldsType->structFieldsIdx;
    structFieldsType  = ptrFieldsType->structFieldsType;
    max_fields        = ptrFieldsType->max_fields;
    Log(INFO,"  max_fields [%d]",max_fields);

    for (i = 0; i < max_fields; i++)  {
      if (!structFieldsDesc[i]) {
	return;
      }

      if (structFieldsType[i]) {
	
	if (strcmp(structFieldsDesc[i], ARRAY_PTR_FIELD_DESC)==0) {
	  ptr=pStruct + structFieldsOffset[i];
	  sizeArr=pStruct + structFieldsOffset[i+1];
	  iSize=(int *)*sizeArr;
	  for (j = 0; j < iSize; j++)  {
	    sprintf(keyAux, "[%d]",j);
	    ptrArr=*ptr + (structFieldsType[i]->structSize * j);
	    showRequestStruct((char*)(*ptrArr), structFieldsType[i], keyAux, tabAux);
	  }
	}
	else {
          if ((int)structFieldsOffset[(i*ARR_OFFSET_COUNT)+envField] < 0) {
            Log(ERROR,"\tstructFieldsDesc[%d]: %s not in [%s]", i, structFieldsDesc[i], npsEnvDesc[envField]);
            continue;
          }      

          ptr=pStruct + structFieldsOffset[(i*ARR_OFFSET_COUNT)];	  
          showRequestStruct((char *)(*ptr), structFieldsType[i], structFieldsDesc[i], tabAux);
	}
      }
      else {
	if (strcmp(structFieldsDesc[i], ARRAY_SIZE_FIELD_DESC)==0){
	  Log(INFO,"%s%s items %d", arrTab,structFieldsDesc[i], (int *)(*sizeArr) );
	}
	else {
          if ((int)structFieldsOffset[(i*ARR_OFFSET_COUNT)+envField] < 0) {
            Log(ERROR,"\tstructFieldsDesc[%d]: %s not in [%s]", i, structFieldsDesc[i], npsEnvDesc[envField]);
            continue;
          }      

          ptr=pStruct + structFieldsOffset[i*ARR_OFFSET_COUNT];	  
          if ((char*)(*ptr)) {
            sprintf(fieldValue, "%s", (char *)(*ptr));
            //Log(INFO,"%s%s = %s", arrTab, structFieldsDesc[i], MaskFieldData(fieldValue, structFieldsDesc[i]));
	    Log(INFO,"%s%s = %s", arrTab, structFieldsDesc[i], fieldValue);
          }
          else {
            Log(INFO,"%s%s = %s", arrTab, structFieldsDesc[i], "(null)");
          }
	  
	}
      }
    }
  }
}

void showRequest(int type,char *pRequest) {
  char **ptr=NULL;
  int i, max_fields, j, envField, offset;
  char **structFieldsDesc;
  size_t *structFieldsOffset;
  struct nps_generics **structFieldsType;
  char fieldValue[1024];

  envField=getEnvironment();
  Log(INFO,"********************* showRequest **********************************");
  Log(INFO,"showRequest: %s env[%d]", GET_SOAP_ACTION(type), envField);
  structFieldsDesc=methodsFields[type-1].structFieldsDesc;
  structFieldsOffset=methodsFields[type-1].structFieldsOffset;
  structFieldsType=methodsFields[type-1].structFieldsType;
  max_fields=methodsFields[type-1].max_fields;

  Log(INFO,"showRequest: max_fields %d envField[%d]", max_fields, envField);
  
  for (i = 0; i < max_fields; i++)  {
      if (!structFieldsDesc[i]) {
        break;
      }

      offset=(i*ARR_OFFSET_COUNT)+envField;
      
      if ((long)(structFieldsOffset[offset]) < 0) {
	Log(ERROR,"  structFieldsDesc[%d]: %s not in [%s]", i, structFieldsDesc[i], npsEnvDesc[envField]);
	continue;
      }
      
      offset=i*ARR_OFFSET_COUNT;

      ptr=(char*) pRequest + methodsFields[type-1].structFieldsOffset[offset];
      
      if (structFieldsType[i]) {
	      showRequestStruct((char *)(*ptr), structFieldsType[i], structFieldsDesc[i], "  ");
      }
      else {
        if ((char*)(*ptr)) {
          sprintf(fieldValue, "%s", (char *)(*ptr));
          Log(INFO,"  %s = %s", structFieldsDesc[i], fieldValue);
        }
        else {
          Log(INFO,"  %s = %s", structFieldsDesc[i], "(null)");
        }
      }
  }
  Log(INFO,"********************* showRequest End**********************************");
}

void showResponse(int type,char *pResponse) {
  char **ptr=NULL;
  int i, max_fields, j, envField, offset;
  char **structFieldsDesc;
  size_t *structFieldsOffset;
  struct nps_generics **structFieldsType;
  char fieldValue[1024];

  envField=getEnvironment();
  Log(INFO,"********************* showResponse **********************************");
  Log(INFO,"showResponse: %s env[%d]", GET_SOAP_ACTION(type), envField);
  structFieldsDesc=methodsRespFields[type-1].structFieldsDesc;
  structFieldsOffset=methodsRespFields[type-1].structFieldsOffset;
  structFieldsType=methodsRespFields[type-1].structFieldsType;
  max_fields=methodsRespFields[type-1].max_fields;

  Log(INFO,"showResponse: max_fields %d envField[%d]", max_fields, envField);
  
  for (i = 0; i < max_fields; i++)  {
      if (!structFieldsDesc[i]) {
	break;
      }
      
      offset=(i*ARR_OFFSET_COUNT)+envField;
      
      if ((long)(structFieldsOffset[offset]) < 0) {
	Log(ERROR,"  structFieldsDesc[%d]: %s not in [%s]", i, structFieldsDesc[i], npsEnvDesc[envField]);
	continue;
      }
      
      offset=i*ARR_OFFSET_COUNT;
      ptr=(char*) pResponse + structFieldsOffset[offset];
      if (structFieldsType[i]) {
	showRequestStruct((char *)(*ptr), structFieldsType[i], structFieldsDesc[i], "  ");
      }
      else {
        if ((char*)(*ptr)) {
          sprintf(fieldValue, "%s", (char *)(*ptr));
          Log(INFO,"  %s = %s", structFieldsDesc[i], fieldValue);
        }
        else {
          Log(INFO,"  %s = %s", structFieldsDesc[i], "(null)");
        }
	
      }
  }
  
  Log(INFO,"********************* showResponse End **********************************");
}
	
void checkEnvFieldsStruct(char *pStruct, struct nps_generics *ptrFieldsType, char *key, char *arrTab) {
  char **ptr, **sizeArr, **ptrArr;
  int i, j,max_fields;
  char **structFieldsDesc;
  size_t *structFieldsOffset;
  int *structFieldsIdx;
  char keyAux[MAX_SANITIZE_ITEM_KEY_LEN];
  int envField=getEnvironment();
  
  struct nps_generics **structFieldsType;
  
  if (!pStruct) {
    return;
  }
  
  if (ptrFieldsType) {
    structFieldsDesc  = ptrFieldsType->structFieldsDesc;
    structFieldsOffset= ptrFieldsType->structFieldsOffset;
    structFieldsIdx   = ptrFieldsType->structFieldsIdx;
    structFieldsType  = ptrFieldsType->structFieldsType;
    max_fields        = ptrFieldsType->max_fields;

    for (i = 0; i < max_fields; i++)  {
      if (!structFieldsDesc[i]) {
	return;
      }

      if (structFieldsType[i]) {
	
	if (strcmp(structFieldsDesc[i], ARRAY_PTR_FIELD_DESC)==0) {
	  ptr=pStruct + structFieldsOffset[i];
	  sizeArr=pStruct + structFieldsOffset[i+1];
	  for (j = 0; j < (int *)(*sizeArr); j++)  {
	    sprintf(keyAux, "[%d]",j);
	    ptrArr=*ptr + (structFieldsType[i]->structSize * j);
	    checkEnvFieldsStruct((char*)(*ptrArr), structFieldsType[i], keyAux, "  ");
	  }
	}
	else {
          ptr=pStruct + structFieldsOffset[(i*ARR_OFFSET_COUNT)];	  
          if ((int)structFieldsOffset[(i*ARR_OFFSET_COUNT)+envField] < 0) {
            Log(ERROR,"\t1 structFieldsDesc[%d]: %s not in [%s]", i, structFieldsDesc[i], npsEnvDesc[envField]);
	    free(*ptr);
	    *ptr=0;
            continue;
          }      

          checkEnvFieldsStruct((char *)(*ptr), structFieldsType[i], structFieldsDesc[i],"");
	}
      }
      else {
	if (strcmp(structFieldsDesc[i], ARRAY_SIZE_FIELD_DESC)!=0){
	  ptr=pStruct + structFieldsOffset[(i*ARR_OFFSET_COUNT)]; 
          if ((int)structFieldsOffset[(i*ARR_OFFSET_COUNT)+envField] < 0) {
            Log(ERROR,"\t2 structFieldsDesc[%d]: %s not in [%s]", i, structFieldsDesc[i], npsEnvDesc[envField]);
	    free(*ptr);
	    *ptr=0;
            continue;
          }      
	  
	}
      }
    }
  }
}

void checkEnvFields(int type,char *pRequest) {
  char **ptr=NULL;
  int i, max_fields, j, envField, offset;
  char **structFieldsDesc;
  size_t *structFieldsOffset;
  struct nps_generics **structFieldsType;

  envField=getEnvironment();
  Log(DEBUG,"checkEnvFields: %s env[%d]", GET_SOAP_ACTION(type), envField);
  structFieldsDesc=methodsFields[type-1].structFieldsDesc;
  structFieldsOffset=methodsFields[type-1].structFieldsOffset;
  structFieldsType=methodsFields[type-1].structFieldsType;
  max_fields=methodsFields[type-1].max_fields;

  Log(DEBUG,"checkEnvFields: max_fields %d envField[%d]", max_fields, envField);
  
  for (i = 0; i < max_fields; i++)  {
      if (!structFieldsDesc[i]) {
	break;
      }

      offset=(i*ARR_OFFSET_COUNT)+envField;
      
      if ((long)(structFieldsOffset[offset]) < 0) {
	Log(DEBUG,"structFieldsDesc[%d]: %s not in [%s]", i, structFieldsDesc[i], npsEnvDesc[envField]);
        offset=i*ARR_OFFSET_COUNT;

        ptr=(char*) pRequest + methodsFields[type-1].structFieldsOffset[offset];
	free(*ptr);
	*ptr='0';
	continue;
      }
      
      offset=i*ARR_OFFSET_COUNT;

      ptr=(char*) pRequest + methodsFields[type-1].structFieldsOffset[offset];
      
      if (structFieldsType[i]) {
	checkEnvFieldsStruct((char *)(*ptr), structFieldsType[i], structFieldsDesc[i], "");
      }
  }
  Log(DEBUG,"checkEnvFields: done");
}

