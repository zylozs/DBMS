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
        private SqlDataAdapter m_DataAdapter;
        private DataSet m_DataSet;
        private SqlCommandBuilder m_CmdBuilder;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                m_Connection = new SqlConnection(sqlConnection1.ConnectionString);
                m_Connection.Open();

                comboBox1.Items.AddRange(ListTables().ToArray());
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private List<string> ListTables()
        {
            List<string> tables = new List<string>();
            DataTable dt = m_Connection.GetSchema("Tables");
            foreach (DataRow row in dt.Rows)
            {
                string tablename = (string)row[2];
                tables.Add(tablename);
            }
            return tables;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_DataAdapter = new SqlDataAdapter("SELECT * FROM " + comboBox1.SelectedItem.ToString(), m_Connection);
            m_DataSet = new DataSet();
            m_CmdBuilder = new SqlCommandBuilder(m_DataAdapter);

            try
            {
                m_DataAdapter.Fill(m_DataSet, comboBox1.SelectedItem.ToString());
                dataGridView1.DataSource = m_DataSet.Tables[comboBox1.SelectedItem.ToString()];
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        // Query Popup
        private void button2_Click(object sender, EventArgs e)
        {

        }
    }
}
