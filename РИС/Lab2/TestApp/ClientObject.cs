using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace TestApp
{
    public class ClientObject
    {
        public TcpClient client;
        object locker;
        const string path = @"C:\Users\ila\Desktop\share\text.txt";
        public ClientObject(TcpClient tcpClient, object locker)
        {
            this.locker = locker;
            client = tcpClient;
        }

        public void Process()
        {
            NetworkStream stream = null;
            bool statusFile = false;
            try
            {
                while (true)
                {
                    bool acquiredLock = false;
                    lock (locker)
                    {
                        Console.WriteLine($"Enter into critical section. Thread {Thread.CurrentThread.Name}");
                        statusFile = true;
                        stream = client.GetStream();
                        byte[] data = new byte[64]; // буфер для получаемых данных
                        int i = 0;
                        while (i < 5)
                        {
                            // получаем сообщение
                            StringBuilder builder = new StringBuilder();
                            int bytes = 0;
                            do
                            {
                                bytes = stream.Read(data, 0, data.Length);
                                builder.Append(Encoding.Unicode.GetString(data, 0, bytes));
                            }
                            while (stream.DataAvailable);

                            string message = builder.ToString();
                            using (StreamWriter str = new StreamWriter(path, true))
                            {
                                str.WriteLine(message);
                            }
                            Console.WriteLine(message);

                            // отправляем обратно сообщение в верхнем регистре
                            message = message.Substring(message.IndexOf(':') + 1).Trim().ToUpper();
                            data = Encoding.Unicode.GetBytes(message);
                            stream.Write(data, 0, data.Length);
                            i++;
                        }
                        Console.WriteLine($"Exit from critical section. Thread {Thread.CurrentThread.Name}");
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            finally
            {
                if (stream != null)
                    stream.Close();
                if (client != null)
                    client.Close();
            }
        }
    }
}
