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
    public partial class Form2 : Form
    {
        Double firstValue, secondValue;
        String operator_1st = "";
        Boolean operator_pressed;
        Class1 obj;

        public Form2()
        {
            InitializeComponent();
            obj = new Class1();
        }

        private void button20_Click(object sender, EventArgs e)
        {
            Form myForm = new Form1();
            this.Hide();
            myForm.Show();
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

          
            switch (operator_1st)
            {
                case "+":
                    res = obj.add(firstValue, secondValue);
                    result.Text = res.ToString();
                    break;
                case "-":
                    res = obj.sub(firstValue, secondValue);
                    result.Text = res.ToString();
                    break;
                case "*":
                    res = obj.mul(firstValue, secondValue);
                    result.Text = res.ToString();
                    break;
                case "/":
                    res = obj.div(firstValue, secondValue);
                    result.Text = res.ToString();
                    break;
                case "sin":
                    res = obj.sinx(firstValue);
                    result.Text = res.ToString();
                    break;
                case "cos":
                    res = obj.cosx(firstValue);
                    result.Text = res.ToString();
                    break;
                case "tan":
                    res = obj.tanx(firstValue);
                    result.Text = res.ToString();
                    break;
                case "log":
                    res = obj.logx(firstValue);
                    result.Text = res.ToString();
                    break;
                case "exp":
                    res = obj.expx(firstValue);
                    result.Text = res.ToString();
                    break;
                case "Mod":
                    res = obj.Modx(firstValue,secondValue);
                    result.Text = res.ToString();
                    break;
            }
            firstValue =Double.Parse(result.Text);
            operator_pressed = true;
            secondValue = 0;

        }

        private void button19_Click(object sender, EventArgs e)
        {
            result.Clear();
            firstValue = 0;
            secondValue = 0;
           
        }

        private void button5_Click(object sender, EventArgs e)
        {
            result.Clear();
        }

        private void pie_click(object sender, EventArgs e)
        {
            result.Text += "3.1416";
        }

        private void logarithm_click(object sender, EventArgs e)
        {
            Button b = (Button)sender;
            firstValue = Double.Parse(result.Text);
           // history.Text = b.Text +"( " + result.Text + " )";
            operator_1st = b.Text;
            operator_pressed = true;
           
        }

       
    }
}
