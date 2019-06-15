using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.IO.Ports;
namespace SerialCommunicate
{
    public partial class Form1 : Form
    {
        bool BtnchuankouStatue;
        public Form1()
        {
            InitializeComponent();
            System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false;

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)                                     //串口打开就关闭
            {
                try
                {
                    serialPort1.Close();
                    comboBox1.Enabled = true;   //端口列表可用                
                }
                catch { }                                               //确保万无一失
                button1.BackgroundImage = Properties.Resources.guan;
                BtnchuankouStatue = false;
            }
            else
            {
                try
                {
                    serialPort1.PortName = comboBox1.Text;              //端口号
                    serialPort1.Open();
                    button1.BackgroundImage = Properties.Resources.kai;      //图标亮 可以判断串口是否打开
                    BtnchuankouStatue = true;                                //按钮状态
                    comboBox1.Enabled = false;   //端口列表不可用
                    //serialPort1.DataReceived += new SerialDataReceivedEventHandler(serialPort1_DataReceived);
                }
                catch
                {
                    MessageBox.Show("串口打开失败", "错误");
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            timer1.Interval = 100;   //刷新容器的间隔
            timer1.Enabled = true;
            /*****************非常重要************************/

            serialPort1.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);//必须手动添加事件处理程序

        }

        private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)//串口数据接收事件
        {
            string data1=null;
            string data2 = null;
            string data3 = null;
            string data4 = null;
            string data5 = null;

            try
            {


                string str1 = serialPort1.ReadTo("\n");
                //string str2 = serialPort1.ReadTo("$");
                data1 = str1.Substring(0, 2);   //温度
                data2 = str1.Substring(4, 2); //== null || int.Parse(str1.Substring(4, 2)) <= 60 ? "72" : str1.Substring(4, 2);   //湿度

                data3 = str1.Substring(9, 1);   //是否有人
                data4 = str1.Substring(6, 3);   //烟雾
                data5 = str1.Substring(10, 3);   //土壤湿度
            } 
            catch
            {

              
            }

            textBox1.Text = data1;
            textBox2.Text = data2;
            textBox4.Text = data4;
            textBox5.Text = data5;
            if (data3 == "1")
            { textBox3.Text = "是"; }
            else
            { textBox3.Text = "否"; }

        }

        private void SearchAndAddSerialToComboBox(SerialPort MyPort, ComboBox MyBox)
        {                                                               //将可用端口号添加到ComboBox
            //string[] MyString = new string[20];                         //最多容纳20个，太多会影响调试效率
            string Buffer;                                              //缓存
            MyBox.Items.Clear();                                        //清空ComboBox内容
            //int count = 0;
            for (int i = 1; i < 20; i++)                                //循环
            {
                try                                                     //核心原理是依靠try和catch完成遍历
                {
                    Buffer = "COM" + i.ToString();
                    MyPort.PortName = Buffer;
                    MyPort.Open();                                      //如果失败，后面的代码不会执行
                    // MyString[count] = Buffer;
                    MyBox.Items.Add(Buffer);                            //打开成功，添加至下拉列表
                    MyPort.Close();                                     //关闭
                    //count++;
                }
                catch
                {
                    //count--;
                }
            }
            //MyBox.Text = MyString[0];                                   //初始化
        }

        private void button2_Click(object sender, EventArgs e)
        {
            SearchAndAddSerialToComboBox(serialPort1, comboBox1);       //扫描并将可用串口添加至下拉列表
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            groupBox4.Refresh();  //刷新该容器
        }

        private void button1_MouseLeave(object sender, EventArgs e)
        {
            if (BtnchuankouStatue)
            {
                button1.BackgroundImage = Properties.Resources.kai;
            }
            else
            {
                button1.BackgroundImage = Properties.Resources.guan;
            }
        }

        private void button1_MouseMove(object sender, MouseEventArgs e)
        {
            button1.BackgroundImage = Properties.Resources.zhunbei;
        }

        private void label10_Click(object sender, EventArgs e)
        {

        }

        private void groupBox3_Enter(object sender, EventArgs e)
        {

        }

        private void Label4_Click(object sender, EventArgs e)
        {

        }

        private void TextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }
    }
}
