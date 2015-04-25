using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DatabaseClient
{
    public partial class SendSQL : Form
    {
        private Client m_Parent;
        public Client Parent
        {
            get { return m_Parent; }
            set { m_Parent = value; }
        }

        private string m_SQLCommand;
        public string SQLCommand
        {
            get { return m_SQLCommand; }
        }

        public SendSQL()
        {
            InitializeComponent();
        }

        public void initialize(Client parent)
        {
            m_Parent = parent;
        }

        // Send SQL Button
        private void button3_Click(object sender, EventArgs e)
        {
            m_SQLCommand = textBox1.Text;

            if (m_SQLCommand != "")
            {
                if (m_Parent.executeSQL(m_SQLCommand))
                    Close();
            }
            else
                MessageBox.Show("You must specify an SQL Query first.");
        }
    }
}
