# MainclassTestGenerator (MTG)

View in my blog: https://aostl.ink/122/%e4%b8%ba%e4%bd%a0%e7%9a%84-main-java-%e6%b7%bb%e5%8a%a0-junit-%e5%8d%95%e5%85%83%e6%b5%8b%e8%af%95/

## What is this?

It's a generator to help generate a JUnit test file for MainClass.java(or Main.java) and whatever troubles you by using `System.in`, which prevent you from making JUnit test. Utilizing a file including your raw input data, this generator can generate the corresponding JUnit file MainClassTest.java to test your program. 

## How it works?

We redirect the system inputstream to our string inputstream, and the string contains your input data. In this way, we successfully imitate the console input operations. Then what remains to do is just fix the raw data into a MainClassTest.java module. 

## How to use it?

Download one version of the releases or compile on your own computer to get a executable program named `mtg.exe`. Assuming you save it as `<Path>\mtg.exe`, then you should use your console and enter the folder, which is to say, run console in `<Path>`, you can enter the command `mtg` in your console to get help, or you can read the following instructions. 

### Usage

1. `mtg`
   The command to get help.
2. `mtg <InputFilePath> <TestClassName> <JunitFilePath>`
   Appoint your the file including your input data to `<InputFilePath>`, set the name of the class you want to test as `<TestClassName>` and appoint the corresponding JUnit test file path to `<JunitFilePath>`. 
   For example, `mtg D:\data\input.txt MainClass E:\java\src\test\MainClassTest.java`.
   Notice that the path can be both absolute path and relative path. Once you use the relative path, it will base on the folder `mtg.exe` in.
3. `mtg <InputFilePath> <TestClassName>`
4. `mtg <InputFilePath>`