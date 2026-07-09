namespace Extensions;

// 扩展成员（C# 14 preview）
public static class StringArrayExtensions {
    extension(string[] args) {
        // 扩展属性
        public string CommandName => args.Length > 0 ? args[0] : "help";
        public string[] Remaining => args.Length > 1 ? args[1..] : [];

        // 扩展方法
        public bool HasFlag(string flag) => args.Any(a => a == flag);
    }
}
