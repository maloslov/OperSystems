using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OS_Prz3
{
    class Program
    {
        static void Main(string[] args)
        {
            Start:
            Console.WriteLine("0 - запуск с разным приоритетом\n1 - последовательный и параллельный запуск");
            int mode = Convert.ToInt32(Console.ReadLine());
            Stopwatch timer = new Stopwatch();
            switch (mode)
            {
                case 0:
                    {
                        Process a = new Process();
                        a.StartInfo.FileName = "C:\\Users\\Maloslov\\source\\repos\\OperShop\\Debug\\OS_PRZ3_Task1.exe";
                        timer.Reset();
                        timer.Start();
                        a.Start();
                        a.PriorityClass = ProcessPriorityClass.Normal;
                        Console.WriteLine("Base priority: " + a.BasePriority);
                        while (!a.HasExited) { }
                        timer.Stop();
                        Console.WriteLine("Total time: " + timer.Elapsed);
                        Console.WriteLine("PID: " + a.Id + "\n");

                        timer.Reset();
                        timer.Start();
                        a.Start();
                        a.PriorityClass = ProcessPriorityClass.High;
                        Console.WriteLine("Base priority: " + a.BasePriority);
                        while (!a.HasExited) { }
                        timer.Stop();
                        Console.WriteLine("Total time: " + timer.Elapsed);
                        Console.WriteLine("PID: " + a.Id + "\n");

                        break;
                    }
                case 1:
                    {
                        double ave;
                        Process a = new Process();
                        a.StartInfo.FileName = "C:\\Users\\Maloslov\\source\\repos\\OperShop\\Debug\\OS_PRZ3_Task1.exe";
                        
                        Process b = new Process();
                        b.StartInfo.FileName = "C:\\Users\\Maloslov\\source\\repos\\OperShop\\Debug\\OS_PRZ3_Task2.exe";
                        Process c = new Process();
                        c.StartInfo.FileName = "C:\\Users\\Maloslov\\source\\repos\\OperShop\\Debug\\OS_PRZ3_Task3.exe";


                        Console.WriteLine("Part 1 - последовательное");
                        timer.Reset();
                        timer.Start();
                        a.Start();
                        while(!a.HasExited) { }
                        timer.Stop();
                        Console.WriteLine("Time 1: " + timer.Elapsed);
                        ave = timer.Elapsed.TotalSeconds;
                        timer.Reset();
                        timer.Start();
                        b.Start();
                        while(!b.HasExited) { }
                        timer.Stop();
                        ave += timer.Elapsed.TotalSeconds;
                        Console.WriteLine("Time 2: " + timer.Elapsed);
                        timer.Reset();
                        timer.Start();
                        c.Start();
                        while(!c.HasExited) { }
                        timer.Stop();
                        ave += timer.Elapsed.TotalSeconds;
                        Console.WriteLine("Time 3: " + timer.Elapsed);
                        Console.WriteLine("Time average(s): " + (ave / 3));

                        Console.WriteLine("Part 2 - параллельное");
                        Stopwatch t1 = new Stopwatch();
                        Stopwatch t2 = t1;
                        Stopwatch t3 = t1;
                        timer.Reset();
                        timer.Start();
                        t1.Start();
                        a.Start();
                        a.PriorityClass = ProcessPriorityClass.High;
                        t2.Start();
                        b.Start();
                        t3.Start();
                        c.Start();
                        while(true) {
                            if (a.HasExited)
                                t1.Stop();
                            if (b.HasExited)
                                t2.Stop();
                            if (c.HasExited)
                                t3.Stop();
                            if (a.HasExited && b.HasExited && c.HasExited)
                                break;
                        }
                        timer.Stop();
                        Console.WriteLine("Time 1(приоритет): " + t1.Elapsed);
                        Console.WriteLine("Time 2: " + t2.Elapsed);
                        Console.WriteLine("Time 3: " + t3.Elapsed);
                        Console.WriteLine("Time: " + timer.Elapsed);

                        break;
                    }
            }

            if (Console.ReadLine() == "0")
                goto Start;
        }
    }
}
