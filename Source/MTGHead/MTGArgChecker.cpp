#include <string>
#include "MTGHelper.h"
#include "MTGPrintNotice.h"
#include <filesystem>
#include <regex>

namespace mtg
{
    int argChecker(int argc, char **argv, bool *tag, std::string *filePath)
    {
        //                          a b c d e f g h i j k l m n o p q r s t u v w x y z
        const bool availableTags[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0};
        int argcArgv=0;
        const int MAX_FILE_PATH=3;
        std::regex reg ("[.\\\\]");
        argc--;
        if (argc>4)
        {
            mtg::prtError((char *)"Too much arguments for mtg.");
            goto FORMATERR;
        }
        if (argc==0)
        {
            mtg::prtError((char *)"Too few arguments for mtg.");
            goto FORMATERR;
        }
        if (strcmp(argv[1],(char *)"-h")==0)
            return mtg::printHelp();
        for (int i=1;i<=argc;i++,argcArgv++)
            if (argv[i][0]=='-')
                break;
        if (argcArgv>MAX_FILE_PATH)
            argcArgv=MAX_FILE_PATH;
        // deal with options
        for (int i=argcArgv+1;i<=argc;i++)
        {
            int argLen = strlen(argv[i]);
            if (argv[i][0]!='-' || argLen!=2)
            {
                mtg::prtError((char *)"Invalid option: \"%s\"\n",argv[i]);
                goto FORMATERR;
            }
            else if ((argv[i][1]|0b100000)>'z' || (argv[i][1]|0b100000)<'a')
            {
                mtg::prtError((char *)"Invalid option: \"%s\"\n",argv[i]);
                goto FORMATERR;
            }
            else if (availableTags[(argv[i][1]|0b100000)-'a']!=1)
            {
                mtg::prtError((char *)"Invalid option: \"%s\"\n",argv[i]);
                goto FORMATERR;
            }
            else
                tag[(argv[i][1]|0b100000)-'a']=true;
        }
        // deal with filePath
        for (int i=1;i<=argcArgv;i++)
            filePath[i]=argv[i];
        if (std::regex_search(filePath[2],reg))
            filePath[3]=filePath[2],filePath[2].clear();
        if (filePath[2].empty())
            filePath[2]="MainClassTest";
        else
            filePath[2]+="Test";
        if (filePath[3].empty())
            filePath[3]=filePath[2]+".java";
        return true;
    FORMATERR:
        mtg::prtError((char *)"Command format error. See \"mtg -h\" to get help.");
        return false;
    }

    void prtConvertInformation(std::string* filePath)
    {
        puts("Starting to generate JUnit file from:");
        std::filesystem::path pSource = filePath[1];
        pSource = std::filesystem::absolute(pSource);
        filePath[1]=pSource.string();
        winConPrt::prtYellowChar (filePath[1].data()),puts("");
        puts("TestClass name is:");
        winConPrt::prtYellowChar (filePath[2].data()),puts("");
        std::filesystem::path pTarget = filePath[3];
        if (std::filesystem::relative(pTarget)==pTarget)
            pTarget=pSource.parent_path()/pTarget;
        pTarget = std::filesystem::absolute(pTarget);
        filePath[3]=pTarget.string();
        puts("Save the JUnit file as:");
        winConPrt::prtYellowChar (filePath[3].data()),puts("");
    }

    bool checkPath(std::string* filePath, bool *tags)
    {
        std::filesystem::path pSource = filePath[1];
        std::filesystem::path pTarget = filePath[3];
        std::regex reg ("[A-Z]:[^?|*\"<>:]+");
        if (!std::regex_match(filePath[1],reg))
        {
            mtg::prtError((char *)"Fail to load: Path \"%s\" is illegal. We have done nothing.",filePath[1].data());
            return false;
        }
        if (!std::regex_match(filePath[3],reg))
        {
            mtg::prtError((char *)"Fail to load: Path \"%s\" is illegal. We have done nothing.",filePath[3].data());
            return false;
        }
        if (!std::filesystem::exists (pSource))
        {
            mtg::prtError((char *)"Fail to load: File \"%s\" does not exist. We have done nothing.\n", filePath[1].data());
            return false;
        }
        if (std::filesystem::exists(pTarget))
        {
            if (std::filesystem::equivalent(pSource, pTarget))
            {
                mtg::prtError((char *)"Input file is the same as output file. We have done nothing.");
                return false;
            }
            mtg::prtWarning((char *)"File \"%s\" has already exists. ", filePath[3].data());
            if (!mtg::tryContinue(tags))
                return false;
        }
        mtg::prtInformation ((char *)"Generating.");
        return true;
    }
}