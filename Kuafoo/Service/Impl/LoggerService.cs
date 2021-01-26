using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Controls;
using System.Windows.Media;

namespace Kuafoo.Service
{
    public class LoggerService : ILoggerService
    {
        private RichTextBox Screen { get; set; } = null;
        private void Print(string info)
        {
            if (Screen != null)
            {
                System.Windows.Application.Current.Dispatcher.Invoke(new Action(() =>
                {
                    Screen.AppendText($"{info}\n");
                }));
            }
        }
        public void SetScreen(RichTextBox box,bool conf = true)
        {
            Screen = box;

            if (conf)
            {
                //139 35 35
                Screen.Background = new SolidColorBrush(Color.FromRgb(46, 52, 54));
                Screen.Foreground = new SolidColorBrush(Color.FromRgb(255, 255, 255));
            }
        }
        public void Info(string info) => Print($"[I]: {info}");
        public void Error(string info) => Print($"[E]: {info}");
        public void Warn(string info) => Print($"[W]: {info}");
    }
}
