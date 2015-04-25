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
        private int m_NumSelectedChecked;
        private int m_NumFromChecked;

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
            int index = dataGridView1.Rows.Add(1);
            dataGridView1[0, index].Value = left;
            dataGridView1[1, index].Value = comparisonOperator;
            dataGridView1[2, index].Value = right;
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

        // Send Query Button
        private void button2_Click_1(object sender, EventArgs e)
        {
            string error = "";

            // From Check
            bool valid = false;
            for (int i = 0; i < fromCheckedListBox.Items.Count; i++)
            {
                if (fromCheckedListBox.GetItemChecked(i))
                    valid = true;
            }

            if (!valid)
                error += "- You must select a table to query from.\n";

            // Select Check
            valid = false;
            for (int i = 0; i < selectCheckedListBox.Items.Count; i++)
            {
                if (selectCheckedListBox.GetItemChecked(i))
                    valid = true;
            }

            if (!valid)
                error += "- You must select an attribute.\n";

            // Error check, otherwise build the SQL string
            if (error != "")
            {
                MessageBox.Show(error);
            }
            else
            {
                m_SQLCommand = "SELECT ";
                
                int count = 0;
                // Add all selected items with commas between
                for (int i = 0; i < selectCheckedListBox.Items.Count; i++)
                {
                    if (selectCheckedListBox.GetItemChecked(i))
                    {
                        if (count != 0 && count <= m_NumSelectedChecked)
                            m_SQLCommand += ", ";

                        m_SQLCommand += selectCheckedListBox.Items[i].ToString();

                        count++;
                    }
                }

                m_SQLCommand += " FROM ";

                // Add tables with commas between
                count = 0;
                for (int i = 0; i < fromCheckedListBox.Items.Count; i++)
                {
                    if (fromCheckedListBox.GetItemChecked(i))
                    {
                        if (count != 0 && count <= m_NumFromChecked)
                            m_SQLCommand += ", ";

                        m_SQLCommand += fromCheckedListBox.Items[i].ToString();

                        count++;
                    }
                }

                if (dataGridView1.Rows.Count > 0)
                    m_SQLCommand += " WHERE ";

                // Add conditions
                for (int i = 0; i < dataGridView1.Rows.Count; i++)
                {
                    if (i != 0 && i + 1 != dataGridView1.Rows.Count)
                        m_SQLCommand += " AND ";

                    DataGridViewCellCollection cells = dataGridView1.Rows[i].Cells;
                    m_SQLCommand += cells[0].Value + " ";
                    m_SQLCommand += cells[1].Value + " ";
                    m_SQLCommand += cells[2].Value;
                }

                // Execute the command
                if (m_Parent.executeSQL(m_SQLCommand))
                    Close();
            }
        }

        // Select Checkbox Change
        private void selectCheckedListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            int index = selectCheckedListBox.SelectedIndex;
            bool value = selectCheckedListBox.GetItemChecked(index);
            selectCheckedListBox.SetItemChecked(index, !value);

            m_NumSelectedChecked = 0;

            for (int i = 0; i < selectCheckedListBox.Items.Count; i++)
            {
                if (selectCheckedListBox.GetItemChecked(i))
                    m_NumSelectedChecked++;
            }
        }

        // New Condition
        private void button1_Click_1(object sender, EventArgs e)
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

        // From Checkbox Change
        private void fromCheckedListBox_SelectedIndexChanged_1(object sender, EventArgs e)
        {
            int index = fromCheckedListBox.SelectedIndex;
            bool value = fromCheckedListBox.GetItemChecked(index);
            fromCheckedListBox.SetItemChecked(index, !value);

            m_NumFromChecked = 0;

            for (int i = 0; i < fromCheckedListBox.Items.Count; i++)
            {
                if (fromCheckedListBox.GetItemChecked(i))
                    m_NumFromChecked++;
            }

            populateSelectCheckboxes();
        }
    }
}