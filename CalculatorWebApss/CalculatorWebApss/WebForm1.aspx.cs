using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using CalculatorClassLib;

namespace CalculatorWebApss
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        Double firstValue, secondValue;
        String operator_1st = "";
        Boolean operator_pressed;
        Class1 obj;

     
        protected void Page_Load(object sender, EventArgs e)
        {

            obj = new Class1();
            if(!IsPostBack){
                setUpAll();
            }
            
        }
        protected void setUpAll() {
            Session.Add("firstValue", "0");
            Session.Add("secondValue", "0");
            Session.Add("operator_1st", operator_1st);
            Session.Add("operator_pressed", operator_pressed);
        }

        protected void button_Click(object sender, EventArgs e)
        {
            if (result.Text == "0" || operator_pressed)
            {
                result.Text = "";

                operator_pressed = false;
            }
            Button b = (Button)sender;
            if(b.Text == "π"){
                result.Text = "3.1416";
            }else
               result.Text += b.Text;
        }

        protected void operator_click(object sender, EventArgs e)
        {

            Button b = (Button)sender;
            firstValue = Double.Parse(result.Text);
          
            this.operator_1st = b.Text;

            Session["firstValue"] = result.Text;
            Session["operator_1st"] = b.Text;

            result.Text = "";
           
        }

      
        protected void Button18_Click(object sender, EventArgs e)
        {
            result.Text = "";
            firstValue = 0;
            secondValue = 0;
          
            result.Text = operator_1st;
        }

        protected void Button19_Click(object sender, EventArgs e)
        {
            result.Text = operator_1st;
        }

        protected void calc(object sender, EventArgs e)
        {
         
        
        
            firstValue = Double.Parse((String) Session["firstValue"]);
            operator_1st = (String)Session["operator_1st"];
         
          

            Double res;
            switch (operator_1st)
            {
                case "+":
                    secondValue = Double.Parse(result.Text);
                    res = obj.add(firstValue, secondValue);
                    result.Text = res.ToString();
                 

                    break;
                case "-":
                    secondValue = Double.Parse(result.Text);
                    res = obj.sub(firstValue, secondValue);
                    result.Text = res.ToString();
                    break;
                case "*":
                    secondValue = Double.Parse(result.Text);
                    res = obj.mul(firstValue, secondValue);
                    result.Text = res.ToString();
                    break;
                case "/":
                    secondValue = Double.Parse(result.Text);
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
                    secondValue = Double.Parse(result.Text);
                    res = obj.Modx(firstValue, secondValue);
                    result.Text = res.ToString();
                    break;

            }


            Session["firstValue"] = result.Text;
           
        }

        protected void ImageButton1_Click(object sender, ImageClickEventArgs e)
        {
            labelHH.InnerText = "";
            if (scientific_section_one.Visible)
            {
                labelHH.InnerText = "Standard";
                scientific_section_one.Visible = false;
                scientific_section_two.Visible = false;
                
            }
            else
            {
                labelHH.InnerText = "Scientific";
                scientific_section_one.Visible = true;
                scientific_section_two.Visible = true;
            }
        }

    }
}