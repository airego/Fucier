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
        private IProcessService process = new ProcessService();

        public Index()
        {
            InitializeComponent();

            
            service.SetScreen(rtbLogScreen);
            service.Info("功能已启动！");

            process.SetHandler(Response);
        }
        public void Response(object sender, DataReceivedEventArgs e)
        {
            service.Info(e.Data);
        }
        private void btnQuery_Click(object sender, RoutedEventArgs e)
        {
            var pm = new ProcessMap();
            pm.App = "cmd.exe";
            pm.Command = "tracert lucoder.com";
            process.Start(pm);
        }

        private void btnCancle_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                process.Kill();
                while (!process.Status())
                {
                    service.Info("Wait for process!");
                    Thread.Sleep(300);
                }
                service.Info("Process has been killed!");
            }
            catch (Exception ex)
            {
                service.Error(ex.Message);
            }
        }
    }
}
