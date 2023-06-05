using System;
using System.Diagnostics;

namespace Lab8_1
{
    class Program
    {
        static void Main(string[] args)
        {
            Random random = new Random();

            List<int> xValues = GeneratePrimesInRange(103, 10100, 5);
            List<int> aValues = GenerateRandomNumbers(5, 35, 2);

            Console.WriteLine("{0,-10} {1,-12} {2,-8} {3,-6} {4,-10}", "a", "x", "n", "y", "Time, ms");
            Console.WriteLine("--------------------------------------------------------------");

            foreach (int a in aValues)
            {
                foreach (int x in xValues)
                {
                    int[] nValues = { 1024, 2048 };

                    foreach (int n in nValues)
                    {
                        Stopwatch stopwatch = new Stopwatch();

                        stopwatch.Start();

                        long y = ModuleCalculation(a, x, n);

                        Thread.Sleep(10);

                        stopwatch.Stop();

                        Console.WriteLine("{0,-10} {1,-12} {2,-8} {3,-6} {4,-10}", a, x, n, y, stopwatch.ElapsedMilliseconds);
                    }
                }
            }

            Console.ReadKey();
        }

        static long ModuleCalculation(int a, int x, int n)
        {
            long result = 1;
            long power = a;

            while (x > 0)
            {
                if ((x & 1) == 1)
                {
                    result = (result * power) % n;
                }
                power = (power * power) % n;
                x >>= 1;
            }

            return result;
        }

        static List<int> GeneratePrimesInRange(int start, int end, int count)
        {
            Random random = new Random();
            List<int> primes = new List<int>();
            List<int> numbers = new List<int>();

            for (int i = start; i <= end; i++)
            {
                numbers.Add(i);
            }

            while (primes.Count < count && numbers.Count > 0)
            {
                int index = random.Next(numbers.Count);
                int number = numbers[index];
                numbers.RemoveAt(index);

                if (IsPrime(number))
                {
                    primes.Add(number);
                }
            }

            return primes;
        }

        static bool IsPrime(int number)
        {
            if (number < 2)
            {
                return false;
            }

            for (int i = 2; i <= Math.Sqrt(number); i++)
            {
                if (number % i == 0)
                {
                    return false;
                }
            }

            return true;
        }

        static List<int> GenerateRandomNumbers(int start, int end, int count)
        {
            Random random = new Random();
            List<int> numbers = new List<int>();

            while (numbers.Count < count)
            {
                int number = random.Next(start, end + 1);

                if (!numbers.Contains(number))
                {
                    numbers.Add(number);
                }
            }

            return numbers;
        }

    }
    }