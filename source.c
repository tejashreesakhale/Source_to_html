#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "source.h"
int flag = 0;
int is_function(char *word)
{

    if (strcmp(word, "printf") == 0 || strcmp(word, "scanf") == 0 ||
        strcmp(word, "main") == 0 || strcmp(word, "return") == 0 || strcmp(word, "for") == 0)
    {
        return 1;
    }
    return 0;
}
int is_keyword(int ch, char *word, int *i, FILE *fp2)
{

    if (isalnum(ch) || ch == '_')
    {
        if (*i < 49)
            word[(*i)++] = ch;
        return 1;
    }

    if (*i > 0)
    {
        word[*i] = '\0';
        if (strcmp(word, "if") == 0 ||
            strcmp(word, "for") == 0 ||
            strcmp(word, "while") == 0)
        {
            flag = 1;
        }

        if (strcmp(word, "int") == 0 || strcmp(word, "float") == 0 ||
            strcmp(word, "char") == 0 || strcmp(word, "double") == 0 ||
            strcmp(word, "void") == 0)
        {
            fprintf(fp2, "<span style=\"color:red\">%s</span>", word);
        }
        else if (is_function(word))
        {
            fprintf(fp2, "<span style=\"color:purple\">%s</span>", word);
        }
        else
        {
            fprintf(fp2, "%s", word);
        }
        *i = 0;
    }
    return 0;
}

void print_header(FILE *fp1, FILE *fp2)
{
    char word[100];
    int i = 0;

    fgets(word, sizeof(word), fp1);

    fprintf(fp2, "<span style=\"color:purple\">#");
    while (word[i] >= 'a' && word[i] <= 'z')
    {
        fputc(word[i], fp2);
        i++;
    }

    fprintf(fp2, "</span>");

    for (; word[i] != '\0'; i++)
    {
        if (word[i] == '<')
            fprintf(fp2, "<span style=\"color:skyblue\">&lt;");
        else if (word[i] == '>')
            fprintf(fp2, "&gt;</span>");
        else
            fputc(word[i], fp2);
    }
}

void double_quote(FILE *fp1, FILE *fp2)
{
    int ch, i = 0;
    char word[200];

    while ((ch = getc(fp1)) != EOF && ch != '"')
    {
        if (i < 199)
            word[i++] = ch;
    }

    word[i] = '\0';

    fprintf(fp2, "<span style=\"color:skyblue\">\"");
    fprintf(fp2, "</span>");

    fprintf(fp2, "<span style=\"color:skyblue\">");
    print_format(word, fp2);
    fprintf(fp2, "</span>");

    fprintf(fp2, "<span style=\"color:skyblue\">\"");
    fprintf(fp2, "</span>");
}

void print_format(char *word, FILE *fp2)
{
    int i;

    for (i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == '%' &&
            (word[i + 1] == 'd' ||
             word[i + 1] == 's' ||
             word[i + 1] == 'c'))
        {
            fprintf(fp2, "</span>");
            fprintf(fp2, "<span style=\"color:red\">");
            fputc(word[i], fp2);
            fputc(word[i + 1], fp2);
            fprintf(fp2, "</span>");
            fprintf(fp2, "<span style=\"color:skyblue\">");
            i++;
        }
        else
        {
            fputc(word[i], fp2);
        }
    }
}

void print_symbol(int ch, FILE *fp2)
{

    if (ch == '{')
    {
        if (flag == 1)
        {
            fprintf(fp2, "<span style=\"color:purple\">{</span>");
            flag = 2;
        }
        else
        {
            fprintf(fp2, "<span style=\"color:#DAA520 \">{</span>");
        }
    }
    else if (ch == '}')
    {
        if (flag == 2)
        {
            fprintf(fp2, "<span style=\"color:purple\">}</span>");
            flag = 0;
        }
        else
        {
            fprintf(fp2, "<span style=\"color:#DAA520 \">}</span>");
        }
    }
    else
    {
        fputc(ch, fp2);
    }
}
void print_(int ch, FILE *fp2)
{
    if (ch == '(' || ch == ')' ||
        ch == '[' || ch == ']')
    {
        fprintf(fp2, "<span style=\"color:#DAA520 \">");
        fputc(ch, fp2);
        fprintf(fp2, "</span>");
    }
}