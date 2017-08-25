using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using CalculatorClassLib;

namespace WindowsCalculator
{
    public partial class Form1 : Form
    {
        
        Double firstValue, secondValue;
        String operator_1st = "";
        Boolean operator_pressed;
        Class1 obj;
        public Form1()
        {
            InitializeComponent();

            obj = new Class1();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            result.Clear();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button_Click(object sender, EventArgs e)
        {
            if (result.Text == "0" || operator_pressed)
            {
                result.Clear();
               
                operator_pressed = false;
            }
            Button b = (Button)sender;
            result.Text += b.Text;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
           

        }

        private void operator_click(object sender, EventArgs e)
        {
            Button b = (Button)sender;
            firstValue = Double.Parse(result.Text);
           
            operator_1st = b.Text;

            operator_pressed = true;

            
        }

        private void calculator(object sender, EventArgs e)
        {
           
         
            secondValue = Double.Parse(result.Text);

            Double res;
            switch (operator_1st) { 
                case "+":
                        res = obj.add(firstValue,secondValue);
                        result.Text = res.ToString();
                    break;
                case "-":
                       res = obj.sub(firstValue,secondValue);
                        result.Text = res.ToString();
                    break;
                case "*":
                        res = obj.mul(firstValue,secondValue);
                        result.Text = res.ToString();
                    break;
                case "/":
                       res = obj.div(firstValue,secondValue);
                        result.Text = res.ToString();
                    break;
              
            
            }
            firstValue = Double.Parse(result.Text);
            operator_pressed = true;
            secondValue = 0;
          
        }

        private void button19_Click(object sender, EventArgs e)
        {
            result.Clear();
            firstValue = 0;
            secondValue = 0;
          
        }

        private void button20_Click(object sender, EventArgs e)
        {
            Form myForm = new Form2();
            myForm.Show();
            this.Hide();
           
        }

        private void button11_Click(object sender, EventArgs e)
        {

        }
    }
}
