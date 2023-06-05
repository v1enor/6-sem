using System.Text;

namespace lab3_1
{
    class Program
    {
        static void Main(string[] args)
        {
            RouteCipher route = new RouteCipher();
            Console.OutputEncoding = Encoding.Unicode;

            //encrypt
            const int key = 6;
            string msg = "";

            long oldTicks = DateTime.Now.Ticks;

            using (StreamReader sr = new StreamReader("Text.txt"))
            {
                msg = (sr.ReadToEnd());
                msg = msg.Replace(" ", "");
            }

            Console.WriteLine("Длинна сообщения:" + msg.Length);
            string resultRoute = route.Encrypt(msg, key);
            long timeCipher = (DateTime.Now.Ticks - oldTicks) / 1000;

            Console.WriteLine("\nИсходный текст:  " + msg);
            Console.WriteLine("Маршрутный шифр: " + resultRoute);
            Console.WriteLine("Расшифров текст: " + route.Decrypt(resultRoute, key));

            long timeUnCipher = ((DateTime.Now.Ticks - oldTicks ) / 1000)-timeCipher;
            Console.WriteLine("Затрачено на шифрование " + timeCipher + " мс\n");
            Console.WriteLine("Затрачено на дешифрование " + timeUnCipher + " мс\n");
        }
    }
}