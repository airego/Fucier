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
    /// UcImageViewer.xaml 的交互逻辑
    /// </summary>
    public partial class UcImageViewer : UserControl
    {
        public UcImageViewer()
        {
            InitializeComponent();
        }
        public string Source
        {
            get { return img.Source.ToString(); }
            set
            {
                if (value != null && value.Length > 0)
                    img.Source = new BitmapImage(new Uri(value));
            }
        }
        public void ScalToNormal()
        {
            var centerPoint = Mouse.GetPosition(viewerRoot);
            var p = viewerRoot.PointFromScreen(new Point(0, 0));
            sfr.CenterX = p.X;
            sfr.CenterY = p.Y;
            sfr.ScaleX = sfr.ScaleY = 1;
        }
        private void img_MouseWheel(object sender, MouseWheelEventArgs e)
        {
            Point centerPoint = e.GetPosition(viewerRoot);
            sfr.CenterX = centerPoint.X;
            sfr.CenterY = centerPoint.Y;
            if (sfr.ScaleX < 0.3 && sfr.ScaleY < 0.3 && e.Delta < 0)
            {
                return;
            }
            sfr.ScaleX += (double)e.Delta / 3500;
            sfr.ScaleY += (double)e.Delta / 3500;
        }
        private bool isMouseLeftButtonDown = false;
        Point previousMousePoint = new Point(0, 0);
        private void img_MouseDown(object sender, MouseButtonEventArgs e)
        {
            isMouseLeftButtonDown = true;
            previousMousePoint = e.GetPosition(img);
        }

        private void img_MouseUp(object sender, MouseButtonEventArgs e)
        {
            isMouseLeftButtonDown = false;
        }

        private void img_MouseMove(object sender, MouseEventArgs e)
        {
            if (isMouseLeftButtonDown == true)
            {
                Point position = e.GetPosition(img);
                tlt.X += position.X - this.previousMousePoint.X;
                tlt.Y += position.Y - this.previousMousePoint.Y;
            }
        }

        private void img_MouseLeave(object sender, MouseEventArgs e)
        {
            isMouseLeftButtonDown = false;
        }
    }
}
