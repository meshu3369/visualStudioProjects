<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="BmiForm.aspx.cs" Inherits="BMIwebapps.BmiForm" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>BMI</title>
    <link href="~/assets/bootstrap-theme.css" rel="stylesheet" />
    <link href="~/assets/bootstrap.css" rel="stylesheet" />
    <link href="~/assets/font-awesome.css" rel="stylesheet" />
    <link  rel="stylesheet"  href="maxcdn.bootstrapcdn.com/font-awesome/4.1.0/css/font-awesome.min.css” rel=”stylesheet" />

    <link href="~/stylesheet.css" rel="stylesheet" />
</head>
<body>

    <div class="container-fluid main_container">
        <div class="container">
              <div class="row">
                    <div class="col-sm-5">
                        <br />
                      
                            <h4 class="text-center">BMI calculator</h4>
                       
                         
                          <form runat="server" id="main_form" class="form form-vertical" >

                                <div class="form-group">
                                
                                  <asp:TextBox cssClass="form-control" placeholder="User name" ID="username" runat="server"></asp:TextBox>
                                </div>

                               <div class="form-group">
                                
                                   <asp:TextBox cssClass="form-control" placeholder="Age" ID="age" runat="server"></asp:TextBox>
                               </div>
                              
                               <div class="form-group">
                                   Height: 
                                   <asp:TextBox placeholder="5" ID="height_ft" runat="server"></asp:TextBox>  &nbsp;feet
                                   <asp:TextBox placeholder="1" ID="height" runat="server"></asp:TextBox>
                               </div> 
                              
                              <div class="form-group">
                                  
                                   <asp:TextBox cssClass="form-control" placeholder="Your Weight" ID="weight" runat="server"></asp:TextBox>
                               </div>

                                   
                              <div class="form-group">
                                  <asp:Button ID="submit_btn" cssClass="btn btn-md btn-primary" runat="server" Text="Submit" OnClick="submit_click" />
                               </div>

                           
                              
                                   <h4 class="" id="resultMsg" runat="server"></h4>
                              
                          </form>
                    </div>
              </div>
        </div>
    </div>
   

    <script src="assets/bootstrap.js"></script>
</body>
</html>
