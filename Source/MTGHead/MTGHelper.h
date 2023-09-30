#ifndef MTGHELPER
#define MTGHELPER

namespace mtg{
    const char MTG_HELPER_INFO[] = "\
mtg(MainclassTestGenerator) 1.1\n\
For more information, view https://github.com/AOSTL/MainclassTestGenerator\n\
Usage:\n\
mtg <InputSourcePath> <MainClassName> <OutputTargetPath> [-Options]\n\
Options:\n\
-h : Get help information from mtg. Only and always available when it is the first argument and all later arguments will be dismissed.\n\
-y : Always assume \"y\" for all queries.\
";
    const char MTG_JUNIT_HEAD[] = "\
package test;\n\
\n\
import java.io.ByteArrayInputStream;\n\
import java.io.InputStream;\n\
\n\
public class %s {\n\
    @Test\n\
    public void test() {\n\
        final InputStream originalIn = System.in;\n\
        String s = \"\
";
    const char MTG_JUNIT_TAIL[] = "\
        System.setIn(new ByteArrayInputStream(s.getBytes()));\n\
        %s test = new %s();\n\
        %s.main(null);\n\
    }\n\
}\n\
";
    bool printHelp()
    {
        puts(mtg::MTG_HELPER_INFO);
        return false;
    }
}

#endif