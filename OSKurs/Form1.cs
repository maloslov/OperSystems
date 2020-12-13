using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OSServer
{
    enum State { Empty, Server, Client };

    public partial class Form1 : Form
    {
        private static State mode = State.Empty;
        private static string message = "";
        private const int MAX_CLIENTS = 4;
        private const int MAX_BUFFER = 4096;
        private static Socket socket;
        private static IPAddress ipAddr;
        private static IPEndPoint ipEndPoint;
        private static List<Thread> t;
        private static List<Socket> clients;

        public Form1()
        {
            InitializeComponent();
            
        }

        #region Server

        private void serverEntry(int port, int n)
        {

            ipAddr = Dns.GetHostEntry("localhost").AddressList[0]; //.GetHostByName("localhost").AddressList[0]; // IPAddress.Any;
            ipEndPoint = new IPEndPoint(ipAddr, port);
            socket = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            //socket.ReceiveTimeout = 100;
            try
            {
                socket.Bind(ipEndPoint);
                socket.Listen(MAX_CLIENTS);
                //adr.Text = socket.LocalEndPoint.ToString();
                textBox1.Text += DateTime.Now + " - " + 
                    "Сервер " + ipEndPoint + 
                    " начинает работу как "+comboBox1.Text+"\r\n";

                t = new List<Thread>();
                clients = new List<Socket>();
                for(int i = 0; i < MAX_CLIENTS; i++)
                {
                    t.Add(new Thread(Getmsg));
                    t[i].Name = "Поток " + i;
                    clients.Add(null);
                    t[i].Start();
                    message += (DateTime.Now + " - " +
                        t[i].Name +
                        " ожидает соединение\r\n");
                }
                
                timer1.Start();

            } catch(SocketException e)
            {
                if (e.SocketErrorCode == SocketError.AddressAlreadyInUse)
                    serverEntry(port + 1, n);
            }
        }

        private void Getmsg()
        {
                int n = Convert.ToInt32(Thread.CurrentThread.Name.Split(' ')[1]);
            try
            {
                Socket client = socket.Accept();

                lock (clients)
                {
                    clients[n] = client;
                }

                lock (message)
                    message += (DateTime.Now + " - " +
                        Thread.CurrentThread.Name +
                        " принял соединение от " +
                        client.RemoteEndPoint + "\r\n");

                string data = "";

                // Мы дождались клиента, пытающегося с нами соединиться
                byte[] bytes = new byte[MAX_BUFFER];

                    int bytesRec = client.Receive(bytes);
                    data += Encoding.UTF8.GetString(bytes, 0, bytesRec);

                    // Показываем данные на консоли
                    lock (message)
                        message += (DateTime.Now + " - " +
                            Thread.CurrentThread.Name +
                            " получил запрос от " +
                            client.RemoteEndPoint + ": " +
                            data + "\r\n");

                    // Отправляем ответ клиенту
                    string reply = "Спасибо за запрос в " + data.Length.ToString()
                            + " символов";
                    byte[] msg = Encoding.UTF8.GetBytes(reply);
                    client.Send(msg);

                    lock (message)
                        message += (DateTime.Now + " - " +
                            Thread.CurrentThread.Name +
                            " завершил соединение с клиентом " +
                            client.RemoteEndPoint + "\r\n");
                }
                catch (SocketException se)
                {
                    if (se.SocketErrorCode == SocketError.ConnectionAborted)
                        lock (message)
                            message += DateTime.Now + " - " +
                        Thread.CurrentThread.Name +
                        " соединение разорвано\r\n";
                if (se.SocketErrorCode == SocketError.ConnectionReset)
                {
                    lock (message)
                        message += DateTime.Now + " - " +
                    Thread.CurrentThread.Name +
                    " соединение разорвано\r\n";
                    return;
                }

                } catch(ThreadInterruptedException tie)
            {

                //client.Shutdown(SocketShutdown.Both);
                //client.Close();

            }
            if (shutdown1.Enabled)
                lock (clients)
                {
                    clients[n].Shutdown(SocketShutdown.Both);
                    clients[n].Close();
                }

        }


        private void setup1_Click(object sender, EventArgs e)
        {
            if (comboBox1.Text == "")
                return;
            setup1.Enabled = false;
            connectButton.Enabled = false;
            disconnectButton.Enabled = false;
            shutdown1.Enabled = true;
            comboBox1.Enabled = false;
            mode = State.Server;
            serverEntry(11000, 1);
        }

        private void shutdown1_Click(object sender, EventArgs e)
        {
            setup1.Enabled = true;
            connectButton.Enabled = true;
            disconnectButton.Enabled = true;
            shutdown1.Enabled = false;
            comboBox1.Enabled = true;
        }
        #endregion

        #region Client

        private void clientEntry(object EndPoint)
        {
            IPEndPoint ep = (IPEndPoint)EndPoint;
            Socket s = new Socket(ep.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            
            try
            {
                s.Connect(ep);
            }catch(SocketException se)
            {

                if (se.SocketErrorCode == SocketError.ConnectionRefused)
                    lock (message)
                        textBox3.Text //message 
                            += (DateTime.Now + " - " +
                            Thread.CurrentThread.Name +
                            " сервер отказал в соединении " +
                            s.RemoteEndPoint + "\r\n");
                return;
            }
            MessageBox.Show(s.RemoteEndPoint.ToString());
            serverBox.Items.Add(s.RemoteEndPoint.ToString());
        }

        private void connectButton_Click(object sender, EventArgs e)
        {
            mode = State.Client;
            setup1.Enabled = false;
            sendButton.Enabled = true;
            disconnectButton.Enabled = true;
            int port;
            try { 
                port = Convert.ToInt32(connect1.Text);
            }
            catch(FormatException fe)
            {
                MessageBox.Show("Не удалось подключиться к указанному порту!",
                    "Внимание",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            ipAddr = Dns.GetHostEntry("localhost").AddressList[0];
            //ipAddr = IPAddress.Parse(str[0]);
            ipEndPoint = new IPEndPoint(ipAddr, port);
            if (serverBox.Items.Contains(ipEndPoint.ToString()))
            {
                MessageBox.Show("Соединение с этим сервером уже установлено!", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
            clientEntry(ipEndPoint);

        }

        private void disconnectButton_Click(object sender, EventArgs e)
        {
            mode = State.Empty;
            sendButton.Enabled = false;
            disconnectButton.Enabled = false;
            setup1.Enabled = true;
            serverBox.Items.Clear();
        }

        private void sendButton_Click(object sender, EventArgs e)
        {
            if (serverBox.Text == "" || commandBox.Text == "")
                return;

        }
        #endregion

        private void timer1_Tick(object sender, EventArgs e)
        {
            switch (mode)
            {
                case State.Server:
                    {
                        if (!shutdown1.Enabled)
                        {
                            for (int i = 0; i < MAX_CLIENTS; i++)
                            {
                                t[i].Interrupt();
                                //clients[i].Shutdown(SocketShutdown.Both);
                                //clients[i].Close();
                            }
                            //socket.Shutdown(SocketShutdown.Both);
                            textBox1.Text += DateTime.Now + " - " +
                                "Сервер " + ipEndPoint +
                                " завершил работу\r\n";
                            message = "";
                            socket.Close();
                            timer1.Stop();
                            mode = State.Empty;
                        }
                        else
                        {
                            textBox1.Text += message;
                            message = "";

                            for (int i = 0; i < MAX_CLIENTS; i++)
                            {
                                if (t[i].ThreadState == System.Threading.ThreadState.Stopped)
                                {
                                    t[i] = new Thread(Getmsg);
                                    t[i].Name = "Поток " + i;
                                    t[i].Start();
                                }
                            }

                        }
                        break;
                    }
                case State.Client:
                    {

                        break;
                    }
            }
        }

        private void comboBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            e.Handled = true;
        }
    }

    public class EndPoint : Object
    {
        public IPEndPoint ipEnd { get; set; }
        public int port { get; set; }
        public EndPoint(IPEndPoint p, int n)
        {
            ipEnd = p;
            port = n;
        }
    }
}
