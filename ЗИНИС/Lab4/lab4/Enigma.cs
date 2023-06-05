using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LAB_06
{
    public class Enigma
    {
        private static readonly string _alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        private static readonly string _rotor1 = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
        private static readonly string _rotorBeta = "LEYJVCNIXWPBQMDRTAKZGFUHOS";
        private static readonly string _rotorGamma = "FSOKANUERHMBTIYCWLQPZXVGJD";
        private static readonly string[] _reflectorB = { "AY", "BR", "CU", "DH", "EQ", "FS", "GL", "IP", "JX", "KN", "MO", "TZ", "VW" };

        public string Crypt(string text, int posL, int posM, int posR)
        {
            var rotorR = new Rotor(_rotorGamma, posR);
            var rotorM = new Rotor(_rotorBeta, posM);
            var rotorL = new Rotor(_rotor1, posL);
            StringBuilder result = new StringBuilder(text.Length);

            foreach (var ch in text)
            {

                Console.Write(ch);

                char symbol = rotorR[_alphabet.IndexOf(ch)];
                LogToConsole(symbol);
                symbol = rotorM[_alphabet.IndexOf(symbol)];
                LogToConsole(symbol);
                symbol = rotorL[_alphabet.IndexOf(symbol)];
                LogToConsole(symbol);
                symbol = _reflectorB.First(x => x.Contains(symbol)).First(x => !x.Equals(symbol));
                LogToConsole(symbol);
                symbol = rotorL[_alphabet.IndexOf(symbol)];
                LogToConsole(symbol);
                symbol = rotorM[_alphabet.IndexOf(symbol)];
                LogToConsole(symbol);
                symbol = rotorR[_alphabet.IndexOf(symbol)];
                LogToConsole(symbol);
                Console.WriteLine();
                result.Append(symbol);

                rotorR.MoveRotor(posR);

                rotorM.MoveRotor(posM);

                rotorL.MoveRotor(posL);

            }

            return result.ToString();
        }

        public string Decrypt(string text, int posL, int posM, int posR)
        {
            var rotorR = new Rotor(_rotorGamma, posR);
            var rotorM = new Rotor(_rotorBeta, posM);
            var rotorL = new Rotor(_rotor1, posL);
            StringBuilder result = new StringBuilder(text.Length);

            foreach (var ch in text)
            {

                Console.Write(ch);

                char symbol = _alphabet[rotorR.IndexOf(ch)];
                LogToConsole(symbol);
                symbol = _alphabet[rotorM.IndexOf(symbol)];
                LogToConsole(symbol);
                symbol = _alphabet[rotorL.IndexOf(symbol)];
                LogToConsole(symbol);
                symbol = _reflectorB.First(x => x.Contains(symbol)).First(x => !x.Equals(symbol));
                LogToConsole(symbol);
                symbol = _alphabet[rotorL.IndexOf(symbol)];
                LogToConsole(symbol);
                symbol = _alphabet[rotorM.IndexOf(symbol)];
                LogToConsole(symbol);
                symbol = _alphabet[rotorR.IndexOf(symbol)];
                LogToConsole(symbol);
                Console.WriteLine();
                result.Append(symbol);

                rotorR.MoveRotor(posR);

                rotorM.MoveRotor(posM);

                rotorL.MoveRotor(posL);

            }

            return result.ToString();
        }

        public void LogToConsole(char symbol)
        {
            Console.Write(" > " + symbol);
        }
    }
}