using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CalculatorClassLib
{
    public class Class1:Interface1
    {


        public double add(double a, double b)
        {
            return a + b;
        }

        public double sub(double a, double b)
        {
            return a - b;
        }

        public double mul(double a, double b)
        {
            return a * b;
        }

        public double div(double a, double b)
        {
            return a / b;
        }


        public double sinx(double a)
        {
            return Math.Sin(a);
        }

        public double cosx(double a)
        {
            return Math.Cos(a);
        }

        public double tanx(double a)
        {
            return Math.Tan(a);
        }

        public double logx(double a)
        {
            return Math.Log(a);
        }
        public double expx(double a)
        {
            return Math.Log(a);
        }
        public double Modx(double a,double b)
        {
            return (a % b); 
        }
    }
}
