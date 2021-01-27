using Kuafoo.Controllers;
using Kuafoo.Model;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.Json;
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

namespace Kuafoo
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private AppMap app { get; set; }
        public MainWindow()
        {
            InitializeComponent();

            app = JsonSerializer.Deserialize<AppMap>(File.ReadAllText("E:/Fucier/Kuafoo/app.json")) ;
        }
        private List<Window> Factory = new List<Window>();

        private void tbMenu_Tools_V2F_Click(object sender, RoutedEventArgs e)
        {
            var controller = new ToolsController();
            controller.AppMap = app;
            var window = controller.Index();
            Factory.Add(window);
            window.Show();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            foreach (var window in Factory)
            {
                window.Close();
            }
        }
    }
}
