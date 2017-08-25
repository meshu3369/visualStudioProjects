<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="WebForm1.aspx.cs" Inherits="CalculatorWebApss.WebForm1" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
 
<head runat="server">
    <title>Calculator</title>
    <link rel="stylesheet" href="StyleSheet1.css" />
</head>
<body>
    <form id="form1" runat="server">
     <div>
       <asp:ImageButton ID="ImageButton1" runat="server" Height="29px" ImageUrl="~/Images/bar_icon.png" Width="32px" OnClick="ImageButton1_Click" />
        <h4 class="heading_top" runat="server" id="labelHH">Standard</h4>
     </div>
        <br />
        <div >
        </div>
       
     <div >
            <asp:TextBox ID="result" runat="server" Height="31px" Width="304px"></asp:TextBox>
        </div>
          <div class="button_area" runat="server" id="scientific_section_one">
            <asp:Button cssClass="number_button scientific_btn" ID="Button20" runat="server" Height="45px" Text="sin" Width="45px" OnClick="operator_click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="number_button scientific_btn" ID="Button21" runat="server" Height="45px" Text="cos" Width="45px" OnClick="operator_click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="number_button scientific_btn" ID="Button22" runat="server" Height="45px" Text="tan" Width="45px" OnClick="operator_click" BackColor="Black" ForeColor="White" />
            

         </div>


        <div class="button_area"  runat="server" id="scientific_section_two">
            <asp:Button cssClass="number_button scientific_btn" ID="Button1" runat="server" Height="45px" Text="log" Width="45px" OnClick="operator_click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="number_button scientific_btn" ID="Button2" runat="server" Height="45px" Text="exp" Width="45px" OnClick="operator_click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="number_button scientific_btn" ID="Button10" runat="server" Height="45px" Text="Mod" Width="45px" OnClick="operator_click" BackColor="Black" ForeColor="White" />
         </div>
        <div class="button_area">
            <asp:Button cssClass="number_button" ID="Button23" runat="server" Height="45px" Text="7" Width="45px" OnClick="button_Click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="number_button" ID="Button24" runat="server" Height="45px" Text="8" Width="45px" OnClick="button_Click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="number_button" ID="Button25" runat="server" Height="45px" Text="9" Width="45px" OnClick="button_Click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="operator_button" ID="Button26" runat="server" Height="45px" Text="/" Width="50px" OnClick="operator_click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="operator_button scientific_btn" ID="Button3" runat="server" Height="45px" Text="π" Width="58px" OnClick="button_Click" BackColor="Black" ForeColor="White" />    
        </div>

         <div class="button_area">
            <asp:Button cssClass="number_button" ID="Button4" runat="server" Height="45px" Text="4" Width="45px" OnClick="button_Click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="number_button" ID="Button5" runat="server" Height="45px" Text="5" Width="45px" OnClick="button_Click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="number_button" ID="Button6" runat="server" Height="45px" Text="6" Width="45px" OnClick="button_Click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="operator_button" ID="Button11" runat="server" Height="45px" Text="*" Width="50px" OnClick="operator_click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="functional_button" ID="Button19" runat="server" Height="45px" Text="CE" Width="60px" OnClick="Button19_Click" BackColor="Black" ForeColor="White" />


        </div>

         <div class="button_area">
            <asp:Button cssClass="number_button" ID="Button7" runat="server" Height="45px" Text="1" Width="45px" OnClick="button_Click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="number_button" ID="Button8" runat="server" Height="45px" Text="2" Width="45px" OnClick="button_Click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="number_button" ID="Button9" runat="server" Height="45px" Text="3" Width="45px" OnClick="button_Click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="operator_button" ID="Button12" runat="server" Height="45px" Text="-" Width="50px" OnClick="operator_click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="functional_button" ID="Button18" runat="server" Height="45px" Text="C" Width="60px" OnClick="Button18_Click" BackColor="Black" ForeColor="White" />

        </div>

        <div class="button_area">
            <asp:Button cssClass="number_button" ID="Button13" runat="server" Height="45px" Text="00" Width="45px" OnClick="button_Click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="number_button" ID="Button14" runat="server" Height="45px" Text="0" Width="45px" OnClick="button_Click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="number_button" ID="Button15" runat="server" Height="45px" Text="." Width="45px" OnClick="button_Click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="operator_button" ID="Button17" runat="server" Height="45px" Text="+" Width="50px" OnClick="operator_click" BackColor="Black" ForeColor="White" />
            <asp:Button cssClass="functional_button" ID="Button16" runat="server" Height="45px" Text="=" Width="60px" OnClick="calc" BackColor="Black" ForeColor="White" />

        </div>
    </form>

</body>
</html>
