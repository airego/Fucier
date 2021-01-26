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
    /// UcIOFolderSelector.xaml 的交互逻辑
    /// </summary>
    public partial class UcIOFolderSelector : UserControl
    {
        public UcIOFolderSelector()
        {
            InitializeComponent();
        }

        private void btnSel_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("暂时不支持，请自己复制");
        }
    }
}
