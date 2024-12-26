#pragma once
#include "stdlib.h"
#include "stdio.h"

struct Vector
{
    int *data;
    int length;
    int capacity;
};

void vector_init(struct Vector *v)
{
    v->length = 0;
    v->capacity = 8;
    v->data = (int *)malloc(v->capacity * sizeof(int));
}

void vector_push_back(struct Vector *v, int value)
{
    if (v->length == v->capacity)
    {
        v->capacity = v->capacity == 0 ? 1 : v->capacity * 2;
        v->data = (int *)realloc(v->data, v->capacity * sizeof(int));
    }

    v->data[v->length++] = value;
}

void vector_print(struct Vector *v)
{
    for (int i = 0; i < v->length; i++)
    {
        printf("%d ", v->data[i]);
    }
    printf("\n");
}

void vector_free(struct Vector *v)
{
    free(v->data);
    v->length = 0;
    v->capacity = 0;
}

int vector_get(struct Vector *v, int index)
{
    if (index < 0 || index >= v->length)
    {
        return -1;
    }

    return v->data[index];
}

int vector_set(struct Vector *v, int index, int value)
{
    if (index < 0 || index >= v->length)
    {
        return -1;
    }

    v->data[index] = value;
    return 0;
}
