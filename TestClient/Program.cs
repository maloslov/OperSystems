using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace TestClient
{
    class Program
    {
        private const int MAX_BUFFER = 4096;
        static void Main(string[] args)
        {
            try
            {
                SendMessageFromSocket(11000);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
            finally
            {
                Console.ReadLine();
            }
        }

        static void SendMessageFromSocket(int port)
        {

            // Соединяемся с удаленным устройством

            // Устанавливаем удаленную точку для сокета
            IPAddress ipAddr = Dns.GetHostEntry("localhost").AddressList[0]; //.GetHostByName("localhost").AddressList[0];
             //IPAddress.Parse("192.168.1.197"); //ipHost.AddressList[0];
            IPEndPoint ipEndPoint = new IPEndPoint(ipAddr, port);
            

            Socket sender = new Socket(ipEndPoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            
            // Соединяем сокет с удаленной точкой
            sender.Connect(ipEndPoint);

            Console.Write("Введите сообщение: ");
            string message = Console.ReadLine();

            Console.WriteLine("Сокет соединяется с {0} ", sender.RemoteEndPoint.ToString());
            byte[] msg = Encoding.UTF8.GetBytes(message);
            // Буфер для входящих данных
            byte[] bytes = new byte[MAX_BUFFER];
            int bytesSend = sender.Send(msg);

            string buf = null;

                // Получаем ответ от сервера
                int bytesRec = sender.Receive(bytes);

                buf += Encoding.UTF8.GetString(bytes, 0, bytesRec);

            Console.WriteLine("\nОтвет от сервера: {0}\n\n", buf);

            // Используем рекурсию для неоднократного вызова SendMessageFromSocket()
            if (message.IndexOf("<TheEnd>") == -1)
                SendMessageFromSocket(port);

            // Освобождаем сокет
            sender.Shutdown(SocketShutdown.Both);
            sender.Close();
        }
    }
}