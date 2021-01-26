using Kuafoo.Service;
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
using System.Windows.Shapes;

namespace Kuafoo.Views.Tools
{
    /// <summary>
    /// Index.xaml 的交互逻辑
    /// </summary>
    public partial class Index : Window
    {
        public Index()
        {
            InitializeComponent();

            ILoggerService service = new LoggerService();
            service.SetScreen(rtbLogScreen);
            service.Info("功能已启动！");
            service.Info("功能已启动！");
        }
    }
}
