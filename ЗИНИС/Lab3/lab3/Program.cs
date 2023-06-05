using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace lab3
{
    internal static class Program
    {
       
        private const ushort NumberColumns = 8;
        private const string Surname = "ilya";
        private const string Name = "paribok";
        private const string Alfabet = "aąbcćdeęfghijklłmnoóprssśtuwyzźż";

        private static void Main(string[] args)
        {
            Encoding.RegisterProvider(CodePagesEncodingProvider.Instance);
            StreamReader sr = new StreamReader("Text.txt", Encoding.GetEncoding(1251));
            string open = sr.ReadLine();
            Console.WriteLine(open);

            var message = open;
            var numberRows = (ushort)Math.Ceiling((float)message.Length / NumberColumns);

            var textUsage = SymbolsUsage(message);
            var amountSymbols = textUsage.Select((c) => c.Value).Sum();
            Console.WriteLine("Частота каждого символа:");
            foreach (var (ch, amount) in textUsage)
                Console.WriteLine($"{ch} - {amount} ({amount * 100 / amountSymbols:N1}%)");

            var watch = new Stopwatch();
            var multPurmutationMatrix = new char[Surname.Length, Name.Length];
            Console.WriteLine($"Матрица множественной перестановки:\n  {Name}");
            for (var i = 0; i < Surname.Length; i++)
            {
                Console.Write($"{Surname[i]} ");
                for (var j = 0; j < Name.Length; j++)
                {
                    multPurmutationMatrix[i, j] = message[i * Name.Length + j];
                    Console.Write(multPurmutationMatrix[i, j]);
                }

                Console.WriteLine();
            }

            var finalPermutationMatrix = PermutateColumns(PermutateRows(multPurmutationMatrix));
            var encrPermutationMessage = new StringBuilder();
            for (var i = 0; i < Surname.Length; i++)
                for (var j = 0; j < Name.Length; j++)
                    encrPermutationMessage.Append(finalPermutationMatrix[i, j]);
            watch.Stop();
            Console.WriteLine($"Зашифрованное сообщение:\n{encrPermutationMessage}\n" +
                              $"Затраченное время шифрования: {watch.ElapsedMilliseconds} мс");

            var textUsageEncrMultPermut = SymbolsUsage(message);
            var amountSymbolsMultPermut = textUsageEncrMultPermut.Select((c) => c.Value).Sum();
            Console.WriteLine("Частота каждого символа:");
            foreach (var (ch, amount) in textUsageEncrMultPermut)
                Console.WriteLine($"{ch} - {amount} ({amount * 100 / amountSymbolsMultPermut:N1}%)");

            watch.Restart();
            var decrPermutationMatrix = new char[Surname.Length, Name.Length];
            for (var i = 0; i < Surname.Length; i++)
                for (var j = 0; j < Name.Length; j++)
                    decrPermutationMatrix[i, j] = encrPermutationMessage[i * Name.Length + j];

            var finalDecrPermutationMatrix = DepermutateRows(DepermutateColumns(decrPermutationMatrix));
            var decrPermutationMessage = new StringBuilder();
            for (var i = 0; i < Surname.Length; i++)
                for (var j = 0; j < Name.Length; j++)
                    decrPermutationMessage.Append(finalDecrPermutationMatrix[i, j]);
            watch.Stop();
            Console.WriteLine($"Расшифрованное сообщение:\n{decrPermutationMessage}\n" +
                              $"Затраченное время дешифрования: {watch.ElapsedMilliseconds} мс");
        }

        private static Dictionary<char, int> SymbolsUsage(string text)
        {
            var usage = new Dictionary<char, int>();

            foreach (var ch in text.ToLower().Where(c => Alfabet.Contains(c)))
                if (usage.ContainsKey(ch))
                    usage[ch]++;
                else
                    usage.Add(ch, 1);

            return usage;
        }


        private static char[,] DepermutateRows(char[,] permutationMatrix)
        {
            var baseCode = Surname;
            var permutedMessage = baseCode.OrderBy(c => c).ToArray();
            var changedPermutationMatrix = new char[Surname.Length, Name.Length];
            for (var i = 0; i < permutedMessage.Length; i++)
            {
                var index = baseCode.IndexOf(permutedMessage[i]);
                baseCode = baseCode.Remove(index, 1);
                baseCode = baseCode.Insert(index, " ");
                for (var j = 0; j < Name.Length; j++)
                    changedPermutationMatrix[index, j] = permutationMatrix[i, j];
            }

            return changedPermutationMatrix;
        }

        private static char[,] DepermutateColumns(char[,] permutationMatrix)
        {
            var baseCode = Name;
            var permutedMessage = baseCode.OrderBy(c => c).ToArray();
            var changedPermutationMatrix = new char[Surname.Length, Name.Length];
            for (var i = 0; i < permutedMessage.Length; i++)
            {
                var index = baseCode.IndexOf(permutedMessage[i]);
                baseCode = baseCode.Remove(index, 1);
                baseCode = baseCode.Insert(index, " ");
                for (var j = 0; j < Surname.Length; j++)
                    changedPermutationMatrix[j, index] = permutationMatrix[j, i];
            }

            return changedPermutationMatrix;
        }

        private static char[,] PermutateRows(char[,] permutationMatrix)
        {
            var rowsInEncryption = Surname.Select((c, i) => (c, i))
                .ToLookup(
                    tuple => tuple.c,
                    tuple => Enumerable.Range(0, Name.Length)
                        .Select(x => permutationMatrix[tuple.i, x]).ToArray())
                .OrderBy(gr => gr.Key);
            var changedPermutationMatrix = new char[Surname.Length, Name.Length];
            {
                var i = 0;
                foreach (var row in rowsInEncryption)
                    foreach (var arr in row)
                    {
                        for (var j = 0; j < arr.Length; j++)
                            changedPermutationMatrix[i, j] = arr[j];

                        i++;
                    }
            }
            return changedPermutationMatrix;
        }

        private static char[,] PermutateColumns(char[,] permutationMatrix)
        {
            var columnsInEncryption = Name.Select((c, i) => (c, i))
                .ToLookup(
                    tuple => tuple.c,
                    tuple => Enumerable.Range(0, Surname.Length)
                        .Select(x => permutationMatrix[x, tuple.i]).ToArray())
                .OrderBy(gr => gr.Key);
            var changedPermutationMatrix = new char[Surname.Length, Name.Length];
            {
                var i = 0;
                foreach (var row in columnsInEncryption)
                    foreach (var arr in row)
                    {
                        for (var j = 0; j < arr.Length; j++)
                            changedPermutationMatrix[j, i] = arr[j];

                        i++;
                    }
            }
            return changedPermutationMatrix;
        }
    }
}