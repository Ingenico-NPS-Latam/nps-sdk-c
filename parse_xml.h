#ifndef parseXml_H
#define parseXml_H
#include <libxml/parser.h>
#include "npsSdk.h"

#ifdef __cplusplus
extern "C" {
#endif

#define INITIAL_SIZE 0

void parseResponse(int type, char *pResponse, xmlDoc *doc, xmlNode * a_node);

#ifdef __cplusplus
}
#endif

#endif
