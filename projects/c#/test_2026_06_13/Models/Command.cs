namespace Models;

// 主构造函数：参数直接成为属性
public record class Command(string Name, string RawDescription, Func<string[], int> Execute) {
    // field 关键字：惰性求值，只在首次访问时计算
    public string Description => field ??= RawDescription.Trim();
}
