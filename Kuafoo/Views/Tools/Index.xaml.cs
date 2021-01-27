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
        }
        private void btnQuery_Click(object sender, RoutedEventArgs e)
        {
            if (ucFile.Path.Equals(string.Empty) || ucFolder.Path.Equals(string.Empty))
            {
                service.Error("路径不可为空！");
                return;
            }

            var pm = new ProcessMap();
            pm.App = "cmd.exe";
            //ffmpeg -i /data/video_1.mp4 -f image2  -vf fps=fps=1/60 -qscale:v 2 /data/mp4-%05d.jpeg
            pm.Command = $"{AppMap.App.WorkDir}/{AppMap.App.Plugins}/ffmpeg.exe -i {ucFile.Path} -f image2 {ucFolder.Path}/%06d.png";
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
