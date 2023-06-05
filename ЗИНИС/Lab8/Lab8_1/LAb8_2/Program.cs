using lab8_2;
using System.Diagnostics;
using System.Numerics;

namespace lab8_2
{
    class Program
    {
        static void Main(string[] args)
        {

            string Message = "Paribok  Ulsha Alex";

            rsa(Message);
            Console.WriteLine();
            gamala(Message);
        }


        public static void rsa(string Message)
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;

            BigInteger p = BigInteger.Parse("18014398241046527");
            BigInteger q = BigInteger.Parse("1298074214633706835075030044377087");


            Console.WriteLine("RSA_RSA_RSA_RSA_RSA_RSA_RSA_RSA_RSA_RSA_RSA_RSA_RSA_RSA_RSA_RSA_\n");
            Stopwatch stopwatchEnc = new();
            stopwatchEnc.Start();

            Console.WriteLine("p = " + p);
            Console.WriteLine("q = " + q);

            Random rand = new();
            BigInteger n = p * q;
            Console.WriteLine("\nn = " + n);

            BigInteger e = q * p / rand.Next(1, 19);
            for (; e > 0; e--)
            {
                if (NOD(e, (p - 1) * (q - 1)) == 1)
                {
                    break;
                }
            }
            Console.WriteLine("e = " + e);

            BigInteger d = modInverse(e, (p - 1) * (q - 1));
            Console.WriteLine("d = " + d);

            string[] SplitMessage = Message.Split(' ');
            List<BigInteger> BlockMessage = new();

            for (int i = 0; i < SplitMessage.Length; i++)
            {
                BlockMessage.Add(0);
                for (int j = 0; j < SplitMessage[i].Length; j++)
                {
                    BlockMessage[i] += Convert.ToInt32(SplitMessage[i][j]);

                    if (j != SplitMessage[i].Length - 1)
                    {
                        BlockMessage[i] *= 1000;
                    }
                }
            }

            Console.WriteLine("\nСообщение:" + Message);

            foreach (var item in BlockMessage)
            {
                Console.WriteLine(item);
            }

            List<BigInteger> encryptArray = new();
            long ellapledTicks = DateTime.Now.Ticks;

            Console.WriteLine("\nЗашифрованный текст:");
            foreach (var item in BlockMessage)
            {
                encryptArray.Add(BigInteger.ModPow(item, e, n));
                Console.WriteLine(encryptArray[encryptArray.Count - 1]);
            }

            stopwatchEnc.Stop();
            Stopwatch stopwatchDec = new();
            stopwatchDec.Start();

            List<BigInteger> decryptArray = new();
            ellapledTicks = DateTime.Now.Ticks;

            foreach (var item in encryptArray)
            {
                decryptArray.Add(BigInteger.ModPow(item, d, n));
            }

            Console.WriteLine("\nРасшифрованное сообщение:");
            string stringDecryptMessage = "";
            for (int i = 0; i < decryptArray.Count; i++)
            {
                stringDecryptMessage += Convert.ToChar(Convert.ToInt32(decryptArray[i].ToString().Substring(0, decryptArray[i].ToString().Length % 3)));

                for (int j = decryptArray[i].ToString().Length % 3; j < decryptArray[i].ToString().Length; j += 3)
                {
                    stringDecryptMessage += Convert.ToChar(Convert.ToInt32(decryptArray[i].ToString().Substring(j, 3)));
                }

                stringDecryptMessage += " ";
            }
            Console.WriteLine(stringDecryptMessage);

            stopwatchDec.Stop();

            Console.WriteLine($"\nВремя зашифрования : {stopwatchEnc.Elapsed}");
            Console.WriteLine($"Время расшифрования : {stopwatchDec.Elapsed}");
        }


        public static void gamala(string Message)
        {

            BigInteger p = 433494437;



            Console.WriteLine("El-Gamal_El-Gama_El-Gama_El-Gama_El-Gama_El-Gama_El-Gama_El-Gama_El-Gama\n");
            Stopwatch stopwatchEnc = new();
            stopwatchEnc.Start();

            var rand = new Random();

            BigInteger g = p - rand.Next() % p;
            for (; g > 0; g--)
            {
                if (IsPRoot(g, p))
                    break;
            }
            BigInteger x = rand.Next() % p;

            var encrypt = "";
            var y = BigInteger.ModPow(g, x, p);

            Console.WriteLine("Открытые числа p и g");
            Console.WriteLine("p = " + p);
            Console.WriteLine("g = " + g);

            Console.WriteLine();
            Console.WriteLine("x = " + x);
            Console.WriteLine("y = " + y);

            long ellapledTicks = DateTime.Now.Ticks;

            foreach (int code in Message)
                if (code > 0)
                {
                    var k = rand.Next() % (p - 2) + 1;
                    var a = BigInteger.ModPow(g, k, p);
                    var b = BigInteger.ModPow(BigInteger.ModPow(y, k, p) * code, 1, p);
                    encrypt += a + " " + b + " ";
                }

            Console.WriteLine("\nЗашифрованное сообщение: \n" + encrypt);

            stopwatchEnc.Stop();
            Stopwatch stopwatchDec = new();
            stopwatchDec.Start();

            var decrypt = "";
            var arr = encrypt.Split(' ').Where(xx => xx != "").ToArray();
            for (var i = 0; i < arr.Length; i += 2)
            {
                BigInteger a = BigInteger.Parse(arr[i]);
                BigInteger b = BigInteger.Parse(arr[i + 1]);

                if (a != 0 && b != 0)
                {
                    var deM = BigInteger.ModPow(b * BigInteger.ModPow(a, p - 1 - x, p), 1, p);
                    var m = (char)deM;
                    decrypt += m;
                }
            }
            Console.WriteLine("\nРасшифрованное сообщение: \n" + decrypt);

            stopwatchDec.Stop();

            Console.WriteLine($"\nВремя зашифрования : {stopwatchEnc.Elapsed}");
            Console.WriteLine($"\nВремя зашифрования : {stopwatchDec.Elapsed}");
        }



        #region oper
        public static bool IsPRoot(BigInteger g, BigInteger n)
        {
            if (NOD(g, n) != 1)
                return false;

            if (BigInteger.ModPow(g, Euler(n) / 2, n) == 1)
                return false;

            List<BigInteger> factorisation = PrimeFactorization(g);

            foreach (var item in factorisation)
            {
                if (BigInteger.ModPow(g, item, n) == 1)
                    return false;
            }

            return true;
        }

        public static List<BigInteger> PrimeFactorization(BigInteger N)
        {
            List<BigInteger> result = new List<BigInteger>();
            for (int i = 0; N % 2 == 0; N /= 2)
            {
                result.Add(2);
            }
            for (int i = 3; i <= N;)
            {
                if (N % i == 0)
                {
                    result.Add(i);
                    N /= i;
                }
                else
                {
                    i += 2;
                }
            }
            return result;
        }

        public static BigInteger Euler(BigInteger n)
        {
            BigInteger result = n;
            for (int i = 2; i * i <= n; ++i)
                if (n % i == 0)
                {
                    while (n % i == 0)
                        n /= i;
                    result -= result / i;
                }
            if (n > 1)
                result -= result / n;
            return result;
        }

        public static BigInteger modInverse(BigInteger a, BigInteger n)
        {
            BigInteger i = n, v = 0, d = 1;
            while (a > 0)
            {
                BigInteger t = i / a, x = a;
                a = i % x;
                i = x;
                x = d;
                d = v - t * x;
                v = x;
            }
            v %= n;
            if (v < 0) v = (v + n) % n;
            return v;
        }

        public static BigInteger NOD(BigInteger x, BigInteger y)
        {
            while (x != 0 && y != 0)
            {
                if (x > y)
                    x = x % y;
                else
                    y = y % x;
            }
            return (x + y);
        }

    }
    #endregion
}
