using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ZinizCourceProject.ViewModel;

namespace ZinizCourceProject
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        
        public MainWindow()
        {
            InitializeComponent();
            var viewModel = new MainVeiwModel();
            this.DataContext = viewModel;
        }


        private void CloseClick(object sender, MouseButtonEventArgs e)
        {
            this.Close();

        }

        private void HideBtnClick(object sender, MouseButtonEventArgs e)
        {
            this.WindowState = WindowState.Minimized;

        }
        private void FullBtnClick(object sender, MouseButtonEventArgs e)
        {
            this.WindowState = WindowState.Maximized;

        }

        private void AESBtnClick(object sender, RoutedEventArgs e)
        {
            MainFrame.Source = new Uri("View/Pages/AES.xaml", UriKind.Relative);
            Label Label = (Label)this.FindName("MethodName");
            Label.Content = "Метод AES";
        }

        private void TwofishBtnClick(object sender, RoutedEventArgs e)
        {
            MainFrame.Source = new Uri("View/Pages/TwoFish.xaml", UriKind.Relative);
            Label Label = (Label)this.FindName("MethodName");
            Label.Content = "Метод Twofish";
        }

        private void SerpentBtnClick(object sender, RoutedEventArgs e)
        {
            MainFrame.Source = new Uri("View/Pages/Serpnet.xaml", UriKind.Relative);
            Label Label = (Label)this.FindName("MethodName");
            Label.Content = "Метод Serpent";

        }
    }
}
