using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using ZinizCourceProject.ViewModel;

namespace ZinizCourceProject.View.Pages
{
    /// <summary>
    /// Логика взаимодействия для AES.xaml
    /// </summary>
    public partial class Serpnet : Page
    {
        public Serpnet()
        {
            InitializeComponent();
            SerpnetViewModel viewModel = new SerpnetViewModel();
            this.DataContext = viewModel;

        }



       
    }
}
