using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace TestClient
{
    class Program
    {
        const int port = 8888;
        const string address = "192.168.116.70";
        static void Main(string[] args)
        {
            Console.Write("Введите свое имя:");
            string userName = Console.ReadLine();
            TcpClient client = null;
            int i = 0;
            try
            {
                client = new TcpClient(address, port);

                while (true)
                {
                    NetworkStream stream = client.GetStream();
                    Console.Write(userName + ": ");
                    byte[] data;
                    string message;
                    // ввод сообщения
                    message = $"{DateTime.Now.Hour}:{DateTime.Now.Minute}:{DateTime.Now.Second}";
                    message = String.Format("{0}: {1}", userName, message);

                    // преобразуем сообщение в массив байтов
                    data = Encoding.Unicode.GetBytes(Convert.ToString(message));
                    // отправка сообщения
                    stream.Write(data, 0, data.Length);

                    // получаем ответ
                    data = new byte[64]; // буфер для получаемых данных
                    StringBuilder builder = new StringBuilder();
                    int bytes = 0;
                    do
                    {
                        bytes = stream.Read(data, 0, data.Length);
                        builder.Append(Encoding.Unicode.GetString(data, 0, bytes));
                    }
                    while (stream.DataAvailable);

                    message = builder.ToString();
                    Console.WriteLine("Сервер: {0}", message);
                    Thread.Sleep(5000);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            finally
            {
                client.Close();
            }
        }
    }
}
