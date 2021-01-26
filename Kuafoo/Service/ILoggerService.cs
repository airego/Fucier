using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Controls;

namespace Kuafoo.Service
{
    public interface ILoggerService
    {
        void SetScreen(RichTextBox box, bool conf = true);
        void Info(string info);
        void Error(string info);
        void Warn(string info);
    }
}
