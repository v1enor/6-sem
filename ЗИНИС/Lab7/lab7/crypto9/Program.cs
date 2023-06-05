using System;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace crypto9
{
    internal class Program
    {
        public static readonly int Z = 8;
        public static readonly int A = 31;
        public static readonly int N = 420;
        public static readonly int[] D = { 2, 3, 6, 13, 27, 52, 105, 210 };
        public static string M = "ILUSHA PARIBOK ALEXANDROVICH";

        static void Main(string[] args)
        {
            var r = new Knapsack();

            // Generating a super-increasing sequence (closed key)
            int[] d2 = r.Generate(8);
            Console.WriteLine($"Closed key d: {r.Str(D)}");

            // Computing the normal sequence (open key)
            int[] e = r.GetNorm(D, A, N, Z);
            Console.WriteLine($"Open key e: {r.Str(e)}");

            // Encrypting the name
            var stopwatch = Stopwatch.StartNew();
            int[] c = r.GetСipher(e, M, Z);
            Console.WriteLine($"\nEncrypted message C: {r.Str(c)}");
            Console.WriteLine($"Duration of encrypotion: {stopwatch.ElapsedMilliseconds} ms");
            
            
            // Decrypting the name
            int a1 = r.a_1(A, N);

            int[] s = new int[c.Length];
            stopwatch = Stopwatch.StartNew();
            string decryptedMessage = "";

            // Getting the weight vector
            for (int i = 0; i < c.Length; i++)
            {
                s[i] = (c[i] * a1) % N;
            }
            Console.WriteLine($"Weight vector S: {r.Str(s)}     \n a^(-1) = {a1}");
            // Decrypting the weight vector
            foreach (int si in s)
            {
                string m2I = r.Decipher(D, si, Z);
                decryptedMessage += m2I + " ";
            }

            // Time for decryption
            stopwatch.Stop();
            Console.WriteLine($"Decrypted message: {decryptedMessage}");
            Console.WriteLine($"Duration of decryption: {stopwatch.ElapsedMilliseconds} ms");

            // Converting the decrypted message to a string
            string decodedMessageWithoutSpaces = decryptedMessage.Replace(" ", "");
            var stringArray = Enumerable.Range(0, decodedMessageWithoutSpaces.Length / 8)
                .Select(i => Convert.ToByte(decodedMessageWithoutSpaces.Substring(i * 8, 8), 2))
                .ToArray();
            var str = Encoding.UTF8.GetString(stringArray);
            Console.WriteLine($"\nDecoded message: {str}");
        }


    }
}
