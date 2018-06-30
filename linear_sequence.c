#include "linear_sequence.h"
#include "memory.h"

#define ToIterator(x) ((LSQ_Iterator*)(x))
#define ToLsq(x) ((LSQ*)(x))

typedef struct {
    LSQ_BaseTypeT *head;
    LSQ_IntegerIndexT size;
} LSQ;

typedef struct {
    LSQ_IntegerIndexT i;
    LSQ *handle;
} LSQ_Iterator;

/*
LSQ_HandleT LSQ_CreateSequence(void);                                               //1
void LSQ_DestroySequence(LSQ_HandleT handle);                                       //2
LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle);                                  //3
int LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator);                           //4
int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator);                                 //5
int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator);                              //6
LSQ_BaseTypeT* LSQ_DereferenceIterator(LSQ_IteratorT iterator);                     //7
LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index);   //8
LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle);                              //9
LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle);                           //10
void LSQ_DestroyIterator(LSQ_IteratorT iterator);                                   //11
void LSQ_AdvanceOneElement(LSQ_IteratorT iterator);                                 //12
void LSQ_RewindOneElement(LSQ_IteratorT iterator);                                  //13
void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift);            //14
void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos);                //15
void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element);             //16
void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element);              //17
void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement);//18
void LSQ_DeleteFrontElement(LSQ_HandleT handle);                                    //19
void LSQ_DeleteRearElement(LSQ_HandleT handle);                                     //20
void LSQ_DeleteGivenElement(LSQ_IteratorT iterator);                                //21
 */

LSQ_HandleT LSQ_CreateSequence(void) {

    LSQ *seq = malloc(sizeof(LSQ));
    seq->head = NULL;
    seq->size = 0;

    return ((LSQ_HandleT)seq);
}

void LSQ_DestroySequence(LSQ_HandleT handle) {

    if (handle == LSQ_HandleInvalid)
        return;

    free((ToLsq(handle))->head);
    free(ToLsq(handle));
}

LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle) {

    return (handle != LSQ_HandleInvalid ? (ToLsq(handle))->size : 0);
}

int LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator) {

    return ((iterator != NULL) && (ToIterator(iterator)->i >= 0) &&
            (ToIterator(iterator)->i < ToIterator(iterator)->handle->size));
}

int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator){

    return ((iterator != NULL) &&
            (ToIterator(iterator)->i >= ToIterator(iterator)->handle->size));
}

int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator) {

    return ((iterator != NULL) &&
            (ToIterator(iterator)->i < 0));
}

LSQ_BaseTypeT* LSQ_DereferenceIterator(LSQ_IteratorT iterator) {

    if (iterator == NULL)
        return NULL;

    return (ToIterator(iterator)->handle->head + ToIterator(iterator)->i);
}

LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index) {

    if (handle == LSQ_HandleInvalid)
        return (NULL);

    LSQ_Iterator *iter = malloc(sizeof(LSQ_Iterator));
    iter->i = index;
    iter->handle = ToLsq(handle);

    return ((LSQ_IteratorT)iter);
}

LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle) {

    if (handle == LSQ_HandleInvalid)
        return (LSQ_HandleInvalid);

    LSQ_Iterator *iter = malloc(sizeof(LSQ_Iterator));
    iter->i = 0;
    iter->handle = ToLsq(handle);

    return ((LSQ_IteratorT)iter);
}

LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle){

    if (handle == LSQ_HandleInvalid)
        return (LSQ_HandleInvalid);

    LSQ_Iterator *iter = malloc(sizeof(LSQ_Iterator));
    iter->i = ToLsq(handle)->size;
    iter->handle = ToLsq(handle);

    return ((LSQ_IteratorT)iter);
}

void LSQ_DestroyIterator(LSQ_IteratorT iterator){

    free(ToIterator(iterator));
}

void LSQ_AdvanceOneElement(LSQ_IteratorT iterator){

    if (ToIterator(iterator) == NULL)
        return;

    ToIterator(iterator)->i++;
}

void LSQ_RewindOneElement(LSQ_IteratorT iterator){

    if (ToIterator(iterator) == NULL)
        return;

    ToIterator(iterator)->i--;
}

void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift){

    if (ToIterator(iterator) == NULL)
        return;

    ToIterator(iterator)->i += shift;
}

void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos){

    if (ToIterator(iterator) == NULL)
        return;

    ToIterator(iterator)->i = pos;
}

void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element){

    if (ToLsq(handle) == LSQ_HandleInvalid)
        return;

    ToLsq(handle)->size++;
    ToLsq(handle)->head = realloc(ToLsq(handle)->head, sizeof(LSQ_BaseTypeT) * ToLsq(handle)->size);

    memmove(ToLsq(handle)->head + 1, ToLsq(handle)->head, sizeof(LSQ_BaseTypeT) * (ToLsq(handle)->size - 1));
    *(ToLsq(handle)->head) = element;
}

void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element){

    if (ToLsq(handle) == LSQ_HandleInvalid)
        return;

    ToLsq(handle)->size++;
    ToLsq(handle)->head = realloc(ToLsq(handle)->head, sizeof(LSQ_BaseTypeT) * ToLsq(handle)->size);
    *(ToLsq(handle)->head + ToLsq(handle)->size - 1) = element;
}

void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement){

    if (ToIterator(iterator) == NULL)
        return;

    ToIterator(iterator)->handle->size++;
    ToIterator(iterator)->handle->head = realloc(ToIterator(iterator)->handle->head,
                                                 sizeof(LSQ_BaseTypeT)*ToIterator(iterator)->handle->size);

    memmove(ToIterator(iterator)->handle->head + ToIterator(iterator)->i + 1,
            ToIterator(iterator)->handle->head + ToIterator(iterator)->i,
            sizeof(LSQ_BaseTypeT) * (ToIterator(iterator)->handle->size - ToIterator(iterator)->i - 1));
    (*(ToIterator(iterator)->handle->head + ToIterator(iterator)->i)) = newElement;
}

void LSQ_DeleteFrontElement(LSQ_HandleT handle){

    if (ToLsq(handle) == LSQ_HandleInvalid)
        return;

    if (ToLsq(handle)->size == 0)
        return;

    ToLsq(handle)->size--;
    ToLsq(handle)->head++;
}

void LSQ_DeleteRearElement(LSQ_HandleT handle){

    if (ToLsq(handle) == LSQ_HandleInvalid)
        return;

    if (ToLsq(handle)->size == 0)
        return;

    ToLsq(handle)->size--;
}

void LSQ_DeleteGivenElement(LSQ_IteratorT iterator){

    if ((ToIterator(iterator) == NULL) || (!LSQ_IsIteratorDereferencable(iterator)))
        return;

    ToIterator(iterator)->handle->size--;
    memmove(ToIterator(iterator)->handle->head + ToIterator(iterator)->i,
            ToIterator(iterator)->handle->head + ToIterator(iterator)->i + 1,
            sizeof(LSQ_BaseTypeT) * (ToIterator(iterator)->handle->size - ToIterator(iterator)->i));
    ToIterator(iterator)->handle->head = realloc(ToIterator(iterator)->handle->head,
                                                 sizeof(LSQ_BaseTypeT) * (ToIterator(iterator)->handle->size));
}
