#ifndef MTGHELPER
#define MTGHELPER

namespace mtg{
    const char MTG_HELPER_INFO[] = "\
mtg(Mainclass Test Generator) 1.0\n\
Usage:\n\
mtg <Input Source Path> <MainClass Name> <Output Target Path>\n\
For example: mtg MainClassInput.in MainClass MainClassTest.java\n\
Or: mtg D:\\java\\MainClassInput.in MainClass C:\\MainClassTest.java \n\
You can also omit <Output Target Path>, then it will be set as <mtg path>/<MainClass Name>Test.java\n\
For example, use \"mtg MainClassInput.in MainClass\" and put mtg in \"D:\\java\", then the target will be saved as \"D:\\MainClassTest.java\"\
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
}

#endif