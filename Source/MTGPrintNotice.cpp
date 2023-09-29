namespace mtg
{
    #include <cstdio>
    #include "WindowsConsolePrint.h"

    void prtWarning(char *s);
    void prtWarning(char *prtf, char *s);
    void prtError(char *s);
    void prtError(char *prtf, char *s);
    void prtInformation(char *s);
    void prtInformation(char *prtf, char *s);

    void prtWarning(char *s)
    {
        putchar ('[');
        winConPrt::prtYellowChar('W');
        putchar (']');
        printf (" %s\n",s);
    }

    void prtWarning(char *prtf, char *s)
    {
        putchar ('[');
        winConPrt::prtYellowChar('W');
        putchar (']');
        putchar (' ');
        printf (prtf, s);
    }
    
    void prtError(char *s)
    {
        putchar ('[');
        winConPrt::prtRedChar('E');
        putchar (']');
        printf (" %s\n",s);
    }

    void prtError(char *prtf, char *s)
    {
        putchar ('[');
        winConPrt::prtRedChar('E');
        putchar (']');
        putchar (' ');
        printf (prtf, s);
    }

    void prtInformation(char *s)
    {
        printf ("[I] %s\n",s);
    }

    void prtInformation(char *prtf, char *s)
    {
        printf ("[I] ");
        printf (prtf, s);
    }

    bool tryContinue(bool *tags)
    {
        while (true)
        {
            printf ("Do you want to continue? (y/n): ");
            if (tags[24])
                return !puts("");
            char choice;
            choice = getchar();
            getchar();
            if (choice == 'y' || choice == 'Y')
                return true;
            else if (choice == 'n' || choice == 'N')
            {
                mtg::prtError((char *)"Generation interrupted. We have done nothing.");
                return false;
            }
            mtg::prtWarning((char *)"Illegal Input!");
        }
    }
}