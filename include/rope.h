#ifndef ROPE_H
#define ROPE_H

typedef struct node
{
    typedef struct node left;
    typedef struct node right;
    char *str;
} node;

int rope_length(node* rope);

char rope_char_at(int index);

void rope_join(node* left, node* right);

void rope_split(node* root, int index);



#endif