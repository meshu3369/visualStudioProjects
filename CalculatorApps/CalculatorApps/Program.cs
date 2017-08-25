using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CalculatorClassLib;

namespace CalculatorApps
{
    class Program
    {
        static void Main(string[] args)
        {
            int a = Convert.ToInt32(Console.ReadLine());
            int b = Convert.ToInt32(Console.ReadLine());

            Class1 obj = new Class1();
            int sum = obj.add(a,b);
            Console.WriteLine("this is your no: ",sum);
            Console.ReadKey();
        }
    }
}
