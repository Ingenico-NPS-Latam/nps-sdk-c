#include "parse_xml.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nps_utils.h"
//#include <libxml/parser.h>

/**************************************************************
 * Return idx of field *key inside struct pResponse
 *************************************************************/
int GetRespFieldIdxByDesc(char *key, int type,char *pStruct) {
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
    structFieldsDesc=((struct nps_generics *)pStruct)->structFieldsDesc;
    structFieldsOffset=((struct nps_generics *)pStruct)->structFieldsOffset;
    max_fields=((struct nps_generics *)pStruct)->max_fields;
  }
  
  Log(DEBUG,"\tGetRespFieldIdxByDesc max_fields [%d]",max_fields);
  
  for (i = 0; i < max_fields; i++)  {
    
    ptr=(char*) pStruct + structFieldsOffset[(i*ARR_OFFSET_COUNT)];
    
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

void parseStructure(char *tagName, struct nps_generics *ptrFieldsType, char *pResponse, xmlDoc *doc, xmlNode * a_node, int idx){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL, itemCur=NULL;
  xmlChar *key;
  char *varValue, **varPtr, **varPtrArr, **varPtrItem;
  int *arrSize;
  int i, respFound=0, needSize, max_fields;
  char **structFieldsDesc;
  size_t *structFieldsOffset;
  int *structFieldsIdx;
  struct nps_generics **structFieldsType, **ArrayOf, **StructFieldsItem, *auxStructFieldsType;
  
  Log(DEBUG, "****************************parseStructure tagName %s****************************", tagName);

  cur = a_node->children;
  Log(DEBUG, "ptrFieldsType->structSize [%d]", ptrFieldsType->structSize);
  Log(DEBUG, "ptrFieldsType->max_fields [%d]", ptrFieldsType->max_fields);
  if (cur) {
    memset(pResponse, 0, ptrFieldsType->structSize);
    
    structFieldsOffset= ptrFieldsType->structFieldsOffset;
    structFieldsDesc  = ptrFieldsType->structFieldsDesc;
    structFieldsIdx   = ptrFieldsType->structFieldsIdx;
    structFieldsType  = ptrFieldsType->structFieldsType;
    max_fields        = ptrFieldsType->max_fields;
  }

  while (cur != NULL)
  {
    Log(DEBUG, "   cur->name %s",cur->name);
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "   parseStructure node type: Element, name: %s, VALUE %s",cur->name, varValue);
      
      i=GetRespFieldIdxByDesc(cur->name, 0, ptrFieldsType);
      
      if (varValue) {
        if (i>=0) {
          varPtr=(char*)pResponse + structFieldsOffset[(i*ARR_OFFSET_COUNT)];
	  *varPtr=(char *)calloc(strlen(varValue)+1, sizeof(char));
	  strcpy(*varPtr, varValue);
	  Log(DEBUG,"varPtr [%d] *[%d] *s[%s]", varPtr, *varPtr, *varPtr );
	}
      }
      else {
        if (i>=0) {
	  if (structFieldsType[i]) {
	    if (strcmp(structFieldsType[i]->structFieldsDesc[0], ARRAY_PTR_FIELD_DESC) == 0) {
	    
	      itemCur = cur->children;
	      while (itemCur != NULL) {
	    
	        ArrayOf = structFieldsType[i]->structFieldsType;
	        auxStructFieldsType = ArrayOf[0];
      
	        if (idx==0)
                  needSize=auxStructFieldsType->structSize;
	        else {
	          needSize=auxStructFieldsType->structSize * (idx+1);
		}
	    
	        if (idx==0) { 
                  varPtrArr=(char*)pResponse + structFieldsOffset[(i*ARR_OFFSET_COUNT)];
                  *varPtrArr=(char*)malloc(structFieldsType[i]->structSize);
		  
		  varPtr=(char*)(*varPtrArr) + structFieldsType[i]->structFieldsOffset[0];
                  *varPtr=(char*)malloc(needSize);
		  
		  varPtrItem=(char*)(*varPtr);
		  needSize=auxStructFieldsType->structSize * auxStructFieldsType->max_fields;
		  *varPtrItem=(char*)malloc(needSize);
		  memset(*varPtrItem,0, needSize);		  
	        }
	        else {
	          varPtr=(char*)(*varPtrArr) + structFieldsType[i]->structFieldsOffset[0];
	          *varPtr=(char*)realloc(*varPtr, needSize);
	          varPtrItem=(char*)(*varPtr);
		  needSize=auxStructFieldsType->structSize * auxStructFieldsType->max_fields;
		  varPtrItem[idx]=(char*)malloc(needSize);
		  memset(varPtrItem[idx],0, needSize);		  

	        }
	    
  	        StructFieldsItem=ArrayOf[0];
	        Log(DEBUG, " itemCur->name[%s]", itemCur->name);
	        parseStructure(itemCur->name, StructFieldsItem, varPtrItem[idx], doc, itemCur, idx);
	        idx++;
		
                if (idx>0) {
	          arrSize=(char*)(*varPtrArr) + structFieldsType[i]->structFieldsOffset[1];
	          *arrSize=idx;
	        }
	        itemCur = itemCur->next;
	      }
	    }
            else {
              varPtr=(char*)pResponse + structFieldsOffset[i*ARR_OFFSET_COUNT];
              *varPtr=(char*)calloc(structFieldsType[i]->structSize, structFieldsType[i]->structSize);
              parseStructure(cur->name, structFieldsType[i], *varPtr, doc, cur, 0);
	    }
	  }
	}
	else {
	  if (strcmp(cur->name, "item") ==0 ) {
	    ArrayOf = structFieldsType;

	    if (idx==0)
              needSize=(*ArrayOf)->structSize;
	    else 
              needSize=(*ArrayOf)->structSize * (idx+1);
		
	    varPtrArr=(char*)pResponse;
	    
	    if (idx==0) { 
	      varPtr=(char*)(varPtrArr) + ptrFieldsType->structFieldsOffset[0];
	      *varPtr=(char*)malloc(needSize);
	      varPtrItem=(char*)(*varPtr);
	      needSize=(*ArrayOf)->structSize * (*ArrayOf)->max_fields;
	      *varPtrItem=(char*)malloc(needSize);
	      memset(*varPtrItem,0, needSize);		  
	    }
	    else {
	      varPtr=(char*)(varPtrArr) + ptrFieldsType->structFieldsOffset[0];
	      *varPtr=(char*)realloc(*varPtr, needSize);
	      varPtrItem=(char*)(*varPtr);
	      needSize=(*ArrayOf)->structSize * (*ArrayOf)->max_fields;
	      varPtrItem[idx]=(char*)malloc(needSize);
	      memset(varPtrItem[idx],0, needSize);		  
	    }
	    
	    StructFieldsItem=ArrayOf[0];
	    parseStructure(cur->name, StructFieldsItem, varPtrItem[idx], doc, cur, idx);
	    idx++;
		
	    if (idx>0) {
	      
  	      arrSize=(char*)varPtrArr +  ptrFieldsType->structFieldsOffset[1];
	      *arrSize=idx;
	    }
	  }
	
	}
	
      }
    }
    cur = cur->next;
    
   }
   Log(DEBUG, "***********************************parseStructure Exit tagName %s***********************************", tagName);

   return ;
}

void parseResponse(int type, char *pResponse, xmlDoc *doc, xmlNode * a_node){
  xmlNode *cur_node = NULL;
  xmlNodePtr cur = NULL;
  xmlChar *key;
  char *varValue, **varPtr, *aux;
  int i, respFound=0, needSize, max_fields;
  int envField = getEnvironment();
  struct nps_generics **structFieldsType;
  char **structFieldsDesc;
  size_t *structFieldsOffset;
  
  Log(DEBUG, "parseResponse type %s", GET_SOAP_ACTION(type), npsEnvDesc[envField]);
  
  memset(pResponse, 0, methodsRespFields[type-1].structSize);
  
  structFieldsDesc=methodsRespFields[type-1].structFieldsDesc;
  structFieldsOffset=methodsRespFields[type-1].structFieldsOffset;
  structFieldsType=methodsRespFields[type-1].structFieldsType;
  max_fields=methodsRespFields[type-1].max_fields;
  
  cur=GetRespuestaPtr(doc, a_node);
  
  while (cur != NULL)
  {
    if (cur->type == XML_ELEMENT_NODE) {
      varValue=xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
      Log(DEBUG, "node type: Element, name: %s, VALUE %s",cur->name, varValue);
      
      if (varValue) {
        i=GetRespFieldIdxByDesc(cur->name, type, NULL);
	
        if (i>=0) {
          varPtr=(char*) pResponse + methodsRespFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
	  *varPtr=(char *)calloc(strlen(varValue)+1, sizeof(char));
	  strcpy(*varPtr, varValue);
	  varPtr=(char*) pResponse + methodsRespFields[type-1].structFieldsOffset[(i*ARR_OFFSET_COUNT)];
	}
      }
      else {
        i=GetRespFieldIdxByDesc(cur->name, type, NULL);
        Log(DEBUG,"%s >> [%s] [%d]",cur->name, structFieldsDesc[i], i);
        if (i>=0) {
	  Log(DEBUG,"[%s] structFieldsOffset [%d]",structFieldsDesc[i], structFieldsOffset[i*ARR_OFFSET_COUNT]);
	    
	  Log(DEBUG,"structSize[%d]",structFieldsType[i]->structSize);
	  varPtr=(char*) pResponse + structFieldsOffset[i*ARR_OFFSET_COUNT];
	  *varPtr=(char*)calloc(structFieldsType[i]->structSize, structFieldsType[i]->structSize);
          parseStructure(cur->name, structFieldsType[i], *varPtr, doc, cur,0);
	}
      }
	
    }
   
        cur = cur->next;
   }
    
}
    
