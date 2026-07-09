namespace Commands;
using Models;

public static class EchoCommand {
    public static Command Create() =>
        new("echo", "回显输入的文本", args => {
            Console.WriteLine(string.Join(' ', args));
            return 0;
        });
}
