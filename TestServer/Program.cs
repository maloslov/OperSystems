using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Management;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace TestServer
{
    class Program
    {
        private static Socket sListener;
        private static IPHostEntry ipHost;
        private static IPAddress ipAddr;
        private static IPEndPoint ipEndPoint;
        private const int MAX_CLIENTS = 4;
        private const int MAX_BUFFER = 4096;

        static void Main(string[] args)
        {
            Console.WriteLine(Environment.MachineName + "\n" +
                Environment.UserName + "\n" +
                Environment.OSVersion + "\n" +
                "Is x64: " + Environment.Is64BitOperatingSystem + "\n");

                        
            ManagementObjectSearcher ramMonitor =    //запрос к WMI для получения памяти ПК
            new ManagementObjectSearcher("SELECT TotalVisibleMemorySize,FreePhysicalMemory FROM Win32_OperatingSystem");

            long totalRam = 0;
            foreach (ManagementObject objram in ramMonitor.Get())
            {
                totalRam = (long)Convert.ToUInt64(objram["TotalVisibleMemorySize"]);    //общая память ОЗУ
            //    ulong busyRam = totalRam - Convert.ToUInt64(objram["FreePhysicalMemory"]);         //занятная память = (total-free)
            //    Console.WriteLine(((busyRam * 100) / totalRam)+"%");       //вычисляем проценты занятой памяти
            }
            /*
            string prcName = Process.GetCurrentProcess().ProcessName;
            var counter = new PerformanceCounter("Process", "Working Set - Private", prcName);
            Console.WriteLine("{0} kBytes", counter.RawValue / 1024);
            Console.WriteLine(Environment.WorkingSet / 1024 + " kBytes\n" +
                Environment.GetEnvironmentVariable(""));
            */
            Process proc = Process.GetCurrentProcess();

            Console.WriteLine("Physical memory: " + proc.PeakWorkingSet64/1024 + " KB\n" +
                "Phys: "+ proc.WorkingSet64 / totalRam  +"%\n" +
                "Virtual memory: "+proc.VirtualMemorySize64 / 1024 + "KB\n" +
                "Virt: "+ proc.VirtualMemorySize64 / totalRam + "%\n");

            // Устанавливаем для сокета локальную конечную точку
            //ipHost =  //GetHostEntry("localhost");
            ipAddr = Dns.GetHostEntry("localhost").AddressList[0];//IPAddress.Any;
            ipEndPoint = new IPEndPoint(ipAddr, 11000);

            // Создаем сокет Tcp/Ip
            sListener = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            
            // Назначаем сокет локальной конечной точке и слушаем входящие сокеты
            try
            {
                sListener.Bind(ipEndPoint);
                sListener.Listen(MAX_CLIENTS);

                List<Thread> a = new List<Thread>();
                a.Capacity = 5;
                //Thread[] t;
                for (int i = 0; i < MAX_CLIENTS; i++)
                {
                    // t[i] = new Thread(Getmsg);
                    a.Add(new Thread(Getmsg));
                    a[i].Start();
                }
                // Начинаем слушать соединения
                while (true)
                {
                    /*
                    for(int i = 0; i < 4; i++)
                    {
                        
                        if (a[i].ThreadState == ThreadState.Stopped)
                            a[i] = null;
                        
                        if (a[i].Equals(null))
                            a[i] = new Thread(Getmsg);
                        a[i].Start();
                    }
                    */

                    for (int i = 0; i < MAX_CLIENTS; i++)
                    {
                        if (a[i].ThreadState == System.Threading.ThreadState.Stopped)
                        {
                            a[i] = new Thread(Getmsg);
                            a[i].Start();
                        }
                    }



                    /*
                    // Программа приостанавливается, ожидая входящее соединение
                    Socket handler = sListener.Accept();
                    string data = null;

                    // Мы дождались клиента, пытающегося с нами соединиться

                    byte[] bytes = new byte[1024];
                    int bytesRec = handler.Receive(bytes);

                    data += Encoding.UTF8.GetString(bytes, 0, bytesRec);

                    // Показываем данные на консоли
                    Console.Write("Полученный текст: " + data + "\n\n");

                    // Отправляем ответ клиенту\
                    string reply = "Спасибо за запрос в " + data.Length.ToString()
                            + " символов";
                    byte[] msg = Encoding.UTF8.GetBytes(reply);
                    handler.Send(msg);

                    if (data.IndexOf("<TheEnd>") > -1)
                    {
                        Console.WriteLine("Сервер завершил соединение с клиентом.");
                        //break;
                    }

                    handler.Shutdown(SocketShutdown.Both);
                    handler.Close();
                    */
                }
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

        private static void Getmsg()
        {
            Console.WriteLine("Ожидаем соединение через порт {0}", sListener.LocalEndPoint);
            Socket handler = sListener.Accept();

            string data = null;

            // Мы дождались клиента, пытающегося с нами соединиться
            byte[] bytes = new byte[MAX_BUFFER];
            //do {
                int bytesRec = handler.Receive(bytes);
                data += Encoding.UTF8.GetString(bytes, 0, bytesRec);
           // } while (bytes[MAX_BUFFER-1] != 0);

            // Показываем данные на консоли
            Console.Write("Полученный от {0} текст: {1}\n\n", handler.RemoteEndPoint, data);

            // Отправляем ответ клиенту\
            string reply = "Спасибо за запрос в " + data.Length.ToString()
                    + " символов";
            byte[] msg = Encoding.UTF8.GetBytes(reply);
            handler.Send(msg);

            if (data.IndexOf("<TheEnd>") > -1)
            {
                Console.WriteLine("Сервер завершил соединение с клиентом.");
                //break;
            }

            handler.Shutdown(SocketShutdown.Both);
            handler.Close();
            
        }
    }
}
