#include <string>
#include "MTGHelper.h"
#include "MTGPrintNotice.h"
#include <filesystem>
#include <regex>
#include "MTGData.h"

namespace mtg
{
    int argChecker(int argc, char **argv)
    {
        //                          a b c d e f g h i j k l m n o p q r s t u v w x y z
        const bool availableTags[]={0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0};
        int argcArgv=0;
        const int MAX_FILE_PATH=3;
        std::regex reg ("[.\\\\]");
        argc--;
        if (argc==0)
        {
            mtg::prtError((char *)"Too few arguments for mtg.");
            goto FORMATERR;
        }
        if (strcmp(argv[1],(char *)"-h")==0)
            return mtg::printHelp();
        else if (argv[1][0]=='-')
            goto FORMATERR;
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
                mtg::tags[(argv[i][1]|0b100000)-'a']=true;
        }
        // deal with filePath
        for (int i=1;i<=argcArgv;i++)
            mtg::filePath[i]=argv[i];
        if (std::regex_search(mtg::filePath[2],reg))
            mtg::filePath[3]=mtg::filePath[2],mtg::filePath[2].clear();
        if (mtg::filePath[2].empty())
            mtg::filePath[2]="MainClass";
        if (mtg::filePath[3].empty())
            mtg::filePath[3]=mtg::filePath[2]+"Test.java";
        return true;
    FORMATERR:
        mtg::prtError((char *)"Command format error. See \"mtg -h\" to get help.");
        return false;
    }

    void prtConvertInformation()
    {
        puts("Starting to generate JUnit file from:");
        std::filesystem::path pSource = mtg::filePath[1];
        pSource = std::filesystem::absolute(pSource);
        mtg::filePath[1]=pSource.string();
        winConPrt::prtYellowChar (mtg::filePath[1].data()),puts("");
        puts("Class name is:");
        winConPrt::prtYellowChar (mtg::filePath[2].data()),puts("");
        std::filesystem::path pTarget = mtg::filePath[3];
        if (std::filesystem::relative(pTarget)==pTarget)
            pTarget=pSource.parent_path()/pTarget;
        pTarget = std::filesystem::absolute(pTarget);
        mtg::filePath[3]=pTarget.string();
        puts("Save the JUnit file as:");
        winConPrt::prtYellowChar (mtg::filePath[3].data()),puts("");
    }

    bool checkPath()
    {
        std::filesystem::path pSource = mtg::filePath[1];
        std::filesystem::path pTarget = mtg::filePath[3];
        std::regex reg ("[A-Z]:[^?|*\"<>:]+");
        if (!std::regex_match(mtg::filePath[1],reg))
        {
            mtg::prtError((char *)"Fail to load: Path \"%s\" is illegal. We have done nothing.",mtg::filePath[1].data());
            return false;
        }
        if (!std::regex_match(mtg::filePath[3],reg))
        {
            mtg::prtError((char *)"Fail to load: Path \"%s\" is illegal. We have done nothing.",mtg::filePath[3].data());
            return false;
        }
        if (!std::filesystem::exists (pSource))
        {
            mtg::prtError((char *)"Fail to load: File \"%s\" does not exist. We have done nothing.\n", mtg::filePath[1].data());
            return false;
        }
        if (std::filesystem::exists(pTarget))
        {
            if (std::filesystem::equivalent(pSource, pTarget))
            {
                mtg::prtError((char *)"Input file is the same as output file. We have done nothing.");
                return false;
            }
            mtg::prtWarning((char *)"File \"%s\" has already exists. ", mtg::filePath[3].data());
            if (!mtg::tryContinue())
                return false;
        }
        mtg::prtInformation ((char *)"Generating.");
        return true;
    }
}