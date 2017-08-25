using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace BMIwebapps
{
    public partial class BmiForm : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            resultMsg.Visible = false;
        }

        protected void submit_click(object sender, EventArgs e)
        {
            Double heightx_a, heightx_b, weightx, bmi, heightx;

            heightx_a = Double.Parse(height_ft.Text);
            heightx_b = Double.Parse(height.Text);
            heightx_a = heightx_a * 0.3048;
            heightx_b = heightx_b * 0.0254;
            heightx = heightx_a + heightx_b;

            weightx = Double.Parse(weight.Text);

            bmi = (double) weightx / (heightx * heightx);

            String bmi_comment = "";
            if(bmi < 18.5){
                bmi_comment = "you are underweight";
                resultMsg.Attributes["class"] = "alert alert-danger";
            }else if(bmi < 24.9){
                //normal weight;
                bmi_comment = "you are in normal weight";
                resultMsg.Attributes["class"] = "alert alert-success";
            }
            else if (bmi < 29.9)
            {
                //Overweight
                bmi_comment = "you are Overweight";
                resultMsg.Attributes["class"] = "alert alert-warning";
            }
            else if(bmi > 30) { 
              //obesity
                bmi_comment = "you are in obesity. Please consult a doctor";
                resultMsg.Attributes["class"] = "alert alert-danger";
            }


            resultMsg.InnerHtml = "Mr "+username.Text +" your BMI is "+ bmi + ". <br>"+bmi_comment;

            resultMsg.Visible = true;
        }
    }
}