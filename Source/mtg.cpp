#include <iostream>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include "MTGHelper.h"
#include "MTGPrintNotice.h"
#include "WindowsConsolePrint.h"

using namespace std;

void printHelp()
{
    puts(mtg::MTG_HELPER_INFO);
}

void prtConvertInformation(char **argv)
{
    puts("Starting to generate JUnit file from:");
    winConPrt::prtYellowChar (argv[1]),puts("");
    puts("MainClass Name is:");
    winConPrt::prtYellowChar (argv[2]),puts("");
    puts("Save the JUnit file in:");
    winConPrt::prtYellowChar (argv[3]),puts("");
}

bool tryContinue()
{
    while (1)
    {
        printf ("Are you sure to continue? (y/n): ");
        char choice;
        choice = getchar();
        getchar();
        if (choice == 'y' || choice == 'Y')
            return true;
        else if (choice == 'n' || choice == 'N')
        {
            mtg::prtError((char *)"Generation interrupted. We have done nothing.");
            // puts("Press any key to continue.");
            // getchar();
            return false;
        }
        mtg::prtWarning((char *)"Illegal Input!");
    }
}

bool checkPath(char **argv)
{
    FILE *source = fopen (argv[1], "r");
    FILE *target = fopen (argv[3], "r");
    if (source==NULL)
    {
        mtg::prtError((char *)"Fail to open: File \"%s\" does not exist. We have done nothing.\n", argv[1]);
        return false;
    }
    if (target!=NULL)
    {
        filesystem::path p1 = argv[1];
        filesystem::path p2 = argv[3];
        if (filesystem::equivalent(p1, p2))
        {
            mtg::prtError((char *)"Input file is the same as output file. We have done nothing.");
            return false;
        }
        mtg::prtWarning((char *)"File \"%s\" has already exists. ", argv[3]);
        if (!tryContinue())
            return false;
    }
    fclose (source),fclose (target);
    mtg::prtInformation ((char *)"Now generating.");
    return true;
}

void convert(char **argv)
{
    FILE *source = fopen (argv[1], "r");
    FILE *target = fopen (argv[3], "w");
    fprintf (target, mtg::MTG_JUNIT_HEAD, argv[2]);
    char c,c_pre=0;
    while (~(c=fgetc(source)))
    {
        if (c_pre=='\n')
            fprintf (target, " +\n                    \"");
        if (c=='\n')
            fputc('\"',target);
        else
            fputc (c, target);
        c_pre=c;
    }
    if (c_pre=='\n')
        fprintf (target, ";\n");
    else
        fprintf (target, "\";\n");
    fprintf (target, mtg::MTG_JUNIT_TAIL, argv[2],argv[2],argv[2]);
    fclose (source),fclose (target);
    mtg::prtInformation ((char *)"Generation completed.");
}

int argChecker(int argc, char **argv)
{
    if (argc==1)
    {
        printHelp();
        return false;
    }
    else if (argc==2)
    {
        argv[2]=(char *)malloc(sizeof(char)),argv[2][0]=0,strcat(argv[2], "MainClass");
        argv[3]=(char *)malloc(sizeof(char)),argv[3][0]=0,strcat(argv[3], "MainClassTest.java");
    }
    else if (argc==3)
    {
        argv[3]=(char *)malloc(sizeof(char)),argv[3][0]=0;
        strcat(argv[3], argv[2]);
        strcat(argv[3], "Test.java");
    }
    else if (argc>4)
    {
        mtg::prtError((char *)"Command format error! Use \"mtg\" to get help.");
        return false;
    }
    return true;
}

int main(int argc, char **argv)
{
    if (!argChecker (argc,argv))
        return 0;
    prtConvertInformation(argv);
    if (tryContinue())
        if (checkPath(argv))
            convert (argv);
    return 0;
}