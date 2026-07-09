namespace Commands;
using Models;

public static class HelpCommand {
    // 集合表达式：[.. items] 替代 new List<T> { ... }
    public static Command Create(IReadOnlyList<Command> allCommands) =>
        new("help", "显示所有可用命令", args => {
            Console.WriteLine("可用命令：");
            foreach (var cmd in allCommands) {
                Console.WriteLine($"  {cmd.Name,-12} {cmd.Description}");
            }
            return 0;
        });
}
