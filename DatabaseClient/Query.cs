using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DatabaseClient
{
    public partial class Query : Form
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

        private List<string> m_Attributes;

        public Query()
        {
            m_SQLCommand = "";
            m_Attributes = new List<string>();
            InitializeComponent();
        }

        public void initialize(Client parent)
        {
            m_Parent = parent;

            populateFromCheckboxes();
            clearCheckboxes(selectCheckedListBox);
        }

        public void addCondition(string left, string comparisonOperator, string right)
        {
            Console.WriteLine(left);
            Console.WriteLine(comparisonOperator);
            Console.WriteLine(right);
        }

        private void clearCheckboxes(CheckedListBox box)
        {
            box.Items.Clear();
        }

        private void populateFromCheckboxes()
        {
            clearCheckboxes(fromCheckedListBox);

            List<string> tables = m_Parent.ListTables();

            foreach (string str in tables)
            {
                fromCheckedListBox.Items.Add(str);                
            }
        }

        private void populateSelectCheckboxes()
        {
            clearCheckboxes(selectCheckedListBox);
            m_Attributes.Clear();

            foreach (string table in fromCheckedListBox.CheckedItems)
            {
                List<string> attributes = m_Parent.ListTableAttributes(table);

                foreach (string attr in attributes)
                {
                    string attName = table + "." + attr;
                    selectCheckedListBox.Items.Add(attName);
                    m_Attributes.Add(attName);
                }
            }
        }

        // Send Query (Build Query Tab)
        private void button2_Click(object sender, EventArgs e)
        {

        }

        private void fromCheckedListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            int index = fromCheckedListBox.SelectedIndex;
            bool value = fromCheckedListBox.GetItemChecked(index);
            fromCheckedListBox.SetItemChecked(index, value);

            populateSelectCheckboxes();
        }

        // Select Checkbox Change
        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            int index = selectCheckedListBox.SelectedIndex;
            bool value = selectCheckedListBox.GetItemChecked(index);
            selectCheckedListBox.SetItemChecked(index, value);
        }

        // New Condition
        private void button1_Click(object sender, EventArgs e)
        {
            if (m_Attributes == null || m_Attributes.Count == 0)
            {
                MessageBox.Show("You must select a table to add a condition.");
            }
            else
            {
                QueryCondition condition = new QueryCondition();
                condition.initialize(this, m_Attributes);

                condition.Show();
            }
        }

        // Send Query (SQL Tab)
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
