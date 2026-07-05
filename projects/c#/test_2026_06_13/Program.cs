using Commands;
using Extensions;
using Models;

// 集合表达式
List<Command> commands = [
    EchoCommand.Create(),
    new("time", "显示当前时间", _ => {
        Console.WriteLine(DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss"));
        return 0;
    })
];

// 主构造函数创建命令（内联）
commands.Add(new("exit", "退出程序", _ => -1));

// 注册 help 命令（需要 commands 引用）
commands.Add(HelpCommand.Create(commands));

Console.WriteLine("=== C# 14 CLI Toolkit ===");
Console.WriteLine("输入 'help' 查看命令列表\n");

while (true) {
    Console.Write("> ");
    var input = Console.ReadLine();
    if (string.IsNullOrWhiteSpace(input)) continue;

    var inputArgs = input.Split(' ', StringSplitOptions.RemoveEmptyEntries);

    // 使用扩展属性
    var cmdName = inputArgs.CommandName;
    var remaining = inputArgs.Remaining;

    // null 条件赋值
    var command = commands.FirstOrDefault(c =>
        c.Name.Equals(cmdName, StringComparison.OrdinalIgnoreCase));

    if (command is null) {
        Console.WriteLine($"未知命令: {cmdName}，输入 'help' 查看帮助");
        continue;
    }

    var exitCode = command.Execute(remaining);
    if (exitCode == -1) break;
}
