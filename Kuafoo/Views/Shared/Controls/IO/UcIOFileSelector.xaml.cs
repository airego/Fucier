using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Kuafoo.Views.Shared.Controls.IO
{
    /// <summary>
    /// UcIOFileSelector.xaml 的交互逻辑
    /// </summary>
    public partial class UcIOFileSelector : UserControl
    {
        public UcIOFileSelector()
        {
            InitializeComponent();
        }
        public string Path
        {
            get { return tbxPath.Text; }
            set { tbxPath.Text = value; }
        }
        private void btnSel_Click(object sender, RoutedEventArgs e)
        {
            // Create OpenFileDialog 
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();

            // Set filter for file extension and default file extension 
            dlg.DefaultExt = ".mp4";
            dlg.Filter = "MP4 (.mp4)|*.mp4|MKV (.mkv)|*.mkv|ALL file(.*)|*.*";

            // Display OpenFileDialog by calling ShowDialog method 
            bool? result = dlg.ShowDialog();

            // Get the selected file name and display in a TextBox 
            if (result == true)
            {
                // Open document 
                Path = dlg.FileName;
            }
        }
    }
}
