#ifndef xmlSave_H
#define xmlSave_H
#include "npsSdk.h"

#ifdef __cplusplus
extern "C" {
#endif

#define INITIAL_SIZE 0

struct Buffer {
    void *data;
    long next;
    long size;
};

void serializeRequest(int type, char *pRequest, char *pOut);

#ifdef __cplusplus
}
#endif

#endif
