#ifndef SOURCE_H
#define SOURCE_H

#include <stdio.h>

void print_header(FILE *fp1, FILE *fp2);
void print_symbol(int ch, FILE *fp2);
void print_format(char *word, FILE *fp2);
int is_keyword(int ch, char *word, int *i, FILE *fp2);
void double_quote(FILE *fp1, FILE *fp2);
void print_(int ch, FILE *fp2);

#endif