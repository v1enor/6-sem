using System;
using System.Linq;

namespace lab3_1
{
    class RouteCipher
    {
        static readonly char[] Alphabet = {'a','ą','b','c','ć','d','e','ę','f','g','h','i','j','k',
                                             'l','ł','m','n','ń','o','ó','p','r','s','ś','t','u','w',
                                             'y','z','ź','ż'};
        static readonly int N = Alphabet.Length;
        int[] colFx1 = new int[N];
        int[] colFx2 = new int[N];

        public string Encrypt(string msg, int key)
        {
            int len = msg.Length;
            //кол-во вхождений
            for (int i = 0; i < N; i++)                                            //каждая буква алфавита провер. кол-во вхожд во фразе
            {
                colFx1[i] = msg.Count(el => el == Alphabet[i]);
            }

            if (len % key != 0)
            {
                for (int i = 0; i < (key - (len % key)); i++)                                            //каждая буква алфавита провер. кол-во вхожд во фразе
                {
                    msg += '_';
                }
            }

            string result = string.Empty;
            string[] msgInArray = new string[(msg.Length / key) + 1];

            for (int i = 0; i < (msg.Length / key); i++)
            {
                msgInArray[i] = msg.Substring(i * key, key );
                Console.WriteLine("msgInArray[" + i + "] = " + msgInArray[i]);
            }

            for (int i = 0; i < key; i++)
            {
                for (int k = 0; k < msgInArray.Length - 1; k++)
                {
                    result += msgInArray[k].Substring(i, 1);
                }
            }

            return result;
        }




        public string Decrypt(string msg, int key)
        {
            int len = msg.Length;

            //кол-во вхождений
            for (int i = 0; i < N; i++)                                            //каждая буква алфавита провер. кол-во вхожд во фразе
            {
                colFx2[i] = msg.Count(el => el == Alphabet[i]);
            }

            string result = string.Empty;
            string[] msgInArray = new string[(len / key)];

            for (int i = 0; i < key; i++)
            { 
                msgInArray[i] = msg.Substring(i * (len / key), (len / key));
                Console.WriteLine("msgInArray[" + i + "] = " + msgInArray[i]);
            }

            for (int i = 0; i < (len / key); i++)
            {
                for (int k = 0; k < key; k++)
                {
                    if (msgInArray[k].Length <= i) continue;
                    result += msgInArray[k].Substring(i, 1);
                }
            }

            //for (int i = 0; i < N; i++) // вывод кол-ва вхождений
            //{
            //    Console.WriteLine(colFx2[i] + " --- " + Alphabet[i]);
            //}

            return result;
        }
    }
}
