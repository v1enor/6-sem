using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LAB_06
{
    public class Rotor
    {
        private readonly char[] _rotorChar;
        private int _currentIndex;

        public Rotor(string rotorString, int startIndex)
        {
            _rotorChar = rotorString.ToCharArray();
            _currentIndex = startIndex >= rotorString.Length ? 0 : startIndex;
        }

        public char this[int index]
        {
            get
            {
                return _rotorChar[(index + _currentIndex) % _rotorChar.Length];
            }
        }

        public int IndexOf(char symbol)
        {
            int index = _rotorChar.ToList().IndexOf(symbol);

            // shows how much the shift to the right has occurred
            int rightOffset = _rotorChar.Length - _currentIndex;
            int offsetRotorIndex = (index + rightOffset) % _rotorChar.Length;

            return offsetRotorIndex;
        }

        // Return true if the Rotor has made a full revolution
        public bool MoveRotor(int offset)
        {
            _currentIndex = _currentIndex + offset;
            if (_currentIndex >= _rotorChar.Length)
            {
                _currentIndex = _currentIndex % _rotorChar.Length;
                return true;
            }
            return false;
        }

        public char CurrentRotor()
        {
            return _rotorChar[_currentIndex];
        }

        public void Reset()
        {
            _currentIndex = 0;
        }
    }
}