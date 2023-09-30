#include <iostream>
#include <string>
#include "MTGSource.h"

void convert(std::string* filePath)
{
    FILE *source = fopen (filePath[1].data(), "r");
    FILE *target = fopen (filePath[3].data(), "w");
    fprintf (target, mtg::MTG_JUNIT_HEAD, filePath[2].data());
    char c,c_pre=0;
    while (~(c=fgetc(source)))
    {
        if (c_pre=='\n')
            fprintf (target, " +\n                   \"");
        if (c=='\n')
            fputc('\\',target),fputc('n',target),fputc('\"',target);
        else
            fputc (c, target);
        c_pre=c;
    }
    if (c_pre=='\n')
        fprintf (target, ";\n");
    else
        fprintf (target, "\";\n");
    fprintf (target, mtg::MTG_JUNIT_TAIL, filePath[2].data(),filePath[2].data(),filePath[2].data());
    fclose (source),fclose (target);
    mtg::prtInformation ((char *)"Generation completed. The JUnit test file has been saved as \"%s\"",filePath[3].data());
}

int main(int argc, char **argv)
{
    bool tags[30];
    std::string filePath[4];
    memset(tags,0,sizeof(tags));
    if (!mtg::argChecker (argc,argv,tags,filePath))
        return 0;
    mtg::prtConvertInformation(filePath);
    if (mtg::tryContinue(tags))
        if (mtg::checkPath(filePath,tags))
            convert (filePath);
    return 0;
}