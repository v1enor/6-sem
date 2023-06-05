using System;

namespace crypto9
{
    internal class Knapsack
    {
        //Генерация сверхвозрастающей посл-сти
        public int[] Generate(int z)
        {
            Random rnd = new Random();
            int[] k = new int[z];
            int sum = 0;
            for (int i = 0; i < z; i++)
            {
                k[i] = rnd.Next(sum, sum + 23);
                sum += k[i];
            }
            return k;
        }

        //Вычисление нормальной посл-сти:  ei=di*a (mod n)
        public int[] GetNorm(int[] d, int a, int n, int z)
        {
            int[] e = new int[z];

            for (int i = 0; i < z; i++)
            {
                e[i] = (d[i] * a) % n;
            }
            return e;
        }

        // Зашифрование сообщения
        public int[] GetСipher(int[] e, string m, int z)
        {
            int j = 0;
            int[] result = new int[m.Length];

            Console.Write("Original message M: ");

            foreach (char mi in m)
            {
                var total = 0;
                string mi2 = '0' + GetBytes(mi.ToString()); //110010
                Console.Write($"{mi2} ");

                for (int i = 0; i < mi2.Length; i++)
                {
                    if (mi2[i] == '1') total += e[i];
                }
                result[j] = total;
                j++;
            }
            return result;
        }

        //Расшифрование сообщения: Si=5, 5-3=2; 2-2=0;  mi=1100000
        public string Decipher(int[] d, int si, int z)
        {
            string res = "";
            string res2 = "";

            for (int i = z; i > 0; i--)
            {
                if (si >= d[i - 1])
                {
                    res += '1';
                    si = si - d[i - 1];
                }
                else
                {
                    res += '0';
                }
            }
            for (int i = res.Length - 1; i > -1; i--)
            {
                res2 += res[i];
            }
            return res2;
        }

        public int a_1(int a, int n)
        {
            int res = 0;
            for (int i = 0; i < 10000; i++)
            {
                if (((a * i) % n) == 1) return (i);
            }
            return (res);
        }

        public string Str(int[] a)
        {
            string res = "";
            foreach (int x in a)
            {
                res += x + "; ";
            }
            return res;
        }

        public string GetBytes(string str)
        {
            string strB = "";
            foreach (var s in str)
            {
                strB += Convert.ToString(s, 2);
            }
            return strB;
        }

    }
}
