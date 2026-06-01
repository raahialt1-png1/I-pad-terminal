using System;

class Program {
    static void Main(string[] args) {
        string user = args.Length > 0 ? args[0] : "Guest";
        Console.WriteLine($"C# Runtime: Welcome to the matrix, {user}!");
    }
}
