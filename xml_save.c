#include "xml_save.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void new_buffer(struct Buffer *b) {
    b->data = (void*)malloc(INITIAL_SIZE);
    memset(b->data, '0', INITIAL_SIZE);
    b->size = INITIAL_SIZE;
    b->next = 0;

    return;
}

void reserve_space(struct Buffer *b, long bytes) {
    long new_size = b->next + bytes;
    if((new_size) > b->size) {
        b->data = realloc(b->data, new_size);
        b->size = new_size; 
    }
}

void serialize_string(char *eName, char *value, struct Buffer *b) {
  
  long need_size;
  char *buff;
  
  if (!value) {
    return;
  }

  /*<psp_NumPayments>1</psp_NumPayments>
   * <></> =5*/
  
  need_size=5;
  need_size+=strlen(eName)*2;
  need_size+=strlen(value);

  reserve_space(b, need_size);
 
  buff=(char *)calloc(need_size + 1, sizeof(char));
  
  sprintf(buff,"<%s>%s</%s>",eName, value, eName);
  
  memcpy(((char *)b->data) + b->next, buff, need_size);
  
  b->next += need_size;

  free(buff);
}

void serialize_open_node(char *eName, char *xsi_type, struct Buffer *b){
  int need_size;
  char *buff;
  
  if (!eName || !xsi_type) {
    return;
  }
  
  
  need_size=2+21;
  need_size+=strlen(eName);
  need_size+=strlen(xsi_type);
  reserve_space(b, need_size);
  
  buff=malloc(need_size+1);
  
  sprintf(buff,"<%s xmlns=\"\" xsi:type=\"%s\">",eName, xsi_type);
  
  memcpy(((char *)b->data) + b->next, buff, need_size);

  b->next += need_size;
  
  free(buff);
}


void serialize_close_node(char *eName, struct Buffer *b){
  int need_size;
  char *buff;
  
  if (!eName) {
    return;
  }
  
  /*</psp_AmountAdditionalDetails>
   * </eName>
   * len(</>)=3
   */
  need_size=3;
  need_size+=strlen(eName);
  reserve_space(b, need_size);
  
  buff=malloc(need_size+1);
  
  sprintf(buff,"</%s>",eName);
  memcpy(((char *)b->data) + b->next, buff, need_size);

  b->next += need_size;
  free(buff);
}

/*<eName xmlns="" xsi:type="SOAP-ENC:Array" SOAP-ENC:arrayType="tnsArrayType[count]">
 * eName=Taxes
 * tnsArrayType=tns:TaxesRequestStruct
 * count=2
 * len '< xmlns="" xsi:type="SOAP-ENC:Array" SOAP-ENC:arrayType="[]">' = 61
 * 
 */
void serialize_open_array(char *eName, char *tnsArrayType, int count, struct Buffer *b){
  int need_size, auxCount;
  char *buff;
  
  if (!eName || !tnsArrayType) {
    return;
  }
  
  need_size=61;
  need_size+=strlen(eName);
  need_size+=strlen(tnsArrayType);
  
  auxCount = count;
  while (auxCount) {
    need_size++;
    auxCount/=10;
  }
  
  reserve_space(b, need_size);
  
  buff=malloc(need_size+1);
  
  sprintf(buff,"<%s xmlns=\"\" xsi:type=\"SOAP-ENC:Array\" SOAP-ENC:arrayType=\"%s[%d]\">", eName,tnsArrayType,count);
  
  memcpy(((char *)b->data) + b->next, buff, need_size);

  b->next += need_size;
  
  free(buff);
}

void serialize_close_array(char *eName, struct Buffer *b){
  int need_size;
  char *buff;
  
  if (!eName) {
    return;
  }
  
  /*</psp_AmountAdditionalDetails>
   * </eName>
   * len(</>)=3
   */
  need_size=3;
  need_size+=strlen(eName);
  reserve_space(b, need_size);
  
  buff=malloc(need_size+1);
  
  sprintf(buff,"</%s>",eName);
  memcpy(((char *)b->data) + b->next, buff, need_size);

  b->next += need_size;
  free(buff);
}

void serialize_ArrayOf(char *xmlName, char *xsi_type, char *x, struct Buffer *output, struct nps_generics *ptrFieldsType, int sizeArr) {
    char **ptrArr, **ptrItem;
    char *xsiType;
    size_t *structFieldsOffset;
    int i;
    
    if (!x) {
      return;
    }
    if (ptrFieldsType) {    
      ptrArr=x;
      structFieldsOffset= ptrFieldsType->structFieldsOffset;
    
      xsiType=(char *) malloc(strlen("tns:") + strlen(xsi_type) + 1);
      sprintf(xsiType, "tns:%s", xsi_type);

      serialize_open_array(xmlName, xsiType, sizeArr, output);
    
      for (i = 0; i < sizeArr; ++i){
	ptrItem=*ptrArr + (ptrFieldsType->structSize * i);
	Log(DEBUG, "           %d- ptrItem[%d] *[%d]", i,ptrItem, *ptrItem);
        serialize_Structure("item", xsi_type, *ptrItem, output, ptrFieldsType);
      }
    
      serialize_close_array(xmlName, output);
    }
}


void serialize_Structure(char *xmlName, char *xsi_type, char *x, struct Buffer *output, struct nps_generics *ptrFieldsType){
  char **ptr=NULL, **ptrArr, **sizeArr;
  char **structFieldsDesc;
  size_t *structFieldsOffset;
  int *structFieldsIdx;
  struct nps_generics **structFieldsType,  **itemStructFieldsType;
  int i, max_fields;
  char fieldValue[1024];
  char *xsiType;
  int isArray=0;
  int openNode=0;
  
  if (!x) 
    return;
    
  Log(DEBUG, "serialize_Structure xmlName[%s] xsi_type[%s]", xmlName, xsi_type);
  if (ptrFieldsType) {    
    
    structFieldsOffset= ptrFieldsType->structFieldsOffset;
    structFieldsDesc  = ptrFieldsType->structFieldsDesc;
    structFieldsIdx   = ptrFieldsType->structFieldsIdx;
    structFieldsType  = ptrFieldsType->structFieldsType;
    max_fields        = ptrFieldsType->max_fields;
    Log(DEBUG, "serialize_Structure max_fields[%d]", max_fields);
    
    xsiType=(char *) malloc(strlen("tns:") + strlen(xsi_type) + 1);
    sprintf(xsiType, "tns:%s", xsi_type);
    
    if (strcmp(structFieldsDesc[0], ARRAY_PTR_FIELD_DESC)==0)  {
      isArray=1;
    }
    else {
      openNode=1;
      serialize_open_node(xmlName, xsiType, output);
    }
    
    for (i = 0; i < max_fields; i++)  {
      Log(DEBUG, "structFieldsDesc[%d][%s] of [%d]", i, structFieldsDesc[i],max_fields);
      if (!structFieldsDesc[i]) {
	break;
      }
      
      if (structFieldsType[i]) {
	
	if (strcmp(structFieldsDesc[i], ARRAY_PTR_FIELD_DESC)==0) {
	  Log(DEBUG,"structFieldsDesc[i] [%s] array...",structFieldsDesc[i]);
	  isArray=1;
          ptrArr= x + structFieldsOffset[0];
          sizeArr= x + structFieldsOffset[1];
	  ptr=*ptrArr;
          itemStructFieldsType=structFieldsType;
	  serialize_ArrayOf(xmlName, itemStructFieldsType[0]->structXsiType, (char *)ptrArr, output, itemStructFieldsType[0], (int *)(*sizeArr));
	}
	else {
	  if (structFieldsType[i]->max_fields == 2) {
	    if (structFieldsType[i]->structFieldsType) {
	      if (strcmp(structFieldsType[i]->structFieldsDesc[0],ARRAY_PTR_FIELD_DESC)==0) {
	        ptr= x + structFieldsOffset[i*ARR_OFFSET_COUNT];
	       
                ptrArr= *ptr + structFieldsType[i]->structFieldsOffset[0];
                sizeArr= *ptr + structFieldsType[i]->structFieldsOffset[1];
                ptr=*ptrArr;
                itemStructFieldsType=structFieldsType[i]->structFieldsType;
	       
	        isArray=1;
	        serialize_ArrayOf(structFieldsDesc[i], itemStructFieldsType[0]->structXsiType, (char *)ptrArr, output, itemStructFieldsType[0], (int *)(*sizeArr));
	      }
	    }
	  }
	}
	if (isArray==0) {
	  ptr=x + structFieldsOffset[i*ARR_OFFSET_COUNT];
          serialize_Structure(structFieldsDesc[i], structFieldsType[i]->structXsiType, *ptr, output, structFieldsType[i]);
	}
      }
      else {

	if (strcmp(structFieldsDesc[i],ARRAY_SIZE_FIELD_DESC) != 0) {
          ptr=x + structFieldsOffset[i*ARR_OFFSET_COUNT];	  
          if ((char*)(*ptr)) {
            sprintf(fieldValue, "%s", (char *)(*ptr));
	    Log(DEBUG,"[%d] serialize_string(%s,%s...)", i, structFieldsDesc[i], fieldValue);	    
	    serialize_string(structFieldsDesc[i], fieldValue, output);
	  }
        }
      }

    }
    
    if (openNode==1) 
      serialize_close_node(xmlName, output); 
  }
  Log(DEBUG, "***************************serialize_Structure Exit [%s]************************", xsi_type);
}

void serializeRequest(int type, char *pRequest, char *pOut) {
  
  char **ptr=NULL;
  int i, max_fields;
  char **structFieldsDesc;
  size_t *structFieldsOffset;
  int *structFieldsIdx;
  struct nps_generics **structFieldsType;
  int envField = getEnvironment();

  Log(DEBUG,"serializeRequest Init [%s] env[%s]", GET_SOAP_ACTION(type), npsEnvDesc[envField]);
    
  structFieldsDesc=methodsFields[type-1].structFieldsDesc;
  structFieldsOffset=methodsFields[type-1].structFieldsOffset;
  structFieldsIdx=methodsFields[type-1].structFieldsIdx;
  structFieldsType=methodsFields[type-1].structFieldsType;
  max_fields=methodsFields[type-1].max_fields;

  for (i = 0; i < max_fields; i++)  {
    if (!structFieldsDesc[i]) {
      break;
    }

    if ((int)structFieldsOffset[(i*ARR_OFFSET_COUNT)+envField]<0) {
      Log(ERROR, "structFieldsDesc[%s] not exist in [%s]",structFieldsDesc[i], npsEnvDesc[envField]);
      continue;
    }    
    
    ptr=(char*) pRequest + methodsFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
    Log(DEBUG, "%s = %s (%d *%d)", methodsFields[type-1].structFieldsDesc[i], structFieldsDesc[i], ptr, *ptr);
    
    if (structFieldsType[i]) {
      if (*ptr)
        serialize_Structure(structFieldsDesc[i], structFieldsType[i]->structXsiType, (char *)(*ptr), (struct Buffer *)pOut, structFieldsType[i]);
    }
    else 
      serialize_string(structFieldsDesc[i], (char *)(*ptr), (struct Buffer *)pOut);
  }
      
}
    
