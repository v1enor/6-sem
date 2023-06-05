using System;

namespace LAB_06
{
    class Program
    {
        static void Main()
        {
            Enigma enigma = new Enigma();
            string encoded = enigma.Crypt("PARIBOK", 3, 1,3);
            Console.WriteLine(encoded);
            Console.WriteLine(enigma.Decrypt(encoded, 3, 1, 3));
        }
    }
}