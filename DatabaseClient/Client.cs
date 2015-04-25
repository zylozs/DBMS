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
    public partial class Client : Form
    {
        private SqlConnection m_Connection;
        private SqlDataAdapter m_DataAdapter;
        private DataSet m_DataSet;
        private SqlCommandBuilder m_CmdBuilder;

        public Client()
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

        public List<string> ListTables()
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

        public List<string> ListTableAttributes(string tableName)
        {
            List<string> attributes = new List<string>();
            string sql = "SELECT * FROM " + tableName + " WHERE 1=0";

            m_DataAdapter = new SqlDataAdapter(sql, m_Connection);
            m_DataSet = new DataSet();
            m_CmdBuilder = new SqlCommandBuilder(m_DataAdapter);

            m_DataAdapter.Fill(m_DataSet, tableName);
            foreach (DataColumn col in m_DataSet.Tables[0].Columns)
            {
                attributes.Add(col.ColumnName);
            }

            return attributes;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            executeSQL("SELECT * FROM " + comboBox1.SelectedItem.ToString(), comboBox1.SelectedItem.ToString());
        }

        public bool executeSQL(string sql)
        {
            m_DataAdapter = new SqlDataAdapter(sql, m_Connection);
            m_DataSet = new DataSet();
            m_CmdBuilder = new SqlCommandBuilder(m_DataAdapter);

            try
            {
                m_DataAdapter.Fill(m_DataSet);

                if (m_DataSet.Tables.Count > 0)
                    dataGridView1.DataSource = m_DataSet.Tables[0];
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return false;
            }

            return true;
        }

        public bool executeSQL(string sql, string table)
        {
            m_DataAdapter = new SqlDataAdapter(sql, m_Connection);
            m_DataSet = new DataSet();
            m_CmdBuilder = new SqlCommandBuilder(m_DataAdapter);

            try
            {
                m_DataAdapter.Fill(m_DataSet, table);
                dataGridView1.DataSource = m_DataSet.Tables[table];
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return false;
            }

            return true;
        }

        // Query Popup
        private void button2_Click(object sender, EventArgs e)
        {
            Query query = new Query();
            query.initialize(this);

            query.Show();
        }

        // Send SQL Button
        private void button3_Click(object sender, EventArgs e)
        {
            SendSQL popup = new SendSQL();
            popup.initialize(this);

            popup.Show();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                int changes = 0;
                m_DataAdapter.UpdateCommand = m_CmdBuilder.GetUpdateCommand();
                changes = m_DataAdapter.Update(m_DataSet.Tables[comboBox1.SelectedItem.ToString()]);

                MessageBox.Show(changes.ToString() + " Record(s) Updated.");
            }

            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
