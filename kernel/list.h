#pragma once
#include "defs.h"

struct list {
    struct list *next;
    struct list *prev;
};

void lst_init(struct list *);

void lst_remove(struct list *);

void lst_push(struct list *, void *);

void *lst_pop(struct list *);

void lst_print(struct list *);

int lst_empty(struct list *);

struct proc_list {
    struct proc_list *next;
    struct proc_list *prev;
    struct proc* proc;
};

struct proc_list* proc_lst_create(struct proc*);

void proc_lst_init(struct proc_list *);

void proc_lst_remove(struct proc_list *);

void proc_lst_push(struct proc_list *, struct proc_list *);

int proc_lst_empty(struct proc_list *);
