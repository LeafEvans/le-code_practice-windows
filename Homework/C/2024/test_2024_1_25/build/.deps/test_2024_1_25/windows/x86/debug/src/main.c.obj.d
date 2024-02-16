{
    files = {
        [[src\main.c]]
    },
    depfiles_gcc = "main.o: src\\main.c\
",
    values = {
        "gcc",
        {
            "-m32",
            "-g",
            "-O0",
            "-fexceptions"
        }
    }
}