//FileCopy.c                                                                 
//Name: Gavin Worley

#include <stdio.h>
#include <stdlib.h>

int main()
{
FILE *file, *file1;
char contents[100], c;

printf("Enter the filename to open for reading \n");
scanf("%s", contents);
file = fopen(contents, "r");
if (file == NULL)
{
printf("Cannot open file %s\n", contents);
exit(0);
}

printf("Enter the filename to open for writing \n");
scanf("%s", contents);

file1 = fopen(contents, "w");
if (file1 == NULL)
{
printf("Cannot open file %s\n", contents);
exit(0);
}
c = fgetc(file);
while (c != EOF)
{
fputc(c, file1);
c = fgetc(file);
}

printf("\nContents copied to %s", contents);

fclose(file);
fclose(file1);
return 0;
}