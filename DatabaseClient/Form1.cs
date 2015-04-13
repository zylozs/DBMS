using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Security;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DatabaseClient
{
    public partial class Form1 : Form
    {
        private SqlConnection m_Connection;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            m_Connection = new SqlConnection(sqlConnection1.ConnectionString);

            SecureString pwd = txtPwd.SecurePassword;
            pwd.MakeReadOnly();
            SqlCredential cred = new SqlCredential(txtUserId.Text, pwd);
            m_Connection.Credential = cred;
            m_Connection.Open();
        }

        private void sqlConnection1_InfoMessage(object sender, SqlInfoMessageEventArgs e)
        {

        }
    }
}
