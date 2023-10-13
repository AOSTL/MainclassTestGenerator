#include <iostream>
#include <string>
#include "MTGSource.h"
#include <regex>

void convert(std::string* filePath)
{
    FILE *source = fopen (filePath[1].data(), "r");
    std::string res=mtg::MTG_JUNIT_HEAD;
    char c,c_pre=0;
    while (~(c=fgetc(source)))
    {
        if (c_pre=='\n')
            res+=" +\n                   \"";
        if (c=='\n')
            res+="\\n\"";
        else if (c=='\\')
            res+="\\\\";
        else if (c=='%')
            res+="%%%%";
        else res+=c;
        c_pre=c;
    }
    if (c_pre=='\n')
        res+=";\n";
    else
        res+="\";\n";
    res+=mtg::MTG_JUNIT_TAIL;
    fclose (source);
    std::string pattern="[^\\\\]+$";
    std::smatch fileName;
    std::regex_search(filePath[3],fileName,std::regex(pattern));
    pattern="^.*[^(.java)]";
    std::string tmp=fileName.str(0).data();
    std::regex_search(tmp,fileName,std::regex(pattern));
    tmp=fileName.str(0).data();
    if (mtg::tags[18])
    {
        printf(res.data(),tmp.data(),filePath[2].data(),filePath[2].data(),filePath[2].data());
        mtg::prtInformation ((char *)"Generation completed.");
    }
    else
    {
        FILE *target = fopen (filePath[3].data(), "w");
        fprintf(target,res.data(),filePath[2].data(),filePath[2].data(),filePath[2].data(),filePath[2].data());
        fclose (target);
        mtg::prtInformation ((char *)"Generation completed. The JUnit test file has been saved as \"%s\"",filePath[3].data());
    }
}

int main(int argc, char **argv)
{
    mtg::TagsReset();
    if (!mtg::argChecker (argc,argv))
        return 0;
    mtg::prtConvertInformation();
    if (mtg::tryContinue())
        if (mtg::checkPath())
            convert (mtg::filePath);
    return 0;
}