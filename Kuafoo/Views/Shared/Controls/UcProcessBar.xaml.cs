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

namespace Kuafoo.Views.Shared.Controls
{
    /// <summary>
    /// UcProcessBar.xaml 的交互逻辑
    /// </summary>
    public partial class UcProcessBar : UserControl
    {
        public UcProcessBar()
        {
            InitializeComponent();
        }
        public void Update(int val)
        {
            labProcess.Dispatcher.Invoke(() =>
            {
                labProcess.Content = $"{val} %";
            });
            pbProcess.Dispatcher.Invoke(() =>
            {
                pbProcess.Value = val;
            });
        }
    }
}
