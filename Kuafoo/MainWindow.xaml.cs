using Kuafoo.Controllers;
using Kuafoo.Model;
using System.Collections.Generic;
using System.IO;
using System.Text.Json;
using System.Windows;

namespace Kuafoo
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private AppMap app { get; set; }
        public MainWindow()
        {
            InitializeComponent();

            app = JsonSerializer.Deserialize<AppMap>(File.ReadAllText("E:/Fucier/Kuafoo/app.json"));
        }
        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            foreach (var window in Factory)
            {
                window.Close();
            }
        }
        private List<Window> Factory = new List<Window>();
        private Dictionary<string, string> FileFactory = new Dictionary<string, string>();

        #region 文件
        private void tbMenu_File_Open_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.DefaultExt = ".png";
            dlg.Filter = "PNG|*.png|TIF|*.tif|JPG|*.jpg|BMP|*.bmp|ALL file|*.*";
            bool? result = dlg.ShowDialog();
            if (result == true)
            {
                var file = dlg.FileName;
                var filename = Path.GetFileName(file);
                if (FileFactory.ContainsKey(filename))
                    FileFactory[filename] = file;
                else
                {
                    lsvFiles.Items.Add(filename);
                    FileFactory.Add(filename, file);
                }
                imgViewer.Source = file;
            }
        }
        private void lsvFiles_SelectionChanged(object sender, System.Windows.Controls.SelectionChangedEventArgs e)
        {
            try
            {
                var sel = "";

                if (lsvFiles.SelectedValue == null)
                    return;

                if (FileFactory.ContainsKey(sel))
                {
                    imgViewer.Source = FileFactory[sel];
                }
            }
            catch (System.Exception ex)
            {
                System.Console.WriteLine(ex.Message);
            }
        }
        private void lsvItemOpen_Click(object sender, RoutedEventArgs e)
        {
            var sel = "";

            if (lsvFiles.SelectedValue == null)
                return;
            sel = lsvFiles.SelectedValue.ToString();

            if (FileFactory.ContainsKey(sel))
            {
                imgViewer.Source = FileFactory[sel];
            }
        }

        private void lsvItemClose_Click(object sender, RoutedEventArgs e)
        {
            var sel = "";

            if (lsvFiles.SelectedValue == null)
                return;
            sel = lsvFiles.SelectedValue.ToString();

            if (lsvFiles.Items.Contains(sel))
            {
                lsvFiles.Items.Remove(sel);
            }

            if (FileFactory.ContainsKey(sel))
            {
                FileFactory.Remove(sel);
            }

            imgViewer.Source = null;
        }
        private void tbMenu_File_Scal1_1_Click(object sender, RoutedEventArgs e)
        {
            imgViewer.ScalToNormal();
        }
        #endregion

        #region 工具
        private void tbMenu_Tools_V2F_Click(object sender, RoutedEventArgs e)
        {
            var controller = new ToolsController();
            controller.AppMap = app;
            var window = controller.Index();
            Factory.Add(window);
            window.Show();
        }

        private void tbMenu_Tools_Standard_Click(object sender, RoutedEventArgs e)
        {
            var controller = new ToolsController();
            controller.AppMap = app;
            var window = controller.Standard();
            Factory.Add(window);
            window.Show();
        }

        #endregion

        #region 关于
        private void btnAbout_Click(object sender, RoutedEventArgs e)
        {
            var controller = new AboutController();
            controller.AppMap = app;
            var window = controller.Index();
            Factory.Add(window);
            window.Show();
        }
        #endregion
    }
}
