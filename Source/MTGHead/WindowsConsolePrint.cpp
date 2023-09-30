namespace winConPrt
{
    #include <cstdio>
    #include <windows.h>

    void prtRedChar(char c);
    void prtRedChar(char *c);
    void prtYellowChar(char c);
    void prtYellowChar(char *c);

    void prtRedChar(char c)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04);
        putchar (c);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    }

    void prtRedChar(char *c)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04);
        printf ("%s",c);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    }

    void prtYellowChar(char c)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x06);
        putchar (c);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    }

    void prtYellowChar(char *c)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x06);
        printf ("%s",c);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
    }
}