using Org.BouncyCastle.Crypto;
using Org.BouncyCastle.Crypto.Parameters;
using Org.BouncyCastle.Security;
using System;
using System.Diagnostics;
using System.Text;

namespace ZinizCourceProject.Model
{
    internal class SerpnetEncryptor
    {

        public static string EncryptionTime { get; private set; }
        public static string DecryptionTime { get; private set; }

        public static string GetEncriptionTime()
        {
            return EncryptionTime;
        }

        public static string GetDecriptionTime()
        {
            return DecryptionTime;
        }


        public static string Encrypt(string inputText, string key)
        {
            byte[] inputBytes = Encoding.UTF8.GetBytes(inputText);
            byte[] keyBytes = AesEncryptor.GetHash(key);
  
            byte[] ivBytes = (byte[])keyBytes.Clone();
            Array.Sort(ivBytes);


            Stopwatch stopwatch = Stopwatch.StartNew(); // запускаем таймер
            IBufferedCipher cipher = CipherUtilities.GetCipher("Serpent/CBC/PKCS7Padding");
            cipher.Init(true, new ParametersWithIV(new KeyParameter(keyBytes), ivBytes));
            byte[] encryptedBytes = cipher.DoFinal(inputBytes);

            stopwatch.Stop(); // останавливаем таймер
            TimeSpan ts = stopwatch.Elapsed; // получаем затраченное время
            EncryptionTime = $"{ts.TotalMilliseconds} ms"; // устанавливаем значение свойства, связанного с текстом времени выполнения шифрования

            return Convert.ToBase64String(encryptedBytes);
        }

        public static  string Decrypt(string encryptedText, string key)
        {
            byte[] encryptedBytes = Convert.FromBase64String(encryptedText);
            byte[] keyBytes = AesEncryptor.GetHash(key);
            byte[] ivBytes = (byte[])keyBytes.Clone();
            Array.Sort(ivBytes);


            Stopwatch stopwatch = Stopwatch.StartNew(); // запускаем таймер
            IBufferedCipher cipher = CipherUtilities.GetCipher("Serpent/CBC/PKCS7Padding");
            cipher.Init(false, new ParametersWithIV(new KeyParameter(keyBytes), ivBytes));
            byte[] decryptedBytes = cipher.DoFinal(encryptedBytes);
            stopwatch.Stop(); // останавливаем таймер
            TimeSpan ts = stopwatch.Elapsed; // получаем затраченное время
            DecryptionTime = $"{ts.TotalMilliseconds} ms"; // устанавливаем значение свойства, связанного с текстом времени выполнения шифрования

            return Encoding.UTF8.GetString(decryptedBytes);
        }
    }
}
