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
    public partial class QueryCondition : Form
    {
        private Query m_Parent;
        public Query Parent
        {
            get { return m_Parent; }
            set { m_Parent = value; }
        }

        public QueryCondition()
        {
            InitializeComponent();

            hideLeftSide();
            hideRightSide();
        }

        public void initialize(Query parent, List<string> attributes)
        {
            m_Parent = parent;

            foreach (string attr in attributes)
            {
                comboBox2.Items.Add(attr);
                comboBox3.Items.Add(attr);
            }
        }

        private void hideLeftSide()
        {
            // Left Side
            comboBox2.Visible = false;
            textBox1.Visible = false;
        }

        private void hideRightSide()
        {
            // Right Side
            comboBox3.Visible = false;
            textBox2.Visible = false;
        }

        // Left Side Combo Box
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            hideLeftSide();

            switch(comboBox1.SelectedIndex)
            {
                case 0:
                    comboBox2.Visible = true;
                    break;
                case 1:
                    textBox1.Visible = true;
                    break;
            }
        }

        // Operator Combo Box
        private void comboBox5_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        // Right Side Combo Box
        private void comboBox4_SelectedIndexChanged(object sender, EventArgs e)
        {
            hideRightSide();

            switch (comboBox4.SelectedIndex)
            {
                case 0:
                    comboBox3.Visible = true;
                    break;
                case 1:
                    textBox2.Visible = true;
                    break;
            }
        }

        // Ok Button
        private void button1_Click(object sender, EventArgs e)
        {
            bool valid = true;
            string left = "";
            string comparisonOperator = "";
            string right = "";

            // Left Side Check
            switch(comboBox1.SelectedIndex)
            {
                case 0:
                    if (comboBox2.SelectedIndex == -1)
                        valid = false;
                    else
                        left = comboBox2.SelectedItem.ToString();
                    break;
                case 1:
                    if (textBox1.Text == "")
                        valid = false;
                    else
                        left = textBox1.Text;
                    break;
            }

            // Operator Check
            if (comboBox5.SelectedIndex == -1)
                valid = false;
            else
            {
                // Grab the string from the begin to the first space as the operator
                string text = comboBox5.SelectedItem.ToString();
                text = text.Substring(0, text.IndexOf(' '));
                comparisonOperator = text;
            }

            // Right Side Check
            switch (comboBox4.SelectedIndex)
            {
                case 0:
                    if (comboBox3.SelectedIndex == -1)
                        valid = false;
                    else
                        right = comboBox3.SelectedItem.ToString();
                    break;
                case 1:
                    if (textBox2.Text == "")
                        valid = false;
                    else
                        right = textBox2.Text;
                    break;
            }

            if (valid)
            {
                m_Parent.addCondition(left, comparisonOperator, right);
                Close();
            }
            else
                MessageBox.Show("Please select everything before hitting ok.");
        }

        // Cancel Button
        private void button2_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}