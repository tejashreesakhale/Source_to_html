#include <stdio.h>
#include "source.h"

int main(int argc, int argv[])
{
    FILE *fp1, *fp2;
    int ch, i = 0;
    char word[50];

    fp1 = fopen("sample.txt", "r");
    fp2 = fopen("output.html", "w");

    if (fp1 == NULL || fp2 == NULL)
    {
        printf("File opening failed\n");
        return 1;
    }
    printf("created file\n");

    fputs("<html>\n<head>\n<title>source code</title>\n</head>\n<body>\n<pre>", fp2);

    while ((ch = getc(fp1)) != EOF)
    {
        if (ch == '(' || ch == ')' ||
            ch == '[' || ch == ']')
        {
            is_keyword(ch, word, &i, fp2);
            print_(ch, fp2);
            continue;
        }

        if (ch == '{' || ch == '}' || ch == '\n')
        {
            is_keyword(ch, word, &i, fp2);
            print_symbol(ch, fp2);
            continue;
        }
        if (ch == '#')
        {
            is_keyword(ch, word, &i, fp2);
            print_header(fp1, fp2);
            continue;
        }

        if (ch == '"')
        {
            is_keyword(ch, word, &i, fp2);
            double_quote(fp1, fp2);
            continue;
        }

        if (is_keyword(ch, word, &i, fp2))
            continue;

        if (ch == '<')
            fputs("&lt;", fp2);
        else if (ch == '>')
            fputs("&gt;", fp2);
        else if (ch == '&')
            fputs("&amp;", fp2);
        else
            fputc(ch, fp2);
    }

    fputs("</pre>\n</body>\n</html>", fp2);

    fclose(fp1);
    fclose(fp2);
    printf("Successfully converted to HTML!\n");
    return 0;
}
