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
        public string Extension { get; set; } = "MP4 (.mp4)|*.mp4|MKV (.mkv)|*.mkv|ALL file(.*)|*.*";
        public string ExtensionDefault { get; set; } = ".mp4";
        private void btnSel_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.DefaultExt = ExtensionDefault;
            dlg.Filter = Extension;
            bool? result = dlg.ShowDialog();
            if (result == true)
                Path = dlg.FileName;
        }
    }
}
