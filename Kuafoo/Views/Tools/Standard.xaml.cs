using Kuafoo.Model;
using Kuafoo.Service;
using System;
using System.Collections.Generic;
using System.Diagnostics;
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
    /// Standard.xaml 的交互逻辑
    /// </summary>
    public partial class Standard : Window
    {
        private ILoggerService service = new LoggerService();
        private IProcessService process = new ProcessService();
        public AppMap AppMap { get; set; }
        public Standard()
        {
            InitializeComponent();
            service.Info("功能已启动！");

            process.SetHandler(Response);
            ucFile.Extension = "PNG(*.png)|*.png|JPG(*.jpg)|*.jpg|TIF(*.tif)|*.tif|BMP(*.bmp)|*.bmp|*(*.*)|*.*";
        }
        public void Response(object sender, DataReceivedEventArgs e)
        {
            if (e != null && e.Data.Length > 2)
            {
                if (e.Data[0] == 'r')
                {
                    labRes.Dispatcher.Invoke(() =>
                    {
                        labRes.Content = $"{cbxType.Text} 算法评判结果为：{e.Data.Split(':')[1]}";
                    });
                }
            }
        }
        private void btnQuery_Click(object sender, RoutedEventArgs e)
        {
            if (ucFile.Path.Equals(string.Empty))
            {
                service.Error("路径不可为空！");
                return;
            }
            var pm = new ProcessMap();
            pm.App = $"cmd.exe";
            var action = cbxType.Text;

            switch (cbxType.Text.Trim().ToLower())
            {
                case "thenengrad": action = "1"; break;
                case "eav": action = "2"; break;
                case "energy_gradient": action = "3"; break;
                case "banner": action = "4"; break;
                default:
                    break;
            }
            pm.Command = $"{AppMap.App.WorkDir}/{AppMap.App.Plugins}/standard.exe {ucFile.Path} {action}";
            process.Start(pm);
            service.Info("服务已启动！");
        }
    }
}
