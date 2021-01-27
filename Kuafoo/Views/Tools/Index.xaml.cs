using Kuafoo.Model;
using Kuafoo.Service;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Threading;
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
        private ILoggerService service = new LoggerService();
        private ProcessMap process = new ProcessMap();

        public Index()
        {
            InitializeComponent();

            
            service.SetScreen(rtbLogScreen);
            service.Info("功能已启动！");

            process.Handller = Response;
        }
        public void Response(object sender, DataReceivedEventArgs e)
        {
            service.Info(e.Data);
        }
        private void btnQuery_Click(object sender, RoutedEventArgs e)
        {
            process.Command = "dir";
            process.Start();
        }

        private void btnCancle_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                process.Kill();
            }
            catch (Exception ex)
            {
                service.Error(ex.Message);
            }
        }
    }
}
