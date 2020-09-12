#include <stdio.h>

#define MAXLINE 1000

int getl(char line[], int maxline);
void reverse(char to[], char from[], int len);


int main()
{
    int len;
    char line[MAXLINE];
    char rline[MAXLINE];

    len = 0;
    while ((len = getl(line, MAXLINE)) > 0) {
        reverse(rline, line, len);
        printf("%s", rline);
    }
    return 0;
}

int getl(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void reverse(char to[], char from[], int lim)
{
    int i;
    i = 0;
    for (i = 0; i < lim - 1; ++i) {
        to[lim - 2 - i] = from[i];
    }
    to[lim - 1] = '\n';
    to[lim] = '\0';
}