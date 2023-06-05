using System;
using System.Diagnostics;
using System.Linq;
using System.Text;
using Rebex.Security.Cryptography;
using ZinizCourceProject.View.Pages;

namespace ZinizCourceProject.Model
{
    internal class TwoFishEncryptor
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
        public static string EncryptTwofish(string plaintext, string MsgKey)
        {
            byte[] plaintextBytes = Encoding.UTF8.GetBytes(plaintext);
            byte[] key = AesEncryptor.GetHash(MsgKey);

            byte[] iv = (byte[])key.Clone();
            Array.Sort(iv);
            using (TwofishManaged twofish = new TwofishManaged())
            {
                twofish.Key = key;
                twofish.IV= iv;
                

                using (var encryptor = twofish.CreateEncryptor())
                {
                    Stopwatch stopwatch = Stopwatch.StartNew(); // запускаем таймер
                    byte[] cipherText = encryptor.TransformFinalBlock(plaintextBytes, 0, plaintextBytes.Length);
                    byte[] result = new byte[iv.Length + cipherText.Length];
                    Buffer.BlockCopy(iv, 0, result, 0, iv.Length);
                    Buffer.BlockCopy(cipherText, 0, result, iv.Length, cipherText.Length);

                    stopwatch.Stop(); // останавливаем таймер
                    TimeSpan ts = stopwatch.Elapsed; // получаем затраченное время
                    EncryptionTime = $"{ts.TotalMilliseconds} ms"; // устанавливаем значение свойства, связанного с текстом времени выполнения шифрования

                    return Convert.ToBase64String(result);
                }
            }
        }


        public static string DecryptTwofish(string cipherText, string MsgKey)
        {
            byte[] cipherTextBytes = Convert.FromBase64String(cipherText);
            byte[] key = AesEncryptor.GetHash(MsgKey);
            byte[] iv = (byte[])key.Clone();
            Array.Sort(iv);
            using (TwofishManaged twofish = new TwofishManaged())
            {
                twofish.Key = key;
                twofish.IV = iv;
                Buffer.BlockCopy(cipherTextBytes, 0, iv, 0, iv.Length);
                

                using (var decryptor = twofish.CreateDecryptor())
                {
                    Stopwatch stopwatch = Stopwatch.StartNew(); // запускаем таймер
                    byte[] plainTextBytes = decryptor.TransformFinalBlock(cipherTextBytes, iv.Length, cipherTextBytes.Length - iv.Length);

                    stopwatch.Stop(); // останавливаем таймер
                    TimeSpan ts = stopwatch.Elapsed; // получаем затраченное время
                    DecryptionTime = $"{ts.TotalMilliseconds} ms"; // устанавливаем значение свойства, связанного с текстом времени выполнения шифрования

                    return Encoding.UTF8.GetString(plainTextBytes);
                }
            }
        }

        
        
    }

}
