#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <libxml/parser.h>

//#include "NpsMethods.h"
#include "npsSdk.h"
#include "xml_save.h"
#include "parse_xml.h"
#include "nps_utils.h"

int setLog(enum log_level logLevel, char * LogFileName , FILE  * logFd) {
  int ret=0;
  if ((logLevel == DEBUG ) && ( NpsEnvField == PROD_ENV )) {
    Log(ERROR, "Can't use DEBUG Level on PRODUCTION environment");
    return -1;
  }
  else {
    LogInit( logLevel, LogFileName , logFd);
    NpsLogLevel=logLevel;
    return ret;
  }
};

int setEnvironment(enum envs iEnv) {

  if (iEnv<PROD_ENV || iEnv>STAGE_ENV) {
    Log(ERROR, "Invalid Environment. PROD_ENV[%d], SANDBOX_ENV[%d], STAGE_ENV[%d]",PROD_ENV,SANBOX_ENV,STAGE_ENV);
    sprintf(NpsErrDesc, "Invalid Environment. PROD_ENV[%d], SANDBOX_ENV[%d], STAGE_ENV[%d]",PROD_ENV,SANBOX_ENV,STAGE_ENV);
    return -1;
  }
  if ((NpsLogLevel==DEBUG) && (iEnv==PROD_ENV)) {
    Log(ERROR, "Can't set PRODUCTION env using DEBUG log level");
    sprintf(NpsErrDesc, "%s", "Can't set PRODUCTION env using DEBUG log level");
    return -1;
  }
  NpsEnvField=iEnv;
  Log(INFO, "setEnvironment [%d]", NpsEnvField);  

  switch (iEnv) {
    case 1: sprintf(pref_env, "prd"); break;
    case 2: sprintf(pref_env, "sbx"); break;
    case 3: sprintf(pref_env, "stg"); break;
  }
  return 0;
};

int setConnTimeout(int conn_timeout){
  if (conn_timeout <= 0) {
    Log(ERROR, "Connection timout must be greater than zero");
    sprintf(NpsErrDesc, "%s", "Connection timout must be greater than zero");
    return -1;
  }
  NpsConnTimeout=conn_timeout;
  return 0;
}

int setExecTimeout(int exec_timeout){
  if (exec_timeout <= 0) {
    Log(ERROR, "Execution timout must be greater than zero");
    sprintf(NpsErrDesc, "%s", "Execution timout must be greater than zero");
    return -1;
  }

  NpsExecTimeout=exec_timeout;
  return 0;
}

int getConnTimeout(){
  return(NpsConnTimeout);
}

int getExecTimeout(){
  return(NpsExecTimeout);
}

int getEnvironment() {

  return NpsEnvField;
};

int getLogLevel() {

  return NpsLogLevel;
};

char *getNpsErrDesc() {
  return NpsErrDesc;
}

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *context) {
  size_t bytec = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)context;
  mem->memory = realloc(mem->memory, mem->size + bytec + 1);
  if(mem->memory == NULL) {
    Log(ERROR,"not enough memory (realloc returned NULL)\n");
    sprintf(NpsErrDesc,"not enough memory (realloc returned NULL)\n");
    return 0;
  }
  memcpy(&(mem->memory[mem->size]), ptr, bytec);
  mem->size += bytec;
  mem->memory[mem->size] = 0;
  return nmemb;
}

static size_t xmlEscape(char *out, char *in) {
  int i, j = 0;
  for(i = 0; in[i] != 0; i++) {
    // encoding non-ASCII characters is beyond the scope of this example...
    if((unsigned char)in[i] > 127) abort();
    switch(in[i]) {
      case '"':
        if(out) sprintf(out+j, "&quot;"); j += 6; break;
      case '\'':
        if(out) sprintf(out+j, "&apos;"); j += 6; break;
      case '<':
        if(out) sprintf(out+j, "&lt;"); j += 4; break;
      case '>':
        if(out) sprintf(out+j, "&gt;"); j += 4; break;
      case '&':
        if(out) sprintf(out+j, "&amp;"); j += 5; break;
      default:
        if(out) out[j] = in[i]; j++;
    }
  }
  if(out) out[j] = 0;
  return j;
}

static size_t compose_soap_frobnicate(int type, char *buf, char *bufIn, long bufInLen,size_t size) {
  return snprintf(buf, size, "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
    "<soap:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\""
    " xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\""
    " xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">"
    "<soap:Body>"
    "<%s>"
    "<Requerimiento>"
    "%.*s"
    "</Requerimiento>"
    "</%s>"
    "</soap:Body>"
    "</soap:Envelope>", GET_SOAP_ACTION(type), bufInLen,bufIn, GET_SOAP_ACTION(type));
}

static void print_element_names(xmlDoc *doc, xmlNode * a_node)
{
  xmlNode *cur_node = NULL;
  xmlAttr *cur_attr = NULL;
  xmlChar *attr;
  
  for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      Log(DEBUG,"node type: Element, name: %s, VALUE %s",cur_node->name, xmlNodeListGetString(doc, cur_node->xmlChildrenNode, 1));
    }
    print_element_names(doc, cur_node->children);
  }
}

static void print_format_xml(char* pref_tab, char* tab, xmlDoc *doc, xmlNode * a_node)
{
  xmlNode *cur_node = NULL;
  xmlAttr *cur_attr = NULL;
  xmlChar *attr;
  char *pref_aux;
  
  for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      Log(DEBUG,"%s%s => %s",pref_tab, cur_node->name, xmlNodeListGetString(doc, cur_node->xmlChildrenNode, 1));
    }
    pref_aux=malloc(strlen(pref_tab)+strlen(tab));
    sprintf(pref_aux,"%s%s",pref_tab, tab);
    print_format_xml(pref_aux, tab, doc, cur_node->children);
  }
}

int sendRequest(int type, char *apiKey, char *pRequest, char *pResponse) {
  
  Log(DEBUG,"sendRequest Init");
  CURL *curl;
  CURLcode res;

  xmlDoc         *document;
  xmlNode        *root, *first_child, *node;  
  char url[100];
  int envField = getEnvironment();
  int connTimeout, execTimout;
  memset(NpsErrDesc,0, strlen(NpsErrDesc));
 
  switch (envField) {
    case PROD_ENV: sprintf(url,"https://services2.nps.com.ar/ws.php"); break;
    case SANBOX_ENV: sprintf(url, "https://sandbox.nps.com.ar/ws.php");break;
    //case STAGE_ENV:  sprintf(url,"https://implementacion.nps.com.ar/ws.php"); break; 
    case STAGE_ENV: sprintf(url,"https://psp.localhost:443/ws.php"); break;
  }
  Log(INFO, " sendrequest to [%s]",url); 

  struct Buffer out, *pOut;  
  struct MemoryStruct chunk;
  chunk.memory = malloc(1);
  chunk.size = 0;
  chunk.memory[chunk.size] = 0;
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);

    pOut=&out;
    new_buffer(pOut);
    checkEnvFields(type,pRequest);

    if (GetMerchDetNotAddServices[type-1].noAddService == 0) {
      AddExtraInf(type,pRequest);
    }
    
    sanitize(type,pRequest);    
    setSecureHash(type, apiKey, pRequest);
   
    serializeRequest(type, pRequest, pOut);

    size_t soap_size = compose_soap_frobnicate(type, NULL, pOut->data, pOut->size,0) + 1;
    char soap[soap_size];
    
    compose_soap_frobnicate(type, soap, pOut->data, pOut->size, soap_size);

    Log(DEBUG,"soap (%d) [%s]", soap_size,soap);
    
    connTimeout=getConnTimeout();
    execTimout=getExecTimeout();

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, soap);
    curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_BASIC);
    curl_easy_setopt(curl, CURLOPT_USERNAME, "user");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "password");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, execTimout);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, connTimeout);    

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: text/xml; charset=utf-8");
    headers = curl_slist_append(headers, "SOAPAction: \"https://psp.localhost:443/ws.php/\"");
    headers = curl_slist_append(headers, "Accept: text/plain"); // Example output easier to read as plain text.

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    // Make the example URL work even if your CA bundle is missing.
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

    /*CURLOPT_SSL_VERIFYHOST :
     * 2 that certificate must indicate that the server is the server to which you meant to connect
     * 1, curl_easy_setopt will return an error and the option value will not be changed 
     * 0, the connection succeeds regardless of the names in the certificate */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);

    res = curl_easy_perform(curl);

    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
      Log(ERROR, "curl_easy_perform() failed: %s", curl_easy_strerror(res));
      memset(pResponse, 0, methodsRespFields[type-1].structSize);
      sprintf(NpsErrDesc,"curl_easy_perform() failed: %s", curl_easy_strerror(res));
      return -1;
    } else {
      Log(DEBUG, "RESPONSE:\n %s\n",chunk.memory);
    }
    
    document = xmlReadMemory(chunk.memory, (long)chunk.size, "noname.xml", NULL, 0); 
    root = xmlDocGetRootElement(document);
    
    Log(DEBUG,"Root is <%s> (%i)", root->name, root->type);

    print_format_xml("  ", "  ", document, root);
    first_child = root->children;
    Log(DEBUG,"...");
    Log(DEBUG,"...");
    
    parseResponse(type, pResponse, document, root);  
    
    // Remember to call the appropriate "free" functions.
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    free(chunk.memory);
    curl_global_cleanup();
  }
  return 0;
}
