/*------------------------------------------------------------------------------
    * File:        Onegin.cpp
    * Description: Program sort strings of text file
    * Created:     31 oct 2020
    * Copyright:   (C) 2020 MIPT
    * Author:      Artem Puzankov
    * Email:       puzankov.ao@phystech.edu
    */
//------------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys\stat.h>
#include <locale.h>

//#define NDEBUG
#include <assert.h>

#define NOLINES  1
#define NOSYMB   2
#define OK       0


struct node
{
    void*  data         = nullptr;
    struct node* left   = nullptr;
    struct node* right  = nullptr;
};

struct Text_Info
{
   char*  Text        = nullptr;
   size_t Size        = 0;
   size_t LineNum     = 0;
   struct line* Lines = nullptr;
};

struct line
{
    char*  str = nullptr;
    size_t len = 0;
};


//------------------------------------------------------------------------------
/*! @brief   Get name of file from command line
 *
 *  @param   argc is number of command line arguments
 *  @param   argv is arguments
 *
 *  @return  name of file
 */

char* GetFileName (int argc, char** argv);

//------------------------------------------------------------------------------
/*! @brief   Get pointer to file
 *
 *  @param   FileName is file name
 *
 *  @return  pointer to file
 */

FILE* GetFilePointer (char* FileName);

//------------------------------------------------------------------------------
/*! @brief   Fills the structure
 *
 *  @param   txtstruct is the structure to be filled
 *  @param   fp is pointer to file
 *
 *  @return  error code
 */

int fillinStruct (struct Text_Info* txtstruct, FILE* fp);

//------------------------------------------------------------------------------
/*! @brief   Get size of file
 *
 *  @param   fp is pointer to file
 *
 *  @return  size of file
 */

size_t CountSize (FILE* fp);

//------------------------------------------------------------------------------
/*! @brief   Get text of file
 *
 *  @param   fp is pointer to file
 *  @param   len is length of text
 *
 *  @return  pointer to text
 */

char* GetText (FILE* fp, size_t len);

//------------------------------------------------------------------------------
/*! @brief   Get number of lines in text
 *
 *  @param   text contains text
 *  @param   len is length of text
 *
 *  @return  number of lines in text
 */

size_t GetLineNum (char* text, size_t len);

//------------------------------------------------------------------------------
/*! @brief   Get pointers to start of lines and their lengths
 *
 *  @param   text contains text
 *  @param   num is number of strings
 *
 *  @return  array of lines
 */

struct line* GetLine (const char* text, size_t num);

//------------------------------------------------------------------------------
/*! @brief   Tree sort
 *
 *  @param   values is array of values
 *  @param   num is number of values
 *  @param   size is size of value
 *  @param   CompareFunc is comparison function
 */

void TreeSort (void* values, size_t num, size_t size, int (*CompareFunc)(const void*, const void*));

//------------------------------------------------------------------------------
/*! @brief   Insert pointer to value to binary tree of struct
 *
 *  @param   pproot is pointer to pointer to struct
 *  @param   pvalue is pointer to value
 *  @param   CompareFunc is comparison function
 */

void insert (struct node** pproot, void* pvalue, int (*CompareFunc)(const void*, const void*));

//------------------------------------------------------------------------------
/*! @brief   Rewrite contents of tree into array
 *
 *  @param   proot is pointer to struct
 *  @param   values is array of values
 *  @param   size is size of value
 *
 *  @return  pointer to value
 */

void* rewrite (struct node* proot, void* values, size_t size);

//------------------------------------------------------------------------------
/*! @brief   Compare two lines from left alphabetically
 *
 *  @param   p1 is pointer to first line
 *  @param   p2 is pointer to second line
 *
 *  @return  positive integer if first line bigger then second
 *  @return  0 if first line the same as second
 *  @return  negative integer if first line smaller then second
 */

int CompareFromLeft (const void *p1, const void *p2);

//------------------------------------------------------------------------------
/*! @brief   Compare two lines from right alphabetically
 *
 *  @param   p1 is pointer to first line
 *  @param   p2 is pointer to second line
 *
 *  @return  positive integer if first line bigger then second
 *  @return  0 if first line the same as second
 *  @return  negative integer if first line smaller then second
 */


int CompareFromRight (const void *p1, const void *p2);

//------------------------------------------------------------------------------
/*! @brief   Copmare two strings by letters
 *
 *  @param   line1 is first line
 *  @param   line2 is second line
 *  @param   dir is direction of comparing (+1 - compare from left, -1 - compare from right)
 *
 *  @return  positive integer if first line bigger then second
 *  @return  0 if first line the same as second
 *  @return  negative integer if first line smaller then second
 */

int StrCompare (struct line line1, struct line line2, int dir);

//------------------------------------------------------------------------------
/*! @brief   Write lines to file
 *
 *  @param   lines is array of lines
 *  @param   num is number of lines
 *  @param   filename is name of file
 */

void Write(struct line* Lines, size_t num, const char* filename);

//------------------------------------------------------------------------------
/*! @brief   Print text to file
 *
 *  @param   text contains text
 *  @param   len is length of text
 *  @param   filename is name of file
 */

void Print(char* text, size_t len, const char* filename);

//------------------------------------------------------------------------------
/*! @brief   Check that char is letter
 *
 *  @param   c is char
 *
 *  @return  1 if c is letter
 *  @return  0 if c is not letter
 */

int  isAlpha (const unsigned char c);

//------------------------------------------------------------------------------

const char* output_name_1 = "SortedFromLeft.txt";
const char* output_name_2 = "SortedFromRight.txt";
const char* original_name = "original.txt";

const char* default_name = "Onegin.txt";

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"Russian");

    printf("\n ** -- **       Program sort strings of text file      ** -- **"
           "\n ** -- ** Sorting from left   and   Sorting from right ** -- **\n");


    char* InputFileName = GetFileName(argc, argv);
    FILE* InputFILE = GetFilePointer(InputFileName);


    struct Text_Info InputText;

    int err = fillinStruct(&InputText, InputFILE);
    switch (err)
    {
        case OK:      /* WOW! Program works correctly! eeeeeeeeeeeeeeeeee */ break;

        case NOSYMB:  printf("\n File is empty!");                           return 0;

        case NOLINES: printf("\n There are no lines with letters in text!"); return 0;

        default:      assert(0);
    }

    fclose(InputFILE);


    TreeSort(InputText.Lines, InputText.LineNum, sizeof(struct line), CompareFromLeft);
    Write   (InputText.Lines, InputText.LineNum, output_name_1);

    TreeSort(InputText.Lines, InputText.LineNum, sizeof(struct line), CompareFromRight);
    Write   (InputText.Lines, InputText.LineNum, output_name_2);

    printf("\n Sort finished. Check files \"%s\" and  \"%s\"\n", output_name_1, output_name_2);


    Print(InputText.Text, InputText.Size, original_name);

    printf("\n Original text available in file \"%s\"\n", original_name);


    return 0;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

char* GetFileName(int argc, char *argv[])
{
    assert(argc);
    assert(argv);

    if (argc > 1)
    {
        return argv[1];
    }

    return "";
}

//------------------------------------------------------------------------------

FILE* GetFilePointer(char* filename)
{
    assert(filename);

    FILE* fp = nullptr;
    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("\n ERROR. Input file \"%s\" is not found\n", filename);
        printf(" \"%s\" will be opened instead\n", default_name);

        fp = fopen(default_name, "r");
    }

    return fp;
}

//------------------------------------------------------------------------------

int fillinStruct(struct Text_Info* txtstruct, FILE* fp)
{
    assert(txtstruct);
    assert(fp);

    txtstruct->Size = CountSize(fp);
    if (txtstruct->Size == 0)
        return NOSYMB;

    txtstruct->Text = GetText  (fp, txtstruct->Size);
    assert(txtstruct->Text);

    txtstruct->LineNum = GetLineNum(txtstruct->Text, txtstruct->Size);
    if (txtstruct->LineNum == 0)
        return NOLINES;

    txtstruct->Lines   = GetLine   (txtstruct->Text, txtstruct->LineNum);
    assert(txtstruct->Lines);

    return OK;
}

//------------------------------------------------------------------------------

size_t CountSize(FILE* fp)
{
    assert(fp);

    struct stat prop;
    fstat(fileno(fp), &prop);

    return prop.st_size;
}

//------------------------------------------------------------------------------

char* GetText(FILE* fp, size_t len)
{
    assert(fp);
    assert(len);

    char* text = (char*)calloc(len + 1, 1);
    fread(text, 1, len, fp);

    return text;
}

//------------------------------------------------------------------------------

size_t GetLineNum(char* text, size_t len)
{
    assert(text);
    assert(len);

    char* start = text;

    size_t num = 0;

    while (1)
    {
        while (not isAlpha(*text++) && (text - start < len));
        if (isAlpha(*--text))
            ++num;
        else
            break;

        text = strchr(text, '\n') + 1;

        if ((int)text == 1) break;

        *(text - 1) = '\0';
    }

    return num;
}

//------------------------------------------------------------------------------

struct line* GetLine(const char* text, size_t num)
{
    assert(text);
    assert(num);

    struct line* Lines = (struct line*)calloc(num + 2, sizeof(line));
    struct line* temp  = Lines;

    while (num-- > 0)
    {
        while (not isAlpha(*text++));
        --text;

        temp->str = (char*)text;
        temp->len = strlen(text);
        temp++;

        text = strchr(text, '\0') + 1;
    }

    return Lines;
}

//-----------------------------------------------------------------

void TreeSort(void* values, size_t num, size_t size, int (*CompareFunc)(const void*, const void*))
{
    struct node* proot = nullptr;

    void* newval = (void*)calloc(num, size);
    for (int i = 0; i < num; ++i)
    {
        memmove((newval + size*i), (values + size*i), size);
        insert(&proot, (newval + size*i), CompareFunc);
    }

    rewrite(proot, values, size);
    free(newval);
}

//-----------------------------------------------------------------

void insert(struct node** pproot, void* pvalue, int (*CompareFunc)(const void*, const void*))
{
    assert(pvalue);

    if (not *pproot)
    {
        *pproot = (struct node*)calloc(1, sizeof(struct node));

        (*pproot)->data  = pvalue;
        (*pproot)->left  = nullptr;
        (*pproot)->right = nullptr;
    }
    else if (CompareFunc(pvalue, (*pproot)->data) < 0)
        insert(&(*pproot)->left,  pvalue, CompareFunc);
    else
        insert(&(*pproot)->right, pvalue, CompareFunc);
}

//-----------------------------------------------------------------

void* rewrite(struct node* proot, void* values, size_t size)
{
    assert(values);

    if (proot != NULL)
    {
        values = rewrite(proot->left, values, size);

        memmove(values, proot->data, size);

        values = rewrite(proot->right, values + size, size);

        free(proot);
    }

    return values;
}

//------------------------------------------------------------------------------

int CompareFromLeft(const void* p1, const void* p2)
{
    assert(p1);
    assert(p2);
    assert(p1 != p2);

    return StrCompare(*(struct line*)p1, *(struct line*)p2, 1);
}

//------------------------------------------------------------------------------

int CompareFromRight(const void* p1, const void* p2)
{
    assert(p1);
    assert(p2);
    assert(p1 != p2);

    return StrCompare(*(struct line*)p1, *(struct line*)p2, -1);
}

//------------------------------------------------------------------------------

int StrCompare(struct line line1, struct line line2, int dir)
{
    assert((dir == 1) || (dir == -1));


    int i1 = 0;
    int i2 = 0;

    if (dir == -1)
    {
        i1 = line1.len - 1;
        i2 = line2.len - 1;
    }

    while ((line1.str[i1] != '\0') && (line2.str[i2] != '\0'))
    {
        if (not(isAlpha(line1.str[i1])))
        {
            i1 += dir;
            continue;
        }

        if (not(isAlpha(line2.str[i2])))
        {
            i2 += dir;
            continue;
        }

        if ((unsigned char)line1.str[i1] == (unsigned char)line2.str[i2])
        {
            i1 += dir;
            i2 += dir;
            continue;
        }

        else return ((unsigned char)line1.str[i1] - (unsigned char)line2.str[i2]);
    }

    if (dir == 1)
        return ((unsigned char)line1.str[i1] - (unsigned char)line2.str[i2]);
    else
        return ((unsigned char)line1.str[i2] - (unsigned char)line2.str[i1]);

    return 0;
}

//------------------------------------------------------------------------------

int isAlpha(const unsigned char c)
{
    return (   ((unsigned char)'a' <= c) && (c <= (unsigned char)'z')
            || ((unsigned char)'A' <= c) && (c <= (unsigned char)'Z')
            || ((unsigned char)'а' <= c) && (c <= (unsigned char)'я')
            || ((unsigned char)'А' <= c) && (c <= (unsigned char)'Я'));
}

//------------------------------------------------------------------------------

void Write(struct line* Lines, size_t num, const char* filename)
{
    assert(Lines);
    assert(num);
    assert(filename);

    FILE* fp = fopen(filename, "w");

    for(int i = 0; i < num; ++i)
        fprintf(fp, "%s\n", Lines[i].str);

    fclose(fp);
}

//------------------------------------------------------------------------------

void Print(char* text, size_t len, const char* filename)
{
    assert(text);
    assert(len);
    assert(filename);

    FILE* fp = fopen(filename, "w");

    for (int i = 0; i < len; ++i)
        fputc(text[i], fp);

    fclose(fp);
}

//------------------------------------------------------------------------------








// 600!
