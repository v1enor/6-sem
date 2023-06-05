using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace TestApp
{
    class Program
    {
        static object locker = new();
        const int port = 8888;
        static TcpListener listener;
        const string path = @"C:\Users\ila\Desktop\share\test.txt";
        static void Main(string[] args)
        {
            try
            {
                Thread thread1, thread2;
                listener = new TcpListener(IPAddress.Parse("192.168.116.70"), port);
                listener.Start();
                Console.WriteLine("Ожидание подключений...");

                while (true)
                {
                    TcpClient client = listener.AcceptTcpClient();
                    ClientObject clientObject = new ClientObject(client, locker);
                    if(Thread.CurrentThread.Name != "First")
                    {
                        Thread.CurrentThread.Name = "First";
                        thread1 = new Thread(new ThreadStart(clientObject.Process));
                        thread1.Name = "First"; 
                        thread1.Start();
                    }
                    else
                    {
                        thread2 = new Thread(new ThreadStart(clientObject.Process));
                        thread2.Name = "Second";
                        thread2.Start();
                    }

                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            finally
            {
                if (listener != null)
                    listener.Stop();
            }
        }
    }
}
