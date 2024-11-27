#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    uint32_t capacity;
    uint32_t top;
    uint32_t *items;
} Stack;

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->capacity = capacity;
    s->top = 0;
    s->items = calloc(s->capacity, sizeof(uint32_t));
    return s;
}

void stack_free(Stack **sp) {
    if (sp != NULL && *sp != NULL) {
        if ((*sp)->items) {
            free((*sp)->items);
            (*sp)->items = NULL;
        }
        free(*sp);
    }
    if (sp != NULL) {
        *sp = NULL;
    }
}

bool stack_full(const Stack *s) {
    return s->top == s->capacity;
}

bool stack_push(Stack *s, uint32_t val) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = val;
    s->top++;
    return true;
}

bool stack_pop(Stack *s, uint32_t *val) {
    if (s->top > 0) {
        *val = s->items[s->top - 1];
        s->top = s->top - 1;
        return true;
    } else {
        return false;
    }
}

bool stack_peek(const Stack *s, uint32_t *val) {
    if (s->top <= 0) {
        return false;
    }
    if (val == NULL) {
        return false;
    }
    if (s == NULL) {
        return false;
    }
    *val = s->items[s->top - 1];
    return true;
}

uint32_t stack_size(const Stack *s) {
    return s->top;
}

bool stack_empty(const Stack *s) {
    return s->top == 0;
}

void stack_copy(Stack *dst, const Stack *src) {
    if (dst->capacity < src->top)
        return;

    for (uint32_t index = 0; index < src->top; index++) {
        dst->items[index] = src->items[index];
    }
    dst->top = src->top;
}

void stack_print(const Stack *s, FILE *f, char *vals[]) {
    for (uint32_t index2 = 0; index2 < s->top; index2 = index2 + 1) {
        fprintf(f, "%s\n", vals[s->items[index2]]);
    }
}
