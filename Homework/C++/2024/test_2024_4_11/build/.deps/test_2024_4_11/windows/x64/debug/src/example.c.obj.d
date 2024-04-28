{
    files = {
        [[src\example.c]]
    },
    values = {
        "clang",
        {
            "-Qunused-arguments",
            "-m64",
            "-g",
            "-O0",
            "-std=c99",
            "-fexceptions",
            "-fcxx-exceptions"
        }
    },
    depfiles_gcc = "build\\.objs\\test_2024_4_11\\windows\\x64\\debug\\src\\__cpp_example.c.c:   src/example.c src/../include/example.h\
"
}