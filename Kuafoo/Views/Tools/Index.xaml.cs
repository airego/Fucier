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
        public AppMap AppMap { get; set; }

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
            if (e != null && e.Data != null)
            {
                if (!(e.Data.Equals(string.Empty) || e.Data.Length <= 0))
                {
                    var spls = e.Data.Split(':');
                    if (spls[0][0].Equals('l'))
                        service.Info(spls[1]);
                    else if (spls[0][0].Equals('p'))
                        pbProcess.Update(Convert.ToInt32(spls[1]));
                    else
                        service.Warn(e.Data);
                }
                else
                    service.Info(e.Data);
            }
        }
        private void btnQuery_Click(object sender, RoutedEventArgs e)
        {
            if (ucFile.Path.Equals(string.Empty) || ucFolder.Path.Equals(string.Empty))
            {
                service.Error("路径不可为空！");
                return;
            }
            pbProcess.Update(0);
            var pm = new ProcessMap();
            pm.App = $"cmd.exe";
            pm.Command = $"{AppMap.App.WorkDir}/{AppMap.App.Plugins}/v2m.exe {ucFile.Path} {ucFolder.Path}";
            process.Start(pm);
            service.Info("服务已启动！");
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
                pbProcess.Update(100);
                service.Info("Process has been killed!");
            }
            catch (Exception ex)
            {
                service.Error(ex.Message);
            }
        }
    }
}
