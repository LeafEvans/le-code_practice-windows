{
    files = {
        [[src\diceroll.c]]
    },
    values = {
        "clang",
        {
            "-Qunused-arguments",
            "-m64",
            "-g",
            "-O0",
            "-fexceptions",
            "-fcxx-exceptions"
        }
    },
    depfiles_gcc = "build\\.objs\\test_2024_2_25\\windows\\x64\\debug\\src\\__cpp_diceroll.c.c:   src/diceroll.c src/../inc/diceroll.h\
"
}