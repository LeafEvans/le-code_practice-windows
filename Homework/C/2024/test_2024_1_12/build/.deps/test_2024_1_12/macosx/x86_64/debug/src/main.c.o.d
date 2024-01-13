{
    files = {
        [[src\main.c]]
    },
    values = {
        "gcc",
        {
            "-m64",
            "-g",
            "-O0",
            "-std=c11"
        }
    },
    depfiles_gcc = "main.o: src\\main.c\
"
}