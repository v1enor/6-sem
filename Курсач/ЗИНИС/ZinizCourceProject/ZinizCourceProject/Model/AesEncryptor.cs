using Org.BouncyCastle.Crypto;
using Org.BouncyCastle.Crypto.Engines;
using Org.BouncyCastle.Crypto.Modes;
using Org.BouncyCastle.Crypto.Parameters;
using Org.BouncyCastle.Security;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace ZinizCourceProject.Model
{
    public class AesEncryptor
    {

        private const CipherMode Mode = CipherMode.CBC;
        private const PaddingMode Padding = PaddingMode.PKCS7;

        public static string EncryptionTime { get; private set; }
        public static string DecryptionTime { get; private set; }

        public static string Encrypt(string plainText, string key)
        {
    
            byte[] keyBytes = GetHash(key);
            byte[] iv = (byte[])keyBytes.Clone();
            Array.Sort(iv);
                
            byte[] plainTextBytes = Encoding.UTF8.GetBytes(plainText);

            Stopwatch stopwatch = Stopwatch.StartNew();
            IBufferedCipher cipher = CipherUtilities.GetCipher("AES/CBC/PKCS7Padding");
            KeyParameter keyParam = new KeyParameter(keyBytes);
            ParametersWithIV parameters = new ParametersWithIV(keyParam, iv);
            cipher.Init(true, parameters);

            byte[] encryptedBytes = cipher.DoFinal(plainTextBytes);
            stopwatch.Stop(); // останавливаем таймер
            TimeSpan ts = stopwatch.Elapsed; // получаем затраченное время
            EncryptionTime = $"{ts.TotalMilliseconds} ms"; // устанавливаем значение свойства, связанного с текстом времени выполнения шифрования

            return Convert.ToBase64String(encryptedBytes);
        }

        public static string Decrypt(string cipherText, string key)
        {

            byte[] encryptedBytes = Convert.FromBase64String(cipherText);
            byte[] keyBytes = GetHash(key);
            byte[] iv = (byte[])keyBytes.Clone();
            Array.Sort(iv);

            Stopwatch stopwatch = Stopwatch.StartNew();
            IBufferedCipher cipher = CipherUtilities.GetCipher("AES/CBC/PKCS7Padding");
            KeyParameter keyParam = new KeyParameter(keyBytes);
            ParametersWithIV parameters = new ParametersWithIV(keyParam, iv);
            cipher.Init(false, parameters);

            byte[] decryptedBytes = cipher.DoFinal(encryptedBytes);

            stopwatch.Stop(); // останавливаем таймер
            TimeSpan ts = stopwatch.Elapsed; // получаем затраченное время
            DecryptionTime = $"{ts.TotalMilliseconds} ms"; // устанавливаем значение свойства, связанного с текстом времени выполнения шифрования


            return Encoding.UTF8.GetString(decryptedBytes);

        }

        public static string GetEncriptionTime()
        {
            return EncryptionTime;
        }

        public static string GetDecriptionTime()
        {
            return DecryptionTime;
        }
        public static byte[] GetHash(string input)
        {
            using (MD5 md5Hash = MD5.Create())
            {
                // Преобразуем входную строку в массив байтов
                byte[] inputBytes = Encoding.UTF8.GetBytes(input);

                // Вычисляем хэш-код для входных байтов
                byte[] hashBytes = md5Hash.ComputeHash(inputBytes);

                return hashBytes;
            }
        }
    }
}
