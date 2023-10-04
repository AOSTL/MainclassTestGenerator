#ifndef MTGHELPER
#define MTGHELPER

namespace mtg{
    const char MTG_HELPER_INFO[] = "\
mtg(MainclassTestGenerator) 1.12\n\
For more information, view https://github.com/AOSTL/MainclassTestGenerator\n\
Usage:\n\
mtg <InputSourcePath> <MainClassName> <OutputPath> [-Options]\n\
Options:\n\
-e \n\
    Show errors only.\n\
-h\n\
    Get help information from mtg.\n\
    Only available when it is the first argument and later arguments will be dismissed.\n\
-p <PackageName>\n\
    Appoint the package name for JUnit file.\n\
    No package statement will be added to the file if followed by no legal package name.\n\
-s \n\
    Print the result to console instead of file.\n\
    If so, your output path will be dismissed.\n\
-y\n\
    Assume \"y\" for all queries.\
";
    const char MTG_JUNIT_HEAD[] = "\
package test;\n\
\n\
import java.io.ByteArrayInputStream;\n\
import java.io.InputStream;\n\
import org.junit.Test;\n\
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
        System.setIn(originalIn);\n\
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