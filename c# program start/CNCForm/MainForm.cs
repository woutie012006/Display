using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CNCForm
{
    public partial class MainForm : Form
    {
        //You can just use SerialPort1 it's added in the form code
        Administration administration;


        public MainForm(Administration administration)
        {
            InitializeComponent();
            this.administration = administration;

            serialPort1.NewLine = "#";

            rescanBtn.PerformClick();

            if (serialPortSelectionBox.Items.Count > 0) serialPortSelectionBox.SelectedIndex = 0;

        }
        //this works over usb pretty sure wifi works on a socket so, you should check how to change it 
        //just wanted to show it worked on usb :p
        //check http://forum.arduino.cc/index.php?topic=4871.0 for possible socket solution(should be tested with the hardware) 
        #region serial connection




        private void connectBtn_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
                connectBtn.Text = "Connect";
            }
            else
            {
                String port = serialPortSelectionBox.Text;
                try
                {
                    serialPort1.PortName = port;
                    serialPort1.Open();
                    if (serialPort1.IsOpen)
                    {
                        serialPort1.DiscardInBuffer();
                        serialPort1.DiscardOutBuffer();
                    }
                    connectBtn.Text = "Disconnect";
                }
                catch (Exception exception)
                {
                    Debug.WriteLine(exception);

                }
            }

        }


        private void rescanBtn_Click(object sender, EventArgs e)
        {
            String[] ports = SerialPort.GetPortNames();
            Array.Sort(ports);

            serialPortSelectionBox.Items.Clear();
            foreach (String port in ports)
            {
                serialPortSelectionBox.Items.Add(port);
            }
            
        }

        private void SendData(string s) 
        {
            serialPort1.Write(s);
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            //do stuff
        }
        #endregion

        
    }
}
